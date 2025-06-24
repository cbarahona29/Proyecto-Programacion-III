#pragma once
#include <map>
#include <string>
#include <vector>
#include "ColaMedico.h" 
#include "../Medico/Medico.h"

using namespace std;

class ColasPorEspecialidad {
private:
    map<string, ColaMedico> mapaColas;

public:
    void agregarMedico(const Medico& medico, const string& especialidad) {
        mapaColas[especialidad].push(medico);
    }

    bool estaVacia(const string& especialidad) {
        auto locMapa = mapaColas.find(especialidad);
        return locMapa == mapaColas.end() || locMapa->second.estaVacia();
    }

    Medico* atenderSiguienteMedico(const string& especialidad) {
        if (mapaColas.find(especialidad) == mapaColas.end()) {
            return nullptr; // No se encontró la especialidad
        }

        Medico* medico = mapaColas[especialidad].pop(); // Eliminar al médico de la cola
        return medico; // Retornar puntero al médico
    }

    string mostrarColas() {
        string resultado;
        for (auto& iteracion : mapaColas) {
            const string& especialidad = iteracion.first;
            ColaMedico& colaIteracion = iteracion.second;

            resultado += "\n---------------" + especialidad + "---------------";
            if (colaIteracion.estaVacia()) {
                resultado += "\nNo hay médicos en espera";
                continue;
            }

            vector<Medico*> medicos = colaIteracion.obtenerMedicos();
            for (Medico* medico : medicos) {
                resultado += "-" + medico->getNombre() + "\n";
            }
        }
        return resultado;
    }

    string mostrarColasFiltradas(const string& especialidadD) {
        string resultado = "";
        if (estaVacia(especialidadD)) {
            resultado += "No hay médicos en la fila de espera de " + especialidadD;
            return resultado;
        }

        auto locMapa = mapaColas.find(especialidadD);
        if (locMapa != mapaColas.end()) {
            resultado += "\n---------------" + especialidadD + "---------------";
            vector<Medico*> medicos = locMapa->second.obtenerMedicos();

            for (Medico* medico : medicos) {
                resultado += "-" + medico->getNombre() + "\n";
            }
        }

        return resultado;
    }

    vector<Medico*> obtenerTodos() {
        vector<Medico*> resultado;
        for (auto& par : mapaColas) {
            vector<Medico*> medicos = par.second.obtenerMedicos();
            resultado.insert(resultado.end(), medicos.begin(), medicos.end());
        }
        return resultado;
    }
    
    int contarMedicos(const string& especialidadDeseada) {
        int medicosEnFila = 0;

        auto locMapa = mapaColas.find(especialidadDeseada);
        if (locMapa != mapaColas.end()) {
            vector<Medico*> medicos = locMapa->second.obtenerMedicos();
            medicosEnFila = medicos.size();
        }

        return medicosEnFila;
    }

    vector<string> obtenerEspecialidades() {
        vector<string> especialidades;
        for (const auto& ind : mapaColas) {
            especialidades.push_back(ind.first);
        }
        return especialidades;
    }
};
