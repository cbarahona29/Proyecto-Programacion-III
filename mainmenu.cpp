#include "mainmenu.h"
#include "./ui_mainmenu.h"
#include <QMessageBox>

// Incluye los headers de las ventanas que quieres abrir
#include "menuadmin.h"
#include "menudoctor.h"
#include "menurecepcionista.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    // Conectar el botón con la función de login
    connect(ui->pushButton, &QPushButton::clicked, this, &MainMenu::onLoginClicked);

    // Configurar el campo de contraseña para ocultar el texto
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::onLoginClicked()
{
    // Obtener los valores de los campos
    QString id = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    // Validar credenciales
    if (id == "1" && password == "12345") {
        // Abrir ventana de administrador
        MenuAdmin *adminWindow = new MenuAdmin();
        adminWindow->show();
        this->hide(); // Ocultar la ventana de login
    }
    else if (id == "2" && password == "12345") {
        // Abrir ventana de doctor
        MenuDoctor *doctorWindow = new MenuDoctor();
        doctorWindow->show();
        this->hide();
    }
    else if (id == "3" && password == "12345") {
        // Abrir ventana de recepcionista
        MenuRecepcionista *recepcionistaWindow = new MenuRecepcionista();
        recepcionistaWindow->show();
        this->hide();
    }
    else {
        // Mostrar mensaje de error
        QMessageBox::warning(this, "Error de Autenticación",
                             "ID o contraseña incorrectos.\n\nCredenciales válidas:\n"
                             "• ID: 1 (Admin)\n"
                             "• ID: 2 (Doctor)\n"
                             "• ID: 3 (Recepcionista)\n"
                             "• Contraseña: 12345");

        // Limpiar los campos
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}
