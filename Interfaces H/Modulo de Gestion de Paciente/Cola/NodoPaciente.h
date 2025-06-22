#include "../Paciente/Paciente.h"

class NodoPaciente {
    public:
    NodoPaciente(Paciente paciente) {
        this->paciente = paciente;
        nodoSiguiente = nullptr;
    }
    
    NodoPaciente* getSiguiente() const{
        return nodoSiguiente;
    }

    Paciente getPaciente() const {
        return paciente;
    }

    void setSiguiente(NodoPaciente* nodoPaciente){
        nodoSiguiente = nodoPaciente;
    }
    friend class ColaPacientes;
    
    private:
    NodoPaciente(){}; //constructor por defecto;
    Paciente paciente;
    NodoPaciente* nodoSiguiente;
};