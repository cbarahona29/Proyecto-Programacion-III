#ifndef ATENDERPACIENTE_H
#define ATENDERPACIENTE_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <vector>

class AtenderPaciente : public QDialog {
    Q_OBJECT

public:
    explicit AtenderPaciente(const std::vector<QString>& pacientes, QWidget* parent = nullptr);
    QString getPacienteSeleccionado() const;

private:
    QComboBox* comboBox;
};

#endif

