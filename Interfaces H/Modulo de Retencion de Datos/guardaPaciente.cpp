#include "guardaPaciente.h"
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;
using std::cout;
using std::endl;

// Constructor: crea carpeta principal si no existe
guardaPaciente::guardaPaciente() {
    if (!checkMainFolder()) {
        crearMainFolder();
    }
}

// Verifica si la carpeta "Pacientes" existe
bool guardaPaciente::checkMainFolder() {
    return fs::exists("../../Folders Guarda Datos/Pacientes") && fs::is_directory("../../Folders Guarda Datos/Pacientes");
}

// Crea carpeta "Pacientes"
void guardaPaciente::crearMainFolder() {
    fs::create_directory("../../Folders Guarda Datos/Pacientes");
}

// Verifica si existe una carpeta con el nombre del paciente
bool guardaPaciente::existePaciente(string& nombrePaciente) {
    string path = "../../Folders Guarda Datos/Pacientes/" + nombrePaciente;
    return fs::exists(path) && fs::is_directory(path);
}

// Crea carpeta para paciente y registra su info
bool guardaPaciente::registrarPaciente(const Paciente& paciente) {
    string nombre = paciente.getNombre();
    if (existePaciente(nombre)) return false; // ya existe

    std::string path = "../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(paciente.getID());
    return fs::create_directory(path) && registrarInfo(paciente) && crearExpediente(paciente.getID()); 
}

// Guarda info del paciente en texto
bool guardaPaciente::registrarInfo(const Paciente& paciente) {
    string path = "Pacientes/" + paciente.getNombre() + "/info.txt";
    ofstream archivo(path);
    if (!archivo) return false;

    archivo << paciente.getID() << '\n';
    archivo << paciente.getNombre() << '\n';
    archivo << paciente.getFechaNacimiento() << '\n';
    archivo << paciente.getDireccion() << '\n';
    archivo << paciente.getNumIdentidad() << '\n';
    archivo << paciente.getNumTelefono() << '\n';
    archivo << paciente.getEmail() << '\n';
    archivo << paciente.getGenero() << '\n';
    archivo << paciente.getAlergias() << '\n';

    archivo.close();
    return true;
}

Paciente guardaPaciente::extraerPaciente (int ID) {
    Paciente paciente = extraerInfoPaciente(ID);
    paciente.setExpediente(leerExpediente(ID));

    return paciente;
}

// Extrae info del paciente desde info.txt
Paciente guardaPaciente::extraerInfoPaciente(int ID) {
    std::string path = "../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(ID) + "/info.txt";
    ifstream archivo(path);
    if (!archivo) return Paciente (false);

    int id, identidad, telefono;
    string nombre, nacimiento, direccion, email, genero, alergias;

    archivo >> id;
    archivo.ignore(); // para eliminar el \n
    getline(archivo, nombre);
    getline(archivo, nacimiento);
    getline(archivo, direccion);
    archivo >> identidad;
    archivo >> telefono;
    archivo.ignore();
    getline(archivo, email);
    getline(archivo, genero);
    getline(archivo, alergias);

    archivo.close();
    return Paciente(id, nombre, nacimiento, direccion, identidad, telefono, email, genero, alergias);
}

// Crea archivo binario vacío del expediente
bool guardaPaciente::crearExpediente(int ID) {
    std::string ruta = "../../Folders Guarda Datos/Pacientes/Paciente"+ std::to_string(ID) +"/ExpedienteClinico.bin";
    ofstream expediente (ruta, std::ios::binary);

    if (expediente.is_open()) {
        expediente.close();
        return true;
    } 
    return false;
}

// Guarda una consulta dentro del expediente
bool guardaPaciente::guardarConsulta(const Paciente& paciente, const ConsultaMedica& consulta) {
    // Abre el archivo y lo configura para hacer append
    std::string ruta = "../../Folders Guarda Datos/Pacientes/Paciente"+ std::to_string(paciente.getID()) +"/ExpedienteClinico.bin";
    ofstream expediente (ruta, std::ios::binary | std::ios::app);

    if (expediente.is_open()) {
        if (expediente.write(reinterpret_cast<const char*>(&consulta), sizeof(consulta))){
            expediente.close();
            return true;
        }
    }
    return false;
}

// Lee y devuelve el expediente médico
ExpedienteMedico guardaPaciente::leerExpediente(int ID) {
    ExpedienteMedico expediente;

    std::string ruta = "../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(ID) + "/ExpedienteClinico.bin";

    std::ifstream archivo(ruta, std::ios::binary);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el expediente binario del paciente con ID " << ID << '\n';
        return expediente;  // Devuelve objeto vacío
    }

    ConsultaMedica c;
    while (archivo.read(reinterpret_cast<char*>(&c), sizeof(ConsultaMedica))) {
        expediente.agregarConsulta(c);  
    }

    archivo.close();
    return expediente;
}

// Eliminar info, expediente y carpeta del paciente
bool guardaPaciente::borrarInfo(string& nombrePaciente) {
    return fs::remove("../../Folders Guarda Datos/Pacientes/" + nombrePaciente + "/info.txt");
}

bool guardaPaciente::borrarExpediente(string& nombrePaciente) {
    return fs::remove("../../Folders Guarda Datos/Pacientes/" + nombrePaciente + "/expediente.bin");
}

bool guardaPaciente::borrarPaciente(string& nombrePaciente) {
    return fs::remove_all("../../Folders Guarda Datos/Pacientes/" + nombrePaciente);
}
