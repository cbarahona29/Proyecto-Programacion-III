/**
 * Esta clase tiene como proposito guardar y estructurar pacientes y su informacion
 * esto incluye:
 * - Cada Paciente
 * - Expediente Clinico de cada paciente
 * 
 * La estructura sera de la siguiente manera:
 * - Pacientes
 *  - Paciente 1
 *      - Informacion
 *      - ExpedienteClinico.bin
 *  - Paciente 2
 *      - Informacion
 *      - ExpedienteClinico.bin
 *      
 *  La Informacion del Paciente se guarda siguiendo esta estructura  
 * 
 */

// Librerias estandar
#include <iostream>
#include <filesystem>
#include <string>

// Archivos 
#include "../Modulo de Gestion de Paciente/Paciente/Paciente.h"
#include "../Modulo de Gestion de Paciente/Paciente/ExpedienteMedico.h"
#include "../Modulo de Gestion de Paciente/Paciente/ConsultaMedica.h"

namespace fs = std::filesystem;
using std::string;

class guardaPaciente {
    private:


    public:
        guardaPaciente () {
            // Debe chequear si existe el folder paciente
        }

        // Funciones de FileSystem (similar a Java file)
        bool checkMainFolder (); // Para chequear si el main Paciente folder existe
        void crearMainFolder (); // Para crear el main Paciente folder si no existe
     

        bool existePaciente (string& nombrePaciente); // para chequear si existe paciente (para registrar paciente)
        
        //
        bool registrarPaciente (const Paciente& paciente); // crea un folder para el paciente
        Paciente extraerPaciente (string& nombrePaciente); // Lee el archivo y regresa el objeto pero enteramente
                
                bool crearExpediente (); // crea el expediente dentro del folder de paciente
                void guardarConsulta (const Paciente& paciente); // Agrega consulta a expediente
                ExpedienteMedico leerExpediente (string& nombrePaciente); // Lee el archivo & regresa un objeto de Expediente Clinico
                
                bool registrarInfo (const Paciente& paciente); // Crea el documento y registra Informacion del Paciente
                Paciente extraerInfoPaciente (string& nombrePaciente); // Lee el archivo y regresa objeto paciente
        

        // Eliminar/Borrar Paciente ***
        bool borrarExpediente (string& nombrePaciente);
        bool borrarInfo (string& nombrePaciente);
        bool borrarPaciente (string& nombrePaciente);
};