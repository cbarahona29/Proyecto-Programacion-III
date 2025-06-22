#include <thread>
#include <map>
#include <string>
#include "ColasPorEspecialidad.h"
#include "Medico.h"
using namespace std;

class Estadisticas{
    
    private:
    bool estaActivo;
    thread hilo;
    ColasPorEspecialidad& colas;
    const map<int, Medico*>& medicos; //keys: id y el objeto de medico

    string obtenerEstadisticas(){
        string resultado;
        resultado+="-------Pacientes en espera-------\n";

        for(const string& especialidad: colas.obtenerEspecialidades()){
            resultado+= especialidad + ": " + to_string(colas.contarPacientes(especialidad)) + " pacientes\n";
        };

        resultado+="-------Medicos disponibles-------\n";
        int medDisponibles=0;
        for(const auto& ind: medicos){
            if(ind.second->estaDisponible()){
                resultado+=ind.second->getNombre() + "\n";
                medDisponibles++;
            }
            resultado+="\t" + to_string(medDisponibles) + "/" + to_string(medicos.size()) + " medicos disponibles";
        }
        return resultado;        
    }

    void hiloEstadisticas(){
        while(estaActivo){
            string estadisticas = obtenerEstadisticas();

            //esperar 20 segundos cada vez
            for(int i=0; i<20 && estaActivo; i++){
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }

    public:

    Estadisticas(ColasPorEspecialidad& colas,const map<int ,Medico*> medicos)
        :colas(colas),medicos(medicos),estaActivo(true){
            hilo = thread(&Estadisticas::hiloEstadisticas, this);
        }
    

    void detenerHilo(){
        estaActivo = false;
        if(hilo.joinable()){
            hilo.join();
        }
    }
};