#ifndef MENURECEPCIONISTA_H
#define MENURECEPCIONISTA_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>

class Login;

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
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(QString texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);

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
};

#endif // MENURECEPCIONISTA_H
