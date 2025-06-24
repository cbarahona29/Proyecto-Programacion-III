#include "gestionPaciente.h"
#include <iostream>
#include <algorithm>

gestionPaciente::gestionPaciente() {
    cargarDatos();
}

// Registro de paciente con parámetros individuales
void gestionPaciente::registrarPaciente(int ID, std::string nombre, std::string fechaNacimiento,
                                        std::string direccion, int numIdentidad, int numTelefono,
                                        std::string eMail, std::string genero, std::string alergias) {
    if (saver.existePaciente(ID)) return;

    Paciente nuevo(ID, nombre, fechaNacimiento, direccion, numIdentidad, numTelefono, eMail, genero, alergias);
    pacientes.push(nuevo);
    saver.registrarPaciente(nuevo);
}

// Registro de paciente con objeto Paciente
void gestionPaciente::registrarPaciente(Paciente paciente) {
    if (saver.existePaciente(paciente.getID())) return;

    pacientes.push(paciente);
    saver.registrarPaciente(paciente);
}

// Cargar datos desde archivos
void gestionPaciente::cargarDatos() {
    // Verificar si existe la carpeta principal
    if (!saver.checkMainFolder()) return;

    // Buscar todos los pacientes en el directorio
    namespace fs = std::filesystem;

    for (const auto& entrada : fs::directory_iterator("Pacientes")) {
        if (entrada.is_directory()) {
            std::string nombre = entrada.path().filename().string();
            if (nombre.substr(0, 8) == "Paciente") {
                try {
                    int id = std::stoi(nombre.substr(8));
                    Paciente paciente = saver.extraerPaciente(id);
                    if (paciente.getExiste()) { // Solo cargar si el paciente existe y es válido
                        pacientes.push(paciente);
                    }
                } catch (...) {
                    // Ignorar directorios con nombres inválidos
                }
            }
        }
    }
}

// Buscar por ID
Paciente* gestionPaciente::buscarPaciente(int ID) {
    std::vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();
    for (auto& p : vectorPaciente) {
        if (p.getID() == ID) return &p;
    }
    return nullptr;
}

// Buscar por identidad
Paciente* gestionPaciente::buscarPacientePorIdentidad(int numIdentidad) {
    std::vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();
    for (auto& p : vectorPaciente) {
        if (p.getNumIdentidad() == numIdentidad) return &p;
    }
    return nullptr;
}

// Buscar por nombre
Paciente* gestionPaciente::buscarPacientePorNombre(const std::string& nombre) {
    std::vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();
    for (auto& p : vectorPaciente) {
        if (p.getNombre() == nombre) return &p;
    }
    return nullptr;
}

// Eliminar paciente
bool gestionPaciente::eliminarPaciente(const Paciente& paciente) {
    // Primero eliminar de los archivos
    bool eliminadoArchivos = saver.borrarPaciente(paciente.getID());

    if (eliminadoArchivos) {
        // Luego eliminar de la cola en memoria
        // Reconstruimos la cola sin el paciente eliminado
        ColaPacientes nuevaCola;
        std::vector<Paciente> vectorPaciente = pacientes.obtenerPacientes();

        for (auto& p : vectorPaciente) {
            if (p.getID() != paciente.getID()) {
                nuevaCola.push(p);
            }
        }

        pacientes = nuevaCola;
        return true;
    }

    return false;
}

// Consultar expediente
ExpedienteMedico gestionPaciente::consultarExpediente(const Paciente& paciente) {
    return saver.leerExpediente(paciente.getID());
}

// Registrar consulta médica al expediente
void gestionPaciente::registrarConsulta(const Paciente& paciente, const ConsultaMedica& consulta) {
    saver.guardarConsulta(paciente, consulta);

    // También actualizar el paciente en memoria si existe
    Paciente* p = buscarPaciente(paciente.getID());
    if (p != nullptr) {
        ExpedienteMedico expedienteActualizado = saver.leerExpediente(paciente.getID());
        p->setExpediente(expedienteActualizado);
    }
}

// Mostrar todos los pacientes
std::vector<Paciente> gestionPaciente::mostrarPacientes() {
    return pacientes.obtenerPacientes();
}
