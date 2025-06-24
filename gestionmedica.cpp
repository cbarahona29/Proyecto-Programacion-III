// Libs estandar
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "gestionMedica.h"
using std::ostringstream;
using std::vector;
using std::runtime_error;

void gestionMedica::registrarMedico(int ID, int colegiacion, int numIdentidad, int numTelefono, const string& nombre, const string& especialidad, const string& fechaNacimiento, const string& eMail) {
    Medico nuevo(ID, colegiacion, numIdentidad, numTelefono, nombre, especialidad, fechaNacimiento, eMail, true);
    if (saver.existeMedico(nuevo.getNumColegiacion())) return;
    if (buscarMedicoPorIdentidad(nuevo.getNumIdentidad())) return;
    colaEspecialidad.agregarMedico(nuevo, especialidad);
    saver.registrarMedico(nuevo);
}

Medico* gestionMedica::buscarMedico(int ID) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    for (Medico* m : lista) {
        if (m->getID() == ID)
            return m;
    }
    return nullptr;
}

Medico* gestionMedica::buscarMedicoPorIdentidad(int numIdentidad) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    for (Medico* m : lista) {
        if (m->getNumIdentidad() == numIdentidad)
            return m;
    }
    return nullptr;
}

Medico* gestionMedica::buscarMedico(const string& nombre) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    for (Medico* m : lista) {
        if (m->getNombre() == nombre)
            return m;
    }
    throw runtime_error("Médico no encontrado por nombre.");
}

vector<Medico*> gestionMedica::buscarPorEspecialidad(const string& especialidad) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    vector<Medico*> filtrados;
    for (Medico* m : lista) {
        if (m->getEspecialidad() == especialidad) {
            filtrados.push_back(m);
        }
    }
    return filtrados;
}

bool gestionMedica::editarMedico(int ID, const Medico& datosActualizados) {
    Medico* viejoPtr = buscarMedico(ID);
    bool editado = false;
    if (viejoPtr == nullptr) {
        return editado;
    } else {
        Medico& viejo = *viejoPtr;
        viejo = datosActualizados;
        editado = true;
        return saver.registrarMedico(datosActualizados);
    }
}

void gestionMedica::marcarDisponible(int ID) {
    Medico* medico = buscarMedico(ID);
    if (medico != nullptr) {
        medico->setEstado(true);
    }
}

void gestionMedica::marcarOcupado(int ID) {
    Medico* medico = buscarMedico(ID);
    if (medico != nullptr) {
        medico->setEstado(false);
    }
}

bool gestionMedica::estaOcupado(int ID) {
    Medico* m = buscarMedico(ID);
    if (m != nullptr) {
        return !m->estaDisponible();
    }
    return false;
}

string gestionMedica::listarMedicos() {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    string resultado;
    if (lista.empty()) {
        return "No hay médicos registrados actualmente.";
    }
    resultado += "Lista de todos los médicos registrados:\n";
    for (Medico* medico : lista) {
        if (medico) {
            resultado += "- " + medico->getNombre() + " (" + medico->getEspecialidad() + ")\n";
        }
    }
    return resultado;
}

string gestionMedica::listarPorEspecialidad(const string& especialidad) {
    vector<Medico*> lista = buscarPorEspecialidad(especialidad);
    string resultado;
    if (lista.empty()) {
        return "No hay médicos registrados en la especialidad de " + especialidad + ".";
    }
    resultado += "Médicos en la especialidad de " + especialidad + ":\n";
    for (Medico* medico : lista) {
        resultado += "- " + medico->getNombre() + " (" + medico->getEspecialidad() + ")\n";
    }
    return resultado;
}

