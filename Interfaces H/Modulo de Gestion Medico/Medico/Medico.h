#include <iostream>
#include <string>

class Medico {
private:
    int ID, numColegiacion, numIdentidad, numTelefono;
    string nombre, especialidad, fechaNacimiento, eMail;
    bool disponible;

public:
    // Constructor
    Medico(int id, int colegiacion, int numIdentidad, int numTelefono, string nombre, string especialidad, string fechaNacimiento,string eMail, bool disponible) {
        ID = id;
        numColegiacion = colegiacion;
        this->numIdentidad = numIdentidad;
        this->numTelefono = numTelefono;
        this->nombre = nombre;
        this->especialidad = especialidad;
        this->fechaNacimiento = fechaNacimiento;
        this->eMail = eMail;
        this->disponible = disponible;
    }

    // Getters
    int getID() const { return ID; }
    int getNumColegiacion() const { return numColegiacion; }
    int getNumIdentidad() const { return numIdentidad; }
    int getNumTelefono() const { return numTelefono; }

    string getNombre() const { return nombre; }
    string getEspecialidad() const { return especialidad; }
    string getFechaNacimiento() const { return fechaNacimiento; }
    string getEmail() const { return eMail; }

    bool estaDisponible() const { return disponible; }

    // Setters
    void setID(int id) { ID = id; }
    void setNumColegiacion(int colegiacion) { numColegiacion = colegiacion; }
    void setNumIdentidad(int identidad) { numIdentidad = identidad; }
    void setNumTelefono(int telefono) { numTelefono = telefono; }

    void setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
    void setEspecialidad(const string& esp) { especialidad = esp; }
    void setFechaNacimiento(const string& fecha) { fechaNacimiento = fecha; }
    void setEmail(const string& correo) { eMail = correo; }

    void setEstado(bool estado) { disponible = estado; }

    // Operador para comparar por ID 
    bool operator==(const Medico& otro) const {
        return this->ID == otro.ID;
    }
};
