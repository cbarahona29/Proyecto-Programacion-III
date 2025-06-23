#include <map>
#include <string>
#include <vector>
#include "ColaPacientes.h"
#include "Modulo de Gestion de Paciente/Paciente/ConsultaMedica.h"
#include "Modulo de Gestion Medico/Medico/Medico.h"
#include "Modulo de Gestion de Paciente/Paciente/Paciente.h"

using namespace std;

class ColasPorEspecialidad{
    private:
        map <string, ColaPacientes> mapaColas;

    public:
    void agregarPaciente(const Paciente& paciente, const string& especialidad){
        //& pq es una referencia(no crear copias inecesarias) y const para que no se puedan modificar
        mapaColas[especialidad].push(paciente);
    }; 

    bool estaVacia(const string& especialidad){
        auto locMapa = mapaColas.find(especialidad);
        return locMapa == mapaColas.end() || locMapa->second.estaVacia();
    };
    
    Paciente* atenderSiguientePaciente(const string& especialidad, const Medico& medico,
        string motivo, string diagnostico, string tratamiento, string notas, string fecha ){
        if(mapaColas.find(especialidad) == mapaColas.end()){
            return nullptr; //no se encontro la especialidad
        }

        Paciente* paciente = mapaColas[especialidad].pop(); //eliminar al paciente de la cola
        if(paciente){ //si se encontro un paciente y se elimino
            ConsultaMedica consultaRealizada= ConsultaMedica(medico,motivo,diagnostico,tratamiento,notas,fecha);
            ///FALTA AGREGAR AL EXPEDIENTE DEL PACIENTE
        }
        else{//no se encontro el paciente
            return nullptr;
        }
        return paciente; //despues se debe borrar el espacio en memoria de este al llamar la funcion
    };
    
    string mostrarColas(){
        string resultado;
        for (const auto& iteracion: mapaColas){
            const string& especialidad = iteracion.first; //primera clave del mapa
            const ColaPacientes& colaIteracion = iteracion.second; //segunda clave del mapa

            resultado+= "\n---------------"+ especialidad + "---------------";
            if (colaIteracion.estaVacia()){
                resultado+="\nNo hay pacientes en espera";
                continue;
            }
            vector<Paciente> pacientes = colaIteracion.obtenerPacientes();

            for (Paciente& paciente : pacientes){
                resultado+="-" + paciente.getNombre() + "\n";
            }

        }
         return resultado;
    };

    string mostrarColasFiltradas(const string& especialidadD){
        string resultado="";
        if(estaVacia(especialidadD)){
            resultado+= "No hay pacientes en la fila de espera de " + especialidadD;
            return resultado;
        }

        for (const auto& iteracion: mapaColas){
            const string& especialidad = iteracion.first; //primera clave del mapa
            const ColaPacientes& colaIteracion = iteracion.second; //segunda clave del mapa

            if (especialidad == especialidadD){

            }
            resultado+= "\n---------------"+ especialidad + "---------------";
            vector<Paciente> pacientes = colaIteracion.obtenerPacientes();

            for (Paciente& paciente : pacientes){
                resultado+="-" + paciente.getNombre() + "\n";
            }

        }
        return resultado;
        
    }

    int contarPacientes(const string& especialidadDeseada){
        int pacientesEnFila=0;

        for (const auto& iteracion: mapaColas){
            const string& especialidad = iteracion.first; //primera clave del mapa
            const ColaPacientes& colaIteracion = iteracion.second; //segunda clave del mapa

            if (especialidad == especialidadDeseada){
                vector<Paciente> pacientes = colaIteracion.obtenerPacientes();

                for (Paciente& paciente : pacientes){
                    pacientesEnFila++;
                }
            }       
        }
        return pacientesEnFila;
    }

    vector <string> obtenerEspecialidades(){
        vector<string> especialidades;
        for (const auto& ind: mapaColas){
            especialidades.push_back(ind.first);
        }
        return especialidades;
    }
};