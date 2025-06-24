#ifndef GESTOR_MEDICO_H
#define GESTOR_MEDICO_H

#include <iostream>
#include <string>
#include "Medico.h"
#include "ColasPorEspecialidadMedico.h"
#include "guardaMedico.h"

using std::string;

class gestionMedica {
private:
    ColasPorEspecialidad colaEspecialidad;
    guardaMedico saver;

public:
    void registrarMedico(int ID, int colegiacion, int numIdentidad, int numTelefono, const string& nombre, const string& especialidad, const string& fechaNacimiento, const string& eMail);
    void registrarMedico(Medico medico);

    void cargarDatos();

    Medico* buscarMedico(int ID);
    Medico* buscarMedicoPorIdentidad(int numIdentidad);
    Medico* buscarMedico(const string& nombre);
    vector<Medico*> buscarPorEspecialidad(const string& especialidad);

    bool editarMedico(int ID, const Medico& datosActualizados);

    void marcarDisponible(int ID);
    void marcarOcupado(int ID);
    bool estaOcupado(int ID);
    std::vector<Medico*> obtenerTodos();


    string listarMedicos();
    string listarPorEspecialidad(const string& especialidad);
};

#endif
