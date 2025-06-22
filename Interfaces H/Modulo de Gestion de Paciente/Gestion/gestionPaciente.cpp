#include <iostream>
#include <string> 

// Inclusion de Objetos de Paciente
#include "Paciente/Paciente.h"
#include "Paciente/ExpedienteMedico.h"
#include "Paciente/ConsultaMedica.h"
 
class gestionPaciente{
    private:

    Paciente paciente;
    public: 

    // Busqueda de Pacientes
    Paciente gestionPaciente::buscarPaciente (int ID);
    Paciente gestionPaciente::buscarPaciente (int numIdentidad);
    Paciente gestionPaciente::buscarPaciente (const string& nombre);

    // Registro de Pacientes
   void gestionPaciente::registrarPaciente (int ID, string nombre, string fechaNacimiento,string direccion, int numIdentidad, int numTelefono, string eMail, string genero,string alergias){
    Paciente paciente(int ID, string nombre, string fechaNacimiento,string direccion, int numIdentidad, int numTelefono, string eMail, string genero, string alergias);
 }

    // Eliminar
        bool gestionPaciente::eliminarPaciente (const Paciente& paciente);

        // Expediente Clinico
        ExpedienteMedico gestionPaciente::consultarExpediente (const Paciente& paciente);
        void gestionPaciente::registrarConsulta (const Paciente& paciente, const ConsultaMedica& consulta);

        // Mostrar Pacientes    -   Falta filtrado
        string gestionPaciente::mostrarPacientes ();

}