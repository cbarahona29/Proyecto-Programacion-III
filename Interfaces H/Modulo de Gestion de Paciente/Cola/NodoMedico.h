#include "../../Modulo de Gestion Medico/Medico/Medico.h"

class NodoMedico {
    public:
    NodoMedico(Medico medico) {
        this->medico = medico;
        nodoSiguiente = nullptr;
    }
    
    NodoMedico* getSiguiente() const{
        return nodoSiguiente;
    }

    Medico getMedico() const {
        return medico;
    }

    void setSiguiente(NodoMedico* nodoMedico){
        nodoSiguiente = nodoMedico;
    }
    friend class ColaMedico;
    
    private:
    NodoMedico(){}; //constructor por defecto;
    Medico medico;
    NodoMedico* nodoSiguiente;
};