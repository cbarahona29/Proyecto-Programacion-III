#ifndef GESTOR_MEDICO_H
#define GESTOR_MEDICO_H

#include <iostream>
#include <string>
#include "../Medico/Medico.h"
#include "../Cola/ColasPorEspecialidadMedico.h"

// Inclusion de Objetos de Guardar datos
#include "../../Modulo de Retencion de Datos/guardaMedico.cpp"

using std::string;

class gestionMedica {
private:
    ColasPorEspecialidad colaEspecialidad;
    guardaMedico saver;
public:
    // Registro
    void registrarMedico(int ID, int colegiacion, int numIdentidad, int numTelefono, const string& nombre, const string& especialidad,const string& fechaNacimiento, const string& eMail);
    void registrarMedico(Medico medico);

    void cargarDatos();

    // Buscar médico por ID, identidad o nombre
    Medico* buscarMedico(int ID);
    Medico* buscarMedicoPorIdentidad(int numIdentidad);
    Medico* buscarMedico(const string& nombre);
    vector<Medico*> buscarPorEspecialidad(const string& especialidad);

    // Editar información del médico
    bool editarMedico(int ID, const Medico& datosActualizados);

    // Cambiar estado del médico
    void marcarDisponible(int ID);
    void marcarOcupado(int ID);
    bool estaOcupado(int ID);

    // Listar médicos
    string listarMedicos();
    string listarPorEspecialidad(const string& especialidad);
};

#endif
