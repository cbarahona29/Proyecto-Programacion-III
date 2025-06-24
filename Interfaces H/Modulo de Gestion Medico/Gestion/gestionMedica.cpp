// Libs estandar
#include <sstream>
#include <stdexcept>

// Dependencias
#include "gestionMedica.h"

using std::ostringstream;
using std::vector;
using std::runtime_error;

// Registrar medico 
void gestionMedica::registrarMedico(int ID, int colegiacion, int numIdentidad, int numTelefono,const string& nombre, const string& especialidad,const string& fechaNacimiento, const string& eMail) {
    Medico nuevo(ID, colegiacion, numIdentidad, numTelefono, nombre,especialidad, fechaNacimiento, eMail, true); // estado disponible
    
    if (saver.existeMedico(nuevo.getNumColegiacion())) return;
    if (buscarMedico(nuevo.getNumIdentidad()))return;
    
    colaEspecialidad.agregarMedico(nuevo, especialidad);
    saver.registrarMedico(nuevo);
}

// Buscar por ID
Medico* gestionMedica::buscarMedico(int ID) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    for (Medico* m : lista) {
        if (m->getID() == ID)
            return m;
    }
    return nullptr;
}

// Buscar por numero de identidad
Medico* gestionMedica::buscarMedicoPorIdentidad(int numIdentidad) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    for (Medico* m : lista) {
        if (m->getNumIdentidad() == numIdentidad)
            return m;
    }
    return nullptr;
}

    // Buscar por nombre
Medico* gestionMedica::buscarMedico(const string& nombre) {
    vector<Medico*> lista = colaEspecialidad.obtenerTodos();
    for (Medico* m : lista) {
        if (m->getNombre() == nombre)
            return m;
    }
    throw runtime_error("Médico no encontrado por nombre.");
}

// Buscar por especialidad
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

// Editar la informacion de un médico
bool gestionMedica::editarMedico(int ID, const Medico& datosActualizados) {
    Medico*viejoPtr = buscarMedico(datosActualizados.getID())
    bool editado = false;

    if (viejo == nullptr){
        return editado;
    } else {
        Medico& viejo = *viejoPtr;
        viejo = datosActualizados;
        editado = true;
        return saver.registrarInfo(datosActualizados);
    }
}

// Marcar como disponible
void gestionMedica::marcarDisponible(int ID) {
    buscarMedico(ID)->setEstado(true);
}

// Marcar como ocupado
void gestionMedica::marcarOcupado(int ID) {
    buscarMedico(ID)->setEstado(false);
}

// Comprobar si está ocupado
bool gestionMedica::estaOcupado(int ID) {
    Medico* m = buscarMedico(ID);
    return !m->estaDisponible(); 
}


// Listar todos los medicos
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

// Listar medicos por especialidad
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

}