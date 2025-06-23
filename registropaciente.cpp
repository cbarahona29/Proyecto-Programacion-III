#include "registropaciente.h"
#include "guardaPaciente.h"
#include "Paciente.h"
#include <QMessageBox>

RegistroPaciente::RegistroPaciente(QWidget *parent) : QWidget(parent) {
    configurarUI();
    configurarEventos();
    generarProximoID(); // Generar el próximo ID automáticamente
}

void RegistroPaciente::configurarUI() {
    setWindowTitle("Registro de Pacientes");
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
    QLabel* titulo = new QLabel("Registro de Pacientes");
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

    gridCampos->addWidget(new QLabel("Direccion:"), 0, 2);
    txtDireccion = new QLineEdit();
    txtDireccion->setPlaceholderText("Ingrese la dirección completa");
    gridCampos->addWidget(txtDireccion, 0, 3);

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

    gridCampos->addWidget(new QLabel("Genero:"), 2, 2);
    cmbGenero = new QComboBox();
    cmbGenero->addItems({
        "Seleccionar género...",
        "Masculino",
        "Femenino",
        "Otro"
    });
    gridCampos->addWidget(cmbGenero, 2, 3);

    // Fila 4
    gridCampos->addWidget(new QLabel("Fecha de Nacimiento:"), 3, 0);
    txtFechaNacimiento = new QLineEdit();
    txtFechaNacimiento->setPlaceholderText("DD/MM/YYYY");
    gridCampos->addWidget(txtFechaNacimiento, 3, 1);

    gridCampos->addWidget(new QLabel("Email:"), 3, 2);
    txtEmail = new QLineEdit();
    txtEmail->setPlaceholderText("paciente@ejemplo.com");
    gridCampos->addWidget(txtEmail, 3, 3);

    // Fila 5
    gridCampos->addWidget(new QLabel("Alergias:"), 4, 0);
    cmbAlergias = new QComboBox();
    cmbAlergias->addItems({
        "Ninguna",
        "Penicilina",
        "Aspirina",
        "Ibuprofeno",
        "Látex",
        "Polen",
        "Alimentos (mariscos)",
        "Alimentos (nueces)",
        "Alimentos (huevos)",
        "Alimentos (leche)",
        "Animales (gatos)",
        "Animales (perros)",
        "Otra (especificar en comentarios)"
    });
    gridCampos->addWidget(cmbAlergias, 4, 1, 1, 3); // Span across 3 columns

    layoutPrincipal->addLayout(gridCampos);
    layoutPrincipal->addStretch();

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addStretch();

    btnRegistrar = new QPushButton("Registrar Paciente");
    btnRegresar = new QPushButton("Regresar");

    layoutBotones->addWidget(btnRegistrar);
    layoutBotones->addWidget(btnRegresar);
    layoutBotones->addStretch();

    layoutPrincipal->addLayout(layoutBotones);
}

void RegistroPaciente::configurarEventos() {
    connect(btnRegistrar, &QPushButton::clicked, this, &RegistroPaciente::registrarPaciente);
    connect(btnRegresar, &QPushButton::clicked, this, &RegistroPaciente::regresar);
}

void RegistroPaciente::generarProximoID() {
    try {
        guardaPaciente gestor;
        int proximoID = gestor.obtenerProximoID();
        txtId->setText(QString::number(proximoID));
    } catch (...) {
        txtId->setText("1"); // ID por defecto si hay error
    }
}

void RegistroPaciente::registrarPaciente() {
    // Validar campos obligatorios (excluyendo ID que es automático)
    if (txtDireccion->text().isEmpty() ||
        txtIdentidad->text().isEmpty() || txtNumTelefono->text().isEmpty() ||
        txtNombre->text().isEmpty() || txtFechaNacimiento->text().isEmpty() ||
        txtEmail->text().isEmpty() || cmbGenero->currentIndex() == 0) {

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
        guardaPaciente gestor;

        // Verificar si el paciente ya existe
        if (gestor.existePaciente(id)) {
            QMessageBox::warning(this, "Paciente Existente",
                                 "Ya existe un paciente registrado con este ID.");
            return;
        }

        // Crear objeto Paciente
        Paciente nuevoPaciente(
            id,
            txtNombre->text().toStdString(),
            txtFechaNacimiento->text().toStdString(),
            txtDireccion->text().toStdString(),
            identidad,
            telefono,
            txtEmail->text().toStdString(),
            cmbGenero->currentText().toStdString(),
            cmbAlergias->currentText().toStdString()
            );

        // Intentar registrar el paciente
        if (gestor.registrarPaciente(nuevoPaciente)) {
            QString mensaje = QString("Paciente registrado exitosamente:\n\n"
                                      "ID: %1\n"
                                      "Nombre: %2\n"
                                      "Género: %3\n"
                                      "Identidad: %4\n"
                                      "Teléfono: %5\n"
                                      "Email: %6\n"
                                      "Alergias: %7\n"
                                      "Dirección: %8")
                                  .arg(txtId->text())
                                  .arg(txtNombre->text())
                                  .arg(cmbGenero->currentText())
                                  .arg(txtIdentidad->text())
                                  .arg(txtNumTelefono->text())
                                  .arg(txtEmail->text())
                                  .arg(cmbAlergias->currentText())
                                  .arg(txtDireccion->text());

            QMessageBox::information(this, "Registro Exitoso", mensaje);

            // Limpiar campos después del registro exitoso
            limpiarCampos();
            // Generar nuevo ID para el próximo registro
            generarProximoID();
        } else {
            QMessageBox::critical(this, "Error de Registro",
                                  "No se pudo registrar el paciente.\n\n"
                                  "Posibles causas:\n"
                                  "• El paciente ya existe con ese ID\n"
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

void RegistroPaciente::regresar() {
    this->hide();
    emit regresarAlMenu();
}
// Agregar este método a la clase guardaPaciente

int guardaPaciente::obtenerProximoID() {
    int maxID = 0;

    try {
        // Verificar si la carpeta principal existe
        if (!checkMainFolder()) {
            crearMainFolder();
            return 1; // Si no existe la carpeta, el primer ID será 1
        }

        string rutaPacientes = "Pacientes";

        // Recorrer todos los directorios en la carpeta Pacientes
        for (const auto& entrada : fs::directory_iterator(rutaPacientes)) {
            if (entrada.is_directory()) {
                string nombreCarpeta = entrada.path().filename().string();

                // Verificar si el nombre de la carpeta es un número (ID)
                try {
                    int id = std::stoi(nombreCarpeta);
                    if (id > maxID) {
                        maxID = id;
                    }
                } catch (const std::invalid_argument&) {
                    // Ignorar carpetas que no sean números
                    continue;
                } catch (const std::out_of_range&) {
                    // Ignorar números fuera de rango
                    continue;
                }
            }
        }

        return maxID + 1;

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error del sistema de archivos: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener próximo ID: " << e.what() << std::endl;
        return 1;
    }
}

void RegistroPaciente::limpiarCampos() {
    // No limpiar el ID ya que es automático
    txtDireccion->clear();
    txtIdentidad->clear();
    txtNumTelefono->clear();
    txtNombre->clear();
    cmbGenero->setCurrentIndex(0);
    cmbAlergias->setCurrentIndex(0);
    txtFechaNacimiento->clear();
    txtEmail->clear();
}
