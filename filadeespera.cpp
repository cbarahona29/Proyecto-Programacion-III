#include "FiladeEspera.h"
#include <iostream>

FiladeEspera::FiladeEspera() {

}

void FiladeEspera::inscribirPaciente(Paciente paciente, std::string especialidad) {
    colasEspecialidad.agregarPaciente(paciente, especialidad);
}

void FiladeEspera::asignarPaciente(Paciente paciente){}


std::string FiladeEspera::mostrarCola() {
    return colasEspecialidad.mostrarColas();
}

std::string FiladeEspera::mostrarColaPorEspecialidad(string especialidad) {
    return colasEspecialidad.mostrarColasFiltradas(especialidad);
}

bool FiladeEspera::removerPacienteDeFila(Paciente paciente, string especialidad) {
}
