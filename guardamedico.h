#ifndef GUARDAMEDICO_H
#define GUARDAMEDICO_H

#include "Medico.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class guardaMedico
{
public:
    guardaMedico();

    // Operaciones CRUD
    bool registrarMedico(const Medico& medico);
    Medico buscarPorColegiacion(int numColegiacion);
    std::vector<Medico> listarTodos();
    bool actualizarMedico(const Medico& medico);
    bool eliminarMedico(int numColegiacion);

    // Utilidades
    int obtenerProximoID();
    bool existeMedico(int numColegiacion);

private:
    const std::string CARPETA_BASE = "Medicos";

    bool crearDirectorioMedico(int numColegiacion);
    std::string obtenerRutaMedico(int numColegiacion) const;
    bool guardarDatosMedico(const Medico& medico, const std::string& ruta);
    Medico cargarDatosMedico(const std::string& ruta);
    bool validarEstructuraCarpetas();
};

#endif // GUARDAMEDICO_H
