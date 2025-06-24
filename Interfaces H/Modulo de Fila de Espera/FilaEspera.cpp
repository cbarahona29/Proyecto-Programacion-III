#include "FilaEspera.h"
#include <iostream>

FilaEspera::FilaEspera() {
    // Si necesitas inicializar algo, hazlo aquí
}

void FilaEspera::inscribirPaciente(Paciente paciente, std::string especialidad) {
    colasEspecialidad.agregarPaciente(paciente, especialidad);
}

void FilaEspera::asignarPaciente(Paciente paciente){}


std::string FilaEspera::mostrarCola() {
    return colasEspecialidad.mostrarColas();
}

std::string FilaEspera::mostrarColaPorEspecialidad(string especialidad) {
    return colasEspecialidad.mostrarColasFiltradas(especialidad);
}

bool FilaEspera::removerPacienteDeFila(Paciente paciente, string especialidad) {
   colasEspecialidad.obtenerCola(especialidad).eliminarPaciente(paciente.getNombre());
}
