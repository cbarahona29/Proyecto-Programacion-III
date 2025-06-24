#include "MenuAdmin.h"
#include "Login.h"
#include "registropaciente.h"
#include "registromed.h"
#include "Ajustes.h"
#include "FilaEspera.h"
#include "guardaCuentas.h"
#include "BuscarPacientes.h"
#include "BuscarMedicos.h"  // Añadir el include para BuscarMedicos
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

MenuAdmin::MenuAdmin(Login* login)
    : loginWindow(login), gestorCuentas(nullptr) {
    configurarUI();
    configurarEventos();

    // Inicializar el gestor de cuentas
    try {
        gestorCuentas = new guardaCuentas();
    } catch (const std::exception& e) {
        // Si falla la inicialización, gestorCuentas permanecerá como nullptr
        qDebug() << "Error al inicializar guardaCuentas:" << e.what();
    }
}

MenuAdmin::~MenuAdmin() {
    // Limpiar ventanas hijas
    if (ventanaRegistroPaciente) {
        delete ventanaRegistroPaciente;
    }
    if (ventanaRegistroMedico) {
        delete ventanaRegistroMedico;
    }
    if (ventanaAjustes) {
        delete ventanaAjustes;
    }
    if (ventanaFilaEspera) {
        delete ventanaFilaEspera;
    }
    if (ventanaBuscarPacientes) {
        delete ventanaBuscarPacientes;
    }
    if (ventanaBuscarMedicos) {  // Añadir limpieza de la ventana de búsqueda de médicos
        delete ventanaBuscarMedicos;
    }

    // Limpiar el gestor de cuentas
    if (gestorCuentas) {
        delete gestorCuentas;
    }
}

void MenuAdmin::setGestorCuentas(guardaCuentas* gestor) {
    gestorCuentas = gestor;
}

void MenuAdmin::configurarUI() {
    setWindowTitle("Sistema Médico - Panel de Administración");
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

    labelBienvenida = new QLabel("Bienvenido Administrador");
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

    btnRegistrarPaciente = crearBoton("Registrar Paciente");
    btnBuscarPacientes = crearBoton("Buscar Pacientes");
    btnRegistrarMedico = crearBoton("Registrar Médico");
    btnBuscarMedicos = crearBoton("Buscar Médicos");
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

QPushButton* MenuAdmin::crearBoton(const QString& texto) {
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

void MenuAdmin::configurarEventos() {
    connect(btnRegistrarPaciente, &QPushButton::clicked, this, &MenuAdmin::registrarPaciente);
    connect(btnBuscarPacientes, &QPushButton::clicked, this, &MenuAdmin::buscarPacientes);
    connect(btnRegistrarMedico, &QPushButton::clicked, this, &MenuAdmin::registrarMedico);
    connect(btnBuscarMedicos, &QPushButton::clicked, this, &MenuAdmin::buscarMedicos);
    connect(btnFilaEspera, &QPushButton::clicked, this, &MenuAdmin::mostrarFilaEspera);
    connect(btnAjustes, &QPushButton::clicked, this, &MenuAdmin::mostrarAjustes);
    connect(btnSalir, &QPushButton::clicked, this, &MenuAdmin::salir);
}

void MenuAdmin::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Administrador " + usuario);
}

void MenuAdmin::registrarPaciente() {
    if (!ventanaRegistroPaciente) {
        ventanaRegistroPaciente = new RegistroPaciente();
    }
    ventanaRegistroPaciente->show();
}

void MenuAdmin::buscarPacientes() {
    // Crear la ventana de búsqueda de pacientes si no existe
    if (!ventanaBuscarPacientes) {
        ventanaBuscarPacientes = new BuscarPacientes(this);
    }
    ventanaBuscarPacientes->show();
    ventanaBuscarPacientes->raise();  // Traer al frente
    ventanaBuscarPacientes->activateWindow();  // Activar la ventana
}

void MenuAdmin::registrarMedico() {
    if (!ventanaRegistroMedico) {
        ventanaRegistroMedico = new RegistroMed();
    }
    ventanaRegistroMedico->show();
}

void MenuAdmin::buscarMedicos() {
    // Crear la ventana de búsqueda de médicos si no existe


}

void MenuAdmin::mostrarFilaEspera() {
    if (!ventanaFilaEspera) {
        ventanaFilaEspera = new FilaEspera(this);
    }
    ventanaFilaEspera->show();
}

void MenuAdmin::mostrarAjustes() {
    // Si no tenemos gestor, intentar crearlo
    if (!gestorCuentas) {
        try {
            gestorCuentas = new guardaCuentas();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error",
                                  QString("No se pudo inicializar el sistema de cuentas:\n%1").arg(e.what()));
            return;
        }
    }

    if (!ventanaAjustes) {
        ventanaAjustes = new Ajustes(this, gestorCuentas);
    }
    ventanaAjustes->show();
}

void MenuAdmin::salir() {
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Cerrar Sesión",
        "¿Desea cerrar sesión y volver al login?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta == QMessageBox::Yes) {
        // Cerrar ventanas hijas
        if (ventanaRegistroPaciente) {
            ventanaRegistroPaciente->close();
            delete ventanaRegistroPaciente;
            ventanaRegistroPaciente = nullptr;
        }
        if (ventanaRegistroMedico) {
            ventanaRegistroMedico->close();
            delete ventanaRegistroMedico;
            ventanaRegistroMedico = nullptr;
        }
        if (ventanaAjustes) {
            ventanaAjustes->close();
            delete ventanaAjustes;
            ventanaAjustes = nullptr;
        }
        if (ventanaFilaEspera) {
            ventanaFilaEspera->close();
            delete ventanaFilaEspera;
            ventanaFilaEspera = nullptr;
        }
        if (ventanaBuscarPacientes) {
            ventanaBuscarPacientes->close();
            delete ventanaBuscarPacientes;
            ventanaBuscarPacientes = nullptr;
        }
        if (ventanaBuscarMedicos) {  // Añadir limpieza de la ventana de búsqueda de médicos
            ventanaBuscarMedicos->close();
            delete ventanaBuscarMedicos;
            ventanaBuscarMedicos = nullptr;
        }

        // Limpiar el gestor de cuentas si fue creado aquí
        if (gestorCuentas) {
            delete gestorCuentas;
            gestorCuentas = nullptr;
        }

        hide();
        loginWindow->cerrarSesion();
    }
}
