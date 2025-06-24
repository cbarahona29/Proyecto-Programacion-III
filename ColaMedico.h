#pragma once

#include <vector>
#include "NodoMedico.h"

using namespace std;

class ColaMedico{
private:
    NodoMedico* fin;
    NodoMedico* frente;
public:
    ColaMedico(){
        fin =nullptr;
        frente= nullptr;
    }
    void push(Medico medico){ // agregar medico a la cola
        NodoMedico* nuevoNodo = new NodoMedico(medico);

        if(estaVacia()){
            frente = nuevoNodo;
            fin = nuevoNodo;
        }
        else {
            fin->setSiguiente(nuevoNodo); //accedemos al final con la flechita y hacemos que este apunte al nuevo nodo
            fin = nuevoNodo; //por ende el nuevo nodo es el ultimo nodo de la cola
        }
    }

    vector<Medico*> obtenerMedicos() {
        vector<Medico*> medicos;
        NodoMedico* nodoActual = frente;

        while(nodoActual!=nullptr){
            medicos.push_back(nodoActual->getMedico()); //agregamos el medico al vector
            nodoActual = nodoActual->getSiguiente();
        }

        return medicos;
    }

    Medico* pop(){//eliminar al primer medico de la cola
        if(estaVacia()){
            return nullptr; // la cola ya esta vacia
        }

        NodoMedico* nodoAEliminar = frente; //pq es first in first out
        Medico* medico = nodoAEliminar->getMedico(); //copiamos el paciente
        frente = frente->getSiguiente();

        if(frente == nullptr){
            fin = nullptr; //la cola se vacia
        }

        delete nodoAEliminar;
        return medico; //se retorna para mejor orden
    }

    bool estaVacia() const{
        return frente == nullptr;
    }


};
