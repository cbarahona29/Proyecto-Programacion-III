#ifndef MENUDR_H
#define MENUDR_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox> // For QMessageBox
#include <QInputDialog> // For QInputDialog
#include <QTextEdit> // For QTextEdit
#include <QGroupBox> // For QGroupBox
#include <QDateTime> // For QDateTime
#include <map>       // For std::map
#include <vector>    // For std::vector
#include <string>    // For std::string

// Forward declarations
class Login;
class BuscarPacientes; // This is the external dialog

class MenuDr : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuDr(Login* login, QWidget *parent = nullptr);
    ~MenuDr();
    void setUsuario(const QString& usuario);

private slots:
    void mostrarExpedientes();
    void buscarPaciente(); // Now correctly declared once
    void mostrarFilaEspera();
    void atenderPaciente();
    void salir();

    // New private slots/functions from your provided code
    void mostrarExpedienteDetallado(const QString& idPaciente);
    QString generarHistorialConsultas(const QString& idPaciente);
    void mostrarInformacionPaciente(const std::map<std::string, std::string>& paciente);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);
    void realizarConsulta(const std::map<std::string, std::string>& paciente);


private:
    void configurarUI();
    QPushButton* crearBoton(const QString& texto);
    void configurarEventos();

    Login* loginWindow;
    BuscarPacientes* ventanaBuscarPacientes; // Pointer to the external BuscarPacientes dialog

    QLabel* labelBienvenida;
    QPushButton* btnExpedientesClinicos;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnFilaEspera;
    QPushButton* btnAtenderPaciente;
    QPushButton* btnSalir;

    // Data for demonstration purposes (you might have a dedicated class for patient management)
    std::vector<std::map<std::string, std::string>> pacientes;
};

#endif // MENUDR_H
