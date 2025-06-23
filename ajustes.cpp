#include "Ajustes.h"
#include "MenuAdmin.h"
#include <QInputDialog>

Ajustes::Ajustes(MenuAdmin* menuAdmin, QWidget *parent)
    : QMainWindow(parent), menuAdminWindow(menuAdmin) {
    configurarUI();
    configurarEventos();
}

void Ajustes::configurarUI() {
    setWindowTitle("Sistema Médico - Ajustes");
    setFixedSize(600, 500); // Aumenté la altura para acomodar los nuevos botones
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
    layoutPrincipal->setSpacing(30);

    // Título
    labelTitulo = new QLabel("Configuración de Ajustes");
    labelTitulo->setAlignment(Qt::AlignCenter);
    labelTitulo->setStyleSheet(
        "color: black; "
        "font-size: 18px; "
        "font-weight: bold; "
        "margin: 20px;"
        );
    layoutPrincipal->addWidget(labelTitulo);

    // Botones principales
    QVBoxLayout* layoutBotones = new QVBoxLayout();
    layoutBotones->setSpacing(15); // Reduje el espaciado para acomodar más botones
    layoutBotones->setAlignment(Qt::AlignCenter);

    btnCrearCuentaDoctor = crearBoton("Crear Cuenta de Doctor");
    btnCrearCuentaRecepcionista = crearBoton("Crear Cuenta de Recepcionista");
    btnEliminarCuentas = crearBoton("Eliminar Cuentas");
    btnCambiarContrasena = crearBoton("Cambiar Contraseña de Administrador");
    btnRegresar = crearBoton("Regresar al Menú");

    layoutBotones->addWidget(btnCrearCuentaDoctor);
    layoutBotones->addWidget(btnCrearCuentaRecepcionista);
    layoutBotones->addWidget(btnEliminarCuentas);
    layoutBotones->addWidget(btnCambiarContrasena);
    layoutBotones->addWidget(btnRegresar);

    layoutPrincipal->addLayout(layoutBotones);
    layoutPrincipal->addStretch();
}

QPushButton* Ajustes::crearBoton(const QString& texto) {
    QPushButton* boton = new QPushButton(texto);
    boton->setFixedSize(300, 45); // Reduje ligeramente la altura para que quepan mejor
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

void Ajustes::configurarEventos() {
    connect(btnCrearCuentaDoctor, &QPushButton::clicked, this, &Ajustes::crearCuentaDoctor);
    connect(btnCrearCuentaRecepcionista, &QPushButton::clicked, this, &Ajustes::crearCuentaRecepcionista);
    connect(btnEliminarCuentas, &QPushButton::clicked, this, &Ajustes::eliminarCuentas);
    connect(btnCambiarContrasena, &QPushButton::clicked, this, &Ajustes::cambiarContrasenaRecepcion);
    connect(btnRegresar, &QPushButton::clicked, this, &Ajustes::regresarAlMenu);
}

QMessageBox* Ajustes::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
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

void Ajustes::crearCuentaDoctor() {
    QMessageBox* msg = crearMensaje("Crear Cuenta Doctor",
                                    "Función para crear cuenta de doctor.\n"
                                    "Esta funcionalidad estará disponible próximamente.",
                                    QMessageBox::Information);
    msg->exec();
    delete msg;
}

void Ajustes::crearCuentaRecepcionista() {
    bool ok;
    QString nombreUsuario = QInputDialog::getText(this,
                                                  "Crear Cuenta Recepcionista",
                                                  "Ingrese el nombre de usuario:",
                                                  QLineEdit::Normal,
                                                  "",
                                                  &ok);

    if (ok && !nombreUsuario.isEmpty()) {
        QString contrasena = QInputDialog::getText(this,
                                                   "Crear Cuenta Recepcionista",
                                                   "Ingrese la contraseña:",
                                                   QLineEdit::Password,
                                                   "",
                                                   &ok);

        if (ok && !contrasena.isEmpty()) {
            QString confirmarContrasena = QInputDialog::getText(this,
                                                                "Confirmar Contraseña",
                                                                "Confirme la contraseña:",
                                                                QLineEdit::Password,
                                                                "",
                                                                &ok);

            if (ok && contrasena == confirmarContrasena) {
                // Aquí implementarías la lógica para crear la cuenta de recepcionista
                QMessageBox* msg = crearMensaje("Éxito",
                                                QString("Cuenta de recepcionista '%1' creada correctamente.").arg(nombreUsuario),
                                                QMessageBox::Information);
                msg->exec();
                delete msg;
            } else if (ok) {
                QMessageBox* msg = crearMensaje("Error",
                                                "Las contraseñas no coinciden.",
                                                QMessageBox::Warning);
                msg->exec();
                delete msg;
            }
        }
    }
}

void Ajustes::eliminarCuentas() {
    QMessageBox* msgConfirm = new QMessageBox(this);
    msgConfirm->setWindowTitle("Eliminar Cuentas");
    msgConfirm->setText("¿Está seguro de que desea eliminar cuentas?");
    msgConfirm->setInformativeText("Esta acción no se puede deshacer.");
    msgConfirm->setIcon(QMessageBox::Warning);
    msgConfirm->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgConfirm->setDefaultButton(QMessageBox::No);
    msgConfirm->setStyleSheet(
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

    int resultado = msgConfirm->exec();
    delete msgConfirm;

    if (resultado == QMessageBox::Yes) {
        // Aquí implementarías la lógica para mostrar una lista de cuentas y permitir eliminarlas
        QMessageBox* msg = crearMensaje("Eliminar Cuentas",
                                        "Función para eliminar cuentas.\n"
                                        "Esta funcionalidad estará disponible próximamente.\n"
                                        "Se mostrará una lista de usuarios para seleccionar cuáles eliminar.",
                                        QMessageBox::Information);
        msg->exec();
        delete msg;
    }
}

void Ajustes::cambiarContrasenaRecepcion() {
    bool ok;
    QString nuevaContrasena = QInputDialog::getText(this,
                                                    "Cambiar Contraseña",
                                                    "Ingrese la nueva contraseña para recepción:",
                                                    QLineEdit::Password,
                                                    "",
                                                    &ok);

    if (ok && !nuevaContrasena.isEmpty()) {
        // Confirmar la nueva contraseña
        QString confirmarContrasena = QInputDialog::getText(this,
                                                            "Confirmar Contraseña",
                                                            "Confirme la nueva contraseña:",
                                                            QLineEdit::Password,
                                                            "",
                                                            &ok);

        if (ok && nuevaContrasena == confirmarContrasena) {
            // Aquí implementarías la lógica para cambiar la contraseña
            QMessageBox* msg = crearMensaje("Éxito",
                                            "Contraseña de recepción cambiada correctamente.",
                                            QMessageBox::Information);
            msg->exec();
            delete msg;
        } else if (ok) {
            QMessageBox* msg = crearMensaje("Error",
                                            "Las contraseñas no coinciden.",
                                            QMessageBox::Warning);
            msg->exec();
            delete msg;
        }
    }
}

void Ajustes::regresarAlMenu() {
    hide();
    if (menuAdminWindow) {
        menuAdminWindow->show();
        menuAdminWindow->raise();
        menuAdminWindow->activateWindow();
    }
}
