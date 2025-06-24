#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>
#include <QTextEdit> // Added for QTextEdit

// Forward declarations to avoid circular includes and speed up compilation
class MenuDr;
class MenuAdmin;
class MenuRecepcionista;

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login();

    // Destructor to clean up dynamically allocated menus
    ~Login();

    void cerrarSesion(); // Slot to return to login

private slots:
    void hacerLogin();

private:
    void configurarUI();
    void configurarUsuarios();
    void conectarEventos();
    void cargarCredencialesDesdeArchivos(); // New function for loading doctor credentials
    void mostrarMensaje(QString mensaje, bool exito);
    void abrirDashboard();

    QLineEdit* campoID;
    QLineEdit* campoPassword;
    QPushButton* botonLogin;
    QTextEdit* areaTexto; // Added QTextEdit

    // Stores username -> {password, role}
    QMap<QString, QPair<QString, QString>> usuarios;
    QString usuarioActual;
    QString tipoUsuarioActual;

    MenuDr* menuDr;
    MenuAdmin* menuAdmin;
    MenuRecepcionista* menuRecepcionista;
};

#endif // LOGIN_H
