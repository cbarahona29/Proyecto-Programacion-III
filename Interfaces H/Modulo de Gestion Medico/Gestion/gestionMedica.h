#ifndef GESTOR_MEDICO_H
#define GESTOR_MEDICO_H

#include <iostream>
#include <string>
#include "../Medico/Medico.h"
#include "../../Modulo de Gestion de Paciente/Cola/ColasPorEspecialidad.h"

using std::string;

class gestionMedica {
private:
    ColaPorEspecialidad colaEspecialidad;
    int ultimoID = 0; // Para autogenerar ID

public:
    // Registro
    void registrarMedico(int colegiacion, int numIdentidad, int numTelefono, const string& nombre, const string& especialidad,const string& fechaNacimiento, const string& eMail);

    // Buscar médico por ID, identidad o nombre
    Medico buscarMedico(int ID);
    Medico buscarMedicoPorIdentidad(int numIdentidad);
    Medico buscarMedico(const string& nombre);
    vector<Medico> buscarPorEspecialidad(const string& especialidad);

    // Editar información del médico
    bool editarMedico(int ID, const Medico& datosActualizados);

    // Cambiar estado del médico
    bool marcarDisponible(int ID);
    bool marcarOcupado(int ID);
    bool estaOcupado(int ID);

    // Listar médicos
    string listarMedicos();
    string listarPorEspecialidad(const string& especialidad);
};

#endif
