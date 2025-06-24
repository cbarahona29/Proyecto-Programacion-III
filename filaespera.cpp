#include "FilaEspera.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>

FilaEspera::FilaEspera(QWidget *parent) : QDialog(parent) {
    configurarUI();
}

void FilaEspera::configurarUI() {
    setWindowTitle("Fila de Espera");
    setFixedSize(500, 400);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(15);

    // Título
    QLabel* titulo = new QLabel("Lista de Pacientes en Espera");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 16px; font-weight: bold;");
    layoutPrincipal->addWidget(titulo);

    // Lista de espera
    listaEspera = new QListWidget();
    listaEspera->setStyleSheet(
        "QListWidget {"
        "   background-color: white;"
        "   border: 1px solid #ccc;"
        "   border-radius: 5px;"
        "}"
        "QListWidget::item {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #eee;"
        "}"
        );
    layoutPrincipal->addWidget(listaEspera);

    // Información total
    infoTotal = new QLabel();
    infoTotal->setAlignment(Qt::AlignCenter);
    infoTotal->setStyleSheet("font-size: 12px; color: #666;");
    layoutPrincipal->addWidget(infoTotal);

    // Botón cerrar
    QPushButton* btnCerrar = new QPushButton("Cerrar");
    btnCerrar->setFixedWidth(100);
    btnCerrar->setStyleSheet(
        "QPushButton {"
        "   background-color: #e8e8e8;"
        "   border: 1px solid #999;"
        "   border-radius: 5px;"
        "   padding: 8px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d8d8d8;"
        "}"
        );

    QHBoxLayout* layoutBoton = new QHBoxLayout();
    layoutBoton->addStretch();
    layoutBoton->addWidget(btnCerrar);
    layoutBoton->addStretch();

    layoutPrincipal->addLayout(layoutBoton);

    connect(btnCerrar, &QPushButton::clicked, this, &FilaEspera::cerrarVentana);
}

void FilaEspera::setCitasAgendadas(const std::vector<CitaAgendada>& citas) {
    citasAgendadas = citas;
}

void FilaEspera::llenarListaEspera() {
    listaEspera->clear();
    QString fechaHoy = QDate::currentDate().toString("yyyy-MM-dd");
    int contador = 0;

    for (const auto& cita : citasAgendadas) {
        if (cita.fecha == fechaHoy) {
            QString item = QString("#%1 - %2\nHora: %3 - Tipo: %4")
            .arg(++contador)
                .arg(cita.paciente)
                .arg(cita.hora)
                .arg(cita.tipo);

            QListWidgetItem* listItem = new QListWidgetItem(item);
            listItem->setSizeHint(QSize(0, 60));
            listaEspera->addItem(listItem);
        }
    }

    infoTotal->setText(QString("Total de pacientes esperando: %1").arg(contador));
}

void FilaEspera::mostrarFilaVacia() {
    listaEspera->clear();
    QListWidgetItem* item = new QListWidgetItem("La fila de espera está vacía");
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::NoItemFlags);
    listaEspera->addItem(item);
    infoTotal->setText("Total de pacientes esperando: 0");
}

void FilaEspera::mostrarFilaEspera() {
    if (citasAgendadas.empty()) {
        mostrarFilaVacia();
    } else {
        llenarListaEspera();
    }
    exec();
}

void FilaEspera::cerrarVentana() {
    accept();
}
