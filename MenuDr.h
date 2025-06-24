#ifndef MENUDR_H
#define MENUDR_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

// Forward declarations
class Login;
class BuscarPacientes;

class MenuDr : public QMainWindow {
    Q_OBJECT

public:
    explicit MenuDr(Login* login, QWidget *parent = nullptr);
    ~MenuDr() override;

    void setUsuario(const QString& usuario);

private slots:
    void mostrarExpedientes();
    void buscarPaciente();
    void mostrarFilaEspera();
    void atenderPaciente();
    void salir();

private:
    void configurarUI();
    QPushButton* crearBoton(const QString& texto);
    void configurarEventos();
    void limpiarVentanasHijas();

    // Componentes de la UI
    QPushButton* btnExpedientesClinicos;
    QPushButton* btnBuscarPaciente;
    QPushButton* btnFilaEspera;
    QPushButton* btnAtenderPaciente;
    QPushButton* btnSalir;
    QLabel* labelBienvenida;

    // Ventanas hijas
    BuscarPacientes* ventanaBuscarPacientes;

    // Referencia a la ventana de login
    Login* loginWindow;
};

#endif // MENUDR_H
