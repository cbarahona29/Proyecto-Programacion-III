#ifndef REGISTROPACIENTE_H
#define REGISTROPACIENTE_H

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

private:
    void configurarUI();
    void configurarEventos();
    void limpiarCampos();

    // Controles de UI
    QLineEdit* txtNombre;
    QLineEdit* txtTelefono;
    QLineEdit* txtEdad;
    QLineEdit* txtGenero;
    QLineEdit* txtIdentidad;
    QLineEdit* txtFechaNacimiento;
    QComboBox* cmbAlergias;
    QLineEdit* txtCorreo;

    QPushButton* btnRegistrar;
    QPushButton* btnRegresar;

signals:
    void regresarAlMenu();
};

#endif // REGISTROPACIENTE_H
