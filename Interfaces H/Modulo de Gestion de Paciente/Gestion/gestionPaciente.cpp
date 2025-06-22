#include "gestionPaciente.h"
#include <sstream>
#include <iostream>
#include <vector>

// Registro de paciente
void gestionPaciente::registrarPaciente(int ID, std::string nombre, std::string fechaNacimiento,
                                        std::string direccion, int numIdentidad, int numTelefono,
                                        std::string eMail, std::string genero, std::string alergias) {
    Paciente nuevo(ID, nombre, fechaNacimiento, direccion, numIdentidad, numTelefono, eMail, genero, alergias);
    pacientes.push(nuevo);
}

// Buscar por ID
Paciente* gestionPaciente::buscarPaciente(int ID) {
    vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();

    for (auto& p : vectorPaciente) {
        if (p.getID() == ID) return &p;
    }
    return nullptr;
}

// Buscar por identidad
Paciente* gestionPaciente::buscarPacientePorIdentidad(int numIdentidad) {
    vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();

    for (auto& p : vectorPaciente) {
        if (p.getNumIdentidad() == numIdentidad) return &p;
    }
    return nullptr;
}

// Buscar por nombre
Paciente* gestionPaciente::buscarPacientePorNombre(const std::string& nombre) {
    vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();

    for (auto& p : vectorPaciente) {
        if (p.getNombre() == nombre) return &p;
    }
    return nullptr;
}

// Eliminar por ID - Al momento no sirve, necesita recorrer la cola y encontrar y borrar directamente el paciente
bool gestionPaciente::eliminarPaciente(const Paciente& paciente) {
    vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();

    for (auto& p : vectorPaciente) {
        if (it->getID() == paciente) {
            pacientes.erase(it);
            return true;
        }
    }
    return false;
}

// Consultar expediente
ExpedienteMedico gestionPaciente::consultarExpediente(const Paciente& paciente) {
    return paciente.getExpediente(); // Suponiendo que expediente sea público o haya un getter
}

// Registrar consulta médica al expediente
void gestionPaciente::registrarConsulta(const Paciente& paciente, const ConsultaMedica& consulta) {
    Paciente* p = buscarPaciente(paciente.getID());
    if (p != nullptr) {
        paciente.getExpediente().agregarConsulta(consulta);
    }
}

// Mostrar todos los pacientes
std::string gestionPaciente::mostrarPacientes() {
    
}
