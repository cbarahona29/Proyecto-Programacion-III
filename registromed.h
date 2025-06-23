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

class RegistroMed : public QWidget
{
    Q_OBJECT

public:
    explicit RegistroMed(QWidget *parent = nullptr);

private slots:
    void registrarMedico();
    void regresar();


private:
    void configurarUI();
    void configurarEventos();
    void limpiarCampos();
    void generarProximoID(); // Nueva función para generar ID automático

    // Controles de UI
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

signals:
    void regresarAlMenu();
};

#endif // REGISTROMED_H
