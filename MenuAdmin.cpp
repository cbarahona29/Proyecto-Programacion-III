#include "MenuAdmin.h"
#include "Login.h"
#include <QInputDialog>
#include <QMessageBox>

MenuAdmin::MenuAdmin(Login* login) : loginWindow(login) {
    // Inicializar las ventanas
    ventanaRegistroPaciente = nullptr;
    ventanaRegistroMedico = nullptr;

    configurarUI();
    configurarEventos();
}

void MenuAdmin::configurarUI() {
    setWindowTitle("Sistema Medico - Panel de Administración");
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

    labelBienvenida = new QLabel("Bienvenido Administrador");
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
    btnBuscarPacientes = crearBoton("Buscar Pacientes");
    btnRegistrarMedico = crearBoton("Registrar Medico");
    btnBuscarMedicos = crearBoton("Buscar Medicos");
    btnFilaEspera = crearBoton("Fila de Espera");
    btnAjustes = crearBoton("Ajustes");
    btnSalir = crearBoton("Salir");

    gridBotones->addWidget(btnRegistrarPaciente, 0, 0);
    gridBotones->addWidget(btnBuscarPacientes, 0, 1);
    gridBotones->addWidget(btnRegistrarMedico, 1, 0);
    gridBotones->addWidget(btnBuscarMedicos, 1, 1);
    gridBotones->addWidget(btnFilaEspera, 2, 0);
    gridBotones->addWidget(btnAjustes, 2, 1);

    // Centrar el botón Salir
    QHBoxLayout* layoutSalir = new QHBoxLayout();
    layoutSalir->addStretch();
    layoutSalir->addWidget(btnSalir);
    layoutSalir->addStretch();

    layoutPrincipal->addLayout(gridBotones);
    layoutPrincipal->addLayout(layoutSalir);
    layoutPrincipal->addStretch();
}

QPushButton* MenuAdmin::crearBoton(QString texto) {
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

void MenuAdmin::configurarEventos() {
    connect(btnRegistrarPaciente, &QPushButton::clicked, [this]() { registrarPaciente(); });
    connect(btnBuscarPacientes, &QPushButton::clicked, [this]() { buscarPacientes(); });
    connect(btnRegistrarMedico, &QPushButton::clicked, [this]() { registrarMedico(); });
    connect(btnBuscarMedicos, &QPushButton::clicked, [this]() { buscarMedicos(); });
    connect(btnFilaEspera, &QPushButton::clicked, [this]() { mostrarFilaEspera(); });
    connect(btnAjustes, &QPushButton::clicked, [this]() { mostrarAjustes(); });
    connect(btnSalir, &QPushButton::clicked, [this]() { salir(); });
}

void MenuAdmin::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Administrador");
}

// Función auxiliar para crear QMessageBox con texto negro
QMessageBox* MenuAdmin::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
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

void MenuAdmin::registrarPaciente() {
    // Crear la ventana de registro de paciente si no existe
    if (!ventanaRegistroPaciente) {
        ventanaRegistroPaciente = new RegistroPaciente();
    }

    // Mostrar la ventana
    ventanaRegistroPaciente->show();
    ventanaRegistroPaciente->raise();
    ventanaRegistroPaciente->activateWindow();
}

void MenuAdmin::buscarPacientes() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuAdmin::registrarMedico() {
    // Crear la ventana de registro de médico si no existe
    if (!ventanaRegistroMedico) {
        ventanaRegistroMedico = new RegistroMed();
    }

    // Mostrar la ventana
    ventanaRegistroMedico->show();
    ventanaRegistroMedico->raise();
    ventanaRegistroMedico->activateWindow();
}

void MenuAdmin::buscarMedicos() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuAdmin::mostrarFilaEspera() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuAdmin::mostrarAjustes() {
    QMessageBox* msg = crearMensaje("Trabajo en Proceso", "Funcion en desarrollo", QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuAdmin::salir() {
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
        // Cerrar las ventanas de registro si están abiertas
        if (ventanaRegistroPaciente) {
            ventanaRegistroPaciente->close();
        }
        if (ventanaRegistroMedico) {
            ventanaRegistroMedico->close();
        }

        hide();
        loginWindow->cerrarSesion();
    }
}
