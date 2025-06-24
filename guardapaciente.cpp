#include "guardaPaciente.h"
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using std::string;
using std::ifstream;
using std::ofstream;

guardaPaciente::guardaPaciente() {
    if (!checkMainFolder()) crearMainFolder();
}

bool guardaPaciente::checkMainFolder() {
    return fs::exists("Pacientes") && fs::is_directory("Pacientes");
}

void guardaPaciente::crearMainFolder() {
    fs::create_directory("Pacientes");
}

bool guardaPaciente::existePaciente(int ID) {
    return fs::exists("Pacientes/Paciente" + std::to_string(ID));
}

bool guardaPaciente::registrarPaciente(const Paciente& paciente) {
    int ID = paciente.getID();
    string path = "Pacientes/Paciente" + std::to_string(ID);
    return !existePaciente(ID)
           && fs::create_directory(path)
           && registrarInfo(paciente)
           && crearExpediente(ID);
}

bool guardaPaciente::registrarInfo(const Paciente& paciente) {
    string path = "Pacientes/Paciente" + std::to_string(paciente.getID()) + "/info.txt";
    ofstream archivo(path);
    if (!archivo) return false;

    archivo << paciente.getID() << '\n'
            << paciente.getNombre() << '\n'
            << paciente.getFechaNacimiento() << '\n'
            << paciente.getDireccion() << '\n'
            << paciente.getNumIdentidad() << '\n'
            << paciente.getNumTelefono() << '\n'
            << paciente.getEmail() << '\n'
            << paciente.getGenero() << '\n'
            << paciente.getAlergias() << '\n';

    return true;
}

Paciente guardaPaciente::extraerPaciente(int ID) {
    Paciente paciente = extraerInfoPaciente(ID);
    paciente.setExpediente(leerExpediente(ID));
    return paciente;
}

Paciente guardaPaciente::extraerInfoPaciente(int ID) {
    string path = "Pacientes/Paciente" + std::to_string(ID) + "/info.txt";
    ifstream archivo(path);
    if (!archivo) return Paciente(false);

    int id, identidad, telefono;
    string nombre, nacimiento, direccion, email, genero, alergias;

    archivo >> id;
    archivo.ignore();
    std::getline(archivo, nombre);
    std::getline(archivo, nacimiento);
    std::getline(archivo, direccion);
    archivo >> identidad >> telefono;
    archivo.ignore();
    std::getline(archivo, email);
    std::getline(archivo, genero);
    std::getline(archivo, alergias);

    return Paciente(id, nombre, nacimiento, direccion, identidad, telefono, email, genero, alergias);
}

bool guardaPaciente::crearExpediente(int ID) {
    string path = "Pacientes/Paciente" + std::to_string(ID) + "/ExpedienteClinico.bin";
    ofstream expediente(path, std::ios::binary);
    return expediente.is_open();
}

bool guardaPaciente::guardarConsulta(const Paciente& paciente, const ConsultaMedica& consulta) {
    string path = "Pacientes/Paciente" + std::to_string(paciente.getID()) + "/ExpedienteClinico.bin";
    ofstream archivo(path, std::ios::binary | std::ios::app);
    return archivo.is_open() && archivo.write(reinterpret_cast<const char*>(&consulta), sizeof(ConsultaMedica));
}

ExpedienteMedico guardaPaciente::leerExpediente(int ID) {
    ExpedienteMedico expediente;
    string path = "Pacientes/Paciente" + std::to_string(ID) + "/ExpedienteClinico.bin";
    ifstream archivo(path, std::ios::binary);

    if (!archivo.is_open()) return expediente;

    ConsultaMedica c;
    while (archivo.read(reinterpret_cast<char*>(&c), sizeof(ConsultaMedica))) {
        expediente.agregarConsulta(c);
    }

    return expediente;
}

bool guardaPaciente::borrarInfo(int ID) {
    return fs::remove("Pacientes/Paciente" + std::to_string(ID) + "/info.txt");
}

bool guardaPaciente::borrarExpediente(int ID) {
    return fs::remove("Pacientes/Paciente" + std::to_string(ID) + "/ExpedienteClinico.bin");
}

bool guardaPaciente::borrarPaciente(int ID) {
    return borrarInfo(ID) && borrarExpediente(ID) && fs::remove_all("Pacientes/Paciente" + std::to_string(ID));
}

int guardaPaciente::obtenerProximoID() {
    if (!checkMainFolder()) {
        crearMainFolder();
        return 1;
    }

    int maxID = 0;
    for (const auto& entrada : fs::directory_iterator("Pacientes")) {
        if (entrada.is_directory()) {
            string nombre = entrada.path().filename().string();
            if (nombre.substr(0, 8) == "Paciente") {
                try {
                    int id = std::stoi(nombre.substr(8));
                    maxID = std::max(maxID, id);
                } catch (...) {}
            }
        }
    }

    return maxID + 1;
}
