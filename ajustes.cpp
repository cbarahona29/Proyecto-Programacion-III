#include "Ajustes.h"
#include "MenuAdmin.h"
#include <QInputDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>

Ajustes::Ajustes(MenuAdmin* menuAdmin, QWidget *parent)
    : QMainWindow(parent), menuAdminWindow(menuAdmin) {
    configurarUI();
    configurarEventos();
}

void Ajustes::configurarUI() {
    setWindowTitle("Sistema Médico - Ajustes");
    setFixedSize(600, 400);
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
    layoutBotones->setSpacing(20);
    layoutBotones->setAlignment(Qt::AlignCenter);

    btnCrearCuentas = crearBoton("Crear Cuentas");
    btnCambiarContrasena = crearBoton("Cambiar Contraseña");
    btnEliminarCuentas = crearBoton("Eliminar Cuentas");
    btnRegresar = crearBoton("Regresar al Menú");

    layoutBotones->addWidget(btnCrearCuentas);
    layoutBotones->addWidget(btnCambiarContrasena);
    layoutBotones->addWidget(btnEliminarCuentas);
    layoutBotones->addWidget(btnRegresar);

    layoutPrincipal->addLayout(layoutBotones);
    layoutPrincipal->addStretch();
}

QPushButton* Ajustes::crearBoton(const QString& texto) {
    QPushButton* boton = new QPushButton(texto);
    boton->setFixedSize(300, 50);
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
    connect(btnCrearCuentas, &QPushButton::clicked, this, &Ajustes::abrirCrearCuentas);
    connect(btnCambiarContrasena, &QPushButton::clicked, this, &Ajustes::abrirCambiarContrasena);
    connect(btnEliminarCuentas, &QPushButton::clicked, this, &Ajustes::abrirEliminarCuentas);
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

void Ajustes::abrirCrearCuentas() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Crear Cuentas");
    dialog->setFixedSize(400, 350);
    dialog->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "}"
        "QComboBox {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    // Selector de tipo de cuenta
    QLabel* labelTipo = new QLabel("Seleccione el tipo de cuenta:");
    QComboBox* comboTipo = new QComboBox();
    comboTipo->addItem("Doctor");
    comboTipo->addItem("Recepcionista");

    layout->addWidget(labelTipo);
    layout->addWidget(comboTipo);

    // Selector específico de cuenta
    QLabel* labelCuentaEspecifica = new QLabel("Seleccione la cuenta específica:");
    QComboBox* comboCuentaEspecifica = new QComboBox();

    layout->addWidget(labelCuentaEspecifica);
    layout->addWidget(comboCuentaEspecifica);

    // Campo de contraseña
    QLabel* labelContrasena = new QLabel("Contraseña:");
    QLineEdit* lineContrasena = new QLineEdit();
    lineContrasena->setEchoMode(QLineEdit::Password);

    layout->addWidget(labelContrasena);
    layout->addWidget(lineContrasena);

    // Función para actualizar el combo de cuentas específicas
    auto actualizarCuentasEspecificas = [=]() {
        comboCuentaEspecifica->clear();
        if (comboTipo->currentText() == "Doctor") {
            comboCuentaEspecifica->addItem("Dr. García");
            comboCuentaEspecifica->addItem("Dr. López");
            comboCuentaEspecifica->addItem("Dr. Martínez");
            comboCuentaEspecifica->addItem("Dr. Rodríguez");
        } else {
            comboCuentaEspecifica->addItem("Recepcionista 1");
            comboCuentaEspecifica->addItem("Recepcionista 2");
            comboCuentaEspecifica->addItem("Recepcionista 3");
        }
    };

    connect(comboTipo, QOverload<int>::of(&QComboBox::currentIndexChanged), actualizarCuentasEspecificas);
    actualizarCuentasEspecificas(); // Inicializar

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnCrear = new QPushButton("Crear");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    btnCrear->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    btnCancelar->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    layoutBotones->addWidget(btnCrear);
    layoutBotones->addWidget(btnCancelar);
    layout->addLayout(layoutBotones);

    connect(btnCrear, &QPushButton::clicked, [=]() {
        if (!lineContrasena->text().isEmpty()) {
            QMessageBox* msg = crearMensaje("Éxito",
                                            QString("Cuenta creada para %1 correctamente.").arg(comboCuentaEspecifica->currentText()),
                                            QMessageBox::Information);
            msg->exec();
            delete msg;
            dialog->accept();
        } else {
            QMessageBox* msg = crearMensaje("Error", "Ingrese una contraseña.", QMessageBox::Warning);
            msg->exec();
            delete msg;
        }
    });

    connect(btnCancelar, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
    delete dialog;
}

void Ajustes::abrirCambiarContrasena() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Cambiar Contraseña");
    dialog->setFixedSize(400, 300);
    dialog->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "}"
        "QComboBox {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* labelTipo = new QLabel("Seleccione el tipo de cuenta:");
    QComboBox* comboTipo = new QComboBox();
    comboTipo->addItem("Administrador");
    comboTipo->addItem("Doctor");
    comboTipo->addItem("Recepcionista");

    layout->addWidget(labelTipo);
    layout->addWidget(comboTipo);

    // Selector específico de cuenta (solo para Doctor y Recepcionista)
    QLabel* labelCuentaEspecifica = new QLabel("Seleccione la cuenta específica:");
    QComboBox* comboCuentaEspecifica = new QComboBox();

    layout->addWidget(labelCuentaEspecifica);
    layout->addWidget(comboCuentaEspecifica);

    QLabel* labelNuevaContra = new QLabel("Nueva contraseña:");
    QLineEdit* lineNuevaContra = new QLineEdit();
    lineNuevaContra->setEchoMode(QLineEdit::Password);

    QLabel* labelConfirmarContra = new QLabel("Confirmar contraseña:");
    QLineEdit* lineConfirmarContra = new QLineEdit();
    lineConfirmarContra->setEchoMode(QLineEdit::Password);

    layout->addWidget(labelNuevaContra);
    layout->addWidget(lineNuevaContra);
    layout->addWidget(labelConfirmarContra);
    layout->addWidget(lineConfirmarContra);

    // Función para actualizar el combo de cuentas específicas
    auto actualizarCuentasEspecificas = [=]() {
        comboCuentaEspecifica->clear();
        if (comboTipo->currentText() == "Doctor") {
            labelCuentaEspecifica->show();
            comboCuentaEspecifica->show();
            comboCuentaEspecifica->addItem("Dr. García");
            comboCuentaEspecifica->addItem("Dr. López");
            comboCuentaEspecifica->addItem("Dr. Martínez");
            comboCuentaEspecifica->addItem("Dr. Rodríguez");
        } else if (comboTipo->currentText() == "Recepcionista") {
            labelCuentaEspecifica->show();
            comboCuentaEspecifica->show();
            comboCuentaEspecifica->addItem("Recepcionista 1");
            comboCuentaEspecifica->addItem("Recepcionista 2");
            comboCuentaEspecifica->addItem("Recepcionista 3");
        } else {
            // Administrador
            labelCuentaEspecifica->hide();
            comboCuentaEspecifica->hide();
        }
    };

    connect(comboTipo, QOverload<int>::of(&QComboBox::currentIndexChanged), actualizarCuentasEspecificas);
    actualizarCuentasEspecificas(); // Inicializar

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnCambiar = new QPushButton("Cambiar");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    btnCambiar->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    btnCancelar->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    layoutBotones->addWidget(btnCambiar);
    layoutBotones->addWidget(btnCancelar);
    layout->addLayout(layoutBotones);

    connect(btnCambiar, &QPushButton::clicked, [=]() {
        if (lineNuevaContra->text().isEmpty() || lineConfirmarContra->text().isEmpty()) {
            QMessageBox* msg = crearMensaje("Error", "Complete todos los campos.", QMessageBox::Warning);
            msg->exec();
            delete msg;
        } else if (lineNuevaContra->text() != lineConfirmarContra->text()) {
            QMessageBox* msg = crearMensaje("Error", "Las contraseñas no coinciden.", QMessageBox::Warning);
            msg->exec();
            delete msg;
        } else {
            QString cuentaTexto = comboTipo->currentText();
            if (comboTipo->currentText() != "Administrador") {
                cuentaTexto = comboCuentaEspecifica->currentText();
            }
            QMessageBox* msg = crearMensaje("Éxito",
                                            QString("Contraseña de %1 cambiada correctamente.").arg(cuentaTexto),
                                            QMessageBox::Information);
            msg->exec();
            delete msg;
            dialog->accept();
        }
    });

    connect(btnCancelar, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
    delete dialog;
}

void Ajustes::abrirEliminarCuentas() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Eliminar Cuentas");
    dialog->setFixedSize(400, 250);
    dialog->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "}"
        "QComboBox {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* labelTipo = new QLabel("Seleccione el tipo de cuenta a eliminar:");
    QComboBox* comboTipo = new QComboBox();
    comboTipo->addItem("Doctor");
    comboTipo->addItem("Recepcionista");

    layout->addWidget(labelTipo);
    layout->addWidget(comboTipo);

    // Selector específico de cuenta
    QLabel* labelCuentaEspecifica = new QLabel("Seleccione la cuenta específica:");
    QComboBox* comboCuentaEspecifica = new QComboBox();

    layout->addWidget(labelCuentaEspecifica);
    layout->addWidget(comboCuentaEspecifica);

    // Función para actualizar el combo de cuentas específicas
    auto actualizarCuentasEspecificas = [=]() {
        comboCuentaEspecifica->clear();
        if (comboTipo->currentText() == "Doctor") {
            comboCuentaEspecifica->addItem("Dr. García");
            comboCuentaEspecifica->addItem("Dr. López");
            comboCuentaEspecifica->addItem("Dr. Martínez");
            comboCuentaEspecifica->addItem("Dr. Rodríguez");
        } else {
            comboCuentaEspecifica->addItem("Recepcionista 1");
            comboCuentaEspecifica->addItem("Recepcionista 2");
            comboCuentaEspecifica->addItem("Recepcionista 3");
        }
    };

    connect(comboTipo, QOverload<int>::of(&QComboBox::currentIndexChanged), actualizarCuentasEspecificas);
    actualizarCuentasEspecificas(); // Inicializar

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnEliminar = new QPushButton("Eliminar");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    btnEliminar->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    btnCancelar->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    layoutBotones->addWidget(btnEliminar);
    layoutBotones->addWidget(btnCancelar);
    layout->addLayout(layoutBotones);

    connect(btnEliminar, &QPushButton::clicked, [=]() {
        QMessageBox* msgConfirm = new QMessageBox(this);
        msgConfirm->setWindowTitle("Confirmar Eliminación");
        msgConfirm->setText(QString("¿Está seguro de que desea eliminar la cuenta de %1?").arg(comboCuentaEspecifica->currentText()));
        msgConfirm->setInformativeText("Esta acción no se puede deshacer.");
        msgConfirm->setIcon(QMessageBox::Warning);
        msgConfirm->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgConfirm->setDefaultButton(QMessageBox::No);

        int resultado = msgConfirm->exec();
        delete msgConfirm;

        if (resultado == QMessageBox::Yes) {
            QMessageBox* msg = crearMensaje("Éxito",
                                            QString("Cuenta de %1 eliminada correctamente.").arg(comboCuentaEspecifica->currentText()),
                                            QMessageBox::Information);
            msg->exec();
            delete msg;
            dialog->accept();
        }
    });

    connect(btnCancelar, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
    delete dialog;
}

void Ajustes::regresarAlMenu() {
    hide();
    if (menuAdminWindow) {
        menuAdminWindow->show();
        menuAdminWindow->raise();
        menuAdminWindow->activateWindow();
    }
}
