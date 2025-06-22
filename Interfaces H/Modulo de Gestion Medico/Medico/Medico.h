#include <iostream>
#include <string>

using std::string;

class Medico {
    private:
        int ID, numColegiacion, numIdentidad, numTelefono;
        string nombre, especialidad, fechaNacimiento, eMail ;
        bool disponible;

    public:
        // Constructor
        Medico(int id, int colegiacion, int numIdentidad, int numTelefono, string nombre, string especialidad, string fechaNacimiento, string eMail, bool disponible) {
            ID = id;
            numColegiacion = colegiacion;
            this->numIdentidad= numIdentidad;
            this->nombre = nombre;
            this->especialidad = especialidad;
            this->fechaNacimiento= fechaNacimiento;
            this->eMail= eMail;
            this->disponible = disponible;
        }

        // Getters
        int getID() { return ID; }
        int getNumColegiacion() { return numColegiacion; }
        string getNombre() { return nombre; }
        bool isDisponible() { return disponible; }

        // Setters
        void setID(int id) { ID = id; }
        void setNumColegiacion(int colegiacion) { numColegiacion = colegiacion; }
        void setNombre(string nuevoNombre) { nombre = nuevoNombre; }
        void setDisponible(bool estado) { disponible = estado; }
};