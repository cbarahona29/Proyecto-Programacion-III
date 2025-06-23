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
        Paciente(int ID, string nombre, string fechaNacimiento, string direccion, int numIdentidad, int numTelefono, string eMail, string genero, string alergias)
        :   ID(ID), nombre(nombre),  
            fechaNacimiento(fechaNacimiento),
            direccion(direccion), numIdentidad(numIdentidad),
            numTelefono(numTelefono), eMail(eMail),
            genero(genero), alergias(alergias) {
                
                expediente = ExpedienteMedico(); 
        }

        // Constructor en caso de no ser encontrado
        bool Existe;
        Paciente (bool existe) : Existe(existe) {}

        // Getters
        int getID() const { return ID; }
        int getNumIdentidad() const { return numIdentidad; }
        int getNumTelefono() const { return numTelefono; }

        string getNombre() const { return nombre; }
        string getEmail() const { return eMail; }
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

        void setExpediente (ExpedienteMedico expediente) {this->expediente = expediente;}

        // Sobre carga de Operadores
        bool operator== (const Paciente& otro) const {
            return ID == otro.ID;
        }

        friend class NodoPaciente; //se declara como clase amiga para que pueda usar su constructor privado

};