#include "MenuRecepcionista.h"
#include "Login.h"
#include "registropaciente.h"
#include "FilaEspera.h""
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
    inicializarDatos();
    configurarUI();
    configurarEventos();
    ventanaRegistro = nullptr;  // Inicializar el puntero
}

void MenuRecepcionista::inicializarDatos() {
    // Inicializar pacientes de ejemplo
    pacientes = {
        {"001", "Juan Pérez", "35", "99887766", "Colonia Centro"},
        {"002", "María González", "28", "88776655", "Colonia Kennedy"},
        {"003", "Carlos Rodríguez", "42", "77665544", "Colonia Palmira"},
        {"004", "Ana Martínez", "31", "66554433", "Colonia Miraflores"},
        {"005", "Luis Hernández", "29", "55443322", "Colonia Las Minitas"}
    };

    // Inicializar médicos de ejemplo
    medicos = {
        {"M001", "Dr. Roberto Silva", "Medicina General", "99123456"},
        {"M002", "Dra. Ana Martínez", "Cardiología", "88234567"},
        {"M003", "Dr. Luis Hernández", "Pediatría", "77345678"},
        {"M004", "Dra. Carmen López", "Ginecología", "66456789"},
        {"M005", "Dr. Miguel Torres", "Traumatología", "55567890"}
    };

    // Inicializar citas agendadas de ejemplo
    citasAgendadas = {
        {"Juan Pérez", "Dr. Roberto Silva", "2025-06-21", "09:00", "Consulta General"},
        {"María González", "Dra. Ana Martínez", "2025-06-21", "10:30", "Cardiología"},
        {"Carlos Rodríguez", "Dr. Luis Hernández", "2025-06-21", "11:00", "Pediatría"}
    };
}

void MenuRecepcionista::configurarUI() {
    setWindowTitle("Sistema Médico - Recepción");
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

    labelBienvenida = new QLabel("Bienvenida Recepcionista");
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

void MenuRecepcionista::configurarEventos() {
    connect(btnRegistrarPaciente, &QPushButton::clicked, [this]() { registrarPaciente(); });
    connect(btnBuscarPaciente, &QPushButton::clicked, [this]() { buscarPaciente(); });
    connect(btnAgendarCita, &QPushButton::clicked, [this]() { agendarCita(); });
    connect(btnBuscarMedico, &QPushButton::clicked, [this]() { buscarMedico(); });
    connect(btnFilaEspera, &QPushButton::clicked, [this]() { mostrarFilaEspera(); });
    connect(btnSalir, &QPushButton::clicked, [this]() { salir(); });
}

void MenuRecepcionista::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenida Recepcionista " + usuario);
}

QMessageBox* MenuRecepcionista::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
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

void MenuRecepcionista::registrarPaciente() {
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

void MenuRecepcionista::buscarPaciente() {
    // Crear el QInputDialog personalizado
    QInputDialog* inputDialog = new QInputDialog(this);
    inputDialog->setWindowTitle("Buscar Paciente");
    inputDialog->setLabelText("Ingrese el ID del paciente:");
    inputDialog->setTextValue("");
    inputDialog->setInputMode(QInputDialog::TextInput);

    // Aplicar stylesheet simple - fondo negro, letras blancas
    inputDialog->setStyleSheet("color: white;");

    // Mostrar el diálogo y obtener el resultado
    int result = inputDialog->exec();
    QString idPaciente = inputDialog->textValue();

    if (result == QDialog::Accepted && !idPaciente.isEmpty()) {
        bool encontrado = false;
        for (const auto& paciente : pacientes) {
            if (paciente.id == idPaciente) {
                mostrarInformacionPaciente(paciente);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            QMessageBox* msg = crearMensaje("Paciente No Encontrado",
                                            "No se encontró ningún paciente con el ID: " + idPaciente,
                                            QMessageBox::Warning);
            msg->exec();
            delete msg;
        }
    }

    delete inputDialog;
}
void MenuRecepcionista::mostrarInformacionPaciente(const Paciente& paciente) {
    QDialog* ventanaInfo = new QDialog(this);
    ventanaInfo->setWindowTitle("Información del Paciente");
    ventanaInfo->setFixedSize(450, 350);
    ventanaInfo->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "}"
        "QGroupBox {"
        "   background-color: white;"
        "   border: 1px solid #ccc;"
        "   border-radius: 5px;"
        "   margin: 10px;"
        "   padding: 10px;"
        "}"
        "QGroupBox::title {"
        "   color: #333;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(ventanaInfo);
    layout->setSpacing(15);

    // Título
    QLabel* titulo = new QLabel("Información del Paciente");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px; color: #333;");
    layout->addWidget(titulo);

    // Información del paciente en un GroupBox
    QGroupBox* groupInfo = new QGroupBox("Datos Personales");
    QFormLayout* formLayout = new QFormLayout(groupInfo);
    formLayout->setSpacing(10);

    QLabel* labelId = new QLabel(paciente.id);
    QLabel* labelNombre = new QLabel(paciente.nombre);
    QLabel* labelEdad = new QLabel(paciente.edad + " años");
    QLabel* labelTelefono = new QLabel(paciente.telefono);
    QLabel* labelDireccion = new QLabel(paciente.direccion);

    labelId->setStyleSheet("font-weight: bold; color: #0066cc; font-size: 14px;");
    labelNombre->setStyleSheet("font-weight: bold; color: #333; font-size: 14px;");
    labelEdad->setStyleSheet("color: #666; font-size: 13px;");
    labelTelefono->setStyleSheet("color: #666; font-size: 13px;");
    labelDireccion->setStyleSheet("color: #666; font-size: 13px;");

    formLayout->addRow("ID:", labelId);
    formLayout->addRow("Nombre:", labelNombre);
    formLayout->addRow("Edad:", labelEdad);
    formLayout->addRow("Teléfono:", labelTelefono);
    formLayout->addRow("Dirección:", labelDireccion);

    layout->addWidget(groupInfo);

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnCerrar = new QPushButton("Cerrar");
    QPushButton* btnAgendarCita = new QPushButton("Agendar Cita");

    layoutBotones->addStretch();
    layoutBotones->addWidget(btnAgendarCita);
    layoutBotones->addWidget(btnCerrar);

    layout->addLayout(layoutBotones);

    // Conectar botones
    connect(btnCerrar, &QPushButton::clicked, ventanaInfo, &QDialog::accept);
    connect(btnAgendarCita, &QPushButton::clicked, [=]() {
        ventanaInfo->accept();
        agendarCita();
    });

    // Mostrar la ventana
    ventanaInfo->exec();
    delete ventanaInfo;
}

void MenuRecepcionista::buscarMedico() {
    // Crear el QInputDialog personalizado
    QInputDialog* inputDialog = new QInputDialog(this);
    inputDialog->setWindowTitle("Buscar Médico");
    inputDialog->setLabelText("Ingrese el ID del médico:");
    inputDialog->setTextValue("");
    inputDialog->setInputMode(QInputDialog::TextInput);

    // Aplicar stylesheet simple - fondo negro, letras blancas
    inputDialog->setStyleSheet("color: white;");

    // Mostrar el diálogo y obtener el resultado
    int result = inputDialog->exec();
    QString idMedico = inputDialog->textValue();

    if (result == QDialog::Accepted && !idMedico.isEmpty()) {
        // Buscar el médico por ID
        bool encontrado = false;
        for (const auto& medico : medicos) {
            if (medico.id == idMedico) {
                mostrarInformacionMedico(medico);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            QMessageBox* msg = crearMensaje("Médico No Encontrado",
                                            "No se encontró ningún médico con el ID: " + idMedico,
                                            QMessageBox::Warning);
            msg->exec();
            delete msg;
        }
    }

    delete inputDialog;
}
void MenuRecepcionista::mostrarInformacionMedico(const Medico& medico) {
    QDialog* ventanaInfo = new QDialog(this);
    ventanaInfo->setWindowTitle("Información del Médico");
    ventanaInfo->setFixedSize(450, 320);
    ventanaInfo->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "}"
        "QGroupBox {"
        "   background-color: white;"
        "   border: 1px solid #ccc;"
        "   border-radius: 5px;"
        "   margin: 10px;"
        "   padding: 10px;"
        "}"
        "QGroupBox::title {"
        "   color: #333;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(ventanaInfo);
    layout->setSpacing(15);

    // Título
    QLabel* titulo = new QLabel("Información del Médico");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px; color: #333;");
    layout->addWidget(titulo);

    // Información del médico en un GroupBox
    QGroupBox* groupInfo = new QGroupBox("Datos Profesionales");
    QFormLayout* formLayout = new QFormLayout(groupInfo);
    formLayout->setSpacing(10);

    QLabel* labelId = new QLabel(medico.id);
    QLabel* labelNombre = new QLabel(medico.nombre);
    QLabel* labelEspecialidad = new QLabel(medico.especialidad);
    QLabel* labelTelefono = new QLabel(medico.telefono);

    labelId->setStyleSheet("font-weight: bold; color: #0066cc; font-size: 14px;");
    labelNombre->setStyleSheet("font-weight: bold; color: #333; font-size: 14px;");
    labelEspecialidad->setStyleSheet("font-weight: bold; color: #009900; font-size: 13px;");
    labelTelefono->setStyleSheet("color: #666; font-size: 13px;");

    formLayout->addRow("ID:", labelId);
    formLayout->addRow("Nombre:", labelNombre);
    formLayout->addRow("Especialidad:", labelEspecialidad);
    formLayout->addRow("Teléfono:", labelTelefono);

    layout->addWidget(groupInfo);

    // Botón cerrar
    QPushButton* btnCerrar = new QPushButton("Cerrar");
    btnCerrar->setFixedWidth(100);

    QHBoxLayout* layoutBoton = new QHBoxLayout();
    layoutBoton->addStretch();
    layoutBoton->addWidget(btnCerrar);
    layoutBoton->addStretch();

    layout->addLayout(layoutBoton);

    // Conectar el botón cerrar
    connect(btnCerrar, &QPushButton::clicked, ventanaInfo, &QDialog::accept);

    // Mostrar la ventana
    ventanaInfo->exec();
    delete ventanaInfo;
}

void MenuRecepcionista::agendarCita() {
    QDialog* ventanaCita = new QDialog(this);
    ventanaCita->setWindowTitle("Agendar Nueva Cita");
    ventanaCita->setFixedSize(400, 350);
    ventanaCita->setStyleSheet(
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
        "   border: 1px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "   min-height: 25px;"
        "}"
        "QComboBox:hover {"
        "   border: 2px solid #666;"
        "}"
        "QDateEdit, QTimeEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #ccc;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "   min-height: 25px;"
        "}"
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "   min-height: 30px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(ventanaCita);
    layout->setSpacing(15);

    // Título
    QLabel* titulo = new QLabel("Agendar Nueva Cita Médica");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
    layout->addWidget(titulo);

    // Formulario
    QFormLayout* formLayout = new QFormLayout();
    formLayout->setSpacing(10);

    // ComboBox de pacientes
    QComboBox* comboPacientes = new QComboBox();
    comboPacientes->addItem("Seleccione un paciente...", "");
    for (const auto& paciente : pacientes) {
        QString texto = QString("%1 - %2").arg(paciente.id, paciente.nombre);
        comboPacientes->addItem(texto, paciente.id);
    }
    formLayout->addRow("Paciente:", comboPacientes);

    // ComboBox de médicos
    QComboBox* comboMedicos = new QComboBox();
    comboMedicos->addItem("Seleccione un médico...", "");
    for (const auto& medico : medicos) {
        QString texto = QString("%1 - %2").arg(medico.nombre, medico.especialidad);
        comboMedicos->addItem(texto, medico.id);
    }
    formLayout->addRow("Médico:", comboMedicos);

    // Fecha de la cita
    QDateEdit* fechaCita = new QDateEdit();
    fechaCita->setDate(QDate::currentDate());
    fechaCita->setMinimumDate(QDate::currentDate());
    fechaCita->setCalendarPopup(true);
    formLayout->addRow("Fecha:", fechaCita);

    // Hora de la cita
    QTimeEdit* horaCita = new QTimeEdit();
    horaCita->setTime(QTime(8, 0));
    horaCita->setTimeRange(QTime(8, 0), QTime(17, 0));
    horaCita->setDisplayFormat("hh:mm");
    formLayout->addRow("Hora:", horaCita);

    // Tipo de cita
    QComboBox* comboTipoCita = new QComboBox();
    comboTipoCita->addItems({"Consulta General", "Consulta Especializada", "Control", "Urgencia"});
    formLayout->addRow("Tipo de Cita:", comboTipoCita);

    layout->addLayout(formLayout);

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnAgendar = new QPushButton("Agendar Cita");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    layoutBotones->addStretch();
    layoutBotones->addWidget(btnAgendar);
    layoutBotones->addWidget(btnCancelar);

    layout->addLayout(layoutBotones);

    // Conectar botones
    connect(btnCancelar, &QPushButton::clicked, ventanaCita, &QDialog::reject);
    connect(btnAgendar, &QPushButton::clicked, [=]() {
        if (comboPacientes->currentData().toString().isEmpty() ||
            comboMedicos->currentData().toString().isEmpty()) {
            QMessageBox::warning(ventanaCita, "Datos Incompletos",
                                 "Por favor seleccione un paciente y un médico.");
            return;
        }

        // Crear nueva cita
        CitaAgendada nuevaCita;
        nuevaCita.paciente = comboPacientes->currentText().split(" - ")[1];
        nuevaCita.medico = comboMedicos->currentText().split(" - ")[0];
        nuevaCita.fecha = fechaCita->date().toString("yyyy-MM-dd");
        nuevaCita.hora = horaCita->time().toString("hh:mm");
        nuevaCita.tipo = comboTipoCita->currentText();

        citasAgendadas.push_back(nuevaCita);

        QMessageBox::information(ventanaCita, "Cita Agendada",
                                 "La cita ha sido agendada exitosamente.");
        ventanaCita->accept();
    });

    ventanaCita->exec();
    delete ventanaCita;
}

void MenuRecepcionista::mostrarFilaEspera() {
    // Crear una instancia de la ventana FilaEspera
    FilaEspera* ventanaFilaEspera = new FilaEspera(this);

    // Pasar las citas agendadas a la ventana de fila de espera
    ventanaFilaEspera->setCitasAgendadas(citasAgendadas);

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
        hide();
        loginWindow->cerrarSesion();
    }
}
