#include "Login.h"
#include "MenuDr.h"
#include "MenuAdmin.h"
#include "MenuRecepcionista.h"
#include <QTime>
#include <QTimer>

Login::Login() {
    configurarUI();
    configurarUsuarios();
    conectarEventos();
    menuDr = nullptr;
    menuAdmin = nullptr;
    menuRecepcionista = nullptr;
}

void Login::configurarUI() {
    setWindowTitle("Sistema Médico - Login");
    setFixedSize(800, 600);
    setStyleSheet("background-color: #f0f0f0;");

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setAlignment(Qt::AlignCenter);


    QLabel* labelID = new QLabel("ID");
    labelID->setStyleSheet("font-weight: bold; color: black;");
    layout->addWidget(labelID);

    campoID = new QLineEdit();
    campoID->setFixedHeight(30);
    campoID->setStyleSheet("border: 1px solid #999; padding: 5px; background-color: white; color: black;");
    layout->addWidget(campoID);

    QLabel* labelPass = new QLabel("Contraseña");
    labelPass->setStyleSheet("font-weight: bold; color: black;");
    layout->addWidget(labelPass);

    campoPassword = new QLineEdit();
    campoPassword->setEchoMode(QLineEdit::Password);
    campoPassword->setFixedHeight(30);
    campoPassword->setStyleSheet("border: 1px solid #999; padding: 5px; background-color: white; color: black;");
    layout->addWidget(campoPassword);

    botonLogin = new QPushButton("Iniciar Sesion");
    botonLogin->setFixedSize(120, 35);
    botonLogin->setStyleSheet(
        "QPushButton { background-color: #e0e0e0; border: 1px solid #999; border-radius: 3px; padding: 5px; color: black; }"
        "QPushButton:hover { background-color: #d0d0d0; }"
        "QPushButton:pressed { background-color: #c0c0c0; }"
        );

    QHBoxLayout* botonLayout = new QHBoxLayout();
    botonLayout->addStretch();
    botonLayout->addWidget(botonLogin);
    botonLayout->addStretch();
    layout->addLayout(botonLayout);

    areaTexto = new QTextEdit();
    areaTexto->setFixedHeight(100);
    areaTexto->setPlainText("Sistema listo...");
    areaTexto->setStyleSheet("background-color: #f8f8f8; border: 1px solid #ccc; padding: 8px; color: black;");
    areaTexto->setReadOnly(true);
    layout->addWidget(areaTexto);
}

void Login::configurarUsuarios() {
    usuarios["admin"] = {"123456", "administrador"};
    usuarios["doctor"] = {"medico123", "doctor"};
    usuarios["recepcionista"] = {"recepcionista123", "recepcionista"};
    usuarios["test"] = {"test", "doctor"};
}

void Login::conectarEventos() {
    QObject::connect(botonLogin, &QPushButton::clicked, [this]() { hacerLogin(); });
    QObject::connect(campoPassword, &QLineEdit::returnPressed, [this]() { hacerLogin(); });
    QObject::connect(campoID, &QLineEdit::returnPressed, [this]() { hacerLogin(); });
}

void Login::hacerLogin() {
    std::string id = campoID->text().toStdString();
    std::string pass = campoPassword->text().toStdString();

    if (id.empty() || pass.empty()) {
        mostrarMensaje(" ERROR: Complete todos los campos", false);
        return;
    }

    if (usuarios.find(id) != usuarios.end() && usuarios[id].first == pass) {
        std::string tipoUsuario = usuarios[id].second;
        mostrarMensaje("LOGIN EXITOSO: Bienvenido " + QString::fromStdString(id) + "!", true);
        usuarioActual = QString::fromStdString(id);
        tipoUsuarioActual = QString::fromStdString(tipoUsuario);

        // Crear y mostrar dashboard después de 1 segundo
        QTimer::singleShot(1000, [this]() {
            abrirDashboard();
        });
    } else {
        mostrarMensaje(" LOGIN FALLIDO: Credenciales incorrectas", false);
        campoPassword->clear();
    }
}

void Login::mostrarMensaje(QString mensaje, bool exito) {
    QString textoCompleto = mensaje;

    if (exito) {
        areaTexto->setStyleSheet("background-color: #e8f5e8; border: 1px solid #4CAF50; padding: 8px; color: #2E7D32;");
    } else {
        areaTexto->setStyleSheet("background-color: #ffeaea; border: 1px solid #f44336; padding: 8px; color: #c62828;");
    }

    areaTexto->setPlainText(textoCompleto);
}

void Login::abrirDashboard() {
    hide();  // Ocultar ventana de login

    if (tipoUsuarioActual == "doctor") {
        if (!menuDr) {
            menuDr = new MenuDr(this);
        }
        menuDr->setUsuario(usuarioActual);
        menuDr->show();
    }
    else if (tipoUsuarioActual == "administrador") {
        if (!menuAdmin) {
            menuAdmin = new MenuAdmin(this);
        }
        menuAdmin->setUsuario(usuarioActual);
        menuAdmin->show();
    }
    else if (tipoUsuarioActual == "recepcionista") {
        if (!menuRecepcionista) {
            menuRecepcionista = new MenuRecepcionista(this);
        }
        menuRecepcionista->setUsuario(usuarioActual);
        menuRecepcionista->show();
    }
}

void Login::cerrarSesion() {
    // Limpiar todos los menús
    if (menuDr) {
        menuDr->hide();
        menuDr = nullptr;
    }
    if (menuAdmin) {
        menuAdmin->hide();
        menuAdmin = nullptr;
    }
    if (menuRecepcionista) {
        menuRecepcionista->hide();
        menuRecepcionista = nullptr;
    }

    usuarioActual = "";
    tipoUsuarioActual = "";
    campoID->clear();
    campoPassword->clear();
    campoID->setFocus();
    areaTexto->setPlainText("Sistema listo...");
    areaTexto->setStyleSheet("background-color: #f8f8f8; border: 1px solid #ccc; padding: 8px; color: black;");
    show();
}
