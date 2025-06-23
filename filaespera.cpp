#include "FilaEspera.h"
#include <QListWidgetItem>
#include <QSize>

FilaEspera::FilaEspera(QWidget *parent)
    : QDialog(parent)
{
    configurarUI();
    configurarEstilos();
    configurarEventos();
}

FilaEspera::~FilaEspera()
{
    // El destructor se encarga automáticamente de la limpieza
}

void FilaEspera::configurarUI()
{
    setWindowTitle("Fila de Espera");
    setFixedSize(600, 400);

    // Layout principal
    layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(15);

    // Título
    titulo = new QLabel("Lista de Pacientes en Espera");
    titulo->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(titulo);

    // Lista de espera
    listaEspera = new QListWidget();
    layoutPrincipal->addWidget(listaEspera);

    // Información total
    infoTotal = new QLabel();
    infoTotal->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(infoTotal);

    // Botón cerrar
    btnCerrar = new QPushButton("Cerrar");
    btnCerrar->setFixedWidth(100);

    QHBoxLayout* layoutBoton = new QHBoxLayout();
    layoutBoton->addStretch();
    layoutBoton->addWidget(btnCerrar);
    layoutBoton->addStretch();

    layoutPrincipal->addLayout(layoutBoton);
}

void FilaEspera::configurarEstilos()
{
    setStyleSheet(
        "QDialog {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "}"
        "QLabel {"
        "   color: black;"
        "}"
        "QListWidget {"
        "   background-color: white;"
        "   color: black;"
        "   border: 1px solid #ccc;"
        "   border-radius: 5px;"
        "   font-size: 12px;"
        "}"
        "QListWidget::item {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #eee;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #e3f2fd;"
        "   color: black;"
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

    // Estilo específico para el título
    titulo->setStyleSheet(
        "font-size: 16px; "
        "font-weight: bold; "
        "color: black; "
        "margin: 10px;"
        );
}

void FilaEspera::configurarEventos()
{
    connect(btnCerrar, &QPushButton::clicked, this, &FilaEspera::cerrarVentana);
}

void FilaEspera::setCitasAgendadas(const std::vector<CitaAgendada>& citas)
{
    citasAgendadas = citas;
    actualizarFilaEspera();
}

void FilaEspera::actualizarFilaEspera()
{
    // Limpiar la fila de espera anterior
    filaEspera.clear();

    // Filtrar citas de hoy y crear la fila de espera
    QString fechaHoy = QDate::currentDate().toString("yyyy-MM-dd");
    int posicion = 1;

    for (const auto& cita : citasAgendadas) {
        if (cita.fecha == fechaHoy) {
            std::map<std::string, std::string> pacienteEspera;
            pacienteEspera["posicion"] = std::to_string(posicion);
            pacienteEspera["nombre"] = cita.paciente.toStdString();

            // Generar ID simple basado en la posición
            std::string idStr = std::to_string(posicion);
            while (idStr.length() < 3) {
                idStr = "0" + idStr;
            }
            pacienteEspera["id"] = idStr;

            pacienteEspera["hora_llegada"] = cita.hora.toStdString();
            pacienteEspera["tipo_cita"] = cita.tipo.toStdString();

            filaEspera.push_back(pacienteEspera);
            posicion++;
        }
    }
}

void FilaEspera::llenarListaEspera()
{
    // Limpiar lista anterior
    listaEspera->clear();

    for (const auto& paciente : filaEspera) {
        QString item = QString(" #%1 - %2\n"
                               "    ID: %3\n"
                               "    Llegada: %4\n"
                               "    Tipo: %5")
                           .arg(QString::fromStdString(paciente.at("posicion")))
                           .arg(QString::fromStdString(paciente.at("nombre")))
                           .arg(QString::fromStdString(paciente.at("id")))
                           .arg(QString::fromStdString(paciente.at("hora_llegada")))
                           .arg(QString::fromStdString(paciente.at("tipo_cita")));

        QListWidgetItem* listItem = new QListWidgetItem(item);
        listItem->setSizeHint(QSize(0, 80)); // Altura fija para cada item
        listaEspera->addItem(listItem);
    }

    // Actualizar información total
    QString infoTexto = QString("Total de pacientes esperando: %1").arg(filaEspera.size());
    infoTotal->setText(infoTexto);
    infoTotal->setStyleSheet("font-size: 12px; color: #666; margin: 5px;");
}

void FilaEspera::mostrarFilaVacia()
{
    // Limpiar lista
    listaEspera->clear();

    // Crear un widget para mostrar mensaje de fila vacía
    QListWidgetItem* item = new QListWidgetItem("La fila de espera está vacía");
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::NoItemFlags); // Hacer que no sea seleccionable
    listaEspera->addItem(item);

    // Aplicar estilo especial al mensaje
    listaEspera->setStyleSheet(listaEspera->styleSheet() +
                               "QListWidget::item:first {"
                               "   font-size: 14px;"
                               "   color: #666;"
                               "   font-style: italic;"
                               "   padding: 50px;"
                               "}");

    // Actualizar información total
    infoTotal->setText("Total de pacientes esperando: 0");
    infoTotal->setStyleSheet("font-size: 12px; color: #666; margin: 5px;");
}

void FilaEspera::mostrarFilaEspera()
{
    // Actualizar los datos antes de mostrar
    actualizarFilaEspera();

    if (filaEspera.empty()) {
        mostrarFilaVacia();
    } else {
        llenarListaEspera();
    }

    // Mostrar la ventana
    exec();
}

void FilaEspera::cerrarVentana()
{
    accept();
}
