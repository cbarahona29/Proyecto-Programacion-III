#ifndef MENUADMIN_H
#define MENUADMIN_H

#include <QtWidgets>
#include "registropaciente.h"
#include "registromed.h"

class Login;

class MenuAdmin : public QMainWindow {
    Q_OBJECT

public:
    MenuAdmin(Login* login);
    void setUsuario(const QString& usuario);

private slots:
    void registrarPaciente();
    void buscarPacientes();
    void registrarMedico();
    void buscarMedicos();
    void mostrarFilaEspera();
    void mostrarAjustes();
    void salir();

private:
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(QString texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);

    // UI Components
    QLabel* labelBienvenida;
    QPushButton* btnRegistrarPaciente;
    QPushButton* btnBuscarPacientes;
    QPushButton* btnRegistrarMedico;
    QPushButton* btnBuscarMedicos;
    QPushButton* btnFilaEspera;
    QPushButton* btnAjustes;
    QPushButton* btnSalir;

    // Ventanas
    Login* loginWindow;
    RegistroPaciente* ventanaRegistroPaciente;
    RegistroMed* ventanaRegistroMedico;
};

#endif // MENUADMIN_H
