#include "ExpedientesClinicos.h"
#include <QDateTime>

ExpedientesClinicos::ExpedientesClinicos(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Expediente Clínico");
    setFixedSize(800, 600);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);

    QGroupBox* groupInfo = new QGroupBox("Información del Paciente");
    QVBoxLayout* layoutInfo = new QVBoxLayout(groupInfo);
    lblInfo = new QLabel();
    layoutInfo->addWidget(lblInfo);
    layoutPrincipal->addWidget(groupInfo);

    QGroupBox* groupHistorial = new QGroupBox("Historial de Consultas Médicas");
    QVBoxLayout* layoutHistorial = new QVBoxLayout(groupHistorial);
    txtHistorial = new QTextEdit();
    txtHistorial->setReadOnly(true);
    layoutHistorial->addWidget(txtHistorial);
    layoutPrincipal->addWidget(groupHistorial);

    QHBoxLayout* layoutBotones = new QHBoxLayout();
    btnNuevaConsulta = new QPushButton("Nueva Consulta");
    btnCerrar = new QPushButton("Cerrar");
    layoutBotones->addWidget(btnNuevaConsulta);
    layoutBotones->addStretch();
    layoutBotones->addWidget(btnCerrar);
    layoutPrincipal->addLayout(layoutBotones);

    connect(btnCerrar, &QPushButton::clicked, this, &QDialog::accept);
}

void ExpedientesClinicos::setPaciente(const std::map<std::string, std::string>& paciente) {
    QString info = QString("Nombre: %1\nID: %2\nEdad: %3 años\nTeléfono: %4\nDirección: %5\nFecha de registro: %6")
                       .arg(QString::fromStdString(paciente.at("nombre")))
                       .arg(QString::fromStdString(paciente.at("id")))
                       .arg(QString::fromStdString(paciente.at("edad")))
                       .arg(QString::fromStdString(paciente.at("telefono")))
                       .arg(QString::fromStdString(paciente.at("direccion")))
                       .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
    lblInfo->setText(info);
}

void ExpedientesClinicos::setHistorialHTML(const QString& historial) {
    txtHistorial->setHtml(historial);
}
