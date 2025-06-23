#include <thread>
#include <map>
#include <string>
#include "../Modulo de Gestion de Paciente/Gestion/gestionPaciente.cpp"
#include "../Modulo de Gestion de Paciente/Paciente/Paciente.h"
using namespace std;

class Automatizacion{
    
    private:
    bool estaActivo;
    thread hilo;

    string guardarAutomatico(){
        gestionPaciente gestor;
        for (Paciente* paciente : gestor.mostrarPacientes()){
            Paciente objPaciente = paciente;  
            gestor.guardarPaciente(objPaciente);
        }
    }

    void hiloEstadisticas(){
        while(estaActivo){
            guardarAutomatico();
            //esperar 20 segundos cada vez
            for(int i=0; i<20 && estaActivo; i++){
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }

    public:

    void detenerHilo(){
        estaActivo = false;
        if(hilo.joinable()){
            hilo.join();
        }
    }
};