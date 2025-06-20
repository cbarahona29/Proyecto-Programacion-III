#include <map>
#include <string>
#include <vector>
#include "ColaPacientes.h"
#include "Paciente.h"

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
    
    Paciente* atenderSiguientePaciente(const string& especialidad){
        if(mapaColas.find(especialidad) == mapaColas.end()){
            return nullptr; //no se encontro la especialidad
        }

        Paciente* paciente = mapaColas[especialidad].pop(); //eliminar al paciente de la cola
        if(paciente){ //si se encontro un paciente y se elimino
            //se atencio x paciente
        }
        else{
            //no se encontro paciente
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
    };
};