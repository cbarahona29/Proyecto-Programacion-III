#include <iostream>
#include <string>

using std::string;

class Medico {
    private:
        int ID, numColegiacion;
        string nombre, especialidad;
        bool disponible;

    public:
        // Constructor
        Profesional(int id, int colegiacion, string nombre, string especialidad, bool disponible) {
            ID = id;
            numColegiacion = colegiacion;
            this->nombre = nombre;
            this->especialidad = especialidad;
            this->disponible = disponible;
        }

        // Getters
        int getID() { return ID; }
        int getNumColegiacion() { return numColegiacion; }
        string getNombre() { return nombre; }
        string getEspecialidad() { return especialidad; }
        bool isDisponible() { return disponible; }

        // Setters
        void setID(int id) { ID = id; }
        void setNumColegiacion(int colegiacion) { numColegiacion = colegiacion; }
        void setNombre(string nuevoNombre) { nombre = nuevoNombre; }
        void setEspecialidad(string nuevaEspecialidad) { especialidad = nuevaEspecialidad; }
        void setDisponible(bool estado) { disponible = estado; }
};