#include "Medico.h"

class NodoMedico {
public:
    NodoMedico(Medico medico) {
        this->medico = medico;
        nodoSiguiente = nullptr;
    }

    NodoMedico* getSiguiente() const{
        return nodoSiguiente;
    }

    Medico* getMedico() {
        return &medico;
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
