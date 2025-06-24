#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMap>
#include <QString>
#include <utility>

class MenuDr;
class MenuAdmin;
class MenuRecepcionista;

class Login : public QMainWindow {
    Q_OBJECT

public:
    Login();
    void cerrarSesion();
    QString getUsuarioActual() const { return usuarioActual; }

private:
    void configurarUI();
    void configurarUsuarios();
    void conectarEventos();
    void hacerLogin();
    void mostrarMensaje(QString mensaje, bool exito);
    void abrirDashboard();
    void cargarCredencialesDesdeArchivos();  // ✅ NUEVA FUNCIÓN

    // UI
    QLineEdit* campoID;
    QLineEdit* campoPassword;
    QPushButton* botonLogin;
    QTextEdit* areaTexto;

    // Gestión de usuario
    QMap<QString, QPair<QString, QString>> usuarios; // ID -> (Password, Tipo)
    QString usuarioActual;
    QString tipoUsuarioActual;

    // Menús
    MenuDr* menuDr;
    MenuAdmin* menuAdmin;
    MenuRecepcionista* menuRecepcionista;
};

#endif // LOGIN_H

