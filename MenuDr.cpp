#include "MenuDr.h"
#include "Login.h"
#include <QInputDialog>
#include <QMessageBox>

MenuDr::MenuDr(Login* login) : loginWindow(login) {
    configurarUI();
    configurarEventos();
}

void MenuDr::configurarUI() {
    setWindowTitle("Sistema Médico - Dashboard Principal");
    setFixedSize(800, 600);
    setStyleSheet(
        "QMainWindow {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QWidget {"
        "   color: black;"
        "}"
        "QMessageBox {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QMessageBox QLabel {"
        "   color: black;"
        "}"
        );

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(widget);
    layoutPrincipal->setSpacing(20);

    labelBienvenida = new QLabel("Bienvenido Dr...");
    labelBienvenida->setAlignment(Qt::AlignCenter);
    labelBienvenida->setStyleSheet(
        "color: black; "
        "font-size: 16px; "
        "font-weight: bold; "
        "margin: 20px;"
        );
    layoutPrincipal->addWidget(labelBienvenida);

    // Grid de botones
    QGridLayout* gridBotones = new QGridLayout();
    gridBotones->setSpacing(20);

    btnAgregarPaciente = crearBoton("Agregar Paciente");
    btnExpedientesClinicos = crearBoton("Expedientes Clínicos");
    btnBuscarPaciente = crearBoton("Buscar Paciente");
    btnFilaEspera = crearBoton("Fila de Espera");
    btnAtenderPaciente = crearBoton("Atender Paciente");
    btnSalir = crearBoton("Salir");

    gridBotones->addWidget(btnAgregarPaciente, 0, 0);
    gridBotones->addWidget(btnExpedientesClinicos, 0, 1);
    gridBotones->addWidget(btnBuscarPaciente, 1, 0);
    gridBotones->addWidget(btnFilaEspera, 1, 1);
    gridBotones->addWidget(btnAtenderPaciente, 2, 0);
    gridBotones->addWidget(btnSalir, 2, 1);

    layoutPrincipal->addLayout(gridBotones);
    layoutPrincipal->addStretch();
}

QPushButton* MenuDr::crearBoton(QString texto) {
    QPushButton* boton = new QPushButton(texto);
    boton->setFixedSize(250, 60);
    boton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8; "
        "   border: 1px solid #999; "
        "   border-radius: 5px; "
        "   padding: 10px; "
        "   color: black; "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8; "
        "   border: 2px solid #666; "
        "   color: black; "
        "}"
        "QPushButton:pressed {"
        "   background-color: #c8c8c8; "
        "   color: black; "
        "}"
        );
    return boton;
}

void MenuDr::configurarEventos() {
    connect(btnAgregarPaciente, &QPushButton::clicked, [this]() { agregarPaciente(); });
    connect(btnExpedientesClinicos, &QPushButton::clicked, [this]() { mostrarExpedientes(); });
    connect(btnBuscarPaciente, &QPushButton::clicked, [this]() { buscarPaciente(); });
    connect(btnFilaEspera, &QPushButton::clicked, [this]() { mostrarFilaEspera(); });
    connect(btnAtenderPaciente, &QPushButton::clicked, [this]() { atenderPaciente(); });
    connect(btnSalir, &QPushButton::clicked, [this]() { salir(); });
}

void MenuDr::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Dr. " + usuario);
}

QMessageBox* MenuDr::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(titulo);
    msgBox->setText(texto);
    msgBox->setIcon(icono);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QMessageBox QLabel {"
        "   color: black;"
        "}"
        "QMessageBox QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px 15px;"
        "   min-width: 60px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );
    return msgBox;
}

void MenuDr::agregarPaciente() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuDr::mostrarExpedientes() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuDr::buscarPaciente() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuDr::mostrarFilaEspera() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuDr::atenderPaciente() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuDr::salir() {
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Cerrar Sesión");
    msgBox->setText("¿Desea cerrar sesión y volver al login?");
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QMessageBox QLabel {"
        "   color: black;"
        "}"
        "QMessageBox QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px 15px;"
        "   min-width: 60px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    QMessageBox::StandardButton respuesta = static_cast<QMessageBox::StandardButton>(msgBox->exec());
    delete msgBox;

    if (respuesta == QMessageBox::Yes) {
        hide();
        loginWindow->cerrarSesion();
    }
}
