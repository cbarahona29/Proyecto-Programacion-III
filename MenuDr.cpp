#include "MenuDr.h"
#include "BuscarPacientes.h"
#include "Login.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog> // Make sure this is included
#include <QTextEdit>    // Make sure this is included
#include <QGroupBox>    // Make sure this is included
#include <QDateTime>    // Make sure this is included

MenuDr::MenuDr(Login* login, QWidget *parent)
    : QMainWindow(parent),
    loginWindow(login),
    ventanaBuscarPacientes(nullptr),
    btnExpedientesClinicos(nullptr),
    btnBuscarPaciente(nullptr),
    btnFilaEspera(nullptr),
    btnAtenderPaciente(nullptr),
    btnSalir(nullptr),
    labelBienvenida(nullptr)
{
    // Initialize dummy patient data for demonstration
    // In a real application, this would come from a database or file.
    pacientes.push_back({
        {"id", "001"},
        {"nombre", "Juan Perez"},
        {"edad", "45"},
        {"telefono", "9876-5432"},
        {"direccion", "Calle Falsa 123"},
        {"historial", "Historial de Juan"} // This is a placeholder for actual history
    });
    pacientes.push_back({
        {"id", "002"},
        {"nombre", "Maria Lopez"},
        {"edad", "30"},
        {"telefono", "1234-5678"},
        {"direccion", "Avenida Siempre Viva 742"},
        {"historial", "Historial de Maria"}
    });
    pacientes.push_back({
        {"id", "003"},
        {"nombre", "Carlos Sanchez"},
        {"edad", "60"},
        {"telefono", "5555-1111"},
        {"direccion", "Blvd. Los Olivos 500"},
        {"historial", "Historial de Carlos"}
    });

    configurarUI();
    configurarEventos();
}

MenuDr::~MenuDr() {
    // Limpiar ventanas hijas
    if (ventanaBuscarPacientes) {
        delete ventanaBuscarPacientes;
        ventanaBuscarPacientes = nullptr; // Set to nullptr after deletion
    }
}

void MenuDr::configurarUI() {
    setWindowTitle("Sistema Médico - Dashboard Principal");
    setFixedSize(800, 600);

    // Establecer fondo blanco para la ventana principal
    setStyleSheet(
        "QMainWindow {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QWidget {"
        "    background-color: white;"
        "    color: black;"
        "}"
        );

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(widget);
    layoutPrincipal->setSpacing(20);

    labelBienvenida = new QLabel("Bienvenido Dr...");
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

    btnExpedientesClinicos = crearBoton("Expedientes Clínicos");
    btnBuscarPaciente = crearBoton("Buscar Paciente");
    btnFilaEspera = crearBoton("Fila de Espera");
    btnAtenderPaciente = crearBoton("Atender Paciente");
    btnSalir = crearBoton("Salir");

    gridBotones->addWidget(btnExpedientesClinicos, 0, 0);
    gridBotones->addWidget(btnBuscarPaciente, 0, 1);
    gridBotones->addWidget(btnFilaEspera, 1, 0);
    gridBotones->addWidget(btnAtenderPaciente, 1, 1);

    // Centrar el botón de salir
    QHBoxLayout* salirLayout = new QHBoxLayout();
    salirLayout->addStretch();
    salirLayout->addWidget(btnSalir);
    salirLayout->addStretch();

    layoutPrincipal->addLayout(gridBotones);
    layoutPrincipal->addLayout(salirLayout);
    layoutPrincipal->addStretch();
}

QPushButton* MenuDr::crearBoton(const QString& texto) {
    QPushButton* boton = new QPushButton(texto);
    boton->setFixedSize(250, 60);
    boton->setStyleSheet(
        "QPushButton {"
        "    background-color: white; "
        "    border: 2px solid #ccc; "
        "    border-radius: 5px; "
        "    padding: 10px; "
        "    color: black; "
        "    font-size: 14px; "
        "    font-weight: bold; "
        "}"
        "QPushButton:hover {"
        "    background-color: #f5f5f5; "
        "    border: 2px solid #999; "
        "    color: black; "
        "}"
        "QPushButton:pressed {"
        "    background-color: #e8e8e8; "
        "    color: black; "
        "}"
        );
    return boton;
}

void MenuDr::configurarEventos() {
    connect(btnExpedientesClinicos, &QPushButton::clicked, this, &MenuDr::mostrarExpedientes);
    connect(btnBuscarPaciente, &QPushButton::clicked, this, &MenuDr::buscarPaciente); // Connect to the single, correct search function
    connect(btnFilaEspera, &QPushButton::clicked, this, &MenuDr::mostrarFilaEspera);
    connect(btnAtenderPaciente, &QPushButton::clicked, this, &MenuDr::atenderPaciente);
    connect(btnSalir, &QPushButton::clicked, this, &MenuDr::salir);
}

void MenuDr::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Dr. " + usuario);
}

void MenuDr::mostrarExpedientes() {
    // This will now prompt for a patient ID
    // If you want a general "Expedientes Clinicos" overview, you'd need another function
    QInputDialog* inputDialog = new QInputDialog(this);
    inputDialog->setWindowTitle("Ver Expediente Clínico");
    inputDialog->setLabelText("Ingrese el ID del paciente para ver su expediente:");
    inputDialog->setTextValue("");
    inputDialog->setInputMode(QInputDialog::TextInput);
    inputDialog->setStyleSheet("color: white;"); // This style will only work if the background is also set, for now leaving it as-is based on your original

    if (inputDialog->exec() == QDialog::Accepted) {
        QString idPaciente = inputDialog->textValue().trimmed();
        if (!idPaciente.isEmpty()) {
            mostrarExpedienteDetallado(idPaciente);
        } else {
            QMessageBox::warning(this, "Advertencia", "Debe ingresar un ID de paciente.");
        }
    }
    delete inputDialog;
}


void MenuDr::buscarPaciente() {
    // This `buscarPaciente` implementation opens a QInputDialog and then calls `mostrarInformacionPaciente`
    // It's different from the `BuscarPacientes` external dialog. I'll keep this as requested.

    QInputDialog* inputDialog = new QInputDialog(this);
    inputDialog->setWindowTitle("Buscar Paciente");
    inputDialog->setLabelText("Ingrese el ID del paciente:");
    inputDialog->setTextValue("");
    inputDialog->setInputMode(QInputDialog::TextInput);
    inputDialog->setStyleSheet("color: white;");

    int result = inputDialog->exec();
    QString idPaciente = inputDialog->textValue().trimmed(); // Trim whitespace

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

void MenuDr::mostrarFilaEspera() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Fila de Espera");
    dialog->setFixedSize(500, 400);
    dialog->setStyleSheet("background-color: white; color: black;");

    QLabel* label = new QLabel("Aquí se mostraría la fila de espera", dialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: black;");

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    dialog->exec();
    delete dialog;
}

void MenuDr::atenderPaciente() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Atender Paciente");
    dialog->setFixedSize(400, 300);
    dialog->setStyleSheet("background-color: white; color: black;");

    QLabel* label = new QLabel("Aquí se atendería a un paciente", dialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: black;");

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    dialog->exec();
    delete dialog;
}

void MenuDr::salir() {
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Cerrar Sesión",
        "¿Desea cerrar sesión y volver al login?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta == QMessageBox::Yes) {
        // Cerrar ventanas hijas
        if (ventanaBuscarPacientes) {
            ventanaBuscarPacientes->close();
            delete ventanaBuscarPacientes;
            ventanaBuscarPacientes = nullptr;
        }

        hide();
        loginWindow->cerrarSesion();
    }
}

// --- New functions and implementations ---

void MenuDr::mostrarExpedienteDetallado(const QString& idPaciente) {
    std::map<std::string, std::string> pacienteEncontrado;
    bool encontrado = false;

    // Search for the patient in the 'pacientes' vector
    for (const auto& paciente : pacientes) {
        if (QString::fromStdString(paciente.at("id")) == idPaciente) {
            pacienteEncontrado = paciente;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        QMessageBox* msg = crearMensaje("Error", "Paciente no encontrado.", QMessageBox::Warning);
        msg->exec();
        delete msg;
        return;
    }

    // Create detailed record window
    QDialog* ventanaExpediente = new QDialog(this);
    ventanaExpediente->setWindowTitle("Expediente Clínico - " + QString::fromStdString(pacienteEncontrado.at("nombre")));
    ventanaExpediente->setFixedSize(800, 600);
    ventanaExpediente->setStyleSheet(
        "QDialog {"
        "    background-color: #f0f0f0;"
        "}"
        "QTextEdit {"
        "    background-color: white;"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "    font-size: 11px;"
        "    font-family: 'Arial';"
        "}"
        "QGroupBox {"
        "    font-size: 12px;"
        "    border: 2px solid #999;"
        "    border-radius: 5px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}"
        "QPushButton {"
        "    border: 1px solid #999;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    background-color: #e0e0e0;" // Added background for consistency
        "    color: black;" // Ensure text is black
        "}"
        "QPushButton:hover {"
        "    background-color: #d0d0d0;"
        "}"
        );

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(ventanaExpediente);
    layoutPrincipal->setSpacing(15);

    // Patient Information
    QGroupBox* groupInfo = new QGroupBox("Información del Paciente");
    QVBoxLayout* layoutInfo = new QVBoxLayout(groupInfo);

    QString infoPaciente = QString(
                               "Nombre: %1\n"
                               "ID: %2\n"
                               "Edad: %3 años\n"
                               "Teléfono: %4\n"
                               "Dirección: %5\n"
                               "Fecha de registro: %6"
                               ).arg(QString::fromStdString(pacienteEncontrado.at("nombre")))
                               .arg(QString::fromStdString(pacienteEncontrado.at("id")))
                               .arg(QString::fromStdString(pacienteEncontrado.at("edad")))
                               .arg(QString::fromStdString(pacienteEncontrado.at("telefono")))
                               .arg(QString::fromStdString(pacienteEncontrado.at("direccion")))
                               .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy")); // This will be current date, not actual registration date

    QLabel* lblInfo = new QLabel(infoPaciente);
    lblInfo->setStyleSheet("font-size: 12px; padding: 10px; background-color: #f9f9f9; border-radius: 3px; color: black;"); // Ensure black text
    layoutInfo->addWidget(lblInfo);

    layoutPrincipal->addWidget(groupInfo);

    // Medical History
    QGroupBox* groupHistorial = new QGroupBox("Historial de Consultas Médicas");
    QVBoxLayout* layoutHistorial = new QVBoxLayout(groupHistorial);

    QTextEdit* txtHistorial = new QTextEdit();
    txtHistorial->setReadOnly(true);

    // Generate simulated history
    QString historial = generarHistorialConsultas(idPaciente);
    txtHistorial->setHtml(historial); // Use setHtml for rich text

    layoutHistorial->addWidget(txtHistorial);
    layoutPrincipal->addWidget(groupHistorial);

    // Buttons
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnNuevaConsulta = new QPushButton("Nueva Consulta");
    QPushButton* btnCerrar = new QPushButton("Cerrar");

    layoutBotones->addWidget(btnNuevaConsulta);
    layoutBotones->addStretch();
    layoutBotones->addWidget(btnCerrar);

    layoutPrincipal->addLayout(layoutBotones);

    // Connect events
    connect(btnNuevaConsulta, &QPushButton::clicked, [=]() {
        ventanaExpediente->accept(); // Close the detailed record window
        realizarConsulta(pacienteEncontrado); // Open the new consultation window
    });

    connect(btnCerrar, &QPushButton::clicked, ventanaExpediente, &QDialog::accept);

    ventanaExpediente->exec(); // Show the dialog modally
    delete ventanaExpediente; // Clean up after the dialog closes
}

QString MenuDr::generarHistorialConsultas(const QString& idPaciente) {
    QString historial;

    historial += "<html><body style='font-family: Arial; font-size: 11px; color: black;'>"; // Ensure body text is black

    if (idPaciente == "001") {
        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; background-color: #fcfcfc;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #1 - 15/06/2025 14:30</h4>";
        historial += "<p><strong>Síntomas:</strong> Dolor de cabeza frecuente, fatiga, mareos ocasionales</p>";
        historial += "<p><strong>Diagnóstico:</strong> Cefalea tensional, posible estrés laboral</p>";
        historial += "<p><strong>Tratamiento:</strong> Ibuprofeno 400mg cada 8 horas, descanso, técnicas de relajación</p>";
        historial += "<p><strong>Observaciones:</strong> Paciente refiere mejora con descanso. Recomendar evaluación oftalmológica</p>";
        historial += "</div>";

        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; background-color: #fcfcfc;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #2 - 22/05/2025 10:15</h4>";
        historial += "<p><strong>Síntomas:</strong> Dolor abdominal, náuseas, pérdida de apetito</p>";
        historial += "<p><strong>Diagnóstico:</strong> Gastritis aguda</p>";
        historial += "<p><strong>Tratamiento:</strong> Omeprazol 20mg en ayunas, dieta blanda, evitar irritantes</p>";
        historial += "<p><strong>Observaciones:</strong> Paciente con antecedente de gastritis. Mejoría en 72 horas</p>";
        historial += "</div>";
    } else if (idPaciente == "002") {
        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; background-color: #fcfcfc;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #1 - 18/06/2025 09:45</h4>";
        historial += "<p><strong>Síntomas:</strong> Tos seca persistente, congestión nasal, dolor de garganta</p>";
        historial += "<p><strong>Diagnóstico:</strong> Rinofaringitis viral (resfriado común)</p>";
        historial += "<p><strong>Tratamiento:</strong> Paracetamol 500mg c/6h, abundantes líquidos, reposo relativo</p>";
        historial += "<p><strong>Observaciones:</strong> Síntomas de 3 días de evolución. No fiebre al momento del examen</p>";
        historial += "</div>";
    } else if (idPaciente == "003") {
        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; background-color: #fcfcfc;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #1 - 20/06/2025 16:00</h4>";
        historial += "<p><strong>Síntomas:</strong> Dolor en rodilla derecha, hinchazón, dificultad para caminar</p>";
        historial += "<p><strong>Diagnóstico:</strong> Posible lesión meniscal, artritis reactiva</p>";
        historial += "<p><strong>Tratamiento:</strong> Diclofenaco 50mg c/8h, reposo, aplicar hielo, vendaje compresivo</p>";
        historial += "<p><strong>Observaciones:</strong> Referir a traumatología si no hay mejoría en 1 semana</p>";
        historial += "</div>";

        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px; background-color: #fcfcfc;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #2 - 10/05/2025 11:30</h4>";
        historial += "<p><strong>Síntomas:</strong> Control de presión arterial, mareos matutinos</p>";
        historial += "<p><strong>Diagnóstico:</strong> Hipertensión arterial controlada</p>";
        historial += "<p><strong>Tratamiento:</strong> Continuar con Enalapril 10mg/día, dieta hiposódica</p>";
        historial += "<p><strong>Observaciones:</strong> Presión arterial 130/85. Paciente cumple bien el tratamiento</p>";
        historial += "</div>";
    } else {
        historial += "<div style='text-align: center; padding: 40px; color: #666;'>";
        historial += "<h3>Sin consultas registradas</h3>";
        historial += "<p>Este paciente no tiene consultas médicas registradas en el sistema.</p>";
        historial += "<p>Puede iniciar una nueva consulta haciendo clic en el botón 'Nueva Consulta'.</p>";
        historial += "</div>";
    }

    historial += "</body></html>";

    return historial;
}

void MenuDr::mostrarInformacionPaciente(const std::map<std::string, std::string>& paciente) {
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Información del Paciente");
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QMessageBox QLabel {"
        "    color: black;"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #e8e8e8;"
        "    color: black;"
        "    border: 1px solid #999;"
        "    border-radius: 3px;"
        "    padding: 5px 15px;"
        "    min-width: 60px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #d8d8d8;"
        "}"
        );

    QString info = QString(
                       "ID: %1\n"
                       "Nombre: %2\n"
                       "Edad: %3\n"
                       "Teléfono: %4\n"
                       "Dirección: %5"
                       ).arg(QString::fromStdString(paciente.at("id")))
                       .arg(QString::fromStdString(paciente.at("nombre")))
                       .arg(QString::fromStdString(paciente.at("edad")))
                       .arg(QString::fromStdString(paciente.at("telefono")))
                       .arg(QString::fromStdString(paciente.at("direccion")));

    msgBox->setText(info);
    msgBox->exec();
    delete msgBox;
}

QMessageBox* MenuDr::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(titulo);
    msgBox->setText(texto);
    msgBox->setIcon(icono);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: white;"
        "    color: black;"
        "}"
        "QMessageBox QLabel {"
        "    color: black;"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #e8e8e8;"
        "    color: black;"
        "    border: 1px solid #999;"
        "    border-radius: 3px;"
        "    padding: 5px 15px;"
        "    min-width: 60px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #d8d8d8;"
        "}"
        );
    return msgBox;
}

void MenuDr::realizarConsulta(const std::map<std::string, std::string>& paciente) {
    QDialog* ventanaConsulta = new QDialog(this);
    ventanaConsulta->setWindowTitle("Nueva Consulta para " + QString::fromStdString(paciente.at("nombre")));
    ventanaConsulta->setFixedSize(600, 500);
    ventanaConsulta->setStyleSheet(
        "QDialog {"
        "    background-color: #f0f0f0;"
        "}"
        "QLabel {"
        "    color: black;"
        "    font-weight: bold;"
        "}"
        "QTextEdit, QLineEdit {"
        "    background-color: white;"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    padding: 5px;"
        "    color: black;"
        "}"
        "QPushButton {"
        "    background-color: #e0e0e0;"
        "    border: 1px solid #999;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    color: black;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d0d0d0;"
        "}"
        );

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(ventanaConsulta);
    layoutPrincipal->setSpacing(10);

    // Patient info at the top
    QLabel* lblPatientInfo = new QLabel(QString("Paciente: %1 (ID: %2)").arg(QString::fromStdString(paciente.at("nombre"))).arg(QString::fromStdString(paciente.at("id"))));
    lblPatientInfo->setStyleSheet("font-size: 14px; font-weight: bold; color: #333; margin-bottom: 10px;");
    layoutPrincipal->addWidget(lblPatientInfo);

    // Symptoms
    QLabel* lblSintomas = new QLabel("Síntomas:");
    QTextEdit* txtSintomas = new QTextEdit();
    txtSintomas->setPlaceholderText("Describa los síntomas del paciente...");
    layoutPrincipal->addWidget(lblSintomas);
    layoutPrincipal->addWidget(txtSintomas);

    // Diagnosis
    QLabel* lblDiagnostico = new QLabel("Diagnóstico:");
    QTextEdit* txtDiagnostico = new QTextEdit();
    txtDiagnostico->setPlaceholderText("Ingrese el diagnóstico...");
    layoutPrincipal->addWidget(lblDiagnostico);
    layoutPrincipal->addWidget(txtDiagnostico);

    // Treatment
    QLabel* lblTratamiento = new QLabel("Tratamiento:");
    QTextEdit* txtTratamiento = new QTextEdit();
    txtTratamiento->setPlaceholderText("Indique el tratamiento y medicación...");
    layoutPrincipal->addWidget(lblTratamiento);
    layoutPrincipal->addWidget(txtTratamiento);

    // Observations
    QLabel* lblObservaciones = new QLabel("Observaciones:");
    QTextEdit* txtObservaciones = new QTextEdit();
    txtObservaciones->setPlaceholderText("Notas adicionales, recomendaciones, etc.");
    layoutPrincipal->addWidget(lblObservaciones);
    layoutPrincipal->addWidget(txtObservaciones);

    // Buttons
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnGuardar = new QPushButton("Guardar Consulta");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    layoutBotones->addStretch();
    layoutBotones->addWidget(btnGuardar);
    layoutBotones->addWidget(btnCancelar);

    layoutPrincipal->addLayout(layoutBotones);

    // Connect events
    connect(btnGuardar, &QPushButton::clicked, [=]() {
        // Here you would save the consultation data (symptoms, diagnosis, treatment, observations)
        // to a file or database associated with the patient.
        // For now, we'll just show a message.
        QString sintomas = txtSintomas->toPlainText();
        QString diagnostico = txtDiagnostico->toPlainText();
        QString tratamiento = txtTratamiento->toPlainText();
        QString observaciones = txtObservaciones->toPlainText();

        if (sintomas.isEmpty() || diagnostico.isEmpty() || tratamiento.isEmpty()) {
            QMessageBox::warning(ventanaConsulta, "Campos Obligatorios", "Por favor, complete los campos de Síntomas, Diagnóstico y Tratamiento.");
            return;
        }

        QMessageBox::information(ventanaConsulta, "Consulta Guardada",
                                 QString("La consulta para %1 ha sido 'guardada' (simulado).")
                                     .arg(QString::fromStdString(paciente.at("nombre"))));
        ventanaConsulta->accept();
    });

    connect(btnCancelar, &QPushButton::clicked, ventanaConsulta, &QDialog::reject);

    ventanaConsulta->exec();
    delete ventanaConsulta;
}
