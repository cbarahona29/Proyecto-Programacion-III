/* Esta clase tiene como proposito guardar y estructurar Medicos y su informacion esto incluye:
 * - Cada Medico
 *
 * La estructura sera de la siguiente manera:
 * - Pacientes
 *  - Medico 1
 *      - Informacion
 *  - Medico 2
 *      - Informacion
 *      
 */

// Librerias estandar
#include <iostream>
#include <filesystem>
#include <string>

// Archivos 
#include "Modulo de Gestion Medico/Medico/Medico.h"

namespace fs = std::filesystem;
using std::string;

class guardaMedico {
    private:

    public: 
        guardaMedico () {
            // Debe chequear si existe el folder paciente
        }

        // Funciones de FileSystem (similar a Java file)
        bool checkMainFolder (); // Para chequear si el main Medico folder existe
        void crearMainFolder (); // Para crear el main Paciente folder si no existe
     
        // Funciones Registro de Medico
        bool registrarPaciente (const Medico& medico); // crea un folder para el paciente
        Paciente extraerPaciente (string& nombreMedico); // Lee el archivo y regresa el objeto pero enteramente
        bool registrarInfo (const Medico& medico); // Crea el documento y registra Informacion del Medico

        // Eliminar/Borrar Paciente ***
        bool borrarInfo (string& nombrePaciente);
        bool borrarMedico (string& nombreMedico);
   
};