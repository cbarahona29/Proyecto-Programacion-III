#ifndef MENURECEPCIONISTA_H
#define MENURECEPCIONISTA_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QListWidget>
#include <QGroupBox>
#include <QDebug>
#include <QInputDialog>
#include <QLineEdit>
#include "BuscarMedic.h"


// Forward declarations
class Login;
class RegistroPaciente;
class FilaEspera;

class MenuRecepcionista : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuRecepcionista(Login* login);
    void setUsuario(const QString& usuario);

signals:
    // Señales para comunicarse con otras clases que manejarán la lógica
    void buscarPacienteSolicitado();
    void agendarCitaSolicitado();
    void buscarMedicoSolicitado();

private slots:
    void abrirVentanaRegistro();
    void abrirVentanaBusquedaPaciente();
    void abrirVentanaAgendarCita();
    void abrirVentanaBusquedaMedico();
    void abrirVentanaFilaEspera();
    void salir();

private:
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(QString texto);
    BuscarMedic* ventanaBuscarMedico = nullptr;


    // Widgets principales
    QLabel* labelBienvenida;
    QPushButton* btnRegistrarPaciente;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnAgendarCita;
    QPushButton* btnBuscarMedico;
    QPushButton* btnFilaEspera;
    QPushButton* btnSalir;

    // Referencias a otras ventanas
    Login* loginWindow;
    RegistroPaciente* ventanaRegistro;
};

#endif // MENURECEPCIONISTA_H
