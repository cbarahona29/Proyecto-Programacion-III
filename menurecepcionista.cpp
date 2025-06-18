#include "MenuRecepcionista.h"
#include "Login.h"
#include <QInputDialog>
#include <QMessageBox>

MenuRecepcionista::MenuRecepcionista(Login* login) : loginWindow(login) {
    configurarUI();
    configurarEventos();
}

void MenuRecepcionista::configurarUI() {
    setWindowTitle("Sistema Médico - Recepción");
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

    labelBienvenida = new QLabel("Bienvenida Recepcionista");
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

    btnRegistrarPaciente = crearBoton("Registrar Paciente");
    btnBuscarPaciente = crearBoton("Buscar Paciente");
    btnAgendarCita = crearBoton("Agendar Cita");
    btnBuscarMedico = crearBoton("Buscar Médico");
    btnFilaEspera = crearBoton("Fila de Espera");
    btnSalir = crearBoton("Salir");

    gridBotones->addWidget(btnRegistrarPaciente, 0, 0);
    gridBotones->addWidget(btnBuscarPaciente, 0, 1);
    gridBotones->addWidget(btnAgendarCita, 1, 0);
    gridBotones->addWidget(btnBuscarMedico, 1, 1);
    gridBotones->addWidget(btnFilaEspera, 2, 0);
    gridBotones->addWidget(btnSalir, 2, 1);

    layoutPrincipal->addLayout(gridBotones);
    layoutPrincipal->addStretch();
}

QPushButton* MenuRecepcionista::crearBoton(QString texto) {
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

void MenuRecepcionista::configurarEventos() {
    connect(btnRegistrarPaciente, &QPushButton::clicked, [this]() { registrarPaciente(); });
    connect(btnBuscarPaciente, &QPushButton::clicked, [this]() { buscarPaciente(); });
    connect(btnAgendarCita, &QPushButton::clicked, [this]() { agendarCita(); });
    connect(btnBuscarMedico, &QPushButton::clicked, [this]() { buscarMedico(); });
    connect(btnFilaEspera, &QPushButton::clicked, [this]() { mostrarFilaEspera(); });
    connect(btnSalir, &QPushButton::clicked, [this]() { salir(); });
}

void MenuRecepcionista::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenida Recepcionista " + usuario);
}

// Función auxiliar para crear QMessageBox con texto negro
QMessageBox* MenuRecepcionista::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
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

void MenuRecepcionista::registrarPaciente() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Función en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuRecepcionista::buscarPaciente() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Función en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuRecepcionista::agendarCita() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Función en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuRecepcionista::buscarMedico() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Función en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuRecepcionista::mostrarFilaEspera() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Función en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuRecepcionista::salir() {
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
