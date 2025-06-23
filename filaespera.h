#ifndef FILAESPERA_H
#define FILAESPERA_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QDate>
#include <vector>
#include <map>
#include <string>

// Incluir las estructuras compartidas
#include "Estructuras.h"

class FilaEspera : public QDialog
{
    Q_OBJECT
public:
    explicit FilaEspera(QWidget *parent = nullptr);
    ~FilaEspera();

    // Método para establecer las citas agendadas
    void setCitasAgendadas(const std::vector<CitaAgendada>& citas);

    // Método para mostrar la ventana de fila de espera
    void mostrarFilaEspera();

private slots:
    void cerrarVentana();

private:
    // Elementos de la interfaz
    QVBoxLayout* layoutPrincipal;
    QLabel* titulo;
    QListWidget* listaEspera;
    QLabel* infoTotal;
    QPushButton* btnCerrar;

    // Datos
    std::vector<CitaAgendada> citasAgendadas;
    std::vector<std::map<std::string, std::string>> filaEspera;

    // Métodos privados
    void configurarUI();
    void configurarEstilos();
    void configurarEventos();
    void actualizarFilaEspera();
    void llenarListaEspera();
    void mostrarFilaVacia();
};

#endif // FILAESPERA_H
