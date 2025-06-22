#include <iostream>
#include <string>

using std::string;

class Paciente {
    private:
        Paciente(){} //constructor por defecto
        int ID, numIdentidad, numTelefono;
        string nombre, eMail, genero, fechaNacimiento, direccion, alergias;
        
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
        }

        // Getters
        int getID() { return ID; }
        int getNumIdentidad() { return numIdentidad; }
        int getNumTelefono() { return numTelefono; }

        string getNombre() { return nombre; }
        string getEMail() { return eMail; }
        string getGenero() { return genero; }
        string getFechaNacimiento() { return fechaNacimiento; }
        string getDireccion() { return direccion; }

        // Setters
        void setID(int ID) { this->ID = ID; }
        void setNumIdentidad(int num) { numIdentidad = num; }
        void setNumTelefono(int num) { numTelefono = num; }
        
        void setNombre(string nombre) { this->nombre = nombre; }
        void setEMail(string correo) { eMail = correo; }
        void setGenero(string genero) { this->genero = genero; }
        void setFechaNacimiento(string fecha) { fechaNacimiento = fecha; }
        void setDireccion(string direccion) { this->direccion = direccion; }

        // Sobre carga de Operadores
        bool operator== (const Paciente& otro) const {
            return ID == otro.ID;
        }

        friend class NodoPaciente; //se declara como clase amiga para que pueda usar su constructor privado

};