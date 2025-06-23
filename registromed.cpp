#include "registromed.h"
#include "guardaMedico.h"
#include "Medico.h"
#include <QMessageBox>

RegistroMed::RegistroMed(QWidget *parent) : QWidget(parent) {
    configurarUI();
    configurarEventos();
    generarProximoID(); // Generar el próximo ID automáticamente
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
    txtId->setReadOnly(true); // Hacer que el ID sea solo lectura
    txtId->setStyleSheet("background-color: #f5f5f5; color: #666;"); // Estilo para indicar que es solo lectura
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

void RegistroMed::generarProximoID() {
    try {
        guardaMedico gestor;
        int proximoID = gestor.obtenerProximoID();
        txtId->setText(QString::number(proximoID));
    } catch (...) {
        txtId->setText("1"); // ID por defecto si hay error
    }
}

void RegistroMed::registrarMedico() {
    // Validar campos obligatorios (excluyendo ID que es automático)
    if (txtColegiacion->text().isEmpty() ||
        txtIdentidad->text().isEmpty() || txtNumTelefono->text().isEmpty() ||
        txtNombre->text().isEmpty() || txtFechaNacimiento->text().isEmpty() ||
        txtEmail->text().isEmpty() || cmbEspecialidad->currentIndex() == 0) {

        QMessageBox::warning(this, "Campos Incompletos",
                             "Por favor complete todos los campos obligatorios.");
        return;
    }

    // Validar que los campos numéricos sean válidos
    bool ok;
    int id = txtId->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Error de Validación", "Error en la generación del ID. Reinicie el formulario.");
        return;
    }

    int colegiacion = txtColegiacion->text().toInt(&ok);
    if (!ok || colegiacion <= 0) {
        QMessageBox::warning(this, "Error de Validación", "El número de colegiación debe ser un número válido mayor a 0.");
        return;
    }

    int identidad = txtIdentidad->text().toInt(&ok);
    if (!ok || identidad <= 0) {
        QMessageBox::warning(this, "Error de Validación", "El número de identidad debe ser un número válido mayor a 0.");
        return;
    }

    int telefono = txtNumTelefono->text().toInt(&ok);
    if (!ok || telefono <= 0) {
        QMessageBox::warning(this, "Error de Validación", "El número de teléfono debe ser un número válido mayor a 0.");
        return;
    }

    try {
        // Crear instancia del gestor de archivos
        guardaMedico gestor;

        // Verificar si el médico ya existe
        if (gestor.existeMedico(colegiacion)) {
            QMessageBox::warning(this, "Médico Existente",
                                 "Ya existe un médico registrado con este número de colegiación.");
            return;
        }

        // Crear objeto Medico
        Medico nuevoMedico(
            id,
            colegiacion,
            identidad,
            telefono,
            txtNombre->text().toStdString(),
            cmbEspecialidad->currentText().toStdString(),
            txtFechaNacimiento->text().toStdString(),
            txtEmail->text().toStdString(),
            true  // Por defecto está disponible
            );

        // Intentar registrar el médico
        if (gestor.registrarMedico(nuevoMedico)) {
            QString mensaje = QString("Médico registrado exitosamente:\n\n"
                                      "ID: %1\n"
                                      "Nombre: %2\n"
                                      "Especialidad: %3\n"
                                      "Colegiación: %4\n"
                                      "Teléfono: %5\n"
                                      "Email: %6")
                                  .arg(txtId->text())
                                  .arg(txtNombre->text())
                                  .arg(cmbEspecialidad->currentText())
                                  .arg(txtColegiacion->text())
                                  .arg(txtNumTelefono->text())
                                  .arg(txtEmail->text());

            QMessageBox::information(this, "Registro Exitoso", mensaje);

            // Limpiar campos después del registro exitoso
            limpiarCampos();
            // Generar nuevo ID para el próximo registro
            generarProximoID();
        } else {
            QMessageBox::critical(this, "Error de Registro",
                                  "No se pudo registrar el médico.\n\n"
                                  "Posibles causas:\n"
                                  "• El médico ya existe con ese número de colegiación\n"
                                  "• No hay permisos de escritura en la carpeta\n"
                                  "• La carpeta de destino no se pudo crear\n\n"
                                  "Verifique la consola para más detalles del error.");
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error Inesperado",
                              QString("Ocurrió un error durante el registro: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error Inesperado",
                              "Ocurrió un error desconocido durante el registro.");
    }
}

void RegistroMed::regresar() {
    this->hide();
    emit regresarAlMenu();
}

void RegistroMed::limpiarCampos() {
    // No limpiar el ID ya que es automático
    txtColegiacion->clear();
    txtIdentidad->clear();
    txtNumTelefono->clear();
    txtNombre->clear();
    cmbEspecialidad->setCurrentIndex(0);
    txtFechaNacimiento->clear();
    txtEmail->clear();
}
