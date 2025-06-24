#ifndef AJUSTES_H
#define AJUSTES_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

// Forward declarations
class MenuAdmin;
class guardaCuentas;

class Ajustes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ajustes(MenuAdmin* menuAdmin, guardaCuentas* gestorCuentas, QWidget *parent = nullptr);

private slots:
    void abrirCrearCuentas();
    void abrirCambiarContrasena();
    void abrirEliminarCuentas();
    void abrirListarCuentas();
    void regresarAlMenu();

private:
    void configurarUI();
    QPushButton* crearBoton(const QString& texto);

    // Referencias a otros componentes
    MenuAdmin* menuAdminWindow;
    guardaCuentas* guardaCuentasInstance;
};

#endif // AJUSTES_H
