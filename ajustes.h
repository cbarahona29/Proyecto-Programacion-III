#ifndef AJUSTES_H
#define AJUSTES_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QWidget>
#include <QLineEdit>

class MenuAdmin; // Forward declaration

class Ajustes : public QMainWindow {
    Q_OBJECT

public:
    explicit Ajustes(MenuAdmin* menuAdmin, QWidget *parent = nullptr);

private slots:
    void crearCuentaDoctor();
    void crearCuentaRecepcionista();
    void eliminarCuentas();
    void cambiarContrasenaRecepcion();
    void regresarAlMenu();

private:
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(const QString& texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);

    // Widgets
    QLabel* labelTitulo;
    QPushButton* btnCrearCuentaDoctor;
    QPushButton* btnCrearCuentaRecepcionista;
    QPushButton* btnEliminarCuentas;
    QPushButton* btnCambiarContrasena;
    QPushButton* btnRegresar;

    // Referencias
    MenuAdmin* menuAdminWindow;
};

#endif // AJUSTES_H
