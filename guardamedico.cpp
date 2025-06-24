#include "guardaMedico.h"
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

guardaMedico::guardaMedico() {
    if (!checkMainFolder()) {
        crearMainFolder();
    }
}

bool guardaMedico::checkMainFolder() {
    return fs::exists("Medicos") && fs::is_directory("Medicos");
}

void guardaMedico::crearMainFolder() {
    try {
        fs::create_directory("Medicos");
    } catch (const std::exception& e) {
        cout << "Error al crear carpeta principal: " << e.what() << endl;
    }
}

bool guardaMedico::existeMedico(int numColegiacion) {
    return fs::exists("Medicos/Medico" + std::to_string(numColegiacion));
}

bool guardaMedico::registrarMedico(const Medico& medico) {
    int numColegiacion = medico.getNumColegiacion();
    string path = "Medicos/Medico" + std::to_string(numColegiacion);

    if (existeMedico(numColegiacion)) return false;

    try {
        fs::create_directory(path);
        return registrarInfo(medico);
    } catch (...) {
        return false;
    }
}

bool guardaMedico::registrarInfo(const Medico& medico) {
    string path = "Medicos/Medico" + std::to_string(medico.getNumColegiacion()) + "/info.txt";

    try {
        ofstream archivo(path);
        if (!archivo) return false;

        archivo << medico.getID() << '\n'
                << medico.getNumColegiacion() << '\n'
                << medico.getNumIdentidad() << '\n'
                << medico.getNumTelefono() << '\n'
                << medico.getNombre() << '\n'
                << medico.getEspecialidad() << '\n'
                << medico.getFechaNacimiento() << '\n'
                << medico.getEmail() << '\n'
                << medico.estaDisponible() << '\n';
        archivo.close();

        return fs::exists(path);
    } catch (...) {
        return false;
    }
}

Medico guardaMedico::extraerMedico(int numColegiacion) {
    string path = "Medicos/Medico" + std::to_string(numColegiacion) + "/info.txt";
    ifstream archivo(path);
    if (!archivo) return Medico();

    int ID, identidad, telefono;
    string nombre, especialidad, nacimiento, email;
    bool disponible;

    archivo >> ID >> numColegiacion >> identidad >> telefono;
    archivo.ignore();
    std::getline(archivo, nombre);
    std::getline(archivo, especialidad);
    std::getline(archivo, nacimiento);
    std::getline(archivo, email);
    archivo >> disponible;
    archivo.close();

    return Medico(ID, numColegiacion, identidad, telefono, nombre, especialidad, nacimiento, email, disponible);
}

bool guardaMedico::borrarInfo(int numColegiacion) {
    return fs::remove("Medicos/Medico" + std::to_string(numColegiacion) + "/info.txt");
}

bool guardaMedico::borrarMedico(int numColegiacion) {
    return fs::remove_all("Medicos/Medico" + std::to_string(numColegiacion));
}

int guardaMedico::obtenerSiguienteID() {
    std::vector<int> ids = obtenerTodosLosIDs();
    return ids.empty() ? 0 : (*std::max_element(ids.begin(), ids.end()) + 1);
}

std::vector<int> guardaMedico::obtenerTodosLosIDs() {
    std::vector<int> ids;
    if (!checkMainFolder()) return ids;

    for (const auto& entry : fs::directory_iterator("Medicos")) {
        if (entry.is_directory()) {
            string nombre = entry.path().filename().string();
            if (nombre.substr(0, 6) == "Medico") {
                try {
                    int colegiacion = std::stoi(nombre.substr(6));
                    ifstream archivo(entry.path().string() + "/info.txt");
                    if (archivo) {
                        int id;
                        archivo >> id;
                        ids.push_back(id);
                    }
                } catch (...) {
                    continue;
                }
            }
        }
    }
    return ids;
}
