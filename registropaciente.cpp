#include "registropaciente.h"
#include "guardaPaciente.h"
#include <QMessageBox>

RegistroPaciente::RegistroPaciente(QWidget *parent) : QWidget(parent) {
    configurarUI();
    configurarEventos();
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
    txtId->setPlaceholderText("Se generará automáticamente");
    txtId->setReadOnly(true);
    txtId->setStyleSheet("background-color: #f5f5f5;");
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
    gridCampos->addWidget(cmbAlergias, 4, 1, 1, 3);

    layoutPrincipal->addLayout(gridCampos);
    layoutPrincipal->addStretch();

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addStretch();

    btnRegistrar = new QPushButton("Registrar Paciente");
    btnRegresar = new QPushButton("Regresar");
    btnLimpiar = new QPushButton("Limpiar Campos");

    layoutBotones->addWidget(btnLimpiar);
    layoutBotones->addWidget(btnRegistrar);
    layoutBotones->addWidget(btnRegresar);
    layoutBotones->addStretch();

    layoutPrincipal->addLayout(layoutBotones);

    // Cargar el próximo ID disponible
    cargarProximoID();
}

void RegistroPaciente::configurarEventos() {
    connect(btnRegistrar, &QPushButton::clicked, this, &RegistroPaciente::registrarPaciente);
    connect(btnRegresar, &QPushButton::clicked, this, &RegistroPaciente::regresar);
    connect(btnLimpiar, &QPushButton::clicked, this, &RegistroPaciente::limpiarCampos);
}

void RegistroPaciente::cargarProximoID() {
    try {
        guardaPaciente gestor;
        int proximoID = gestor.obtenerProximoID();
        txtId->setText(QString::number(proximoID));
    } catch (...) {
        txtId->setText("1"); // ID por defecto si hay error
    }
}

void RegistroPaciente::registrarPaciente() {
    try {
        // Crear el objeto Paciente
        int id = txtId->text().toInt();
        std::string nombre = txtNombre->text().trimmed().toStdString();
        std::string fechaNacimiento = txtFechaNacimiento->text().trimmed().toStdString();
        std::string direccion = txtDireccion->text().trimmed().toStdString();
        int identidad = txtIdentidad->text().toInt();
        int telefono = txtNumTelefono->text().toInt();
        std::string email = txtEmail->text().trimmed().toStdString();
        std::string genero = cmbGenero->currentText().toStdString();
        std::string alergias = cmbAlergias->currentText().toStdString();

        Paciente nuevoPaciente(id, nombre, fechaNacimiento, direccion,
                               identidad, telefono, email, genero, alergias);

        // Usar guardaPaciente para registrar
        guardaPaciente gestor;

        if (gestor.registrarPaciente(nuevoPaciente)) {
            QMessageBox::information(this, "Éxito",
                                     "Paciente registrado correctamente con ID: " + QString::number(id));
            limpiarCampos();
            cargarProximoID(); // Cargar el siguiente ID disponible
        } else {
            QMessageBox::critical(this, "Error",
                                  "No se pudo registrar el paciente. Posiblemente el ID ya existe.");
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
                              "Error al registrar paciente: " + QString(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error",
                              "Error desconocido al registrar paciente.");
    }
}

void RegistroPaciente::limpiarCampos() {
    txtNombre->clear();
    txtIdentidad->clear();
    txtNumTelefono->clear();
    txtFechaNacimiento->clear();
    txtDireccion->clear();
    txtEmail->clear();
    cmbGenero->setCurrentIndex(0);
    cmbAlergias->setCurrentIndex(0);

    // Enfocar el primer campo
    txtNombre->setFocus();
}

void RegistroPaciente::regresar() {
    this->hide();
    emit regresarAlMenu();
}
