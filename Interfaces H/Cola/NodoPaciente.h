#include "Paciente.h"

class NodoPaciente {
    public:
    NodoPaciente(Paciente paciente) {
        this->paciente = paciente;
        nodoSiguiente = nullptr;
    }
    
    NodoPaciente* getSiguiente(){
        return nodoSiguiente;
    }

    Paciente getPaciente() {
        return paciente;
    }

    void setSiguiente(NodoPaciente* nodoPaciente){
        nodoSiguiente = nodoPaciente;
    }
    private:
    Paciente paciente;
    NodoPaciente* nodoSiguiente;
};