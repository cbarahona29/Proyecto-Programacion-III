#include "Ajustes.h"
#include "MenuAdmin.h"
#include "guardaCuentas.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

Ajustes::Ajustes(MenuAdmin* menuAdmin, guardaCuentas* gestorCuentas, QWidget *parent)
    : QMainWindow(parent), menuAdminWindow(menuAdmin), guardaCuentasInstance(gestorCuentas) {
    configurarUI();
}

void Ajustes::configurarUI() {
    setWindowTitle("Ajustes del Sistema");
    setFixedSize(500, 400);

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
        "QDialog {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   background-color: white;"
        "}"
        "QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QComboBox {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox::down-arrow {"
        "   image: none;"
        "   border: 1px solid #ccc;"
        "   width: 3px;"
        "   height: 3px;"
        "}"
        );

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(widget);
    layoutPrincipal->setSpacing(20);

    // Título
    QLabel* titulo = new QLabel("Configuración de Ajustes");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet(
        "font-size: 18px; "
        "font-weight: bold; "
        "color: black; "
        "background-color: white;"
        );
    layoutPrincipal->addWidget(titulo);

    // Botones principales
    QPushButton* btnCrearCuentas = crearBoton("Crear Cuentas");
    QPushButton* btnCambiarContrasena = crearBoton("Cambiar Contraseña");
    QPushButton* btnEliminarCuentas = crearBoton("Eliminar Cuentas");
    QPushButton* btnListarCuentas = crearBoton("Listar Cuentas");
    QPushButton* btnRegresar = crearBoton("Regresar");

    layoutPrincipal->addWidget(btnCrearCuentas);
    layoutPrincipal->addWidget(btnCambiarContrasena);
    layoutPrincipal->addWidget(btnEliminarCuentas);
    layoutPrincipal->addWidget(btnListarCuentas);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(btnRegresar);

    // Conectar eventos
    connect(btnCrearCuentas, &QPushButton::clicked, this, &Ajustes::abrirCrearCuentas);
    connect(btnCambiarContrasena, &QPushButton::clicked, this, &Ajustes::abrirCambiarContrasena);
    connect(btnEliminarCuentas, &QPushButton::clicked, this, &Ajustes::abrirEliminarCuentas);
    connect(btnListarCuentas, &QPushButton::clicked, this, &Ajustes::abrirListarCuentas);
    connect(btnRegresar, &QPushButton::clicked, this, &Ajustes::regresarAlMenu);
}

QPushButton* Ajustes::crearBoton(const QString& texto) {
    QPushButton* boton = new QPushButton(texto);
    boton->setFixedHeight(50);
    boton->setStyleSheet(
        "QPushButton {"
        "   background-color: white;"
        "   border: 2px solid #ccc;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   color: black;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5;"
        "   border: 2px solid #999;"
        "   color: black;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "}"
        );
    return boton;
}

void Ajustes::abrirCrearCuentas() {
    if (!guardaCuentasInstance) {
        QMessageBox::critical(this, "Error", "Sistema de cuentas no disponible");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Crear Nueva Cuenta");
    dialog.setFixedSize(400, 350);
    dialog.setStyleSheet(
        "QDialog {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   background-color: white;"
        "}"
        "QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QComboBox {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QPushButton {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 8px 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5;"
        "   border: 2px solid #999;"
        "}"
        );

    QVBoxLayout layout(&dialog);

    QLabel labelTipo("Tipo de cuenta:", &dialog);
    QComboBox comboTipo(&dialog);
    comboTipo.addItems({"Doctor", "Recepcionista"});

    QLabel labelUsuario("Nombre de usuario:", &dialog);
    QLineEdit lineUsuario(&dialog);

    QLabel labelContrasena("Contraseña:", &dialog);
    QLineEdit lineContrasena(&dialog);
    lineContrasena.setEchoMode(QLineEdit::Password);

    QLabel labelColegiacion("Número de colegiación (solo doctores):", &dialog);
    QLineEdit lineColegiacion(&dialog);

    QPushButton btnCrear("Crear", &dialog);
    QPushButton btnCancelar("Cancelar", &dialog);

    layout.addWidget(&labelTipo);
    layout.addWidget(&comboTipo);
    layout.addWidget(&labelUsuario);
    layout.addWidget(&lineUsuario);
    layout.addWidget(&labelContrasena);
    layout.addWidget(&lineContrasena);
    layout.addWidget(&labelColegiacion);
    layout.addWidget(&lineColegiacion);

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(&btnCrear);
    layoutBotones->addWidget(&btnCancelar);
    layout.addLayout(layoutBotones);

    // Controlar visibilidad del campo de colegiación
    connect(&comboTipo, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        bool esDoctor = (index == 0);
        labelColegiacion.setVisible(esDoctor);
        lineColegiacion.setVisible(esDoctor);
    });

    connect(&btnCrear, &QPushButton::clicked, [&]() {
        QString usuario = lineUsuario.text().trimmed();
        QString contrasena = lineContrasena.text();
        QString tipo = comboTipo.currentText();

        if (usuario.isEmpty() || contrasena.isEmpty()) {
            QMessageBox::warning(&dialog, "Error", "Por favor complete todos los campos");
            return;
        }

        bool resultado = false;
        QString mensaje;

        try {
            if (tipo == "Doctor") {
                QString colegiacionText = lineColegiacion.text().trimmed();
                if (colegiacionText.isEmpty()) {
                    QMessageBox::warning(&dialog, "Error", "El número de colegiación es requerido para doctores");
                    return;
                }

                bool ok;
                int numColegiacion = colegiacionText.toInt(&ok);
                if (!ok) {
                    QMessageBox::warning(&dialog, "Error", "El número de colegiación debe ser un número válido");
                    return;
                }

                resultado = guardaCuentasInstance->crearCuentaDoctor(
                    usuario.toStdString(),
                    contrasena.toStdString(),
                    numColegiacion
                    );
                mensaje = resultado ?
                              QString("Cuenta de doctor creada exitosamente") :
                              QString("Error al crear cuenta de doctor. Verifique que el médico existe y no tenga cuenta ya creada");
            } else {
                resultado = guardaCuentasInstance->crearCuentaRecepcionista(
                    usuario.toStdString(),
                    contrasena.toStdString()
                    );
                mensaje = resultado ?
                              QString("Cuenta de recepcionista creada exitosamente") :
                              QString("Error al crear cuenta de recepcionista. El usuario podría ya existir");
            }

            if (resultado) {
                QMessageBox::information(&dialog, "Éxito", mensaje);
                dialog.accept();
            } else {
                QMessageBox::warning(&dialog, "Error", mensaje);
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(&dialog, "Error", QString("Error inesperado: %1").arg(e.what()));
        }
    });

    connect(&btnCancelar, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void Ajustes::abrirCambiarContrasena() {
    if (!guardaCuentasInstance) {
        QMessageBox::critical(this, "Error", "Sistema de cuentas no disponible");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Cambiar Contraseña");
    dialog.setFixedSize(400, 300);
    dialog.setStyleSheet(
        "QDialog {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   background-color: white;"
        "}"
        "QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QPushButton {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 8px 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5;"
        "   border: 2px solid #999;"
        "}"
        );

    QVBoxLayout layout(&dialog);

    QLabel labelUsuario("Usuario:", &dialog);
    QLineEdit lineUsuario(&dialog);

    QLabel labelContraActual("Contraseña actual:", &dialog);
    QLineEdit lineContraActual(&dialog);
    lineContraActual.setEchoMode(QLineEdit::Password);

    QLabel labelNuevaContra("Nueva contraseña:", &dialog);
    QLineEdit lineNuevaContra(&dialog);
    lineNuevaContra.setEchoMode(QLineEdit::Password);

    QLabel labelConfirmar("Confirmar contraseña:", &dialog);
    QLineEdit lineConfirmar(&dialog);
    lineConfirmar.setEchoMode(QLineEdit::Password);

    QPushButton btnCambiar("Cambiar", &dialog);
    QPushButton btnCancelar("Cancelar", &dialog);

    layout.addWidget(&labelUsuario);
    layout.addWidget(&lineUsuario);
    layout.addWidget(&labelContraActual);
    layout.addWidget(&lineContraActual);
    layout.addWidget(&labelNuevaContra);
    layout.addWidget(&lineNuevaContra);
    layout.addWidget(&labelConfirmar);
    layout.addWidget(&lineConfirmar);

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(&btnCambiar);
    layoutBotones->addWidget(&btnCancelar);
    layout.addLayout(layoutBotones);

    connect(&btnCambiar, &QPushButton::clicked, [&]() {
        QString usuario = lineUsuario.text().trimmed();
        QString contraActual = lineContraActual.text();
        QString nuevaContra = lineNuevaContra.text();
        QString confirmar = lineConfirmar.text();

        if (usuario.isEmpty() || contraActual.isEmpty() || nuevaContra.isEmpty() || confirmar.isEmpty()) {
            QMessageBox::warning(&dialog, "Error", "Por favor complete todos los campos");
            return;
        }

        if (nuevaContra != confirmar) {
            QMessageBox::warning(&dialog, "Error", "Las contraseñas no coinciden");
            return;
        }

        if (nuevaContra.length() < 4) {
            QMessageBox::warning(&dialog, "Error", "La nueva contraseña debe tener al menos 4 caracteres");
            return;
        }

        try {
            bool resultado = guardaCuentasInstance->cambiarContrasena(
                usuario.toStdString(),
                contraActual.toStdString(),
                nuevaContra.toStdString()
                );

            if (resultado) {
                QMessageBox::information(&dialog, "Éxito", "Contraseña actualizada exitosamente");
                dialog.accept();
            } else {
                QMessageBox::warning(&dialog, "Error", "No se pudo cambiar la contraseña. Verifique el usuario y contraseña actual");
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(&dialog, "Error", QString("Error inesperado: %1").arg(e.what()));
        }
    });

    connect(&btnCancelar, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void Ajustes::abrirEliminarCuentas() {
    if (!guardaCuentasInstance) {
        QMessageBox::critical(this, "Error", "Sistema de cuentas no disponible");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Eliminar Cuenta");
    dialog.setFixedSize(400, 200);
    dialog.setStyleSheet(
        "QDialog {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   background-color: white;"
        "}"
        "QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "}"
        "QPushButton {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 8px 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5;"
        "   border: 2px solid #999;"
        "}"
        );

    QVBoxLayout layout(&dialog);

    QLabel labelUsuario("Usuario a eliminar:", &dialog);
    QLineEdit lineUsuario(&dialog);

    QPushButton btnEliminar("Eliminar", &dialog);
    QPushButton btnCancelar("Cancelar", &dialog);

    layout.addWidget(&labelUsuario);
    layout.addWidget(&lineUsuario);

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(&btnEliminar);
    layoutBotones->addWidget(&btnCancelar);
    layout.addLayout(layoutBotones);

    connect(&btnEliminar, &QPushButton::clicked, [&]() {
        QString usuario = lineUsuario.text().trimmed();

        if (usuario.isEmpty()) {
            QMessageBox::warning(&dialog, "Error", "Por favor ingrese el nombre de usuario");
            return;
        }

        // Confirmar eliminación
        QMessageBox::StandardButton respuesta = QMessageBox::question(
            &dialog,
            "Confirmar Eliminación",
            QString("¿Está seguro de que desea eliminar la cuenta '%1'?\nEsta acción no se puede deshacer.").arg(usuario),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
            );

        if (respuesta != QMessageBox::Yes) {
            return;
        }

        try {
            bool resultado = guardaCuentasInstance->eliminarCuentaPorUsuario(usuario.toStdString());

            if (resultado) {
                QMessageBox::information(&dialog, "Éxito", QString("Cuenta '%1' eliminada exitosamente").arg(usuario));
                dialog.accept();
            } else {
                QMessageBox::warning(&dialog, "Error", QString("No se pudo eliminar la cuenta '%1'. Verifique que el usuario existe").arg(usuario));
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(&dialog, "Error", QString("Error inesperado: %1").arg(e.what()));
        }
    });

    connect(&btnCancelar, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void Ajustes::abrirListarCuentas() {
    if (!guardaCuentasInstance) {
        QMessageBox::critical(this, "Error", "Sistema de cuentas no disponible");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Lista de Cuentas");
    dialog.setFixedSize(600, 400);
    dialog.setStyleSheet(
        "QDialog {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   background-color: white;"
        "}"
        "QPushButton {"
        "   background-color: white;"
        "   color: black;"
        "   border: 2px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 8px 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5;"
        "   border: 2px solid #999;"
        "}"
        );

    QVBoxLayout layout(&dialog);

    QLabel labelTitulo("Cuentas Registradas en el Sistema", &dialog);
    labelTitulo.setAlignment(Qt::AlignCenter);
    labelTitulo.setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");

    QLabel labelInfo(&dialog);
    labelInfo.setWordWrap(true);
    labelInfo.setStyleSheet("font-family: monospace; font-size: 10px; border: 1px solid #ccc; padding: 10px; background-color: #f9f9f9;");

    QPushButton btnCerrar("Cerrar", &dialog);

    layout.addWidget(&labelTitulo);
    layout.addWidget(&labelInfo);
    layout.addWidget(&btnCerrar);

    try {
        std::vector<Cuenta> cuentas = guardaCuentasInstance->obtenerTodasLasCuentas();

        QString info;
        int totalCuentas = cuentas.size();
        int doctores = 0, recepcionistas = 0, activas = 0, inactivas = 0;

        info += QString("=== RESUMEN ===\n");
        info += QString("Total de cuentas: %1\n\n").arg(totalCuentas);

        if (totalCuentas == 0) {
            info += "No hay cuentas registradas en el sistema.\n";
        } else {
            info += "=== DOCTORES ===\n";
            for (const auto& cuenta : cuentas) {
                if (cuenta.tipo == TipoCuenta::DOCTOR) {
                    doctores++;
                    if (cuenta.activa) activas++;
                    else inactivas++;

                    info += QString("Usuario: %1 | Colegiación: %2 | Estado: %3\n")
                                .arg(QString::fromStdString(cuenta.usuario))
                                .arg(cuenta.referenciaID)
                                .arg(cuenta.activa ? "ACTIVA" : "INACTIVA");
                }
            }

            info += "\n=== RECEPCIONISTAS ===\n";
            for (const auto& cuenta : cuentas) {
                if (cuenta.tipo == TipoCuenta::RECEPCIONISTA) {
                    recepcionistas++;
                    if (cuenta.activa) activas++;
                    else inactivas++;

                    info += QString("Usuario: %1 | ID: %2 | Estado: %3\n")
                                .arg(QString::fromStdString(cuenta.usuario))
                                .arg(cuenta.referenciaID)
                                .arg(cuenta.activa ? "ACTIVA" : "INACTIVA");
                }
            }

            info += QString("\n=== ESTADÍSTICAS ===\n");
            info += QString("Doctores: %1\n").arg(doctores);
            info += QString("Recepcionistas: %1\n").arg(recepcionistas);
            info += QString("Cuentas activas: %1\n").arg(activas);
            info += QString("Cuentas inactivas: %1\n").arg(inactivas);
        }

        labelInfo.setText(info);
    } catch (const std::exception& e) {
        labelInfo.setText(QString("Error al obtener la lista de cuentas: %1").arg(e.what()));
    }

    connect(&btnCerrar, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

void Ajustes::regresarAlMenu() {
    hide();
    if (menuAdminWindow) {
        menuAdminWindow->show();
    }
}
