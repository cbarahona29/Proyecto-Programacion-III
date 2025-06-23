#include "guardaMedico.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <QDebug>

guardaMedico::guardaMedico()
{
    try {
        if (!fs::exists(CARPETA_BASE)) {
            fs::create_directory(CARPETA_BASE);
        }
    } catch (const std::exception& e) {
        qCritical() << "Error al inicializar guardaMedico:" << e.what();
        throw;
    }
}

bool guardaMedico::validarEstructuraCarpetas()
{
    try {
        return fs::exists(CARPETA_BASE) && fs::is_directory(CARPETA_BASE);
    } catch (...) {
        return false;
    }
}

std::string guardaMedico::obtenerRutaMedico(int numColegiacion) const
{
    return CARPETA_BASE + "/Medico_" + std::to_string(numColegiacion);
}

bool guardaMedico::crearDirectorioMedico(int numColegiacion)
{
    try {
        std::string ruta = obtenerRutaMedico(numColegiacion);
        return fs::create_directory(ruta);
    } catch (...) {
        return false;
    }
}

bool guardaMedico::existeMedico(int numColegiacion)
{
    try {
        std::string ruta = obtenerRutaMedico(numColegiacion);
        return fs::exists(ruta) && fs::is_directory(ruta);
    } catch (...) {
        return false;
    }
}

bool guardaMedico::registrarMedico(const Medico& medico)
{
    if (!validarEstructuraCarpetas()) return false;
    if (existeMedico(medico.getNumColegiacion())) return false;

    try {
        std::string ruta = obtenerRutaMedico(medico.getNumColegiacion());

        if (!fs::create_directory(ruta)) {
            qWarning() << "No se pudo crear directorio para médico";
            return false;
        }

        return guardarDatosMedico(medico, ruta + "/datos.txt");
    } catch (const std::exception& e) {
        qCritical() << "Error al registrar médico:" << e.what();
        return false;
    }
}

bool guardaMedico::guardarDatosMedico(const Medico& medico, const std::string& ruta)
{
    try {
        std::ofstream archivo(ruta, std::ios::out | std::ios::binary);
        if (!archivo.is_open()) return false;

        archivo << medico.getID() << "\n";
        archivo << medico.getNumColegiacion() << "\n";
        archivo << medico.getNumIdentidad() << "\n";
        archivo << medico.getNumTelefono() << "\n";
        archivo << medico.getNombre() << "\n";
        archivo << medico.getEspecialidad() << "\n";
        archivo << medico.getFechaNacimiento() << "\n";
        archivo << medico.getEmail() << "\n";
        archivo << (medico.estaDisponible() ? "1" : "0") << "\n";

        if (archivo.fail()) {
            archivo.close();
            return false;
        }

        archivo.close();
        return true;
    } catch (...) {
        return false;
    }
}

Medico guardaMedico::cargarDatosMedico(const std::string& ruta)
{
    try {
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) return Medico();

        int id, colegiacion, identidad, telefono;
        std::string nombre, especialidad, nacimiento, email, disponibleStr;

        archivo >> id >> colegiacion >> identidad >> telefono;
        archivo.ignore();
        std::getline(archivo, nombre);
        std::getline(archivo, especialidad);
        std::getline(archivo, nacimiento);
        std::getline(archivo, email);
        std::getline(archivo, disponibleStr);

        bool disponible = (disponibleStr == "1");

        return Medico(id, colegiacion, identidad, telefono, nombre,
                      especialidad, nacimiento, email, disponible);
    } catch (...) {
        return Medico();
    }
}

Medico guardaMedico::buscarPorColegiacion(int numColegiacion)
{
    if (!existeMedico(numColegiacion)) return Medico();

    try {
        std::string ruta = obtenerRutaMedico(numColegiacion) + "/datos.txt";
        return cargarDatosMedico(ruta);
    } catch (...) {
        return Medico();
    }
}

std::vector<Medico> guardaMedico::listarTodos()
{
    std::vector<Medico> medicos;

    if (!validarEstructuraCarpetas()) return medicos;

    try {
        for (const auto& entry : fs::directory_iterator(CARPETA_BASE)) {
            if (entry.is_directory()) {
                std::string ruta = entry.path().string() + "/datos.txt";
                Medico m = cargarDatosMedico(ruta);
                if (m.getID() > 0) { // Validar que se cargó correctamente
                    medicos.push_back(m);
                }
            }
        }
    } catch (...) {
        // Silenciar errores de lectura
    }

    return medicos;
}

bool guardaMedico::actualizarMedico(const Medico& medico)
{
    if (!existeMedico(medico.getNumColegiacion())) return false;

    try {
        std::string ruta = obtenerRutaMedico(medico.getNumColegiacion()) + "/datos.txt";
        return guardarDatosMedico(medico, ruta);
    } catch (...) {
        return false;
    }
}

bool guardaMedico::eliminarMedico(int numColegiacion)
{
    if (!existeMedico(numColegiacion)) return false;

    try {
        std::string ruta = obtenerRutaMedico(numColegiacion);
        return fs::remove_all(ruta) > 0;
    } catch (...) {
        return false;
    }
}

int guardaMedico::obtenerProximoID()
{
    int maxID = 0;

    if (!validarEstructuraCarpetas()) return 1;

    try {
        for (const auto& entry : fs::directory_iterator(CARPETA_BASE)) {
            if (entry.is_directory()) {
                std::string ruta = entry.path().string() + "/datos.txt";
                std::ifstream archivo(ruta);
                if (archivo.is_open()) {
                    int id;
                    archivo >> id;
                    if (id > maxID) maxID = id;
                }
            }
        }
    } catch (...) {
        // Silenciar errores de lectura
    }

    return maxID + 1;
}
