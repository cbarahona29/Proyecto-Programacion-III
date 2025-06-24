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

#include "gestionMedica.h"

class BuscarMedic : public QDialog {
    Q_OBJECT

public:
    BuscarMedic(QWidget* parent = nullptr);
    ~BuscarMedic();

private slots:
    void buscarMedicos();
    void cargarTodosLosMedicos();
    void editarMedicoSeleccionado();
    void eliminarMedicoSeleccionado();
    void onMedicoSeleccionado();

private:
    void configurarUI();
    void configurarEventos();
    void actualizarTablaMedicos(const std::vector<Medico*>& medicos);
    void mostrarDialogoEdicion(Medico* medico);
    bool validarDatos(const QString& nombre, const QString& fechaNacimiento,
                      const QString& email, const QString& telefono, const QString& identidad);
    QPushButton* crearBotonSimple(const QString& texto, int ancho, int alto);

    // UI
    QComboBox* comboTipoBusqueda;
    QLineEdit* lineEditBusqueda;
    QPushButton* btnBuscar;
    QPushButton* btnCargarTodos;
    QPushButton* btnEditar;
    QPushButton* btnEliminar;
    QPushButton* btnCerrar;
    QTableWidget* tablaMedicos;
    QLabel* labelResultados;

    // Lógica
    gestionMedica* gestor;
    int idMedicoSeleccionado;
};
