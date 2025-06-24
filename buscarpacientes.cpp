#include "BuscarPacientes.h"
#include <QRegularExpression>
#include <QDebug>

BuscarPacientes::BuscarPacientes(QWidget* parent)
    : QDialog(parent), gestor(nullptr), idPacienteSeleccionado(-1) {

    // Inicializar el gestor de pacientes
    try {
        gestor = new gestionPaciente();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
                              QString("No se pudo inicializar el sistema de pacientes:\n%1").arg(e.what()));
        return;
    }

    configurarUI();
    configurarEventos();
    cargarTodosLosPacientes();
}

BuscarPacientes::~BuscarPacientes() {
    if (gestor) {
        delete gestor;
    }
}

void BuscarPacientes::configurarUI() {
    setWindowTitle("Buscar Pacientes");
    setFixedSize(900, 650);

    // Estilo general similar al menú
    setStyleSheet(
        "QDialog {"
        "   background-color: white;"
        "   color: black;"
        "}"
        "QWidget {"
        "   background-color: white;"
        "   color: black;"
        "}"
        );

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(20);

    // Título
    QLabel* labelTitulo = new QLabel("Gestión de Pacientes");
    labelTitulo->setAlignment(Qt::AlignCenter);
    labelTitulo->setStyleSheet(
        "font-size: 18px; "
        "font-weight: bold; "
        "color: black; "
        "padding: 10px;"
        );
    layoutPrincipal->addWidget(labelTitulo);

    // Sección de búsqueda - sin botón limpiar
    QHBoxLayout* layoutBusqueda = new QHBoxLayout();
    layoutBusqueda->setSpacing(10);

    QLabel* labelBuscar = new QLabel("Buscar:");
    labelBuscar->setStyleSheet("color: black; font-weight: bold;");

    comboTipoBusqueda = new QComboBox();
    comboTipoBusqueda->addItem("ID");
    comboTipoBusqueda->addItem("Nombre");
    comboTipoBusqueda->addItem("Número de Identidad");
    comboTipoBusqueda->setFixedSize(150, 35);
    comboTipoBusqueda->setStyleSheet(
        "QComboBox { "
        "   background-color: white; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "   color: black; "
        "   padding: 5px; "
        "}"
        );

    lineEditBusqueda = new QLineEdit();
    lineEditBusqueda->setPlaceholderText("Ingrese criterio de búsqueda...");
    lineEditBusqueda->setFixedHeight(35);
    lineEditBusqueda->setStyleSheet(
        "QLineEdit { "
        "   background-color: white; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "   color: black; "
        "   padding: 5px; "
        "}"
        );

    // Botones de búsqueda - sin botón limpiar
    btnBuscar = crearBotonSimple("Buscar", 100, 35);
    btnCargarTodos = crearBotonSimple("Ver Todos", 100, 35);

    layoutBusqueda->addWidget(labelBuscar);
    layoutBusqueda->addWidget(comboTipoBusqueda);
    layoutBusqueda->addWidget(lineEditBusqueda);
    layoutBusqueda->addWidget(btnBuscar);
    layoutBusqueda->addWidget(btnCargarTodos);
    layoutBusqueda->addStretch();

    layoutPrincipal->addLayout(layoutBusqueda);

    // Tabla de resultados
    labelResultados = new QLabel("Pacientes:");
    labelResultados->setStyleSheet("color: black; font-weight: bold; font-size: 14px;");
    layoutPrincipal->addWidget(labelResultados);

    tablaPacientes = new QTableWidget();
    tablaPacientes->setColumnCount(5);
    QStringList headers = {"ID", "Nombre", "Identidad", "Teléfono", "Email"};
    tablaPacientes->setHorizontalHeaderLabels(headers);
    tablaPacientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablaPacientes->setAlternatingRowColors(true);
    tablaPacientes->horizontalHeader()->setStretchLastSection(true);
    tablaPacientes->setStyleSheet(
        "QTableWidget { "
        "   background-color: white; "
        "   color: black; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "}"
        "QTableWidget::item:selected { background-color: #e8e8e8; }"
        "QHeaderView::section { "
        "   background-color: #f5f5f5; "
        "   color: black; "
        "   border: 1px solid #ccc; "
        "   padding: 8px; "
        "   font-weight: bold; "
        "}"
        );

    layoutPrincipal->addWidget(tablaPacientes, 1);

    // Botones de acción
    QHBoxLayout* layoutAcciones = new QHBoxLayout();
    layoutAcciones->setSpacing(15);

    btnEditar = crearBotonSimple("Editar", 100, 40);
    btnEliminar = crearBotonSimple("Eliminar", 100, 40);
    btnCerrar = crearBotonSimple("Cerrar", 100, 40);

    // Inicialmente deshabilitados
    btnEditar->setEnabled(false);
    btnEliminar->setEnabled(false);

    layoutAcciones->addWidget(btnEditar);
    layoutAcciones->addWidget(btnEliminar);
    layoutAcciones->addStretch();
    layoutAcciones->addWidget(btnCerrar);

    layoutPrincipal->addLayout(layoutAcciones);
}

QPushButton* BuscarPacientes::crearBotonSimple(const QString& texto, int ancho, int alto) {
    QPushButton* boton = new QPushButton(texto);
    boton->setFixedSize(ancho, alto);
    boton->setStyleSheet(
        "QPushButton {"
        "   background-color: white; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "   padding: 5px; "
        "   color: black; "
        "   font-size: 12px; "
        "   font-weight: bold; "
        "}"
        "QPushButton:hover {"
        "   background-color: #f5f5f5; "
        "   border: 2px solid #999; "
        "   color: black; "
        "}"
        "QPushButton:pressed {"
        "   background-color: #e8e8e8; "
        "   color: black; "
        "}"
        "QPushButton:disabled {"
        "   background-color: #f0f0f0; "
        "   border: 2px solid #ddd; "
        "   color: #999; "
        "}"
        );
    return boton;
}

void BuscarPacientes::configurarEventos() {
    connect(btnBuscar, &QPushButton::clicked, this, &BuscarPacientes::buscarPacientes);
    connect(btnCargarTodos, &QPushButton::clicked, this, &BuscarPacientes::cargarTodosLosPacientes);
    connect(btnEditar, &QPushButton::clicked, this, &BuscarPacientes::editarPacienteSeleccionado);
    connect(btnEliminar, &QPushButton::clicked, this, &BuscarPacientes::eliminarPacienteSeleccionado);
    connect(btnCerrar, &QPushButton::clicked, this, &QDialog::close);
    connect(tablaPacientes, &QTableWidget::itemSelectionChanged, this, &BuscarPacientes::onPacienteSeleccionado);
    connect(lineEditBusqueda, &QLineEdit::returnPressed, this, &BuscarPacientes::buscarPacientes);
}

void BuscarPacientes::cargarTodosLosPacientes() {
    if (!gestor) return;

    try {
        std::vector<Paciente> pacientes = gestor->mostrarPacientes();
        actualizarTablaPacientes(pacientes);
        labelResultados->setText(QString("Pacientes (%1 encontrados):").arg(pacientes.size()));

        // Limpiar selección
        idPacienteSeleccionado = -1;
        btnEditar->setEnabled(false);
        btnEliminar->setEnabled(false);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString("Error al cargar pacientes: %1").arg(e.what()));
    }
}

void BuscarPacientes::buscarPacientes() {
    if (!gestor) return;

    QString criterio = lineEditBusqueda->text().trimmed();
    if (criterio.isEmpty()) {
        QMessageBox::information(this, "Información", "Por favor, ingrese un criterio de búsqueda.");
        return;
    }

    std::vector<Paciente> resultados;
    QString tipoBusqueda = comboTipoBusqueda->currentText();

    try {
        if (tipoBusqueda == "ID") {
            bool ok;
            int id = criterio.toInt(&ok);
            if (ok) {
                Paciente* paciente = gestor->buscarPaciente(id);
                if (paciente) {
                    resultados.push_back(*paciente);
                }
            } else {
                QMessageBox::warning(this, "Error", "El ID debe ser un número válido.");
                return;
            }
        } else if (tipoBusqueda == "Nombre") {
            Paciente* paciente = gestor->buscarPacientePorNombre(criterio.toStdString());
            if (paciente) {
                resultados.push_back(*paciente);
            }
        } else if (tipoBusqueda == "Número de Identidad") {
            bool ok;
            int identidad = criterio.toInt(&ok);
            if (ok) {
                Paciente* paciente = gestor->buscarPacientePorIdentidad(identidad);
                if (paciente) {
                    resultados.push_back(*paciente);
                }
            } else {
                QMessageBox::warning(this, "Error", "El número de identidad debe ser válido.");
                return;
            }
        }

        actualizarTablaPacientes(resultados);
        labelResultados->setText(QString("Resultados (%1 encontrados):").arg(resultados.size()));

        // Limpiar selección
        idPacienteSeleccionado = -1;
        btnEditar->setEnabled(false);
        btnEliminar->setEnabled(false);

        if (resultados.empty()) {
            QMessageBox::information(this, "Sin resultados", "No se encontraron pacientes que coincidan con el criterio.");
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString("Error durante la búsqueda: %1").arg(e.what()));
    }
}

void BuscarPacientes::actualizarTablaPacientes(const std::vector<Paciente>& pacientes) {
    tablaPacientes->setRowCount(pacientes.size());

    for (size_t i = 0; i < pacientes.size(); ++i) {
        const Paciente& p = pacientes[i];

        tablaPacientes->setItem(i, 0, new QTableWidgetItem(QString::number(p.getID())));
        tablaPacientes->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.getNombre())));
        tablaPacientes->setItem(i, 2, new QTableWidgetItem(QString::number(p.getNumIdentidad())));
        tablaPacientes->setItem(i, 3, new QTableWidgetItem(QString::number(p.getNumTelefono())));
        tablaPacientes->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(p.getEmail())));
    }

    tablaPacientes->resizeColumnsToContents();
}

void BuscarPacientes::onPacienteSeleccionado() {
    int filaSeleccionada = tablaPacientes->currentRow();
    if (filaSeleccionada >= 0) {
        QTableWidgetItem* itemID = tablaPacientes->item(filaSeleccionada, 0);
        if (itemID) {
            idPacienteSeleccionado = itemID->text().toInt();
            btnEditar->setEnabled(true);
            btnEliminar->setEnabled(true);
        }
    } else {
        idPacienteSeleccionado = -1;
        btnEditar->setEnabled(false);
        btnEliminar->setEnabled(false);
    }
}

void BuscarPacientes::editarPacienteSeleccionado() {
    if (idPacienteSeleccionado == -1) {
        QMessageBox::warning(this, "Error", "No hay ningún paciente seleccionado.");
        return;
    }

    // Buscar el paciente actualizado
    Paciente* paciente = gestor->buscarPaciente(idPacienteSeleccionado);
    if (!paciente) {
        QMessageBox::warning(this, "Error", "No se pudo encontrar el paciente seleccionado.");
        return;
    }

    mostrarDialogoEdicion(paciente);
}

void BuscarPacientes::eliminarPacienteSeleccionado() {
    if (idPacienteSeleccionado == -1) {
        QMessageBox::warning(this, "Error", "No hay ningún paciente seleccionado.");
        return;
    }

    // Buscar el paciente actualizado
    Paciente* paciente = gestor->buscarPaciente(idPacienteSeleccionado);
    if (!paciente) {
        QMessageBox::warning(this, "Error", "No se pudo encontrar el paciente seleccionado.");
        return;
    }

    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Confirmar Eliminación",
        QString("¿Está seguro de que desea eliminar al paciente %1?")
            .arg(QString::fromStdString(paciente->getNombre())),
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta == QMessageBox::Yes) {
        try {
            if (gestor->eliminarPaciente(*paciente)) {
                QMessageBox::information(this, "Éxito", "Paciente eliminado correctamente.");
                // Limpiar selección antes de recargar
                idPacienteSeleccionado = -1;
                btnEditar->setEnabled(false);
                btnEliminar->setEnabled(false);
                // Recargar la lista
                cargarTodosLosPacientes();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo eliminar el paciente.");
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Error al eliminar paciente: %1").arg(e.what()));
        }
    }
}

void BuscarPacientes::mostrarDialogoEdicion(Paciente* paciente) {
    QDialog dialog(this);
    dialog.setWindowTitle("Editar Paciente");
    dialog.setFixedSize(450, 400);
    dialog.setStyleSheet("QDialog { background-color: white; color: black; }");

    QFormLayout* layout = new QFormLayout(&dialog);

    // Campos de edición con estilo simple
    QLineEdit* editNombre = new QLineEdit(QString::fromStdString(paciente->getNombre()));
    QLineEdit* editFechaNac = new QLineEdit(QString::fromStdString(paciente->getFechaNacimiento()));
    QLineEdit* editDireccion = new QLineEdit(QString::fromStdString(paciente->getDireccion()));
    QLineEdit* editIdentidad = new QLineEdit(QString::number(paciente->getNumIdentidad()));
    QLineEdit* editTelefono = new QLineEdit(QString::number(paciente->getNumTelefono()));
    QLineEdit* editEmail = new QLineEdit(QString::fromStdString(paciente->getEmail()));
    QComboBox* comboGenero = new QComboBox();
    comboGenero->addItems({"Masculino", "Femenino", "Otro"});
    comboGenero->setCurrentText(QString::fromStdString(paciente->getGenero()));
    QTextEdit* editAlergias = new QTextEdit(QString::fromStdString(paciente->getAlergias()));
    editAlergias->setMaximumHeight(60);

    // Estilo simple para los campos
    QString estiloLineEdit =
        "QLineEdit { "
        "   background-color: white; "
        "   color: black; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "   padding: 5px; "
        "}";

    editNombre->setStyleSheet(estiloLineEdit);
    editFechaNac->setStyleSheet(estiloLineEdit);
    editDireccion->setStyleSheet(estiloLineEdit);
    editIdentidad->setStyleSheet(estiloLineEdit);
    editTelefono->setStyleSheet(estiloLineEdit);
    editEmail->setStyleSheet(estiloLineEdit);
    comboGenero->setStyleSheet(
        "QComboBox { "
        "   background-color: white; "
        "   color: black; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "   padding: 5px; "
        "}"
        );
    editAlergias->setStyleSheet(
        "QTextEdit { "
        "   background-color: white; "
        "   color: black; "
        "   border: 2px solid #ccc; "
        "   border-radius: 5px; "
        "}"
        );

    layout->addRow("Nombre:", editNombre);
    layout->addRow("Fecha de Nacimiento:", editFechaNac);
    layout->addRow("Dirección:", editDireccion);
    layout->addRow("Número de Identidad:", editIdentidad);
    layout->addRow("Teléfono:", editTelefono);
    layout->addRow("Email:", editEmail);
    layout->addRow("Género:", comboGenero);
    layout->addRow("Alergias:", editAlergias);

    // Botones simples
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    QPushButton* btnGuardar = crearBotonSimple("Guardar", 100, 35);
    QPushButton* btnCancelar = crearBotonSimple("Cancelar", 100, 35);

    layoutBotones->addWidget(btnGuardar);
    layoutBotones->addWidget(btnCancelar);
    layout->addRow(layoutBotones);

    connect(btnGuardar, &QPushButton::clicked, [&]() {
        // Validar datos
        if (!validarDatos(editNombre->text(), editFechaNac->text(), editDireccion->text(),
                          editEmail->text(), editTelefono->text(), editIdentidad->text())) {
            return;
        }

        try {
            // Crear una copia del paciente con los nuevos datos
            Paciente pacienteActualizado = *paciente;
            pacienteActualizado.setNombre(editNombre->text().toStdString());
            pacienteActualizado.setFechaNacimiento(editFechaNac->text().toStdString());
            pacienteActualizado.setDireccion(editDireccion->text().toStdString());
            pacienteActualizado.setNumIdentidad(editIdentidad->text().toInt());
            pacienteActualizado.setNumTelefono(editTelefono->text().toInt());
            pacienteActualizado.setEMail(editEmail->text().toStdString());
            pacienteActualizado.setGenero(comboGenero->currentText().toStdString());
            pacienteActualizado.setAlergias(editAlergias->toPlainText().toStdString());

            // Eliminar el paciente anterior y registrar el actualizado
            gestor->eliminarPaciente(*paciente);
            gestor->registrarPaciente(pacienteActualizado);

            QMessageBox::information(&dialog, "Éxito", "Datos del paciente actualizados correctamente.");

            // Actualizar el ID seleccionado por si cambió
            idPacienteSeleccionado = pacienteActualizado.getID();

            // Recargar la tabla
            cargarTodosLosPacientes();
            dialog.accept();
        } catch (const std::exception& e) {
            QMessageBox::critical(&dialog, "Error", QString("Error al actualizar paciente: %1").arg(e.what()));
        }
    });

    connect(btnCancelar, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

bool BuscarPacientes::validarDatos(const QString& nombre, const QString& fechaNacimiento,
                                   const QString& direccion, const QString& email,
                                   const QString& telefono, const QString& identidad) {
    if (nombre.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre no puede estar vacío.");
        return false;
    }

    if (fechaNacimiento.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "La fecha de nacimiento no puede estar vacía.");
        return false;
    }

    if (direccion.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "La dirección no puede estar vacía.");
        return false;
    }

    // Validar email
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$");
    if (!email.trimmed().isEmpty() && !emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Error", "El formato del email no es válido.");
        return false;
    }

    // Validar teléfono
    bool ok;
    telefono.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "El teléfono debe ser un número válido.");
        return false;
    }

    // Validar identidad
    identidad.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "El número de identidad debe ser un número válido.");
        return false;
    }

    return true;
}
