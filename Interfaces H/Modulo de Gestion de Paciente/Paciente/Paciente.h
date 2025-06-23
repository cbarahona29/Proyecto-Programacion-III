#pragma once

#include <iostream>
#include <string>
#include "ExpedienteMedico.h"

using std::string;

class Paciente {
    private:
        Paciente(){} //constructor por defecto
        int ID, numIdentidad, numTelefono;
        string nombre, eMail, genero, fechaNacimiento, direccion, alergias;
        ExpedienteMedico expediente;

    public:
        // Constructor
        Paciente (int ID, string nombre, string fechaNacimiento,string direccion, int numIdentidad, int numTelefono, string eMail, string genero, string alergias) {
            this->ID = ID;
            this->nombre = nombre;
            this->fechaNacimiento = fechaNacimiento;
            this->direccion = direccion;
            this->numIdentidad = numIdentidad;
            this->numTelefono = numTelefono;
            this->eMail = eMail;
            this->genero = genero;
            this->alergias= alergias;
            expediente ();
        }

        // Getters
        int getID() const { return ID; }
        int getNumIdentidad() const { return numIdentidad; }
        int getNumTelefono() const { return numTelefono; }

        string getNombre() const { return nombre; }
        string getEMail() const { return eMail; }
        string getGenero() const { return genero; }
        string getFechaNacimiento() const { return fechaNacimiento; }
        string getDireccion() const { return direccion; }
        string getAlergias() const { return alergias; }
        ExpedienteMedico getExpediente () const {return expediente;}

        // Setters
        void setID(int ID) { this->ID = ID; }
        void setNumIdentidad(int num) { numIdentidad = num; }
        void setNumTelefono(int num) { numTelefono = num; }
        
        void setNombre(string nombre) { this->nombre = nombre; }
        void setEMail(string correo) { eMail = correo; }
        void setGenero(string genero) { this->genero = genero; }
        void setFechaNacimiento(string fecha) { fechaNacimiento = fecha; }
        void setDireccion(string direccion) { this->direccion = direccion; }
        void setAlergias(string alergias) {this->alergias= alergias; }

        // Sobre carga de Operadores
        bool operator== (const Paciente& otro) const {
            return ID == otro.ID;
        }

        friend class NodoPaciente; //se declara como clase amiga para que pueda usar su constructor privado

};