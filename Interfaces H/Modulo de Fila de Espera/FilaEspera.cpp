#include "FilaEspera.h"
#include "ColasPorEspecialidad.h";
#include <map>

ColasPorEspecialidad colasEspecialidad;

void FilaEspera::inscribirPaciente(Paciente paciente, std::string especialidad) {
    mapaColas[especialidad].push(paciente); 
}

void FilaEspera::asignarPaciente() {
    for (auto& locMapa : mapaColas) {
        if (!locMapa.second.estaVacia()) { 
            Paciente* paciente = locMapa.second.pop(); 
            if (paciente) {
                delete paciente; 
                break;
            }
        }
    }
}

string FilaEspera::mostrarCola() {
    return colasEspecialidad.mostrarColas();
}


string FilaEspera::mostrarColaPorEspecialidad(std::string especialidad) {
    return colasEspecialidad.mostrarColasFiltradas(especialidad);
}

void FilaEspera::removerPacienteDeFila(Paciente paciente) {
    if (colasEspecialidad.eliminarPacienteDeEspecialidad(paciente.getID())) {
        std::cout << "Paciente removido.\n";
    } else {
        std::cout << "Paciente no encontrado.\n";
    }
}
