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
#include <vector>


// Incluir las estructuras compartidas
#include "Estructuras.h"

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

private slots:
    void registrarPaciente();
    void buscarPaciente();
    void agendarCita();
    void buscarMedico();
    void mostrarFilaEspera();
    void salir();

private:
    void inicializarDatos();
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(QString texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);

    // Funciones auxiliares para mostrar información
    void mostrarInformacionPaciente(const Paciente& paciente);
    void mostrarInformacionMedico(const Medico& medico);
    void mostrarFormularioRegistroPaciente();

    // Widgets
    QLabel* labelBienvenida;
    QPushButton* btnRegistrarPaciente;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnAgendarCita;
    QPushButton* btnBuscarMedico;
    QPushButton* btnFilaEspera;
    QPushButton* btnSalir;

    // Referencias
    Login* loginWindow;
    RegistroPaciente* ventanaRegistro;

    // Datos
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<CitaAgendada> citasAgendadas;
};

#endif // MENURECEPCIONISTA_H
