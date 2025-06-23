/* Esta clase tiene como proposito guardar y estructurar Medicos y su informacion esto incluye:
 * - Cada Medico
 *
 * La estructura sera de la siguiente manera:
 * - Medicos
 *  - Medico 1
 *      - Informacion
 *  - Medico 2
 *      - Informacion
 *
 */

#ifndef GUARDAMEDICO_H
#define GUARDAMEDICO_H

// Librerias estandar
#include <iostream>
#include <filesystem>
#include <string>
#include "Medico.h"

namespace fs = std::filesystem;
using std::string;

class guardaMedico {
private:

public:
    guardaMedico(); // Debe chequear si existe el folder medico

    // Funciones de FileSystem (similar a Java file)
    bool checkMainFolder(); // Para chequear si el main Medico folder existe
    void crearMainFolder(); // Para crear el main Medico folder si no existe

    // Funciones Registro de Medico
    bool existeMedico(int numColegiacion); // chequea si existe ya el medico
    bool registrarMedico(const Medico& medico); // crea un folder para el medico
    Medico extraerMedico(int numColegiacion); // Lee el archivo y regresa el objeto pero enteramente
    bool registrarInfo(const Medico& medico); // Crea el documento y registra Informacion del Medico
    int obtenerProximoID(); // Nueva función para obtener el próximo ID disponible

    // Eliminar/Borrar Medico
    bool borrarInfo(int numColegiacion);
    bool borrarMedico(int numColegiacion);
};

#endif // GUARDAMEDICO_H
