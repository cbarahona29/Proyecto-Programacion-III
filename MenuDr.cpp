#include "MenuDr.h"
#include "Login.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QRegularExpression>
#include <QTextEdit>
#include "FilaEspera.h"
#include <QTime>
#include <QDate>
#include <QRegularExpression>

MenuDr::MenuDr(Login* login) : loginWindow(login) {
    inicializarDatos();
    configurarUI();
    configurarEventos();
}

void MenuDr::inicializarDatos() {
    // Inicializar algunos pacientes de ejemplo
    std::map<std::string, std::string> paciente1;
    paciente1["id"] = "001";
    paciente1["nombre"] = "Juan Pérez";
    paciente1["edad"] = "35";
    paciente1["telefono"] = "99887766";
    paciente1["direccion"] = "Colonia Centro, Tegucigalpa";

    std::map<std::string, std::string> paciente2;
    paciente2["id"] = "002";
    paciente2["nombre"] = "María González";
    paciente2["edad"] = "28";
    paciente2["telefono"] = "88776655";
    paciente2["direccion"] = "Colonia Kennedy, Tegucigalpa";

    std::map<std::string, std::string> paciente3;
    paciente3["id"] = "003";
    paciente3["nombre"] = "Carlos Rodríguez";
    paciente3["edad"] = "42";
    paciente3["telefono"] = "77665544";
    paciente3["direccion"] = "Colonia Palmira, Tegucigalpa";

    pacientes.push_back(paciente1);
    pacientes.push_back(paciente2);
    pacientes.push_back(paciente3);

    // Agregar algunos pacientes a la fila de espera
    filaEspera.push_back("Juan Pérez (ID: 001)");
    filaEspera.push_back("María González (ID: 002)");
    filaEspera.push_back("Carlos Rodríguez (ID: 003)");
}

void MenuDr::configurarUI() {
    setWindowTitle("Sistema Médico - Dashboard Principal");
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

    labelBienvenida = new QLabel("Bienvenido Dr...");
    labelBienvenida->setAlignment(Qt::AlignCenter);
    labelBienvenida->setStyleSheet(
        "color: black; "
        "font-size: 16px; "
        "font-weight: bold; "
        "margin: 20px;"
        );
    layoutPrincipal->addWidget(labelBienvenida);

    // Grid de botones (ahora con 5 botones en lugar de 6)
    QGridLayout* gridBotones = new QGridLayout();
    gridBotones->setSpacing(20);

    btnExpedientesClinicos = crearBoton("Expedientes Clínicos");
    btnBuscarPaciente = crearBoton("Buscar Paciente");
    btnFilaEspera = crearBoton("Fila de Espera");
    btnAtenderPaciente = crearBoton("Atender Paciente");
    btnSalir = crearBoton("Salir");

    // Reorganizar el grid para mejor distribución visual
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

QPushButton* MenuDr::crearBoton(QString texto) {
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

void MenuDr::configurarEventos() {
    connect(btnExpedientesClinicos, &QPushButton::clicked, this, &MenuDr::mostrarExpedientes);
    connect(btnBuscarPaciente, &QPushButton::clicked, this, &MenuDr::buscarPaciente);
    connect(btnFilaEspera, &QPushButton::clicked, this, &MenuDr::mostrarFilaEspera);
    connect(btnAtenderPaciente, &QPushButton::clicked, this, &MenuDr::atenderPaciente);
    connect(btnSalir, &QPushButton::clicked, this, &MenuDr::salir);
}

void MenuDr::setUsuario(const QString& usuario) {
    labelBienvenida->setText("Bienvenido Dr. " + usuario);
}

QMessageBox* MenuDr::crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono) {
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

void MenuDr::mostrarInformacionPaciente(const std::map<std::string, std::string>& paciente) {
    QString info = QString("ID: %1\nNombre: %2\nEdad: %3\nTeléfono: %4\nDirección: %5")
                       .arg(QString::fromStdString(paciente.at("id")))
                       .arg(QString::fromStdString(paciente.at("nombre")))
                       .arg(QString::fromStdString(paciente.at("edad")))
                       .arg(QString::fromStdString(paciente.at("telefono")))
                       .arg(QString::fromStdString(paciente.at("direccion")));

    QMessageBox* msg = crearMensaje("Información del Paciente", info, QMessageBox::Information);
    msg->exec();
    delete msg;
}

void MenuDr::mostrarExpedientes() {
    // Crear diálogo para seleccionar paciente
    QDialog* dialogSeleccion = new QDialog(this);
    dialogSeleccion->setWindowTitle("Expedientes Clínicos - Seleccionar Paciente");
    dialogSeleccion->setFixedSize(500, 300);
    dialogSeleccion->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "}"
        "QListWidget {"
        "   background-color: white;"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   font-size: 12px;"
        "   color: black;"
        "}"
        "QListWidget::item {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #eee;"
        "   color: black;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #e3f2fd;"
        "   color: black;"
        "}"
        "QPushButton {"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "   font-size: 12px;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(dialogSeleccion);
    layout->setSpacing(15);

    // Título
    QLabel* titulo = new QLabel("Seleccione un paciente para ver su expediente:");
    titulo->setAlignment(Qt::AlignCenter);
    layout->addWidget(titulo);

    // Lista de pacientes
    QListWidget* listaPacientes = new QListWidget();

    for (const auto& paciente : pacientes) {
        QString item = QString("%1 - %2 (ID: %3)")
        .arg(QString::fromStdString(paciente.at("nombre")))
            .arg(QString::fromStdString(paciente.at("edad")) + " años")
            .arg(QString::fromStdString(paciente.at("id")));

        QListWidgetItem* listItem = new QListWidgetItem(item);
        listItem->setData(Qt::UserRole, QString::fromStdString(paciente.at("id"))); // Guardar ID
        listaPacientes->addItem(listItem);
    }

    layout->addWidget(listaPacientes);

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnVerExpediente = new QPushButton("Ver Expediente");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    btnVerExpediente->setEnabled(false);

    layoutBotones->addStretch();
    layoutBotones->addWidget(btnVerExpediente);
    layoutBotones->addWidget(btnCancelar);

    layout->addLayout(layoutBotones);

    // Conectar eventos
    connect(listaPacientes, &QListWidget::itemSelectionChanged, [=]() {
        btnVerExpediente->setEnabled(listaPacientes->currentItem() != nullptr);
    });

    connect(btnVerExpediente, &QPushButton::clicked, [=]() {
        if (listaPacientes->currentItem()) {
            QString idPaciente = listaPacientes->currentItem()->data(Qt::UserRole).toString();
            dialogSeleccion->accept();
            mostrarExpedienteDetallado(idPaciente);
        }
    });

    connect(btnCancelar, &QPushButton::clicked, dialogSeleccion, &QDialog::reject);

    // Permitir doble clic para ver expediente
    connect(listaPacientes, &QListWidget::itemDoubleClicked, [=]() {
        if (listaPacientes->currentItem()) {
            QString idPaciente = listaPacientes->currentItem()->data(Qt::UserRole).toString();
            dialogSeleccion->accept();
            mostrarExpedienteDetallado(idPaciente);
        }
    });

    dialogSeleccion->exec();
    delete dialogSeleccion;
}

void MenuDr::mostrarExpedienteDetallado(const QString& idPaciente) {
    // Buscar el paciente
    std::map<std::string, std::string> pacienteEncontrado;
    bool encontrado = false;

    for (const auto& paciente : pacientes) {
        if (QString::fromStdString(paciente.at("id")) == idPaciente) {
            pacienteEncontrado = paciente;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        QMessageBox* msg = crearMensaje("Error", "Paciente no encontrado", QMessageBox::Warning);
        msg->exec();
        delete msg;
        return;
    }

    // Crear ventana de expediente detallado
    QDialog* ventanaExpediente = new QDialog(this);
    ventanaExpediente->setWindowTitle("Expediente Clínico - " + QString::fromStdString(pacienteEncontrado.at("nombre")));
    ventanaExpediente->setFixedSize(800, 600);
    ventanaExpediente->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "}"
        "QTextEdit {"
        "   background-color: white;"
        "   border: 1px solid #ccc;"
        "   border-radius: 5px;"
        "   font-size: 11px;"
        "   font-family: 'Arial';"
        "}"
        "QGroupBox {"
        "   font-size: 12px;"
        "   border: 2px solid #999;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 5px 0 5px;"
        "}"
        "QPushButton {"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 8px 16px;"
        "}"
        );

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(ventanaExpediente);
    layoutPrincipal->setSpacing(15);

    // Información del paciente
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
                               .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy"));

    QLabel* lblInfo = new QLabel(infoPaciente);
    lblInfo->setStyleSheet("font-size: 12px; padding: 10px; background-color: #f9f9f9; border-radius: 3px;");
    layoutInfo->addWidget(lblInfo);

    layoutPrincipal->addWidget(groupInfo);

    // Historial de consultas
    QGroupBox* groupHistorial = new QGroupBox("Historial de Consultas Médicas");
    QVBoxLayout* layoutHistorial = new QVBoxLayout(groupHistorial);

    QTextEdit* txtHistorial = new QTextEdit();
    txtHistorial->setReadOnly(true);

    // Generar historial de consultas (simulado)
    QString historial = generarHistorialConsultas(idPaciente);
    txtHistorial->setHtml(historial);

    layoutHistorial->addWidget(txtHistorial);
    layoutPrincipal->addWidget(groupHistorial);

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnNuevaConsulta = new QPushButton("Nueva Consulta");
    QPushButton* btnCerrar = new QPushButton("Cerrar");

    layoutBotones->addWidget(btnNuevaConsulta);
    layoutBotones->addStretch();
    layoutBotones->addWidget(btnCerrar);

    layoutPrincipal->addLayout(layoutBotones);

    // Conectar eventos
    connect(btnNuevaConsulta, &QPushButton::clicked, [=]() {
        ventanaExpediente->accept();
        realizarConsulta(pacienteEncontrado);
    });

    connect(btnCerrar, &QPushButton::clicked, ventanaExpediente, &QDialog::accept);

    ventanaExpediente->exec();
    delete ventanaExpediente;
}

QString MenuDr::generarHistorialConsultas(const QString& idPaciente) {
    QString historial;

    // Verificar si hay consultas guardadas para este paciente
    // (Por ahora generamos datos de ejemplo)

    historial += "<html><body style='font-family: Arial; font-size: 11px;'>";

    // Si no hay consultas reales, mostrar datos de ejemplo
    if (idPaciente == "001") {
        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #1 - 15/06/2025 14:30</h4>";
        historial += "<p><strong>Síntomas:</strong> Dolor de cabeza frecuente, fatiga, mareos ocasionales</p>";
        historial += "<p><strong>Diagnóstico:</strong> Cefalea tensional, posible estrés laboral</p>";
        historial += "<p><strong>Tratamiento:</strong> Ibuprofeno 400mg cada 8 horas, descanso, técnicas de relajación</p>";
        historial += "<p><strong>Observaciones:</strong> Paciente refiere mejora con descanso. Recomendar evaluación oftalmológica</p>";
        historial += "</div>";

        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #2 - 22/05/2025 10:15</h4>";
        historial += "<p><strong>Síntomas:</strong> Dolor abdominal, náuseas, pérdida de apetito</p>";
        historial += "<p><strong>Diagnóstico:</strong> Gastritis aguda</p>";
        historial += "<p><strong>Tratamiento:</strong> Omeprazol 20mg en ayunas, dieta blanda, evitar irritantes</p>";
        historial += "<p><strong>Observaciones:</strong> Paciente con antecedente de gastritis. Mejoría en 72 horas</p>";
        historial += "</div>";
    } else if (idPaciente == "002") {
        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #1 - 18/06/2025 09:45</h4>";
        historial += "<p><strong>Síntomas:</strong> Tos seca persistente, congestión nasal, dolor de garganta</p>";
        historial += "<p><strong>Diagnóstico:</strong> Rinofaringitis viral (resfriado común)</p>";
        historial += "<p><strong>Tratamiento:</strong> Paracetamol 500mg c/6h, abundantes líquidos, reposo relativo</p>";
        historial += "<p><strong>Observaciones:</strong> Síntomas de 3 días de evolución. No fiebre al momento del examen</p>";
        historial += "</div>";
    } else if (idPaciente == "003") {
        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;'>";
        historial += "<h4 style='color: #2196F3; margin-top: 0;'>Consulta #1 - 20/06/2025 16:00</h4>";
        historial += "<p><strong>Síntomas:</strong> Dolor en rodilla derecha, hinchazón, dificultad para caminar</p>";
        historial += "<p><strong>Diagnóstico:</strong> Posible lesión meniscal, artritis reactiva</p>";
        historial += "<p><strong>Tratamiento:</strong> Diclofenaco 50mg c/8h, reposo, aplicar hielo, vendaje compresivo</p>";
        historial += "<p><strong>Observaciones:</strong> Referir a traumatología si no hay mejoría en 1 semana</p>";
        historial += "</div>";

        historial += "<div style='margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; border-radius: 5px;'>";
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

void MenuDr::buscarPaciente() {
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

void MenuDr::mostrarFilaEspera() {
    // Crear instancia de la clase FilaEspera
    FilaEspera* ventanaFila = new FilaEspera(this);

    // Convertir los datos de filaEspera a CitaAgendada
    std::vector<CitaAgendada> citasParaHoy;

    // Si tienes datos en filaEspera, convertirlos a CitaAgendada
    for (const auto& pacienteStr : filaEspera) {
        CitaAgendada cita;

        // Extraer información del string del paciente
        QString pacienteInfo = QString::fromStdString(pacienteStr);

        // Extraer ID del string (formato: "Nombre (ID: XXX)")
        QRegularExpression rx("\\(ID: (\\d+)\\)");
        QRegularExpressionMatch match = rx.match(pacienteInfo);

        if (match.hasMatch()) {
            QString idPaciente = match.captured(1);

            // Buscar el paciente completo en la lista de pacientes
            for (const auto& paciente : pacientes) {
                if (QString::fromStdString(paciente.at("id")) == idPaciente) {
                    cita.paciente = QString::fromStdString(paciente.at("nombre"));
                    cita.fecha = QDate::currentDate().toString("yyyy-MM-dd");
                    cita.hora = QTime::currentTime().toString("HH:mm");
                    cita.tipo = "Consulta General"; // Valor por defecto

                    citasParaHoy.push_back(cita);
                    break;
                }
            }
        } else {
            // Si no se puede extraer ID, usar la información básica
            cita.paciente = pacienteInfo;
            cita.fecha = QDate::currentDate().toString("yyyy-MM-dd");
            cita.hora = QTime::currentTime().toString("HH:mm");
            cita.tipo = "Consulta General";

            citasParaHoy.push_back(cita);
        }
    }

    // Establecer las citas en la ventana
    ventanaFila->setCitasAgendadas(citasParaHoy);

    // Mostrar la ventana
    ventanaFila->mostrarFilaEspera();

    // Limpiar memoria
    delete ventanaFila;
}

void MenuDr::atenderPaciente() {
    if (filaEspera.empty()) {
        QMessageBox* msg = crearMensaje("Fila Vacía",
                                        "No hay pacientes en la fila de espera.",
                                        QMessageBox::Information);
        msg->exec();
        delete msg;
        return;
    }

    // Crear un diálogo personalizado con ComboBox
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Atender Paciente");
    dialog->setFixedSize(400, 200);
    dialog->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 14px;"
        "}"
        "QComboBox {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "   font-size: 12px;"
        "}"
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 15px;"
        "   font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->setSpacing(20);

    QLabel* label = new QLabel("Seleccione el paciente a atender:");
    layout->addWidget(label);

    QComboBox* comboBox = new QComboBox();
    for (const auto& paciente : filaEspera) {
        comboBox->addItem(QString::fromStdString(paciente));
    }
    layout->addWidget(comboBox);

    // Botones
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* btnAtender = new QPushButton("Atender");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnAtender);
    buttonLayout->addWidget(btnCancelar);

    layout->addLayout(buttonLayout);

    // Conectar botones
    connect(btnAtender, &QPushButton::clicked, [=]() {
        QString pacienteSeleccionado = comboBox->currentText();

        // Extraer el ID del paciente seleccionado usando QRegularExpression
        QRegularExpression rx("ID: (\\d+)");
        QRegularExpressionMatch match = rx.match(pacienteSeleccionado);
        QString idPaciente;
        if (match.hasMatch()) {
            idPaciente = match.captured(1);
        }

        // Mostrar información del paciente
        for (const auto& paciente : pacientes) {
            if (QString::fromStdString(paciente.at("id")) == idPaciente) {
                dialog->accept();
                mostrarInformacionPaciente(paciente);

                // Remover paciente de la fila de espera
                for (auto it = filaEspera.begin(); it != filaEspera.end(); ++it) {
                    if (QString::fromStdString(*it) == pacienteSeleccionado) {
                        filaEspera.erase(it);
                        break;
                    }
                }

                // Preguntar si desea realizar consulta
                QMessageBox* msgConsulta = new QMessageBox(this);
                msgConsulta->setWindowTitle("Realizar Consulta");
                msgConsulta->setText("¿Desea realizar una consulta médica para este paciente?");
                msgConsulta->setIcon(QMessageBox::Question);
                msgConsulta->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgConsulta->setStyleSheet(
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

                QMessageBox::StandardButton respuestaConsulta =
                    static_cast<QMessageBox::StandardButton>(msgConsulta->exec());
                delete msgConsulta;

                if (respuestaConsulta == QMessageBox::Yes) {
                    realizarConsulta(paciente);
                } else {
                    QMessageBox* msg = crearMensaje("Paciente Atendido",
                                                    "El paciente " + pacienteSeleccionado + " ha sido atendido.",
                                                    QMessageBox::Information);
                    msg->exec();
                    delete msg;
                }
                return;
            }
        }
    });

    connect(btnCancelar, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
    delete dialog;
}

void MenuDr::realizarConsulta(const std::map<std::string, std::string>& paciente) {
    // Crear diálogo personalizado para la consulta
    QDialog* dialogConsulta = new QDialog(this);
    dialogConsulta->setWindowTitle("Consulta Médica - " + QString::fromStdString(paciente.at("nombre")));
    dialogConsulta->setFixedSize(600, 500);
    dialogConsulta->setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "}"
        "QTextEdit, QLineEdit {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 5px;"
        "   font-size: 11px;"
        "}"
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   color: black;"
        "   border: 1px solid #999;"
        "   border-radius: 3px;"
        "   padding: 8px 15px;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        "QPushButton#btnGuardar {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "}"
        "QPushButton#btnGuardar:hover {"
        "   background-color: #45a049;"
        "}"
        );

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(dialogConsulta);
    layoutPrincipal->setSpacing(15);

    // Información del paciente
    QLabel* lblInfoPaciente = new QLabel(
        QString("Paciente: %1 | ID: %2 | Edad: %3")
            .arg(QString::fromStdString(paciente.at("nombre")))
            .arg(QString::fromStdString(paciente.at("id")))
            .arg(QString::fromStdString(paciente.at("edad")))
        );
    lblInfoPaciente->setStyleSheet("font-size: 14px; color: black; margin-bottom: 10px;");
    layoutPrincipal->addWidget(lblInfoPaciente);

    // Síntomas
    QLabel* lblSintomas = new QLabel("Síntomas:");
    QTextEdit* txtSintomas = new QTextEdit();
    txtSintomas->setMaximumHeight(80);
    txtSintomas->setPlaceholderText("Describa los síntomas que presenta el paciente...");
    layoutPrincipal->addWidget(lblSintomas);
    layoutPrincipal->addWidget(txtSintomas);

    // Diagnóstico
    QLabel* lblDiagnostico = new QLabel("Diagnóstico:");
    QTextEdit* txtDiagnostico = new QTextEdit();
    txtDiagnostico->setMaximumHeight(80);
    txtDiagnostico->setPlaceholderText("Escriba el diagnóstico médico...");
    layoutPrincipal->addWidget(lblDiagnostico);
    layoutPrincipal->addWidget(txtDiagnostico);

    // Tratamiento
    QLabel* lblTratamiento = new QLabel("Tratamiento/Medicamentos:");
    QTextEdit* txtTratamiento = new QTextEdit();
    txtTratamiento->setMaximumHeight(80);
    txtTratamiento->setPlaceholderText("Indique el tratamiento y medicamentos recetados...");
    layoutPrincipal->addWidget(lblTratamiento);
    layoutPrincipal->addWidget(txtTratamiento);

    // Observaciones
    QLabel* lblObservaciones = new QLabel("Observaciones adicionales:");
    QTextEdit* txtObservaciones = new QTextEdit();
    txtObservaciones->setMaximumHeight(60);
    txtObservaciones->setPlaceholderText("Observaciones adicionales (opcional)...");
    layoutPrincipal->addWidget(lblObservaciones);
    layoutPrincipal->addWidget(txtObservaciones);

    // Botones
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnGuardar = new QPushButton("Guardar Consulta");
    QPushButton* btnCancelar = new QPushButton("Cancelar");

    btnGuardar->setObjectName("btnGuardar");

    layoutBotones->addStretch();
    layoutBotones->addWidget(btnGuardar);
    layoutBotones->addWidget(btnCancelar);

    layoutPrincipal->addLayout(layoutBotones);

    // Conectar eventos
    connect(btnGuardar, &QPushButton::clicked, [=]() {
        // Validar campos obligatorios
        if (txtSintomas->toPlainText().trimmed().isEmpty() ||
            txtDiagnostico->toPlainText().trimmed().isEmpty()) {
            QMessageBox* msg = crearMensaje("Campos Requeridos",
                                            "Los campos 'Síntomas' y 'Diagnóstico' son obligatorios.",
                                            QMessageBox::Warning);
            msg->exec();
            delete msg;
            return;
        }

        // Crear nueva consulta (estructura simple sin definir en header)
        // Obtener fecha actual
        QDateTime fechaActual = QDateTime::currentDateTime();
        QString fechaStr = fechaActual.toString("dd/MM/yyyy hh:mm");

        QString sintomas = txtSintomas->toPlainText();
        QString diagnostico = txtDiagnostico->toPlainText();
        QString tratamiento = txtTratamiento->toPlainText();
        QString observaciones = txtObservaciones->toPlainText();

        dialogConsulta->accept();

        // Mostrar confirmación
        QMessageBox* msg = crearMensaje("Consulta Guardada",
                                        QString("La consulta para %1 ha sido guardada exitosamente.\n\n"
                                                "Fecha: %2\n"
                                                "Diagnóstico: %3")
                                            .arg(QString::fromStdString(paciente.at("nombre")))
                                            .arg(fechaStr)
                                            .arg(diagnostico),
                                        QMessageBox::Information);
        msg->exec();
        delete msg;
    });

    connect(btnCancelar, &QPushButton::clicked, dialogConsulta, &QDialog::reject);

    dialogConsulta->exec();
    delete dialogConsulta;
}

void MenuDr::salir() {
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

