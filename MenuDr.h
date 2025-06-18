#ifndef MENUDR_H
#define MENUDR_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <vector>
#include <map>

// Forward declaration
class Login;

class MenuDr : public QMainWindow {
    Q_OBJECT

public:
    QTextEdit* campoSuperior;
    QPushButton* btnAgregarPaciente;
    QPushButton* btnExpedientesClinicos;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnFilaEspera;
    QPushButton* btnAtenderPaciente;
    QPushButton* btnSalir;
    QLabel* labelBienvenida;

    Login* loginWindow;
    std::vector<std::map<std::string, std::string>> pacientes;
    std::vector<std::string> filaEspera;

    MenuDr(Login* login);
    void configurarUI();
    QPushButton* crearBoton(QString texto);
    void configurarEventos();
    void setUsuario(const QString& usuario);
    void inicializarDatos();
    void agregarPaciente();
    void mostrarExpedientes();
    void buscarPaciente();
    void mostrarFilaEspera();
    void atenderPaciente();
    void salir();

private:
    // ... otras declaraciones existentes ...
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);
};

#endif // MENUDR_H
