#include "guardaMedico.h"
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;
using std::cout;
using std::endl;

// Chequea si existe el folder
guardaMedico::guardaMedico () {
    if (!checkMainFolder()){
        crearMainFolder();
    }
}

// Verifica si la carpeta "Medicos" existe
bool guardaMedico::checkMainFolder() {
    return fs::exists("../../Folders Guarda Datos/Medicos") && fs::is_directory("../../Folders Guarda Datos/Medicos");
}

// Crea carpeta "Medicos"
void guardaMedico::crearMainFolder() {
    fs::create_directory("../../Folders Guarda Datos/Medicos");
}

// Verifica si existe una carpeta con el numero de colegiacion del medico
bool guardaMedico::existeMedico(int numColegiacion) {
    string path = "../../Folders Guarda Datos/Medicos/Medico" + std::to_string(numColegiacion);
    return fs::exists(path) && fs::is_directory(path);
}

// Crea carpeta para paciente y registra su info
bool guardaMedico::registrarMedico(const Medico& medico) {
    int numColegiacion = medico.getNumColegiacion();
    if (existeMedico(numColegiacion)) return false; // ya existe

    std::string path = "../../Folders Guarda Datos/Medicos/Medico" + std::to_string(numColegiacion);
    return fs::create_directory(path) && registrarInfo(medico); 
}

// Extrae info de Medico
Medico guardaMedico::extraerMedico (int numColegiacion){
    std::string path = "../../Folders Guarda Datos/Medicos/Medico" + std::to_string(numColegiacion) + "/info.txt";
    std::ifstream archivo(path);
    if (!archivo) return Medico(); // retorna un objeto default si falla

    int ID, identidad, telefono;
    string nombre, especialidad, nacimiento, email;
    bool disponible;

    archivo >> ID;
    archivo >> numColegiacion;
    archivo >> identidad;
    archivo >> telefono;
    archivo.ignore(); // limpiar el \n
    std::getline(archivo, nombre);
    std::getline(archivo, especialidad);
    std::getline(archivo, nacimiento);
    std::getline(archivo, email);
    archivo >> disponible;

    archivo.close();

    return Medico(ID, numColegiacion, identidad, telefono, nombre, especialidad, nacimiento, email, disponible);
}

// Guarda info del Medico en texto
bool guardaMedico::registrarInfo(const Medico& medico) {
    string path = "../../Folders Guarda Datos/Medicos/Medico" + std::to_string(medico.getNumColegiacion()) + "/info.txt";
    ofstream archivo(path);
    if (!archivo) return false;

    archivo << medico.getID() << '\n';
    archivo << medico.getNumColegiacion() << '\n';
    archivo << medico.getNumIdentidad() << '\n';
    archivo << medico.getNumTelefono() << '\n';
    archivo << medico.getNombre() << '\n';
    archivo << medico.getEspecialidad() << '\n';
    archivo << medico.getFechaNacimiento() << '\n';
    archivo << medico.getEmail() << '\n';
    archivo << medico.estaDisponible() << '\n';

    archivo.close();
    return true;
}

// Eliminar/Borrar Medico ***
bool guardaMedico::borrarInfo (int numColegiacion) {
    return fs::remove("../../Folders Guarda Datos/Medicos/Medico" + std::to_string(numColegiacion) + "/info.txt");
}

bool guardaMedico::borrarMedico (int numColegiacion) {
    return fs::remove_all("../../Folders Guarda Datos/Medicos/Medico" + std::to_string(numColegiacion));
}