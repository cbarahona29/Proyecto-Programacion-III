#include "registromed.h"
#include <QMessageBox>

RegistroMed::RegistroMed(QWidget *parent) : QWidget(parent) {
    configurarUI();
    configurarEventos();
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
    gridCampos->addWidget(new QLabel("Nombre:"), 0, 0);
    txtNombre = new QLineEdit();
    gridCampos->addWidget(txtNombre, 0, 1);

    gridCampos->addWidget(new QLabel("Numero de Telefono:"), 0, 2);
    txtTelefono = new QLineEdit();
    gridCampos->addWidget(txtTelefono, 0, 3);

    // Fila 2
    gridCampos->addWidget(new QLabel("Edad:"), 1, 0);
    txtEdad = new QLineEdit();
    gridCampos->addWidget(txtEdad, 1, 1);

    gridCampos->addWidget(new QLabel("Genero:"), 1, 2);
    txtGenero = new QLineEdit();
    gridCampos->addWidget(txtGenero, 1, 3);

    // Fila 3
    gridCampos->addWidget(new QLabel("Numero de Identidad:"), 2, 0);
    txtIdentidad = new QLineEdit();
    gridCampos->addWidget(txtIdentidad, 2, 1);

    gridCampos->addWidget(new QLabel("Fecha de Nacimiento:"), 2, 2);
    txtFechaNacimiento = new QLineEdit();
    txtFechaNacimiento->setPlaceholderText("DD/MM/YYYY");
    gridCampos->addWidget(txtFechaNacimiento, 2, 3);

    // Fila 4
    gridCampos->addWidget(new QLabel("Especialidad:"), 3, 0);
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
    gridCampos->addWidget(cmbEspecialidad, 3, 1);

    gridCampos->addWidget(new QLabel("Correo:"), 3, 2);
    txtCorreo = new QLineEdit();
    gridCampos->addWidget(txtCorreo, 3, 3);

    layoutPrincipal->addLayout(gridCampos);
    layoutPrincipal->addStretch();

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addStretch();

    btnRegistrar = new QPushButton("Registrar Medicos");
    btnRegresar = new QPushButton("Regresar");

    layoutBotones->addWidget(btnRegistrar);
    layoutBotones->addWidget(btnRegresar);
    layoutBotones->addStretch();

    layoutPrincipal->addLayout(layoutBotones);
}

void RegistroMed::configurarEventos() {
    connect(btnRegistrar, &QPushButton::clicked, [this]() { registrarMedico(); });
    connect(btnRegresar, &QPushButton::clicked, [this]() { regresar(); });
}

void RegistroMed::registrarMedico() {
    // Validar campos
    if (txtNombre->text().isEmpty() || txtTelefono->text().isEmpty() ||
        txtEdad->text().isEmpty() || txtGenero->text().isEmpty() ||
        txtIdentidad->text().isEmpty() || txtFechaNacimiento->text().isEmpty() ||
        txtCorreo->text().isEmpty() || cmbEspecialidad->currentIndex() == 0) {

        QMessageBox::warning(this, "Campos Incompletos",
                             "Por favor complete todos los campos obligatorios.");
        return;
    }

    // Aquí agregarías la lógica para guardar el médico en la base de datos
    QString mensaje = QString("Medico registrado exitosamente:\n\n"
                              "Nombre: %1\n"
                              "Especialidad: %2\n"
                              "Teléfono: %3")
                          .arg(txtNombre->text())
                          .arg(cmbEspecialidad->currentText())
                          .arg(txtTelefono->text());

    QMessageBox::information(this, "Registro Exitoso", mensaje);

    // Limpiar campos
    limpiarCampos();
}

void RegistroMed::regresar() {
    hide();
    // Aquí emitirías una señal o llamarías al método para mostrar la ventana anterior
    // emit regresarAlMenu();
}

void RegistroMed::limpiarCampos() {
    txtNombre->clear();
    txtTelefono->clear();
    txtEdad->clear();
    txtGenero->clear();
    txtIdentidad->clear();
    txtFechaNacimiento->clear();
    txtCorreo->clear();
    cmbEspecialidad->setCurrentIndex(0);
}
