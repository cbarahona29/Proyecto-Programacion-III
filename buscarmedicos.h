#ifndef BUSCARMEDICOS_H
#define BUSCARMEDICOS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QAbstractItemView>
#include <vector>
#include <exception>
#include "gestionMedica.h"
#include "Medico.h"        // Tu clase Medico

class BuscarMedicos : public QDialog
{
    Q_OBJECT

public:
    explicit BuscarMedicos(QWidget *parent = nullptr);
    ~BuscarMedicos();

private slots:
    void cargarTodosLosMedicos();
    void buscarMedicos();
    void onMedicoSeleccionado();
    void editarMedicoSeleccionado();
    void eliminarMedicoSeleccionado();

private:
    void configurarUI();
    void configurarEventos();
    void actualizarTablaMedicos(const std::vector<Medico*>& medicos);
    void mostrarDialogoEdicion(Medico* medico);
    bool validarDatos(const QString& nombre, const QString& especialidad,
                      const QString& fechaNacimiento, const QString& email,
                      const QString& telefono, const QString& identidad,
                      const QString& colegiacion);
    QPushButton* crearBotonSimple(const QString& texto, int ancho, int alto);

    // Componentes UI
    QComboBox* comboTipoBusqueda;
    QLineEdit* lineEditBusqueda;
    QPushButton* btnBuscar;
    QPushButton* btnCargarTodos;
    QPushButton* btnEditar;
    QPushButton* btnEliminar;
    QPushButton* btnCerrar;
    QTableWidget* tablaMedicos;
    QLabel* labelResultados;

    // Datos
    gestionMedica* gestor;
    int idMedicoSeleccionado;
};

#endif // BUSCARMEDICOS_H
