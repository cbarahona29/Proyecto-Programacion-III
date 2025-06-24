#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QString>

class RegistroPaciente : public QWidget
{
    Q_OBJECT

public:
    explicit RegistroPaciente(QWidget *parent = nullptr);

private slots:
    void registrarPaciente();
    void regresar();
    void limpiarCampos();

signals:
    void regresarAlMenu();

private:
    // Métodos privados para UI
    void configurarUI();
    void configurarEventos();
    void configurarValidadores();

    // Métodos de validación y utilidad
    void cargarProximoID();
    bool validarCampos();
    bool esValidaFecha(const QString& fecha);

    // Controles de la interfaz
    QLineEdit* txtId;
    QLineEdit* txtDireccion;
    QLineEdit* txtIdentidad;
    QLineEdit* txtNumTelefono;
    QLineEdit* txtNombre;
    QLineEdit* txtFechaNacimiento;
    QLineEdit* txtEmail;
    QComboBox* cmbAlergias;
    QComboBox* cmbGenero;
    QPushButton* btnRegistrar;
    QPushButton* btnRegresar;
    QPushButton* btnLimpiar;
};
