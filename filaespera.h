#ifndef FILAESPERA_H
#define FILAESPERA_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <vector>

struct CitaAgendada {
    QString paciente;
    QString medico;
    QString fecha;
    QString hora;
    QString tipo;
};

class FilaEspera : public QDialog {
    Q_OBJECT

public:
    explicit FilaEspera(QWidget *parent = nullptr);
    void setCitasAgendadas(const std::vector<CitaAgendada>& citas);
    void mostrarFilaEspera();

private slots:
    void cerrarVentana();

private:
    void configurarUI();
    void llenarListaEspera();
    void mostrarFilaVacia();

    QListWidget* listaEspera;
    QLabel* infoTotal;
    std::vector<CitaAgendada> citasAgendadas;
};

#endif // FILAESPERA_H
