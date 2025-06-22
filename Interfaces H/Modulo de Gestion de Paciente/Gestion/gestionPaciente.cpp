#include "gestionPaciente.h"
#include <sstream>
#include <iostream>

// Registro de paciente
void gestionPaciente::registrarPaciente(int ID, std::string nombre, std::string fechaNacimiento,
                                        std::string direccion, int numIdentidad, int numTelefono,
                                        std::string eMail, std::string genero, std::string alergias) {
    Paciente nuevo(ID, nombre, fechaNacimiento, direccion, numIdentidad, numTelefono, eMail, genero, alergias);
    pacientes.push_back(nuevo);
}

// Buscar por ID
Paciente* gestionPaciente::buscarPaciente(int ID) {
    for (auto& p : pacientes) {
        if (p.getID() == ID) return &p;
    }
    return nullptr;
}

// Buscar por identidad
Paciente* gestionPaciente::buscarPacientePorIdentidad(int numIdentidad) {
    for (auto& p : pacientes) {
        if (p.getNumIdentidad() == numIdentidad) return &p;
    }
    return nullptr;
}

// Buscar por nombre
Paciente* gestionPaciente::buscarPacientePorNombre(const std::string& nombre) {
    for (auto& p : pacientes) {
        if (p.getNombre() == nombre) return &p;
    }
    return nullptr;
}

// Eliminar por ID
bool gestionPaciente::eliminarPaciente(int ID) {
    for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
        if (it->getID() == ID) {
            pacientes.erase(it);
            return true;
        }
    }
    return false;
}

// Consultar expediente
ExpedienteMedico gestionPaciente::consultarExpediente(const Paciente& paciente) {
    return paciente.expediente; // Suponiendo que expediente sea público o haya un getter
}

// Registrar consulta médica al expediente
void gestionPaciente::registrarConsulta(const Paciente& paciente, const ConsultaMedica& consulta) {
    Paciente* p = buscarPaciente(paciente.getID());
    if (p != nullptr) {
        p->expediente.agregarConsulta(consulta);
    }
}

// Mostrar todos los pacientes
std::string gestionPaciente::mostrarPacientes() const {
    
}
