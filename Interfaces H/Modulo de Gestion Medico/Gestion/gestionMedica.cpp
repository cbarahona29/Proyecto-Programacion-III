#include "gestionMedico.h"
#include <sstream>
#include <stdexcept>

using std::ostringstream;
using std::vector;
using std::runtime_error;

// Registrar medico con un ID autogenerado
void gestionMedica::registrarMedico(int colegiacion, int numIdentidad, int numTelefono,const string& nombre, const string& especialidad,const string& fechaNacimiento, const string& eMail) {
    int nuevoID = ++ultimoID;
    Medico nuevo(nuevoID, colegiacion, numIdentidad, numTelefono, nombre,especialidad, fechaNacimiento, eMail, true); // estado disponible
    colaEspecialidad.agregar(nuevo);
}

// Buscar por ID
Medico gestionMedica::buscarMedico(int ID) {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
    for (const Medico& m : lista) {
        if (m.getID() == ID)
            return m;
    }
    throw runtime_error("Médico no encontrado por ID.");
}

// Buscar por numero de identidad
Medico gestionMedica::buscarMedicoPorIdentidad(int numIdentidad) {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
    for (const Medico& m : lista) {
        if (m.getNumIdentidad() == numIdentidad)
            return m;
    }
    throw runtime_error("Médico no encontrado por número de identidad.");
}

// Buscar por nombre
Medico gestionMedica::buscarMedico(const string& nombre) {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
    for (const Medico& m : lista) {
        if (m.getNombre() == nombre)
            return m;
    }
    throw runtime_error("Médico no encontrado por nombre.");
}

// Buscar por especialidad
vector<Medico> gestionMedica::buscarPorEspecialidad(const string& especialidad) {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
    vector<Medico> filtrados;

    for (const Medico& m : lista) {
        if (m.getEspecialidad() == especialidad) {
            filtrados.push_back(m);
        }
    }

    return filtrados;
}

// Editar la informacion de un médico
bool gestionMedica::editarMedico(int ID, const Medico& datosActualizados) {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
    ColaPorEspecialidad nuevaCola;
    bool editado = false;

    for (Medico m : lista) {
        if (m.getID() == ID) {
            nuevaCola.agregar(datosActualizados);
            editado = true;
        } else {
            nuevaCola.agregar(m);
        }
    }

    if (editado) {
        colaEspecialidad = nuevaCola;
    }

    return editado;
}

// Marcar como disponible
bool gestionMedica::marcarDisponible(int ID) {
    return cambiarEstado(ID, true);
}

// Marcar como ocupado
bool gestionMedica::marcarOcupado(int ID) {
    return cambiarEstado(ID, false);
}

// Comprobar si está ocupado
bool gestionMedica::estaOcupado(int ID) {
    Medico m = buscarMedico(ID);
    return !m.estaDisponible(); // se asume que `estaDisponible()` devuelve un bool
}

// Interno: cambiar estado
bool gestionMedica::cambiarEstado(int ID, bool disponible) {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
    ColaPorEspecialidad nuevaCola;
    bool cambiado = false;

    for (Medico m : lista) {
        if (m.getID() == ID) {
            m.setEstado(disponible);
            cambiado = true;
        }
        nuevaCola.agregar(m);
    }

    if (cambiado) {
        colaEspecialidad = nuevaCola;
    }

    return cambiado;
}

// Listar todos los medicos
string gestionMedica::listarMedicos() {
    vector<Medico> lista = colaEspecialidad.obtenerTodos();
}

// Listar medicos por especialidad
string gestionMedica::listarPorEspecialidad(const string& especialidad) {
    vector<Medico> lista = buscarPorEspecialidad(especialidad);
}
