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

// Include headers for external dialogs you want to use
#include "BuscarMedic.h"      // Keep this include
#include "BuscarPacientes.h"  // Keep this include
#include "registropaciente.h" // Assuming this is for RegistroPaciente
#include "FilaEspera.h"       // Assuming this is for FilaEspera

// Forward declarations
class Login;

class MenuRecepcionista : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuRecepcionista(Login* login);
    void setUsuario(const QString& usuario);
    // Destructor to clean up dynamically allocated windows
    ~MenuRecepcionista();

signals:
    // These signals might be redundant if you directly open windows in slots,
    // but kept for now if you have other architecture considerations.
    void buscarPacienteSolicitado();
    void agendarCitaSolicitado();
    void buscarMedicoSolicitado();

private slots:
    void abrirVentanaRegistro();
    void abrirVentanaBusquedaPaciente(); // Will open BuscarPacientes dialog
    void abrirVentanaAgendarCita();      // Will open the Agendar Cita QDialog
    void abrirVentanaBusquedaMedico();   // Will open BuscarMedic dialog
    void abrirVentanaFilaEspera();       // Will open FilaEspera dialog
    void salir();

private:
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(QString texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono); // Helper for consistent messages

    // Widgets principales
    QLabel* labelBienvenida;
    QPushButton* btnRegistrarPaciente;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnAgendarCita;
    QPushButton* btnBuscarMedico;
    QPushButton* btnFilaEspera;
    QPushButton* btnSalir;

    // References to other windows, initialized to nullptr
    Login* loginWindow;
    RegistroPaciente* ventanaRegistro = nullptr;
    BuscarMedic* ventanaBuscarMedico = nullptr;      // Now directly managing BuscarMedic
    BuscarPacientes* ventanaBuscarPaciente = nullptr; // Now directly managing BuscarPacientes
};

#endif // MENURECEPCIONISTA_H
