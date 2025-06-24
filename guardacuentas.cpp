#include "guardaCuentas.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;
using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

guardaCuentas::guardaCuentas(guardaMedico* _gestorMedicos) : gestorMedicos(_gestorMedicos) {
    cout << "Inicializando guardaCuentas..." << endl;
    inicializarCarpetas();
}

void guardaCuentas::inicializarCarpetas() {
    // Crear todas las carpetas necesarias de una vez
    const string carpetas[] = {"Cuentas", "Cuentas/Doctores", "Cuentas/Recepcionistas"};

    for (const auto& carpeta : carpetas) {
        if (!fs::exists(carpeta)) {
            try {
                fs::create_directories(carpeta);
                cout << "Carpeta creada: " << carpeta << endl;
            } catch (const std::exception& e) {
                cout << "Error creando " << carpeta << ": " << e.what() << endl;
            }
        }
    }
}

bool guardaCuentas::existeUsuario(const string& usuario) {
    return !extraerCuentaPorUsuario(usuario).usuario.empty();
}

bool guardaCuentas::verificarMedicoExiste(int numColegiacion) {
    return gestorMedicos ? gestorMedicos->existeMedico(numColegiacion) : true;
}

bool guardaCuentas::crearCuentaDoctor(const string& usuario, const string& contrasena, int numColegiacion) {
    cout << "Creando cuenta doctor: " << numColegiacion << endl;

    if (!verificarMedicoExiste(numColegiacion)) {
        cout << "ERROR: Médico no existe" << endl;
        return false;
    }

    if (existeCuentaDoctor(numColegiacion) || existeUsuario(usuario)) {
        cout << "ERROR: Cuenta o usuario ya existe" << endl;
        return false;
    }

    string path = obtenerRutaDoctor(numColegiacion);
    if (crearCarpeta(path)) {
        Cuenta cuenta(0, usuario, contrasena, TipoCuenta::DOCTOR, numColegiacion, true);
        return guardarCredenciales(cuenta, path);
    }
    return false;
}

bool guardaCuentas::crearCuentaRecepcionista(const string& usuario, const string& contrasena) {
    cout << "Creando cuenta recepcionista..." << endl;

    if (existeUsuario(usuario)) {
        cout << "ERROR: Usuario ya existe" << endl;
        return false;
    }

    int siguienteID = obtenerSiguienteIDRecepcionista();
    string path = obtenerRutaRecepcionista(siguienteID);

    if (crearCarpeta(path)) {
        Cuenta cuenta(siguienteID, usuario, contrasena, TipoCuenta::RECEPCIONISTA, siguienteID, true);
        return guardarCredenciales(cuenta, path);
    }
    return false;
}

Cuenta guardaCuentas::extraerCuentaPorUsuario(const string& usuario) {
    // Buscar en ambas carpetas
    const string carpetas[] = {"Cuentas/Doctores", "Cuentas/Recepcionistas"};
    const TipoCuenta tipos[] = {TipoCuenta::DOCTOR, TipoCuenta::RECEPCIONISTA};

    for (int i = 0; i < 2; i++) {
        try {
            for (const auto& entry : fs::directory_iterator(carpetas[i])) {
                if (entry.is_directory()) {
                    Cuenta cuenta = leerCredenciales(entry.path().string(), tipos[i]);
                    if (cuenta.usuario == usuario) {
                        return cuenta;
                    }
                }
            }
        } catch (const std::exception& e) {
            cout << "Error buscando en " << carpetas[i] << ": " << e.what() << endl;
        }
    }
    return Cuenta(); // Cuenta vacía
}

bool guardaCuentas::autenticarUsuario(const string& usuario, const string& contrasena) {
    Cuenta cuenta = extraerCuentaPorUsuario(usuario);
    if (cuenta.usuario.empty() || !cuenta.activa) {
        cout << "Usuario no encontrado o cuenta inactiva" << endl;
        return false;
    }

    bool autenticado = (cuenta.contrasena == contrasena);
    cout << "Autenticación: " << (autenticado ? "exitosa" : "fallida") << endl;
    return autenticado;
}

TipoCuenta guardaCuentas::obtenerTipoCuenta(const string& usuario) {
    return extraerCuentaPorUsuario(usuario).tipo;
}

bool guardaCuentas::cambiarContrasena(const string& usuario, const string& contrasenaActual, const string& nuevaContrasena) {
    if (!autenticarUsuario(usuario, contrasenaActual)) {
        return false;
    }

    Cuenta cuenta = extraerCuentaPorUsuario(usuario);
    cuenta.contrasena = nuevaContrasena;

    string path = (cuenta.tipo == TipoCuenta::DOCTOR) ?
                      obtenerRutaDoctor(cuenta.referenciaID) :
                      obtenerRutaRecepcionista(cuenta.referenciaID);

    return guardarCredenciales(cuenta, path);
}

bool guardaCuentas::activarDesactivarCuenta(const string& usuario, bool activar) {
    Cuenta cuenta = extraerCuentaPorUsuario(usuario);
    if (cuenta.usuario.empty()) return false;

    cuenta.activa = activar;
    string path = (cuenta.tipo == TipoCuenta::DOCTOR) ?
                      obtenerRutaDoctor(cuenta.referenciaID) :
                      obtenerRutaRecepcionista(cuenta.referenciaID);

    return guardarCredenciales(cuenta, path);
}

bool guardaCuentas::eliminarCuentaPorUsuario(const string& usuario) {
    Cuenta cuenta = extraerCuentaPorUsuario(usuario);
    if (cuenta.usuario.empty()) return false;

    string path = (cuenta.tipo == TipoCuenta::DOCTOR) ?
                      obtenerRutaDoctor(cuenta.referenciaID) :
                      obtenerRutaRecepcionista(cuenta.referenciaID);

    try {
        return fs::remove_all(path) > 0;
    } catch (const std::exception& e) {
        cout << "Error eliminando cuenta: " << e.what() << endl;
        return false;
    }
}

std::vector<Cuenta> guardaCuentas::obtenerTodasLasCuentas() {
    std::vector<Cuenta> cuentas;
    obtenerCuentasPorTipo("Cuentas/Doctores", TipoCuenta::DOCTOR, cuentas);
    obtenerCuentasPorTipo("Cuentas/Recepcionistas", TipoCuenta::RECEPCIONISTA, cuentas);
    return cuentas;
}

// Métodos auxiliares privados
bool guardaCuentas::crearCarpeta(const string& path) {
    try {
        return fs::create_directory(path) || fs::exists(path);
    } catch (const std::exception& e) {
        cout << "Error creando carpeta: " << e.what() << endl;
        return false;
    }
}

bool guardaCuentas::guardarCredenciales(const Cuenta& cuenta, const string& path) {
    string archivoPath = path + "/credenciales.txt";
    try {
        ofstream archivo(archivoPath);
        if (!archivo) return false;

        archivo << cuenta.id << '\n'
                << cuenta.usuario << '\n'
                << cuenta.contrasena << '\n'
                << cuenta.activa << '\n';
        archivo.close();

        return fs::exists(archivoPath);
    } catch (const std::exception& e) {
        cout << "Error guardando credenciales: " << e.what() << endl;
        return false;
    }
}

Cuenta guardaCuentas::leerCredenciales(const string& path, TipoCuenta tipo) {
    string archivoPath = path + "/credenciales.txt";
    ifstream archivo(archivoPath);
    if (!archivo) return Cuenta();

    int id;
    string usuario, contrasena;
    bool activa;

    archivo >> id;
    archivo.ignore();
    std::getline(archivo, usuario);
    std::getline(archivo, contrasena);
    archivo >> activa;
    archivo.close();

    // Extraer ID de referencia del nombre de la carpeta
    string carpetaNombre = fs::path(path).filename().string();
    int referenciaID = (tipo == TipoCuenta::DOCTOR) ?
                           std::stoi(carpetaNombre.substr(6)) :  // "Doctor" = 6 chars
                           std::stoi(carpetaNombre.substr(13)); // "Recepcionista" = 13 chars

    return Cuenta(id, usuario, contrasena, tipo, referenciaID, activa);
}

void guardaCuentas::obtenerCuentasPorTipo(const string& carpeta, TipoCuenta tipo, std::vector<Cuenta>& cuentas) {
    try {
        if (!fs::exists(carpeta)) return;

        for (const auto& entry : fs::directory_iterator(carpeta)) {
            if (entry.is_directory()) {
                Cuenta cuenta = leerCredenciales(entry.path().string(), tipo);
                if (!cuenta.usuario.empty()) {
                    cuentas.push_back(cuenta);
                }
            }
        }
    } catch (const std::exception& e) {
        cout << "Error obteniendo cuentas de " << carpeta << ": " << e.what() << endl;
    }
}

int guardaCuentas::obtenerSiguienteIDRecepcionista() {
    int maxID = -1;
    try {
        if (fs::exists("Cuentas/Recepcionistas")) {
            for (const auto& entry : fs::directory_iterator("Cuentas/Recepcionistas")) {
                if (entry.is_directory()) {
                    string carpetaNombre = entry.path().filename().string();
                    if (carpetaNombre.substr(0, 13) == "Recepcionista") {
                        int id = std::stoi(carpetaNombre.substr(13));
                        maxID = std::max(maxID, id);
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        cout << "Error obteniendo siguiente ID: " << e.what() << endl;
    }
    return maxID + 1;
}

// Métodos inline simples
bool guardaCuentas::existeCuentaDoctor(int numColegiacion) {
    return fs::exists(obtenerRutaDoctor(numColegiacion));
}

bool guardaCuentas::existeCuentaRecepcionista(int idRecepcionista) {
    return fs::exists(obtenerRutaRecepcionista(idRecepcionista));
}

string guardaCuentas::obtenerRutaDoctor(int numColegiacion) {
    return "Cuentas/Doctores/Doctor" + std::to_string(numColegiacion);
}

string guardaCuentas::obtenerRutaRecepcionista(int idRecepcionista) {
    return "Cuentas/Recepcionistas/Recepcionista" + std::to_string(idRecepcionista);
}

bool guardaCuentas::activarCuenta(const string& usuario) {
    return activarDesactivarCuenta(usuario, true);
}

bool guardaCuentas::desactivarCuenta(const string& usuario) {
    return activarDesactivarCuenta(usuario, false);
}
