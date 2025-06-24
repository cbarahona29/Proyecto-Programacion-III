#include "MenuRecepcionista.h"
#include "Login.h"
#include "registropaciente.h"
#include "FilaEspera.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QFormLayout>
#include <QTimeEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QListWidget>
#include <QSplitter>
#include <QGroupBox>

MenuRecepcionista::MenuRecepcionista(Login* login) : loginWindow(login) {
    configurarUI();
    configurarEventos();
    ventanaRegistro = nullptr;  // Inicializar el puntero
}

void MenuRecepcionista::configurarUI() {
    setWindowTitle("Sistema Médico - Recepción");
    setFixedSize(800, 600);

    // Establecer fondo blanco para la ventana principal
    setStyleSheet(
        "QMainWindow {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QWidget {"
        "   background-color: white;"
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
        "margin: 20px; "
        "background-color: white;"
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
        "   background-color: white; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "   padding: 10px; "
        "   color: black; "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5; "
        "   border: 2px solid #999; "
        "   color: black; "
        "}"
        "QPushButton:pressed {"
        "   background-color: #e8e8e8; "
        "   color: black; "
        "}"
        );
    return boton;
}

void MenuRecepcionista::configurarEventos() {
    connect(btnRegistrarPaciente, &QPushButton::clicked, [this]() { abrirVentanaRegistro(); });
    connect(btnBuscarPaciente, &QPushButton::clicked, [this]() { abrirVentanaBusquedaPaciente(); });
    connect(btnAgendarCita, &QPushButton::clicked, [this]() { abrirVentanaAgendarCita(); });
    connect(btnBuscarMedico, &QPushButton::clicked, [this]() { abrirVentanaBusquedaMedico(); });
    connect(btnFilaEspera, &QPushButton::clicked, [this]() { abrirVentanaFilaEspera(); });
    connect(btnSalir, &QPushButton::clicked, [this]() { salir(); });
}

void MenuRecepcionista::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenida Recepcionista " + usuario);
}

void MenuRecepcionista::abrirVentanaRegistro() {
    // Crear la ventana de registro si no existe
    if (ventanaRegistro == nullptr) {
        ventanaRegistro = new RegistroPaciente();

        // Conectar la señal para cuando se cierre la ventana
        connect(ventanaRegistro, &QWidget::destroyed, [this]() {
            ventanaRegistro = nullptr;
        });
    }

    // Mostrar la ventana de registro
    ventanaRegistro->show();
    ventanaRegistro->raise();
    ventanaRegistro->activateWindow();
}

void MenuRecepcionista::abrirVentanaBusquedaPaciente() {
    // Emitir señal para que otra clase maneje la lógica
    emit buscarPacienteSolicitado();
}

void MenuRecepcionista::abrirVentanaAgendarCita() {
    // Emitir señal para que otra clase maneje la lógica
    emit agendarCitaSolicitado();
}

void MenuRecepcionista::abrirVentanaBusquedaMedico() {
    // Emitir señal para que otra clase maneje la lógica
    emit buscarMedicoSolicitado();
}

void MenuRecepcionista::abrirVentanaFilaEspera() {
    // Crear una instancia de la ventana FilaEspera
    FilaEspera* ventanaFilaEspera = new FilaEspera(this);

    // Mostrar la ventana de fila de espera
    ventanaFilaEspera->mostrarFilaEspera();

    // Limpiar la memoria después de que se cierre la ventana
    delete ventanaFilaEspera;
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
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px 15px;"
        "   min-width: 60px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "   background-color: #f5f5f5;"
        "   border: 2px solid #999;"
        "}"
        );

    QMessageBox::StandardButton respuesta = static_cast<QMessageBox::StandardButton>(msgBox->exec());
    delete msgBox;

    if (respuesta == QMessageBox::Yes) {
        hide();
        loginWindow->cerrarSesion();
    }
}
