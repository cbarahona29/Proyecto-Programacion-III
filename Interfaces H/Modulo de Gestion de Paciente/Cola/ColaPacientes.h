#include "NodoPaciente.h"
#include <vector>
using namespace std;

class ColaPacientes{
    private:
        NodoPaciente* fin;
        NodoPaciente* frente;
    public:
    ColaPacientes(){
        fin =nullptr;
        frente= nullptr;
    }
    void push(Paciente paciente){ // agregar paciente a la cola
        NodoPaciente* nuevoNodo = new NodoPaciente(paciente);

        if(estaVacia()){
            frente = nuevoNodo;
            fin = nuevoNodo;
        }
        else {
            fin->setSiguiente(nuevoNodo); //accedemos al final con la flechita y hacemos que este apunte al nuevo nodo
            fin = nuevoNodo; //por ende el nuevo nodo es el ultimo nodo de la cola
        }
    }

    vector<Paciente*> obtenerPacientes() {
        vector<Paciente*> pacientes;
        NodoPaciente* nodoActual = frente;

        while(nodoActual!=nullptr){
            pacientes.push_back(nodoActual->getPaciente()); //agregamos el paciente al vector
            nodoActual = nodoActual->getSiguiente();
        }

        return pacientes;
    }

    Paciente* pop(){//eliminar al primer paciente de la cola
        if(estaVacia()){
            return nullptr; // la cola ya esta vacia
        }

        NodoPaciente* nodoAEliminar = frente; //pq es first in first out
        Paciente* pacienteAtendido = new Paciente(nodoAEliminar->getPaciente()); //copiamos el paciente 
        frente = frente->getSiguiente(); 

        if(frente == nullptr){
            fin = nullptr; //la cola se vacia
        }

        delete nodoAEliminar;
        return pacienteAtendido; //se retorna para mejor orden 
    }

    bool estaVacia() const{
        return frente == nullptr;
    }

};