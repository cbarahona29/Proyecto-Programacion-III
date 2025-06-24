#ifndef REGISTROMED_H
#define REGISTROMED_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>

// Incluir nuestras clases de datos
#include "guardaMedico.h"
#include "Medico.h"

class RegistroMed : public QWidget
{
    Q_OBJECT

public:
    explicit RegistroMed(QWidget *parent = nullptr);

private slots:
    void registrarMedico();
    void regresar();

signals:
    void regresarAlMenu();

private:
    // Métodos privados para UI
    void configurarUI();
    void configurarEventos();
    void configurarIDAutomatico();

    // Método para limpiar campos
    void limpiarCampos();

    // Controles de la interfaz
    QLineEdit* txtId;
    QLineEdit* txtColegiacion;
    QLineEdit* txtIdentidad;
    QLineEdit* txtNumTelefono;
    QLineEdit* txtNombre;
    QComboBox* cmbEspecialidad;
    QLineEdit* txtFechaNacimiento;
    QLineEdit* txtEmail;
    QPushButton* btnRegistrar;
    QPushButton* btnRegresar;

    // Instancia de guardaMedico para manejar persistencia
    guardaMedico* gestorMedicos;
};

#endif // REGISTROMED_H
