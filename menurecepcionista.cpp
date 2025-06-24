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
#include <QDebug>

// Note: Removed includes for BuscarMedic.h and BuscarPacientes.h
// because we are no longer managing their instances directly in this specific simplified request.
// If you plan to use those classes elsewhere, ensure their headers are included where needed.

MenuRecepcionista::MenuRecepcionista(Login* login) : loginWindow(login) {
    // Removed call to inicializarDatos() as we're not managing internal data structures now
    configurarUI();
    configurarEventos();
    ventanaRegistro = nullptr;
    ventanaBuscarMedico = nullptr;
    ventanaBuscarPaciente = nullptr;
}

MenuRecepcionista::~MenuRecepcionista() {
    // Clean up dynamically created windows if they still exist
    if (ventanaRegistro) {
        delete ventanaRegistro;
        ventanaRegistro = nullptr;
    }
    if (ventanaBuscarMedico) {
        delete ventanaBuscarMedico;
        ventanaBuscarMedico = nullptr;
    }
    if (ventanaBuscarPaciente) {
        delete ventanaBuscarPaciente;
        ventanaBuscarPaciente = nullptr;
    }
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
    btnAgendarCita = crearBoton("Agendar Cita"); // This one will show your widget
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
    connect(btnRegistrarPaciente, &QPushButton::clicked, this, &MenuRecepcionista::abrirVentanaRegistro);
    connect(btnBuscarPaciente, &QPushButton::clicked, this, &MenuRecepcionista::abrirVentanaBusquedaPaciente);
    connect(btnAgendarCita, &QPushButton::clicked, this, &MenuRecepcionista::abrirVentanaAgendarCita); // Connect to the new slot
    connect(btnBuscarMedico, &QPushButton::clicked, this, &MenuRecepcionista::abrirVentanaBusquedaMedico);
    connect(btnFilaEspera, &QPushButton::clicked, this, &MenuRecepcionista::abrirVentanaFilaEspera);
    connect(btnSalir, &QPushButton::clicked, this, &MenuRecepcionista::salir);
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

void MenuRecepcionista::abrirVentanaRegistro() {
    if (ventanaRegistro == nullptr) {
        ventanaRegistro = new RegistroPaciente();
        connect(ventanaRegistro, &QWidget::destroyed, [this]() {
            ventanaRegistro = nullptr;
        });
    }
    ventanaRegistro->show();
    ventanaRegistro->raise();
    ventanaRegistro->activateWindow();
}

void MenuRecepcionista::abrirVentanaBusquedaPaciente() {
    // This will simply show a warning as there's no actual search logic without data structures
    QMessageBox* msg = crearMensaje("Función No Implementada",
                                    "La función de búsqueda de paciente no está implementada con datos de ejemplo en esta versión.",
                                    QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuRecepcionista::abrirVentanaBusquedaMedico() {
    // This will simply show a warning as there's no actual search logic without data structures
    QMessageBox* msg = crearMensaje("Función No Implementada",
                                    "La función de búsqueda de médico no está implementada con datos de ejemplo en esta versión.",
                                    QMessageBox::Information);
    msg->exec();
    delete msg;
}

// Your provided 'agendarCita' QDialog implementation
void MenuRecepcionista::abrirVentanaAgendarCita() {
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

    // ComboBox de pacientes (will be empty as there's no data initialized)
    QComboBox* comboPacientes = new QComboBox();
    comboPacientes->addItem("Seleccione un paciente...", "");
    // No data population here, so this will remain empty beyond the default item
    formLayout->addRow("Paciente:", comboPacientes);

    // ComboBox de médicos (will be empty as there's no data initialized)
    QComboBox* comboMedicos = new QComboBox();
    comboMedicos->addItem("Seleccione un médico...", "");
    // No data population here, so this will remain empty beyond the default item
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
        // Since no data is being managed, this will always show a warning
        // unless you manually add items to the combo boxes for testing.
        QMessageBox::information(ventanaCita, "Cita Agendada (Simulado)",
                                 "La cita ha sido 'agendada' (sin almacenamiento de datos real).");
        ventanaCita->accept();
    });

    ventanaCita->exec(); // Show the dialog modally
    delete ventanaCita; // Clean up the dialog after it closes
}

void MenuRecepcionista::abrirVentanaFilaEspera() {
    // This will simply show a warning as there's no actual data to display
    QMessageBox* msg = crearMensaje("Función No Implementada",
                                    "La función de fila de espera no está implementada con datos de ejemplo en esta versión.",
                                    QMessageBox::Information);
    msg->exec();
    delete msg;
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
