#include "BuscarMedic.h"
#include <QRegularExpression>

BuscarMedic::BuscarMedic(QWidget* parent)
    : QDialog(parent), gestor(new gestionMedica()), idMedicoSeleccionado(-1) {
    configurarUI();
    configurarEventos();
    cargarTodosLosMedicos();
}

BuscarMedic::~BuscarMedic() {
    delete gestor;
}

void BuscarMedic::configurarUI() {
    setWindowTitle("Buscar Médicos");
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
    tablaMedicos->setColumnCount(5);
    QStringList headers = {"ID", "Nombre", "Identidad", "Teléfono", "Email"};
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

QPushButton* BuscarMedic::crearBotonSimple(const QString& texto, int ancho, int alto) {
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

void BuscarMedic::configurarEventos() {
    connect(btnBuscar, &QPushButton::clicked, this, &BuscarMedic::buscarMedicos);
    connect(btnCargarTodos, &QPushButton::clicked, this, &BuscarMedic::cargarTodosLosMedicos);
    connect(btnEditar, &QPushButton::clicked, this, &BuscarMedic::editarMedicoSeleccionado);
    connect(btnEliminar, &QPushButton::clicked, this, &BuscarMedic::eliminarMedicoSeleccionado);
    connect(btnCerrar, &QPushButton::clicked, this, &QDialog::close);
    connect(tablaMedicos, &QTableWidget::itemSelectionChanged, this, &BuscarMedic::onMedicoSeleccionado);
    connect(lineEditBusqueda, &QLineEdit::returnPressed, this, &BuscarMedic::buscarMedicos);
}

void BuscarMedic::cargarTodosLosMedicos() {
    std::vector<Medico*> medicos = gestor->obtenerTodos();  // <- CAMBIO AQUÍ
    actualizarTablaMedicos(medicos);
    labelResultados->setText(QString("Médicos (%1 encontrados):").arg(medicos.size()));

    // Limpiar selección
    idMedicoSeleccionado = -1;
    btnEditar->setEnabled(false);
    btnEliminar->setEnabled(false);
}

void BuscarMedic::buscarMedicos() {
    QString criterio = lineEditBusqueda->text().trimmed();
    if (criterio.isEmpty()) {
        QMessageBox::information(this, "Información", "Por favor, ingrese un criterio de búsqueda.");
        return;
    }

    std::vector<Medico*> resultados;
    QString tipo = comboTipoBusqueda->currentText();

    try {
        if (tipo == "ID") {
            bool ok;
            int id = criterio.toInt(&ok);
            if (ok) {
                Medico* m = gestor->buscarMedico(id);
                if (m) resultados.push_back(m);
            } else {
                QMessageBox::warning(this, "Error", "El ID debe ser un número válido.");
                return;
            }
        } else if (tipo == "Nombre") {
            Medico* m = gestor->buscarMedico(criterio.toStdString());
            if (m) resultados.push_back(m);
        } else if (tipo == "Número de Identidad") {
            bool ok;
            int idn = criterio.toInt(&ok);
            if (ok) {
                Medico* m = gestor->buscarMedicoPorIdentidad(idn);
                if (m) resultados.push_back(m);
            } else {
                QMessageBox::warning(this, "Error", "El número de identidad debe ser válido.");
                return;
            }
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
    } catch (...) {
        QMessageBox::critical(this, "Error", "No se pudo realizar la búsqueda.");
    }
}

void BuscarMedic::actualizarTablaMedicos(const std::vector<Medico*>& medicos) {
    tablaMedicos->setRowCount(medicos.size());
    for (int i = 0; i < medicos.size(); ++i) {
        Medico* m = medicos[i];
        tablaMedicos->setItem(i, 0, new QTableWidgetItem(QString::number(m->getID())));
        tablaMedicos->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m->getNombre())));
        tablaMedicos->setItem(i, 2, new QTableWidgetItem(QString::number(m->getNumIdentidad())));
        tablaMedicos->setItem(i, 3, new QTableWidgetItem(QString::number(m->getNumTelefono())));
        tablaMedicos->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(m->getEmail())));
    }

    tablaMedicos->resizeColumnsToContents();
}

void BuscarMedic::onMedicoSeleccionado() {
    int fila = tablaMedicos->currentRow();
    if (fila >= 0) {
        QTableWidgetItem* item = tablaMedicos->item(fila, 0);
        if (item) {
            idMedicoSeleccionado = item->text().toInt();
            btnEditar->setEnabled(true);
            btnEliminar->setEnabled(true);
        }
    } else {
        idMedicoSeleccionado = -1;
        btnEditar->setEnabled(false);
        btnEliminar->setEnabled(false);
    }
}

void BuscarMedic::editarMedicoSeleccionado() {
    QMessageBox::information(this, "Editar", "Función editar aún no implementada.");
}

void BuscarMedic::eliminarMedicoSeleccionado() {
    QMessageBox::information(this, "Eliminar", "Función eliminar aún no implementada.");
}
