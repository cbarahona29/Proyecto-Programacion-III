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
    setFixedSize(800, 650); // Aumentar altura para el nuevo campo
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

    // Fila 5 - Campos de contraseña
    gridCampos->addWidget(new QLabel("Contraseña:"), 4, 0);
    txtPassword = new QLineEdit();
    txtPassword->setEchoMode(QLineEdit::Password);
    txtPassword->setPlaceholderText("Ingrese su contraseña");
    gridCampos->addWidget(txtPassword, 4, 1);

    gridCampos->addWidget(new QLabel("Confirmar Contraseña:"), 4, 2);
    txtConfirmPassword = new QLineEdit();
    txtConfirmPassword->setEchoMode(QLineEdit::Password);
    txtConfirmPassword->setPlaceholderText("Confirme su contraseña");
    gridCampos->addWidget(txtConfirmPassword, 4, 3);

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

bool RegistroMed::validarPassword(const QString& password, const QString& confirmPassword) {
    // Verificar que las contraseñas coinciden
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return false;
    }

    // Verificar longitud mínima
    if (password.length() < 6) {
        QMessageBox::warning(this, "Error", "La contraseña debe tener al menos 6 caracteres.");
        return false;
    }

    // Verificar que no esté vacía
    if (password.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "La contraseña no puede estar vacía.");
        return false;
    }

    return true;
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
        QString password = txtPassword->text();
        QString confirmPassword = txtConfirmPassword->text();

        // Validaciones básicas
        if (numColegiacion == 0) {
            QMessageBox::warning(this, "Error", "El número de colegiación es necesario para crear el archivo.");
            return;
        }

        if (nombre.isEmpty()) {
            QMessageBox::warning(this, "Error", "El nombre es obligatorio.");
            return;
        }

        if (especialidad == "Seleccionar especialidad...") {
            QMessageBox::warning(this, "Error", "Debe seleccionar una especialidad.");
            return;
        }

        // Validar contraseña
        if (!validarPassword(password, confirmPassword)) {
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
            // Aquí puedes agregar la lógica para guardar la contraseña
            // Por ejemplo, crear un archivo de credenciales o usar un sistema de autenticación
            bool credencialesGuardadas = guardarCredenciales(numColegiacion, password);

            if (credencialesGuardadas) {
                QMessageBox::information(this, "Éxito",
                                         QString("Médico y cuenta registrados exitosamente.\n\n") +
                                             "ID: " + QString::number(id) + "\n" +
                                             "Nombre: " + nombre + "\n" +
                                             "Especialidad: " + especialidad + "\n" +
                                             "Número de Colegiación: " + QString::number(numColegiacion) + "\n" +
                                             "Archivo creado en: Medicos/Medico" + QString::number(numColegiacion) + "\n" +
                                             "Cuenta de usuario creada exitosamente.");
            } else {
                QMessageBox::warning(this, "Advertencia",
                                     "Médico registrado exitosamente, pero hubo un problema al crear la cuenta de usuario.");
            }

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

bool RegistroMed::guardarCredenciales(int numColegiacion, const QString& password) {
    try {
        // Crear directorio de credenciales si no existe
        QDir dir;
        if (!dir.exists("Credenciales")) {
            dir.mkpath("Credenciales");
        }

        // Crear archivo de credenciales para el médico
        QString nombreArchivo = QString("Credenciales/Medico%1.txt").arg(numColegiacion);
        QFile archivo(nombreArchivo);

        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&archivo);
            stream << "Usuario: " << numColegiacion << "\n";
            stream << "Password: " << password << "\n"; // En producción, esto debería estar encriptado
            stream << "Tipo: Medico\n";
            stream << "Estado: Activo\n";
            stream << "FechaCreacion: " << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") << "\n";

            archivo.close();
            return true;
        }
        return false;
    } catch (...) {
        return false;
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
    txtPassword->clear();
    txtConfirmPassword->clear();

    // Poner el foco en el primer campo editable (número de colegiación)
    txtColegiacion->setFocus();
}

void RegistroMed::regresar() {
    this->hide();
    emit regresarAlMenu();
}
