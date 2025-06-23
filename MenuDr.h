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
    MenuDr(Login* login);
    void setUsuario(const QString& usuario);

private slots:
    void mostrarExpedientes();
    void buscarPaciente();
    void mostrarFilaEspera();
    void atenderPaciente();
    void salir();
    void realizarConsulta(const std::map<std::string, std::string>& paciente);
    void mostrarExpedienteDetallado(const QString& idPaciente);


private:
    void configurarUI();
    QPushButton* crearBoton(QString texto);
    void configurarEventos();
    void inicializarDatos();
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);
    void mostrarInformacionPaciente(const std::map<std::string, std::string>& paciente);
    QString generarHistorialConsultas(const QString& idPaciente);

    // UI Components
    QTextEdit* campoSuperior;
    QPushButton* btnExpedientesClinicos;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnFilaEspera;
    QPushButton* btnAtenderPaciente;
    QPushButton* btnSalir;
    QLabel* labelBienvenida;

    // Data
    Login* loginWindow;
    std::vector<std::map<std::string, std::string>> pacientes;
    std::vector<std::string> filaEspera;

    struct Consulta {
        std::string idPaciente;
        std::string nombrePaciente;
        std::string fecha;
        std::string sintomas;
        std::string diagnostico;
        std::string tratamiento;
        std::string observaciones;
    };
    std::vector<Consulta> historialConsultas;
};

#endif // MENUDR_H
