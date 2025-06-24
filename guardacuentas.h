#ifndef GUARDACUENTAS_H
#define GUARDACUENTAS_H

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include "Medico.h"
#include "guardaMedico.h"

namespace fs = std::filesystem;
using std::string;

enum class TipoCuenta {
    DOCTOR,
    RECEPCIONISTA
};

struct Cuenta {
    int id;
    string usuario;
    string contrasena;
    TipoCuenta tipo;
    int referenciaID;
    bool activa;

    Cuenta() : id(0), usuario(""), contrasena(""), tipo(TipoCuenta::RECEPCIONISTA), referenciaID(0), activa(true) {}
    Cuenta(int _id, const string& _usuario, const string& _contrasena, TipoCuenta _tipo, int _referenciaID, bool _activa = true)
        : id(_id), usuario(_usuario), contrasena(_contrasena), tipo(_tipo), referenciaID(_referenciaID), activa(_activa) {}
};

class guardaCuentas {
private:
    guardaMedico* gestorMedicos;

public:
    guardaCuentas(guardaMedico* _gestorMedicos = nullptr);

    // Verificación y creación de carpetas
    void inicializarCarpetas();

    // Registro de cuentas
    bool crearCuentaDoctor(const string& usuario, const string& contrasena, int numColegiacion);
    bool crearCuentaRecepcionista(const string& usuario, const string& contrasena);

    // Autenticación y gestión
    bool autenticarUsuario(const string& usuario, const string& contrasena);
    TipoCuenta obtenerTipoCuenta(const string& usuario);
    bool cambiarContrasena(const string& usuario, const string& contrasenaActual, const string& nuevaContrasena);
    bool activarCuenta(const string& usuario);
    bool desactivarCuenta(const string& usuario);

    // Eliminación
    bool eliminarCuentaPorUsuario(const string& usuario);

    // Verificaciones
    bool existeCuentaDoctor(int numColegiacion);
    bool existeCuentaRecepcionista(int idRecepcionista);
    bool existeUsuario(const string& usuario);

    // Extracción de cuentas
    Cuenta extraerCuentaPorUsuario(const string& usuario);

    // Utilidades
    int obtenerSiguienteIDRecepcionista();
    std::vector<Cuenta> obtenerTodasLasCuentas();

private:
    // Internos
    bool verificarMedicoExiste(int numColegiacion);
    bool crearCarpeta(const string& path);
    bool guardarCredenciales(const Cuenta& cuenta, const string& path);
    Cuenta leerCredenciales(const string& path, TipoCuenta tipo);
    void obtenerCuentasPorTipo(const string& carpeta, TipoCuenta tipo, std::vector<Cuenta>& cuentas);
    bool activarDesactivarCuenta(const string& usuario, bool activar);

    // Rutas
    string obtenerRutaDoctor(int numColegiacion);
    string obtenerRutaRecepcionista(int idRecepcionista);
};

#endif // GUARDACUENTAS_H
