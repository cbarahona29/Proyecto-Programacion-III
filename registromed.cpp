#include "registromed.h"

RegistroMed::RegistroMed(QWidget *parent) : QWidget(parent) {
    // Inicializar el gestor de médicos
    gestorMedicos = new guardaMedico();

    configurarUI();
    configurarEventos();

    // Configurar ID automático
    configurarIDAutomatico();
}

void RegistroMed::configurarUI() {
    setWindowTitle("Registro de Medicos");
    setFixedSize(800, 600);
    setStyleSheet(
        "QWidget {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "}"
        "QLineEdit, QComboBox {"
        "   background-color: white;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "   color: black;"
        "   font-size: 12px;"
        "}"
        "QLineEdit:focus, QComboBox:focus {"
        "   border: 2px solid #4CAF50;"
        "}"
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   color: black;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   min-width: 120px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "   border: 2px solid #666;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #c8c8c8;"
        "}"
        );

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(20);

    // Título
    QLabel* titulo = new QLabel("Registro de Medicos");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    layoutPrincipal->addWidget(titulo);

    // Grid de campos
    QGridLayout* gridCampos = new QGridLayout();
    gridCampos->setSpacing(15);

    // Fila 1
    gridCampos->addWidget(new QLabel("ID:"), 0, 0);
    txtId = new QLineEdit();
    gridCampos->addWidget(txtId, 0, 1);

    gridCampos->addWidget(new QLabel("Num de Colegiacion:"), 0, 2);
    txtColegiacion = new QLineEdit();
    gridCampos->addWidget(txtColegiacion, 0, 3);

    // Fila 2
    gridCampos->addWidget(new QLabel("Identidad:"), 1, 0);
    txtIdentidad = new QLineEdit();
    gridCampos->addWidget(txtIdentidad, 1, 1);

    gridCampos->addWidget(new QLabel("Numero de Telefono:"), 1, 2);
    txtNumTelefono = new QLineEdit();
    gridCampos->addWidget(txtNumTelefono, 1, 3);

    // Fila 3
    gridCampos->addWidget(new QLabel("Nombre:"), 2, 0);
    txtNombre = new QLineEdit();
    gridCampos->addWidget(txtNombre, 2, 1);

    gridCampos->addWidget(new QLabel("Especialidad:"), 2, 2);
    cmbEspecialidad = new QComboBox();
    cmbEspecialidad->addItems({
        "Seleccionar especialidad...",
        "Medicina General",
        "Cardiologia",
        "Dermatologia",
        "Ginecología",
        "Ortopedia",
        "Pediatría",
        "Psiquiatría"
    });
    gridCampos->addWidget(cmbEspecialidad, 2, 3);

    // Fila 4
    gridCampos->addWidget(new QLabel("Fecha de Nacimiento:"), 3, 0);
    txtFechaNacimiento = new QLineEdit();
    txtFechaNacimiento->setPlaceholderText("DD/MM/YYYY");
    gridCampos->addWidget(txtFechaNacimiento, 3, 1);

    gridCampos->addWidget(new QLabel("Email:"), 3, 2);
    txtEmail = new QLineEdit();
    txtEmail->setPlaceholderText("medico@ejemplo.com");
    gridCampos->addWidget(txtEmail, 3, 3);

    layoutPrincipal->addLayout(gridCampos);
    layoutPrincipal->addStretch();

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addStretch();

    btnRegistrar = new QPushButton("Registrar Medico");
    btnRegresar = new QPushButton("Regresar");

    layoutBotones->addWidget(btnRegistrar);
    layoutBotones->addWidget(btnRegresar);
    layoutBotones->addStretch();

    layoutPrincipal->addLayout(layoutBotones);
}

void RegistroMed::configurarEventos() {
    connect(btnRegistrar, &QPushButton::clicked, this, &RegistroMed::registrarMedico);
    connect(btnRegresar, &QPushButton::clicked, this, &RegistroMed::regresar);
}

void RegistroMed::configurarIDAutomatico() {
    // Obtener el siguiente ID disponible
    int siguienteID = gestorMedicos->obtenerSiguienteID();

    // Configurar el campo ID
    txtId->setText(QString::number(siguienteID));
    txtId->setReadOnly(true); // Bloquear edición
    txtId->setStyleSheet(txtId->styleSheet() +
                         "QLineEdit:read-only { background-color: #f0f0f0; color: #666; }");
}

void RegistroMed::registrarMedico() {
    try {
        // Obtener datos de los campos - ID ya está configurado automáticamente
        int id = txtId->text().toInt(); // Este ya está configurado automáticamente
        int numColegiacion = txtColegiacion->text().isEmpty() ? 0 : txtColegiacion->text().toInt();
        int identidad = txtIdentidad->text().isEmpty() ? 0 : txtIdentidad->text().toInt();
        int telefono = txtNumTelefono->text().isEmpty() ? 0 : txtNumTelefono->text().toInt();
        QString nombre = txtNombre->text().trimmed();
        QString especialidad = cmbEspecialidad->currentText();
        QString fechaNacimiento = txtFechaNacimiento->text();
        QString email = txtEmail->text().trimmed();

        // Si no hay número de colegiación, no se puede registrar
        if (numColegiacion == 0) {
            QMessageBox::warning(this, "Error", "El número de colegiación es necesario para crear el archivo.");
            return;
        }

        // Verificar si el médico ya existe
        if (gestorMedicos->existeMedico(numColegiacion)) {
            QMessageBox::warning(this, "Error",
                                 "Ya existe un médico registrado con ese número de colegiación.");
            return;
        }

        // Crear objeto Medico
        Medico nuevoMedico(id, numColegiacion, identidad, telefono,
                           nombre.toStdString(), especialidad.toStdString(),
                           fechaNacimiento.toStdString(), email.toStdString(), true);

        // Intentar registrar el médico
        bool resultado = gestorMedicos->registrarMedico(nuevoMedico);

        if (resultado) {
            QMessageBox::information(this, "Éxito",
                                     QString("Médico registrado exitosamente.\n\n") +
                                         "ID: " + QString::number(id) + "\n" +
                                         "Nombre: " + nombre + "\n" +
                                         "Especialidad: " + especialidad + "\n" +
                                         "Número de Colegiación: " + QString::number(numColegiacion) + "\n" +
                                         "Archivo creado en: Medicos/Medico" + QString::number(numColegiacion));

            // Limpiar los campos después del registro exitoso
            limpiarCampos();

            // Configurar el nuevo ID automático para el siguiente registro
            configurarIDAutomatico();
        } else {
            QMessageBox::critical(this, "Error",
                                  "No se pudo registrar el médico. Error al crear archivo.");
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
                              "Error inesperado al registrar el médico: " + QString(e.what()));
    }
}

void RegistroMed::limpiarCampos() {
    // No limpiar el ID ya que se maneja automáticamente
    txtColegiacion->clear();
    txtIdentidad->clear();
    txtNumTelefono->clear();
    txtNombre->clear();
    cmbEspecialidad->setCurrentIndex(0);
    txtFechaNacimiento->clear();
    txtEmail->clear();

    // Poner el foco en el primer campo editable (número de colegiación)
    txtColegiacion->setFocus();
}

void RegistroMed::regresar() {
    this->hide();
    emit regresarAlMenu();
}
