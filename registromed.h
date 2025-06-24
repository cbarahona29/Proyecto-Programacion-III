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
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "guardamedico.h"
#include "medico.h"

class RegistroMed : public QWidget
{
    Q_OBJECT

public:
    explicit RegistroMed(QWidget *parent = nullptr);

private slots:
    void registrarMedico();
    void regresar();

private:
    // Métodos privados
    void configurarUI();
    void configurarEventos();
    void configurarIDAutomatico();
    void limpiarCampos();
    bool validarPassword(const QString& password, const QString& confirmPassword);
    bool guardarCredenciales(int numColegiacion, const QString& password);

    // Widgets
    QLineEdit* txtId;
    QLineEdit* txtColegiacion;
    QLineEdit* txtIdentidad;
    QLineEdit* txtNumTelefono;
    QLineEdit* txtNombre;
    QComboBox* cmbEspecialidad;
    QLineEdit* txtFechaNacimiento;
    QLineEdit* txtEmail;
    QLineEdit* txtPassword;           // Nuevo campo
    QLineEdit* txtConfirmPassword;    // Nuevo campo

    QPushButton* btnRegistrar;
    QPushButton* btnRegresar;

    // Gestor de médicos
    guardaMedico* gestorMedicos;

signals:
    void regresarAlMenu();
};

#endif // REGISTROMED_H
