#include "MenuDr.h"
#include "BuscarPacientes.h"
#include "Login.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDialog>

MenuDr::MenuDr(Login* login, QWidget *parent)
    : QMainWindow(parent),
    loginWindow(login),
    ventanaBuscarPacientes(nullptr),
    btnExpedientesClinicos(nullptr),
    btnBuscarPaciente(nullptr),
    btnFilaEspera(nullptr),
    btnAtenderPaciente(nullptr),
    btnSalir(nullptr),
    labelBienvenida(nullptr)
{
    configurarUI();
    configurarEventos();
}

MenuDr::~MenuDr() {
    // Limpiar ventanas hijas
    if (ventanaBuscarPacientes) {
        delete ventanaBuscarPacientes;
    }
}

void MenuDr::configurarUI() {
    setWindowTitle("Sistema Médico - Dashboard Principal");
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
        );

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(widget);
    layoutPrincipal->setSpacing(20);

    labelBienvenida = new QLabel("Bienvenido Dr...");
    labelBienvenida->setAlignment(Qt::AlignCenter);
    labelBienvenida->setStyleSheet(
        "font-size: 16px; "
        "font-weight: bold; "
        "color: black; "
        "background-color: white;"
        );
    layoutPrincipal->addWidget(labelBienvenida);

    // Grid de botones
    QGridLayout* gridBotones = new QGridLayout();
    gridBotones->setSpacing(20);

    btnExpedientesClinicos = crearBoton("Expedientes Clínicos");
    btnBuscarPaciente = crearBoton("Buscar Paciente");
    btnFilaEspera = crearBoton("Fila de Espera");
    btnAtenderPaciente = crearBoton("Atender Paciente");
    btnSalir = crearBoton("Salir");

    gridBotones->addWidget(btnExpedientesClinicos, 0, 0);
    gridBotones->addWidget(btnBuscarPaciente, 0, 1);
    gridBotones->addWidget(btnFilaEspera, 1, 0);
    gridBotones->addWidget(btnAtenderPaciente, 1, 1);

    // Centrar el botón de salir
    QHBoxLayout* salirLayout = new QHBoxLayout();
    salirLayout->addStretch();
    salirLayout->addWidget(btnSalir);
    salirLayout->addStretch();

    layoutPrincipal->addLayout(gridBotones);
    layoutPrincipal->addLayout(salirLayout);
    layoutPrincipal->addStretch();
}

QPushButton* MenuDr::crearBoton(const QString& texto) {
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

void MenuDr::configurarEventos() {
    connect(btnExpedientesClinicos, &QPushButton::clicked, this, &MenuDr::mostrarExpedientes);
    connect(btnBuscarPaciente, &QPushButton::clicked, this, &MenuDr::buscarPaciente);
    connect(btnFilaEspera, &QPushButton::clicked, this, &MenuDr::mostrarFilaEspera);
    connect(btnAtenderPaciente, &QPushButton::clicked, this, &MenuDr::atenderPaciente);
    connect(btnSalir, &QPushButton::clicked, this, &MenuDr::salir);
}

void MenuDr::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Dr. " + usuario);
}

void MenuDr::mostrarExpedientes() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Expedientes Clínicos");
    dialog->setFixedSize(400, 300);
    dialog->setStyleSheet("background-color: white; color: black;");

    QLabel* label = new QLabel("Aquí irían los expedientes clínicos", dialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: black;");

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    dialog->exec();
    delete dialog;
}

void MenuDr::buscarPaciente() {
    // Si la ventana ya existe, simplemente la mostramos
    if (!ventanaBuscarPacientes) {
        ventanaBuscarPacientes = new BuscarPacientes(this);
        // Conectar la señal de destrucción para limpiar el puntero
        connect(ventanaBuscarPacientes, &QObject::destroyed, this, [this]() {
            ventanaBuscarPacientes = nullptr;
        });
    }

    ventanaBuscarPacientes->show();
    ventanaBuscarPacientes->raise();
    ventanaBuscarPacientes->activateWindow();
}

void MenuDr::mostrarFilaEspera() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Fila de Espera");
    dialog->setFixedSize(500, 400);
    dialog->setStyleSheet("background-color: white; color: black;");

    QLabel* label = new QLabel("Aquí se mostraría la fila de espera", dialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: black;");

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    dialog->exec();
    delete dialog;
}

void MenuDr::atenderPaciente() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Atender Paciente");
    dialog->setFixedSize(400, 300);
    dialog->setStyleSheet("background-color: white; color: black;");

    QLabel* label = new QLabel("Aquí se atendería a un paciente", dialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: black;");

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    dialog->exec();
    delete dialog;
}

void MenuDr::salir() {
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Cerrar Sesión",
        "¿Desea cerrar sesión y volver al login?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta == QMessageBox::Yes) {
        // Cerrar ventanas hijas
        if (ventanaBuscarPacientes) {
            ventanaBuscarPacientes->close();
            delete ventanaBuscarPacientes;
            ventanaBuscarPacientes = nullptr;
        }

        hide();
        loginWindow->cerrarSesion();
    }
}
