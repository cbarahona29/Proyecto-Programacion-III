#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <map>
#include <string>

class MenuDr;
class MenuAdmin;
class MenuRecepcionista;

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login();
    void cerrarSesion();

private:
    void configurarUI();
    void configurarUsuarios();
    void conectarEventos();
    void hacerLogin();
    void mostrarMensaje(QString mensaje, bool exito);
    void abrirDashboard();

    // Widgets
    QLineEdit* campoID;
    QLineEdit* campoPassword;
    QPushButton* botonLogin;
    QTextEdit* areaTexto;

    // Datos
    std::map<std::string, std::pair<std::string, std::string>> usuarios; // {usuario: {contraseña, tipo}}
    QString usuarioActual;
    QString tipoUsuarioActual;

    // Referencias a los menús
    MenuDr* menuDr;
    MenuAdmin* menuAdmin;
    MenuRecepcionista* menuRecepcionista;
};

#endif // LOGIN_H
