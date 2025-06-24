    #include "BuscarMedicos.h"
    #include <QRegularExpression>
    #include <QDebug>

    BuscarMedicos::BuscarMedicos(QWidget* parent)
        : QDialog(parent), gestor(nullptr), idMedicoSeleccionado(-1) {

        // Inicializar el gestor de médicos
        try {
            gestor = new gestionMedica();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error",
                                  QString("No se pudo inicializar el sistema de médicos:\n%1").arg(e.what()));
            return;
        }

        configurarUI();
        configurarEventos();
        cargarTodosLosMedicos();
    }

    BuscarMedicos::~BuscarMedicos() {
        if (gestor) {
            delete gestor;
        }
    }

    void BuscarMedicos::configurarUI() {
        setWindowTitle("Buscar Médicos");
        setFixedSize(1000, 650);

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
        QLabel* labelTitulo = new QLabel("Gestión de Médicos");
        labelTitulo->setAlignment(Qt::AlignCenter);
        labelTitulo->setStyleSheet(
            "font-size: 18px; "
            "font-weight: bold; "
            "color: black; "
            "padding: 10px;"
            );
        layoutPrincipal->addWidget(labelTitulo);

        // Sección de búsqueda
        QHBoxLayout* layoutBusqueda = new QHBoxLayout();
        layoutBusqueda->setSpacing(10);

        QLabel* labelBuscar = new QLabel("Buscar:");
        labelBuscar->setStyleSheet("color: black; font-weight: bold;");

        comboTipoBusqueda = new QComboBox();
        comboTipoBusqueda->addItem("ID");
        comboTipoBusqueda->addItem("Nombre");
        comboTipoBusqueda->addItem("Número de Identidad");
        comboTipoBusqueda->addItem("Especialidad");
        comboTipoBusqueda->setFixedSize(170, 35);
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

        // Botones de búsqueda
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
        labelResultados = new QLabel("Médicos:");
        labelResultados->setStyleSheet("color: black; font-weight: bold; font-size: 14px;");
        layoutPrincipal->addWidget(labelResultados);

        tablaMedicos = new QTableWidget();
        tablaMedicos->setColumnCount(7);
        QStringList headers = {"ID", "Nombre", "Especialidad", "Identidad", "Colegiación", "Teléfono", "Email"};
        tablaMedicos->setHorizontalHeaderLabels(headers);
        tablaMedicos->setSelectionBehavior(QAbstractItemView::SelectRows);
        tablaMedicos->setAlternatingRowColors(true);
        tablaMedicos->horizontalHeader()->setStretchLastSection(true);
        tablaMedicos->setStyleSheet(
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

        layoutPrincipal->addWidget(tablaMedicos, 1);

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

    QPushButton* BuscarMedicos::crearBotonSimple(const QString& texto, int ancho, int alto) {
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

    void BuscarMedicos::configurarEventos() {
        connect(btnBuscar, &QPushButton::clicked, this, &BuscarMedicos::buscarMedicos);
        connect(btnCargarTodos, &QPushButton::clicked, this, &BuscarMedicos::cargarTodosLosMedicos);
        connect(btnEditar, &QPushButton::clicked, this, &BuscarMedicos::editarMedicoSeleccionado);
        connect(btnEliminar, &QPushButton::clicked, this, &BuscarMedicos::eliminarMedicoSeleccionado);
        connect(btnCerrar, &QPushButton::clicked, this, &QDialog::close);
        connect(tablaMedicos, &QTableWidget::itemSelectionChanged, this, &BuscarMedicos::onMedicoSeleccionado);
        connect(lineEditBusqueda, &QLineEdit::returnPressed, this, &BuscarMedicos::buscarMedicos);
    }

    void BuscarMedicos::cargarTodosLosMedicos() {
        if (!gestor) return;

        try {
            // Asegúrate de que los datos están cargados
            gestor->cargarDatos();

            // Obtén TODOS los médicos
            std::vector<Medico*> todos = gestor->obtenerTodos();
            actualizarTablaMedicos(todos);
            labelResultados->setText(
                QString("Médicos (%1 encontrados):").arg(todos.size())
                );

            // Reset selección
            idMedicoSeleccionado = -1;
            btnEditar->setEnabled(false);
            btnEliminar->setEnabled(false);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", QString("Error al cargar médicos: %1").arg(e.what()));
        }
    }

    void BuscarMedicos::buscarMedicos() {
        if (!gestor) return;

        QString criterio = lineEditBusqueda->text().trimmed();
        if (criterio.isEmpty()) {
            QMessageBox::information(this, "Información", "Por favor, ingrese un criterio de búsqueda.");
            return;
        }

        std::vector<Medico*> resultados;
        QString tipoBusqueda = comboTipoBusqueda->currentText();

        try {
            if (tipoBusqueda == "ID") {
                bool ok;
                int id = criterio.toInt(&ok);
                if (ok) {
                    Medico* medico = gestor->buscarMedico(id);
                    if (medico) {
                        resultados.push_back(medico);
                    }
                } else {
                    QMessageBox::warning(this, "Error", "El ID debe ser un número válido.");
                    return;
                }
            } else if (tipoBusqueda == "Nombre") {
                Medico* medico = gestor->buscarMedico(criterio.toStdString());
                if (medico) {
                    resultados.push_back(medico);
                }
            } else if (tipoBusqueda == "Número de Identidad") {
                bool ok;
                int identidad = criterio.toInt(&ok);
                if (ok) {
                    Medico* medico = gestor->buscarMedicoPorIdentidad(identidad);
                    if (medico) {
                        resultados.push_back(medico);
                    }
                } else {
                    QMessageBox::warning(this, "Error", "El número de identidad debe ser válido.");
                    return;
                }
            } else if (tipoBusqueda == "Especialidad") {
                resultados = gestor->buscarPorEspecialidad(criterio.toStdString());
            }

            actualizarTablaMedicos(resultados);
            labelResultados->setText(QString("Resultados (%1 encontrados):").arg(resultados.size()));

            // Limpiar selección
            idMedicoSeleccionado = -1;
            btnEditar->setEnabled(false);
            btnEliminar->setEnabled(false);

            if (resultados.empty()) {
                QMessageBox::information(this, "Sin resultados", "No se encontraron médicos que coincidan con el criterio.");
            }
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", QString("Error durante la búsqueda: %1").arg(e.what()));
        }
    }

    void BuscarMedicos::actualizarTablaMedicos(const std::vector<Medico*>& medicos) {
        tablaMedicos->setRowCount(medicos.size());

        for (size_t i = 0; i < medicos.size(); ++i) {
            const Medico* m = medicos[i];
            if (!m) continue;

            tablaMedicos->setItem(i, 0, new QTableWidgetItem(QString::number(m->getID())));
            tablaMedicos->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m->getNombre())));
            tablaMedicos->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m->getEspecialidad())));
            tablaMedicos->setItem(i, 3, new QTableWidgetItem(QString::number(m->getNumIdentidad())));
            tablaMedicos->setItem(i, 4, new QTableWidgetItem(QString::number(m->getNumColegiacion())));
            tablaMedicos->setItem(i, 5, new QTableWidgetItem(QString::number(m->getNumTelefono())));
            tablaMedicos->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(m->getEmail())));
        }

        tablaMedicos->resizeColumnsToContents();
    }

    void BuscarMedicos::onMedicoSeleccionado() {
        int filaSeleccionada = tablaMedicos->currentRow();
        if (filaSeleccionada >= 0) {
            QTableWidgetItem* itemID = tablaMedicos->item(filaSeleccionada, 0);
            if (itemID) {
                idMedicoSeleccionado = itemID->text().toInt();
                btnEditar->setEnabled(true);
                btnEliminar->setEnabled(true);
            }
        } else {
            idMedicoSeleccionado = -1;
            btnEditar->setEnabled(false);
            btnEliminar->setEnabled(false);
        }
    }

    void BuscarMedicos::editarMedicoSeleccionado() {
        if (idMedicoSeleccionado == -1) {
            QMessageBox::warning(this, "Error", "No hay ningún médico seleccionado.");
            return;
        }

        // Buscar el médico actualizado
        Medico* medico = gestor->buscarMedico(idMedicoSeleccionado);
        if (!medico) {
            QMessageBox::warning(this, "Error", "No se pudo encontrar el médico seleccionado.");
            return;
        }

        mostrarDialogoEdicion(medico);
    }

    void BuscarMedicos::eliminarMedicoSeleccionado() {
        if (idMedicoSeleccionado == -1) {
            QMessageBox::warning(this, "Error", "No hay ningún médico seleccionado.");
            return;
        }

        // Buscar el médico actualizado
        Medico* medico = gestor->buscarMedico(idMedicoSeleccionado);
        if (!medico) {
            QMessageBox::warning(this, "Error", "No se pudo encontrar el médico seleccionado.");
            return;
        }

        QMessageBox::StandardButton respuesta = QMessageBox::question(
            this,
            "Confirmar Eliminación",
            QString("¿Está seguro de que desea marcar como no disponible al médico %1?\n(No se puede eliminar completamente con los métodos actuales)")
                .arg(QString::fromStdString(medico->getNombre())),
            QMessageBox::Yes | QMessageBox::No
            );

        if (respuesta == QMessageBox::Yes) {
            try {
                // Como no tenemos eliminarMedico(), marcar como ocupado (no disponible)
                gestor->marcarOcupado(idMedicoSeleccionado);
                QMessageBox::information(this, "Éxito", "Médico marcado como no disponible.");

                // Limpiar selección antes de recargar
                idMedicoSeleccionado = -1;
                btnEditar->setEnabled(false);
                btnEliminar->setEnabled(false);
                // Recargar la lista
                cargarTodosLosMedicos();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Error al marcar médico como no disponible: %1").arg(e.what()));
            }
        }
    }

    void BuscarMedicos::mostrarDialogoEdicion(Medico* medico) {
        QDialog dialog(this);
        dialog.setWindowTitle("Editar Médico");
        dialog.setFixedSize(500, 450);
        dialog.setStyleSheet("QDialog { background-color: white; color: black; }");

        QFormLayout* layout = new QFormLayout(&dialog);

        // Campos de edición con estilo simple
        QLineEdit* editNombre = new QLineEdit(QString::fromStdString(medico->getNombre()));
        QLineEdit* editEspecialidad = new QLineEdit(QString::fromStdString(medico->getEspecialidad()));
        QLineEdit* editFechaNac = new QLineEdit(QString::fromStdString(medico->getFechaNacimiento()));
        QLineEdit* editIdentidad = new QLineEdit(QString::number(medico->getNumIdentidad()));
        QLineEdit* editColegiacion = new QLineEdit(QString::number(medico->getNumColegiacion()));
        QLineEdit* editTelefono = new QLineEdit(QString::number(medico->getNumTelefono()));
        QLineEdit* editEmail = new QLineEdit(QString::fromStdString(medico->getEmail()));

        // ComboBox para estado (disponible/ocupado)
        QComboBox* comboEstado = new QComboBox();
        comboEstado->addItem("Disponible");
        comboEstado->addItem("Ocupado");
        comboEstado->setCurrentText(medico->estaDisponible() ? "Disponible" : "Ocupado");

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
        editEspecialidad->setStyleSheet(estiloLineEdit);
        editFechaNac->setStyleSheet(estiloLineEdit);
        editIdentidad->setStyleSheet(estiloLineEdit);
        editColegiacion->setStyleSheet(estiloLineEdit);
        editTelefono->setStyleSheet(estiloLineEdit);
        editEmail->setStyleSheet(estiloLineEdit);
        comboEstado->setStyleSheet(
            "QComboBox { "
            "   background-color: white; "
            "   color: black; "
            "   border: 2px solid #ccc; "
            "   border-radius: 5px; "
            "   padding: 5px; "
            "}"
            );

        layout->addRow("Nombre:", editNombre);
        layout->addRow("Especialidad:", editEspecialidad);
        layout->addRow("Fecha de Nacimiento:", editFechaNac);
        layout->addRow("Número de Identidad:", editIdentidad);
        layout->addRow("Número de Colegiación:", editColegiacion);
        layout->addRow("Teléfono:", editTelefono);
        layout->addRow("Email:", editEmail);
        layout->addRow("Estado:", comboEstado);

        // Botones simples
        QHBoxLayout* layoutBotones = new QHBoxLayout();
        QPushButton* btnGuardar = crearBotonSimple("Guardar", 100, 35);
        QPushButton* btnCancelar = crearBotonSimple("Cancelar", 100, 35);

        layoutBotones->addWidget(btnGuardar);
        layoutBotones->addWidget(btnCancelar);
        layout->addRow(layoutBotones);

        connect(btnGuardar, &QPushButton::clicked, [&]() {
            // Validar datos
            if (!validarDatos(editNombre->text(), editEspecialidad->text(), editFechaNac->text(),
                              editEmail->text(), editTelefono->text(), editIdentidad->text(),
                              editColegiacion->text())) {
                return;
            }

            try {
                // Crear un médico actualizado con los nuevos datos
                Medico medicoActualizado(
                    medico->getID(),
                    editColegiacion->text().toInt(),
                    editIdentidad->text().toInt(),
                    editTelefono->text().toInt(),
                    editNombre->text().toStdString(),
                    editEspecialidad->text().toStdString(),
                    editFechaNac->text().toStdString(),
                    editEmail->text().toStdString(),
                    comboEstado->currentText() == "Disponible"
                    );

                // Actualizar el médico usando el método de edición
                if (gestor->editarMedico(medico->getID(), medicoActualizado)) {
                    QMessageBox::information(&dialog, "Éxito", "Datos del médico actualizados correctamente.");

                    // Actualizar el ID seleccionado por si cambió
                    idMedicoSeleccionado = medicoActualizado.getID();

                    // Recargar la tabla
                    cargarTodosLosMedicos();
                    dialog.accept();
                } else {
                    QMessageBox::warning(&dialog, "Error", "No se pudo actualizar el médico.");
                }
            } catch (const std::exception& e) {
                QMessageBox::critical(&dialog, "Error", QString("Error al actualizar médico: %1").arg(e.what()));
            }
        });

        connect(btnCancelar, &QPushButton::clicked, &dialog, &QDialog::reject);

        dialog.exec();
    }

    bool BuscarMedicos::validarDatos(const QString& nombre, const QString& especialidad,
                                     const QString& fechaNacimiento, const QString& email,
                                     const QString& telefono, const QString& identidad,
                                     const QString& colegiacion) {
        if (nombre.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Error", "El nombre no puede estar vacío.");
            return false;
        }

        if (especialidad.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Error", "La especialidad no puede estar vacía.");
            return false;
        }

        if (fechaNacimiento.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Error", "La fecha de nacimiento no puede estar vacía.");
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

        // Validar colegiación
        colegiacion.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "El número de colegiación debe ser un número válido.");
            return false;
        }

        return true;
    }
