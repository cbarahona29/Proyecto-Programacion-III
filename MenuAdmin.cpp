#include "MenuAdmin.h"
#include "Login.h"
#include "FilaEspera.h"
#include <QInputDialog>
#include <QMessageBox>

MenuAdmin::MenuAdmin(Login* login) : loginWindow(login) {
    ventanaRegistroPaciente = nullptr;
    ventanaRegistroMedico = nullptr;
    ventanaAjustes = nullptr;
    ventanaFilaEspera = nullptr; // Agregar esta línea

    inicializarDatos();
    configurarUI();
    configurarEventos();
}

void MenuAdmin::inicializarDatos() {
    std::map<std::string, std::string> paciente1;
    paciente1["id"] = "001";
    paciente1["nombre"] = "Juan Pérez";
    paciente1["edad"] = "35";
    paciente1["telefono"] = "99887766";
    paciente1["direccion"] = "Colonia Centro, Tegucigalpa";
    paciente1["fecha_registro"] = "15/01/2025";

    std::map<std::string, std::string> paciente2;
    paciente2["id"] = "002";
    paciente2["nombre"] = "María González";
    paciente2["edad"] = "28";
    paciente2["telefono"] = "88776655";
    paciente2["direccion"] = "Colonia Kennedy, Tegucigalpa";
    paciente2["fecha_registro"] = "18/01/2025";

    std::map<std::string, std::string> paciente3;
    paciente3["id"] = "003";
    paciente3["nombre"] = "Carlos Rodríguez";
    paciente3["edad"] = "42";
    paciente3["telefono"] = "77665544";
    paciente3["direccion"] = "Colonia Palmira, Tegucigalpa";
    paciente3["fecha_registro"] = "20/01/2025";

    pacientes.push_back(paciente1);
    pacientes.push_back(paciente2);
    pacientes.push_back(paciente3);

    // Inicializar algunos médicos de ejemplo
    std::map<std::string, std::string> medico1;
    medico1["id"] = "M001";
    medico1["nombre"] = "Dr. Roberto Silva";
    medico1["especialidad"] = "Medicina General";
    medico1["telefono"] = "99123456";
    medico1["email"] = "r.silva@hospital.hn";
    medico1["fecha_registro"] = "10/01/2025";

    std::map<std::string, std::string> medico2;
    medico2["id"] = "M002";
    medico2["nombre"] = "Dra. Ana Martínez";
    medico2["especialidad"] = "Cardiología";
    medico2["telefono"] = "88234567";
    medico2["email"] = "a.martinez@hospital.hn";
    medico2["fecha_registro"] = "12/01/2025";

    std::map<std::string, std::string> medico3;
    medico3["id"] = "M003";
    medico3["nombre"] = "Dr. Luis Hernández";
    medico3["especialidad"] = "Pediatría";
    medico3["telefono"] = "77345678";
    medico3["email"] = "l.hernandez@hospital.hn";
    medico3["fecha_registro"] = "14/01/2025";

    medicos.push_back(medico1);
    medicos.push_back(medico2);
    medicos.push_back(medico3);

    // Inicializar fila de espera con algunos pacientes
    std::map<std::string, std::string> esperando1;
    esperando1["posicion"] = "1";
    esperando1["nombre"] = "Juan Pérez";
    esperando1["id"] = "001";
    esperando1["hora_llegada"] = "08:30";
    esperando1["tipo_cita"] = "Consulta General";

    std::map<std::string, std::string> esperando2;
    esperando2["posicion"] = "2";
    esperando2["nombre"] = "María González";
    esperando2["id"] = "002";
    esperando2["hora_llegada"] = "09:15";
    esperando2["tipo_cita"] = "Cardiología";

    std::map<std::string, std::string> esperando3;
    esperando3["posicion"] = "3";
    esperando3["nombre"] = "Pedro Martínez";
    esperando3["id"] = "004";
    esperando3["hora_llegada"] = "09:45";
    esperando3["tipo_cita"] = "Pediatría";

    filaEspera.push_back(esperando1);
    filaEspera.push_back(esperando2);
    filaEspera.push_back(esperando3);
}

void MenuAdmin::configurarUI() {
    setWindowTitle("Sistema Medico - Panel de Administración");
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

    labelBienvenida = new QLabel("Bienvenido Administrador");
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
    btnBuscarPacientes = crearBoton("Buscar Pacientes");
    btnRegistrarMedico = crearBoton("Registrar Medico");
    btnBuscarMedicos = crearBoton("Buscar Medicos");
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

QPushButton* MenuAdmin::crearBoton(QString texto) {
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

void MenuAdmin::configurarEventos() {
    connect(btnRegistrarPaciente, &QPushButton::clicked, [this]() { registrarPaciente(); });
    connect(btnBuscarPacientes, &QPushButton::clicked, [this]() { buscarPacientes(); });
    connect(btnRegistrarMedico, &QPushButton::clicked, [this]() { registrarMedico(); });
    connect(btnBuscarMedicos, &QPushButton::clicked, [this]() { buscarMedicos(); });
    connect(btnFilaEspera, &QPushButton::clicked, [this]() { mostrarFilaEspera(); });
    connect(btnAjustes, &QPushButton::clicked, [this]() { mostrarAjustes(); });
    connect(btnSalir, &QPushButton::clicked, [this]() { salir(); });
}

void MenuAdmin::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Administrador");
}

// Función auxiliar para crear QMessageBox con texto negro
QMessageBox* MenuAdmin::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
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

void MenuAdmin::mostrarInformacionPaciente(const std::map<std::string, std::string>& paciente) {
    QString info = QString("ID: %1\nNombre: %2\nEdad: %3 años\nTeléfono: %4\nDirección: %5\nFecha de Registro: %6")
                       .arg(QString::fromStdString(paciente.at("id")))
                       .arg(QString::fromStdString(paciente.at("nombre")))
                       .arg(QString::fromStdString(paciente.at("edad")))
                       .arg(QString::fromStdString(paciente.at("telefono")))
                       .arg(QString::fromStdString(paciente.at("direccion")))
                       .arg(QString::fromStdString(paciente.at("fecha_registro")));

    QMessageBox* msg = crearMensaje("Información del Paciente", info, QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuAdmin::mostrarInformacionMedico(const std::map<std::string, std::string>& medico) {
    QString info = QString("ID: %1\nNombre: %2\nEspecialidad: %3\nTeléfono: %4\nEmail: %5\nFecha de Registro: %6")
                       .arg(QString::fromStdString(medico.at("id")))
                       .arg(QString::fromStdString(medico.at("nombre")))
                       .arg(QString::fromStdString(medico.at("especialidad")))
                       .arg(QString::fromStdString(medico.at("telefono")))
                       .arg(QString::fromStdString(medico.at("email")))
                       .arg(QString::fromStdString(medico.at("fecha_registro")));

    QMessageBox* msg = crearMensaje("Información del Médico", info, QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuAdmin::registrarPaciente() {
    if (!ventanaRegistroPaciente) {
        ventanaRegistroPaciente = new RegistroPaciente();
    }

    ventanaRegistroPaciente->show();
    ventanaRegistroPaciente->raise();
    ventanaRegistroPaciente->activateWindow();
}

void MenuAdmin::buscarPacientes() {
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
            if (QString::fromStdString(paciente.at("id")) == idPaciente) {
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

void MenuAdmin::buscarMedicos() {
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
            if (QString::fromStdString(medico.at("id")) == idMedico) {
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
void MenuAdmin::registrarMedico() {
    if (!ventanaRegistroMedico) {
        ventanaRegistroMedico = new RegistroMed();
    }

    // Mostrar la ventana
    ventanaRegistroMedico->show();
    ventanaRegistroMedico->raise();
    ventanaRegistroMedico->activateWindow();
}


void MenuAdmin::mostrarFilaEspera() {
    if (!ventanaFilaEspera) {
        ventanaFilaEspera = new FilaEspera(this);
    }

    // Convertir los datos de filaEspera a CitaAgendada
    std::vector<CitaAgendada> citasParaHoy;

    for (const auto& pacienteEspera : filaEspera) {
        CitaAgendada cita;
        cita.paciente = QString::fromStdString(pacienteEspera.at("nombre"));
        cita.medico = ""; // No tenemos médico en los datos actuales
        cita.fecha = QDate::currentDate().toString("yyyy-MM-dd"); // Asumimos que es para hoy
        cita.hora = QString::fromStdString(pacienteEspera.at("hora_llegada"));
        cita.tipo = QString::fromStdString(pacienteEspera.at("tipo_cita"));

        citasParaHoy.push_back(cita);
    }

    // Establecer las citas en la ventana
    ventanaFilaEspera->setCitasAgendadas(citasParaHoy);

    // Mostrar la ventana
    ventanaFilaEspera->mostrarFilaEspera();
}

void MenuAdmin::mostrarAjustes() {

    if (!ventanaAjustes) {
        ventanaAjustes = new Ajustes(this);
    }

    // Mostrar la ventana
    ventanaAjustes->show();
    ventanaAjustes->raise();
    ventanaAjustes->activateWindow();
}
void MenuAdmin::salir() {
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
        if (ventanaRegistroPaciente) {
            ventanaRegistroPaciente->close();
        }
        if (ventanaRegistroMedico) {
            ventanaRegistroMedico->close();
        }
        if (ventanaAjustes) {
            ventanaAjustes->close();
        }
        if (ventanaFilaEspera) { // Agregar esta línea
            ventanaFilaEspera->close();
        }

        hide();
        loginWindow->cerrarSesion();
    }
}
