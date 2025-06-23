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

// Verifica si existe una carpeta con el ID del paciente
bool guardaPaciente::existePaciente(int ID) {
    string path = "../../Folders Guarda Datos/Pacientes/Paciente" + ID;
    return fs::exists(path) && fs::is_directory(path);
}

vector<Paciente> guardaPaciente::extractPacientes () {
    string mainFolder = "../../Folders Guarda Datos/Pacientes";
    vector<Paciente> pacientes;

    for (const auto& entry : fs::directory_iterator(mainFolder)) {
        if (entry.is_directory() ) {
            for (const auto& entry2 : fs::directory_iterator(entry.path())){
                pacientes.push_back(extraerPaciente(entry2.path()));
            }
        }
    }

    return pacientes;
}

// Crea carpeta para paciente y registra su info
bool guardaPaciente::registrarPaciente(const Paciente& paciente) {
    int ID = paciente.getID();
    if (existePaciente(ID)) return false; // ya existe

    std::string path = "../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(paciente.getID());
    return fs::create_directory(path) && registrarInfo(paciente) && crearExpediente(paciente.getID()); 
}

// Guarda info del paciente en texto
bool guardaPaciente::registrarInfo(const Paciente& paciente) {
    string path = "../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(paciente.getID()) + "/info.txt";
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

Paciente guardaPaciente::extraerPaciente (const fs::path& carpetaPaciente) {
    fs::path infoPath;
    fs::path binPath;

    // Buscar archivos dentro de la carpeta del paciente
    for (const auto& archivo : fs::directory_iterator(carpetaPaciente)) {
        if (archivo.path().extension() == ".txt") {
            infoPath = archivo.path();
        } else if (archivo.path().extension() == ".bin") {
            binPath = archivo.path();
        }
    }

    // Verificar que ambos archivos existan
    if (!infoPath.empty() && !binPath.empty()) {
        ifstream archivo(infoPath);

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
        Paciente paciente = Paciente(id, nombre, nacimiento, direccion, identidad, telefono, email, genero, alergias);

        // Aquí puede leer expediente.bin (por ejemplo, binario puro)
        std::ifstream archivo2(binPath, std::ios::binary);

        ConsultaMedica c;
        while (archivo2.read(reinterpret_cast<char*>(&c), sizeof(ConsultaMedica))) {
            paciente.getExpediente().agregarConsulta(c);  
        }

        archivo.close();
        return paciente;
    } else {
        std::cerr << "  Archivos faltantes en: " << carpetaPaciente << "\n";
    }
    return Paciente(false);
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
bool guardaPaciente::borrarInfo(int ID) {
    return fs::remove("../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(ID) + "/info.txt");
}

bool guardaPaciente::borrarExpediente(int ID) {
    return fs::remove("../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(ID) + "/expediente.bin");
}

bool guardaPaciente::borrarPaciente(int ID) {
    return fs::remove_all("../../Folders Guarda Datos/Pacientes/Paciente" + std::to_string(ID));
}
