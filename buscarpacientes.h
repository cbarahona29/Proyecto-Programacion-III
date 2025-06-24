#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QTableWidgetItem>

#include "gestionPaciente.h"

class BuscarPacientes : public QDialog
{
    Q_OBJECT

public:
    BuscarPacientes(QWidget* parent = nullptr);
    ~BuscarPacientes();

private slots:
    void buscarPacientes();
    void cargarTodosLosPacientes();
    void editarPacienteSeleccionado();
    void eliminarPacienteSeleccionado();
    void onPacienteSeleccionado();

private:
    void configurarUI();
    void configurarEventos();
    void actualizarTablaPacientes(const std::vector<Paciente>& pacientes);
    void mostrarDialogoEdicion(Paciente* paciente);
    bool validarDatos(const QString& nombre, const QString& fechaNacimiento,
                      const QString& direccion, const QString& email,
                      const QString& telefono, const QString& identidad);
    QPushButton* crearBotonSimple(const QString& texto, int ancho, int alto);

    // UI Components
    QComboBox* comboTipoBusqueda;
    QLineEdit* lineEditBusqueda;
    QPushButton* btnBuscar;
    QPushButton* btnCargarTodos;
    QPushButton* btnEditar;
    QPushButton* btnEliminar;
    QPushButton* btnCerrar;
    QTableWidget* tablaPacientes;
    QLabel* labelResultados;

    // Data
    gestionPaciente* gestor;
    int idPacienteSeleccionado; // Cambiado de Paciente* a int para evitar punteros inválidos
};
