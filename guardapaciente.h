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

#pragma once

// Librerias estandar
#include <iostream>
#include <filesystem>
#include <string>
// Archivos
#include "Paciente.h"
#include "ExpedienteMedico.h"
#include "ConsultaMedica.h"

namespace fs = std::filesystem;
using std::string;

class guardaPaciente {
private:
public:
    guardaPaciente();

    // Funciones de FileSystem (similar a Java file)
    bool checkMainFolder(); // Para chequear si el main Paciente folder existe
    void crearMainFolder(); // Para crear el main Paciente folder si no existe
    bool existePaciente(int ID); // para chequear si existe paciente (para registrar paciente)
    int obtenerProximoID(); // Nuevo método para obtener el próximo ID disponible

    // Funciones principales
    bool registrarPaciente(const Paciente& paciente); // crea un folder para el paciente
    Paciente extraerPaciente(int ID); // Lee el archivo y regresa el objeto pero enteramente
    bool crearExpediente(int ID); // crea el expediente dentro del folder de paciente
    bool guardarConsulta(const Paciente& , const ConsultaMedica& consulta); // Agrega consulta a expediente
    ExpedienteMedico leerExpediente(int ID); // Lee el archivo & regresa un objeto de Expediente Clinico
    bool registrarInfo(const Paciente& paciente); // Crea el documento y registra Informacion del Paciente
    Paciente extraerInfoPaciente(int ID); // Lee el archivo y regresa objeto paciente

    // Eliminar/Borrar Paciente
    bool borrarExpediente(int ID);
    bool borrarInfo(int ID);
    bool borrarPaciente(int IDs);
};
