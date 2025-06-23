#ifndef AJUSTES_H
#define AJUSTES_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class MenuAdmin;

class Ajustes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ajustes(MenuAdmin* menuAdmin, QWidget *parent = nullptr);

private slots:
    void abrirCrearCuentas();
    void abrirCambiarContrasena();
    void abrirEliminarCuentas();
    void regresarAlMenu();

private:
    void configurarUI();
    void configurarEventos();
    QPushButton* crearBoton(const QString& texto);
    QMessageBox* crearMensaje(const QString& titulo, const QString& texto, QMessageBox::Icon icono);

    // Elementos de la interfaz
    QLabel* labelTitulo;
    QPushButton* btnCrearCuentas;
    QPushButton* btnCambiarContrasena;
    QPushButton* btnEliminarCuentas;
    QPushButton* btnRegresar;

    MenuAdmin* menuAdminWindow;
};

#endif // AJUSTES_H
