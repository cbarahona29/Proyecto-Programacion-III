#ifndef MENUADMIN_H
#define MENUADMIN_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>


class Login;
class RegistroPaciente;
class RegistroMed;
class Ajustes;
class FilaEspera;
class guardaCuentas;
class BuscarPacientes;
class BuscarMedic;

class MenuAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuAdmin(Login* login);
    ~MenuAdmin();

    void setUsuario(const QString& usuario);
    void setGestorCuentas(guardaCuentas* gestor);

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
    QPushButton* crearBoton(const QString& texto);

    // Punteros a ventanas
    Login* loginWindow;
    RegistroPaciente* ventanaRegistroPaciente = nullptr;
    RegistroMed* ventanaRegistroMedico = nullptr;
    Ajustes* ventanaAjustes = nullptr;
    FilaEspera* ventanaFilaEspera = nullptr;
    BuscarPacientes* ventanaBuscarPacientes = nullptr;
    BuscarMedic* ventanaBuscarMedicos = nullptr;

    // Controles UI
    QLabel* labelBienvenida;
    QPushButton* btnRegistrarPaciente;
    QPushButton* btnBuscarPacientes;
    QPushButton* btnRegistrarMedico;
    QPushButton* btnBuscarMedicos;
    QPushButton* btnFilaEspera;
    QPushButton* btnAjustes;
    QPushButton* btnSalir;

    // Gestor de cuentas
    guardaCuentas* gestorCuentas;
};

#endif // MENUADMIN_H
