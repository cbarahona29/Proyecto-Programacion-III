#ifndef MENUADMIN_H
#define MENUADMIN_H
#include <QtWidgets>
#include <vector>
#include <map>
#include <string>
#include "registropaciente.h"
#include "registromed.h"
#include "Ajustes.h"
#include "FilaEspera.h" // Agregar este include

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
    // Métodos de configuración
    void configurarUI();
    void configurarEventos();
    void inicializarDatos();

    // Métodos de utilidad
    QPushButton* crearBoton(QString texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);
    void mostrarInformacionPaciente(const std::map<std::string, std::string>& paciente);
    void mostrarInformacionMedico(const std::map<std::string, std::string>& medico);

    // Componentes de UI
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
    Ajustes* ventanaAjustes;
    FilaEspera* ventanaFilaEspera; // Agregar esta línea

    // Datos
    std::vector<std::map<std::string, std::string>> pacientes;
    std::vector<std::map<std::string, std::string>> medicos;
    std::vector<std::map<std::string, std::string>> filaEspera;
};

#endif // MENUADMIN_H
