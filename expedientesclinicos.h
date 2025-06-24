#ifndef EXPEDIENTESCLINICOS_H
#define EXPEDIENTESCLINICOS_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <map>
#include <string>

class ExpedientesClinicos : public QDialog {
    Q_OBJECT

public:
    explicit ExpedientesClinicos(QWidget* parent = nullptr);
    void setPaciente(const std::map<std::string, std::string>& paciente);
    void setHistorialHTML(const QString& historial);

private:
    QTextEdit* txtHistorial;
    QLabel* lblInfo;
    QPushButton* btnNuevaConsulta;
    QPushButton* btnCerrar;
};

#endif
