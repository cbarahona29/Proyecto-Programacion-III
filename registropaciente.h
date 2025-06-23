#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class RegistroPaciente : public QWidget
{
    Q_OBJECT

public:
    explicit RegistroPaciente(QWidget *parent = nullptr);

private slots:
    void registrarPaciente();
    void regresar();

signals:
    void regresarAlMenu();

private:
    // Métodos privados
    void configurarUI();
    void configurarEventos();
    void limpiarCampos();
    void generarProximoID(); // Nuevo método

    // Controles de la interfaz
    QLineEdit* txtId;
    QLineEdit* txtDireccion;
    QLineEdit* txtIdentidad;
    QLineEdit* txtNumTelefono;
    QLineEdit* txtNombre;
    QLineEdit* txtFechaNacimiento;
    QLineEdit* txtEmail;
    QComboBox* cmbAlergias;
    QComboBox* cmbGenero; // Nuevo campo
    QPushButton* btnRegistrar;
    QPushButton* btnRegresar;
};
