#include "Login.h"
#include "MenuDr.h"
#include "MenuAdmin.h"
#include "MenuRecepcionista.h"
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox> // Added for QMessageBox

Login::Login() {
    configurarUI();
    configurarUsuarios();
    conectarEventos();
    menuDr = nullptr;
    menuAdmin = nullptr;
    menuRecepcionista = nullptr;
}

Login::~Login() {
    // Ensure all dynamically allocated menus are deleted when Login is destroyed
    if (menuDr) {
        delete menuDr;
    }
    if (menuAdmin) {
        delete menuAdmin;
    }
    if (menuRecepcionista) {
        delete menuRecepcionista;
    }
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

    botonLogin = new QPushButton("Iniciar Sesión");
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
    // Usuarios fijos
    usuarios["admin"] = {"123456", "administrador"};
    usuarios["recepcionista"] = {"recepcionista123", "recepcionista"};
    usuarios["doctor"] = {"medico123", "doctor"}; // Corrected password as per our discussion

    // Cargar médicos desde archivos
    cargarCredencialesDesdeArchivos();
}

void Login::cargarCredencialesDesdeArchivos() {
    QDir directorio("Credenciales");
    if (!directorio.exists()) return;

    QStringList archivos = directorio.entryList(QStringList() << "Medico*.txt", QDir::Files);
    for (const QString& archivoNombre : archivos) {
        QFile archivo(directorio.filePath(archivoNombre));
        if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) continue;

        QTextStream stream(&archivo);
        QString usuario, password, tipo;

        while (!stream.atEnd()) {
            QString linea = stream.readLine();
            if (linea.startsWith("Usuario: "))
                usuario = linea.mid(9).trimmed();
            else if (linea.startsWith("Password: "))
                password = linea.mid(10).trimmed();
            else if (linea.startsWith("Tipo: "))
                tipo = linea.mid(6).trimmed().toLower();
        }

        if (!usuario.isEmpty() && !password.isEmpty() && !tipo.isEmpty()) {
            usuarios[usuario] = {password, tipo};
        }

        archivo.close();
    }
}

void Login::conectarEventos() {
    connect(botonLogin, &QPushButton::clicked, this, &Login::hacerLogin);
    connect(campoPassword, &QLineEdit::returnPressed, this, &Login::hacerLogin);
    connect(campoID, &QLineEdit::returnPressed, this, &Login::hacerLogin);
}

void Login::hacerLogin() {
    QString id = campoID->text().trimmed();
    QString pass = campoPassword->text().trimmed();

    if (id.isEmpty() || pass.isEmpty()) {
        mostrarMensaje("ERROR: Complete todos los campos", false);
        return;
    }

    if (usuarios.contains(id) && usuarios[id].first == pass) {
        tipoUsuarioActual = usuarios[id].second;
        usuarioActual = id;
        mostrarMensaje("LOGIN EXITOSO: Bienvenido " + id + "!", true);

        QTimer::singleShot(1000, this, &Login::abrirDashboard);
    } else {
        mostrarMensaje("LOGIN FALLIDO: Credenciales incorrectas", false);
        campoPassword->clear();
    }
}

void Login::mostrarMensaje(QString mensaje, bool exito) {
    areaTexto->setPlainText(mensaje);
    if (exito) {
        areaTexto->setStyleSheet("background-color: #e8f5e8; border: 1px solid #4CAF50; padding: 8px; color: #2E7D32;");
    } else {
        areaTexto->setStyleSheet("background-color: #ffeaea; border: 1px solid #f44336; padding: 8px; color: #c62828;");
    }
}

void Login::abrirDashboard() {
    hide();
    if (tipoUsuarioActual == "doctor") {
        if (!menuDr) menuDr = new MenuDr(this);
        menuDr->setUsuario(usuarioActual);
        menuDr->show();
    } else if (tipoUsuarioActual == "administrador") {
        if (!menuAdmin) menuAdmin = new MenuAdmin(this);
        menuAdmin->setUsuario(usuarioActual);
        menuAdmin->show();
    } else if (tipoUsuarioActual == "recepcionista") {
        if (!menuRecepcionista) menuRecepcionista = new MenuRecepcionista(this);
        menuRecepcionista->setUsuario(usuarioActual);
        menuRecepcionista->show();
    }
}

void Login::cerrarSesion() {
    // If the menus are visible, hide them before deleting
    if (menuDr) {
        menuDr->hide();
        delete menuDr;
        menuDr = nullptr;
    }
    if (menuAdmin) {
        menuAdmin->hide();
        delete menuAdmin;
        menuAdmin = nullptr;
    }
    if (menuRecepcionista) {
        menuRecepcionista->hide();
        delete menuRecepcionista;
        menuRecepcionista = nullptr;
    }

    campoID->clear();
    campoPassword->clear();
    usuarioActual.clear();
    tipoUsuarioActual.clear();
    areaTexto->setPlainText("Sistema listo...");
    areaTexto->setStyleSheet("background-color: #f8f8f8; border: 1px solid #ccc; padding: 8px; color: black;");
    show(); // Show the login window again
}
