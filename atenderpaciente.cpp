#include "AtenderPaciente.h"

AtenderPaciente::AtenderPaciente(const std::vector<QString>& pacientes, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Atender Paciente");
    setFixedSize(400, 200);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("Seleccione el paciente a atender:");
    layout->addWidget(label);

    comboBox = new QComboBox();
    for (const auto& p : pacientes) {
        comboBox->addItem(p);
    }
    layout->addWidget(comboBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* btnAtender = new QPushButton("Atender");
    QPushButton* btnCancelar = new QPushButton("Cancelar");
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnAtender);
    buttonLayout->addWidget(btnCancelar);
    layout->addLayout(buttonLayout);

    connect(btnAtender, &QPushButton::clicked, this, &QDialog::accept);
    connect(btnCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

QString AtenderPaciente::getPacienteSeleccionado() const {
    return comboBox->currentText();
}
