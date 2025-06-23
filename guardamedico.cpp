#include "guardaMedico.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>
namespace fs = std::filesystem;
using std::string;
using std::ifstream;
using std::ofstream;

guardaMedico::guardaMedico() {
    try {
        if (!checkMainFolder()) {
            crearMainFolder();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error en constructor guardaMedico: " << e.what() << std::endl;
        throw;
    }
}

bool guardaMedico::checkMainFolder() {
    try {
        return fs::exists("Medicos") && fs::is_directory("Medicos");
    } catch (const std::exception& e) {
        std::cerr << "Error verificando carpeta principal: " << e.what() << std::endl;
        return false;
    }
}

void guardaMedico::crearMainFolder() {
    try {
        if (!fs::create_directory("Medicos")) {
            std::cerr << "Error: No se pudo crear la carpeta Medicos" << std::endl;
            throw std::runtime_error("No se pudo crear la carpeta Medicos");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error creando carpeta principal: " << e.what() << std::endl;
        throw;
    }
}

bool guardaMedico::existeMedico(int numColegiacion) {
    try {
        string path = "Medicos/Medico" + std::to_string(numColegiacion);
        return fs::exists(path) && fs::is_directory(path);
    } catch (const std::exception& e) {
        std::cerr << "Error verificando existencia de médico: " << e.what() << std::endl;
        return false;
    }
}

bool guardaMedico::registrarMedico(const Medico& medico) {
    try {
        int numColegiacion = medico.getNumColegiacion();

        // Verificar si ya existe
        if (existeMedico(numColegiacion)) {
            std::cout << "El médico ya existe con colegiación: " << numColegiacion << std::endl;
            return false;
        }

        // Crear carpeta del médico
        string path = "Medicos/Medico" + std::to_string(numColegiacion);

        if (!fs::create_directory(path)) {
            std::cerr << "Error: No se pudo crear la carpeta del médico: " << path << std::endl;
            return false;
        }

        // Registrar información
        bool resultado = registrarInfo(medico);
        if (!resultado) {
            // Si falla el registro de info, limpiar la carpeta creada
            fs::remove_all(path);
            std::cerr << "Error: Fallo al registrar información, carpeta eliminada" << std::endl;
        }

        return resultado;

    } catch (const std::exception& e) {
        std::cerr << "Error en registrarMedico: " << e.what() << std::endl;
        return false;
    }
}

bool guardaMedico::registrarInfo(const Medico& medico) {
    try {
        string path = "Medicos/Medico" + std::to_string(medico.getNumColegiacion()) + "/info.txt";
        std::cout << "Escribiendo en: " << path << std::endl;

        ofstream archivo(path, std::ios::out | std::ios::trunc);
        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo para escritura: " << path << std::endl;
            return false;
        }

        // Escribir datos con mejor manejo de errores
        archivo << medico.getID() << '\n';
        archivo << medico.getNumColegiacion() << '\n';
        archivo << medico.getNumIdentidad() << '\n';
        archivo << medico.getNumTelefono() << '\n';
        archivo << medico.getNombre() << '\n';
        archivo << medico.getEspecialidad() << '\n';
        archivo << medico.getFechaNacimiento() << '\n';
        archivo << medico.getEmail() << '\n';
        archivo << (medico.estaDisponible() ? "1" : "0") << '\n';

        // Verificar si la escritura fue exitosa
        if (archivo.fail()) {
            std::cerr << "Error durante la escritura del archivo" << std::endl;
            archivo.close();
            return false;
        }

        archivo.flush(); // Forzar escritura al disco
        archivo.close();

        // Verificar que el archivo se cerró correctamente
        if (archivo.is_open()) {
            std::cerr << "Advertencia: El archivo no se cerró correctamente" << std::endl;
        }

        std::cout << "Archivo guardado exitosamente: " << path << std::endl;
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error en registrarInfo: " << e.what() << std::endl;
        return false;
    }
}

Medico guardaMedico::extraerMedico(int numColegiacion) {
    try {
        string path = "Medicos/Medico" + std::to_string(numColegiacion) + "/info.txt";

        ifstream archivo(path);
        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo: " << path << std::endl;
            return Medico(); // Constructor por defecto
        }

        int ID, colegiacion, identidad, telefono;
        string nombre, especialidad, nacimiento, email;
        string disponibleStr;

        // Leer datos con validación
        if (!(archivo >> ID >> colegiacion >> identidad >> telefono)) {
            std::cerr << "Error leyendo datos numéricos del archivo" << std::endl;
            archivo.close();
            return Medico();
        }

        archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (!std::getline(archivo, nombre) ||
            !std::getline(archivo, especialidad) ||
            !std::getline(archivo, nacimiento) ||
            !std::getline(archivo, email) ||
            !std::getline(archivo, disponibleStr)) {
            std::cerr << "Error leyendo strings del archivo" << std::endl;
            archivo.close();
            return Medico();
        }

        bool disponible = (disponibleStr == "1");
        archivo.close();

        return Medico(ID, colegiacion, identidad, telefono, nombre,
                      especialidad, nacimiento, email, disponible);

    } catch (const std::exception& e) {
        std::cerr << "Error en extraerMedico: " << e.what() << std::endl;
        return Medico();
    }
}

int guardaMedico::obtenerProximoID() {
    try {
        int maxID = 0;

        if (!fs::exists("Medicos") || !fs::is_directory("Medicos")) {
            std::cout << "Carpeta Medicos no existe, retornando ID 1" << std::endl;
            return 1;
        }

        for (const auto& entry : fs::directory_iterator("Medicos")) {
            try {
                if (!entry.is_directory()) continue;

                string infoPath = entry.path().string() + "/info.txt";
                ifstream archivo(infoPath);

                if (!archivo.is_open()) {
                    std::cout << "No se pudo abrir: " << infoPath << std::endl;
                    continue;
                }

                int currentID = 0;
                if (archivo >> currentID) {
                    if (currentID > maxID) {
                        maxID = currentID;
                    }
                } else {
                    std::cout << "Error leyendo ID de: " << infoPath << std::endl;
                }

                archivo.close();

            } catch (const std::exception& e) {
                std::cerr << "Error procesando entrada: " << e.what() << std::endl;
                continue;
            }
        }

        int proximoID = maxID + 1;
        std::cout << "Próximo ID calculado: " << proximoID << std::endl;
        return proximoID;

    } catch (const std::exception& e) {
        std::cerr << "Error en obtenerProximoID: " << e.what() << std::endl;
        return 1; // ID por defecto
    }
}

bool guardaMedico::borrarInfo(int numColegiacion) {
    try {
        string path = "Medicos/Medico" + std::to_string(numColegiacion) + "/info.txt";
        return fs::remove(path);
    } catch (const std::exception& e) {
        std::cerr << "Error en borrarInfo: " << e.what() << std::endl;
        return false;
    }
}

bool guardaMedico::borrarMedico(int numColegiacion) {
    try {
        string path = "Medicos/Medico" + std::to_string(numColegiacion);
        return fs::remove_all(path) > 0;
    } catch (const std::exception& e) {
        std::cerr << "Error en borrarMedico: " << e.what() << std::endl;
        return false;
    }
}
