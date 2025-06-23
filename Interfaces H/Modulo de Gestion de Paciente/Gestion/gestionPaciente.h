/*
Modulo de gestion de pacientes
Tiene como funcionalidades:
- Registrar Pacientes (clase Paciente)
- Modificar Info personal existente
- Buscar Paciente por
    - ID
    - Nombre 
    - Numero de Identidad
- Mostrar listado completo o filtrado de pacientes
- Eliminar un paciente (con verificacion de seguridad)
- Asociar expediente medico

*** nota **
!!! La cola de pacientes en esta clase es general y no la fila de espera, no confundir !!!
*/
#include <iostream>
#include <string>

// Inclusion de Objetos de Paciente
#include "../Paciente/Paciente.h"
#include "../Paciente/ExpedienteMedico.h"
#include "../Paciente/ConsultaMedica.h"

// Inclusion de Objetos de Colas
#include "../Cola/ColaPacientes.h"

// Inclusion de Objetos de Guardar datos
#include "../../Modulo de Retencion de Datos/guardaPaciente.cpp"

using std::string;

class gestionPaciente {
    private:
        ColaPacientes pacientes;
        guardaPaciente saver;
    public:
        gestionPaciente ();

        // Busqueda de Pacientes
        Paciente* buscarPaciente (int ID);
        Paciente* buscarPacientePorIdentidad (int numIdentidad);
        Paciente* buscarPacientePorNombre (const string& nombre);

        // Registro de Pacientes
        void registrarPaciente (int ID, string nombre, string fechaNacimiento,string direccion, int numIdentidad, int numTelefono, string eMail, string genero,string alergias);
        void registrarPaciente(Paciente paciente);

        // Cargar Datos
        void cargarDatos();

        // Eliminar
        bool eliminarPaciente (const Paciente& paciente);

        // Expediente Clinico
        ExpedienteMedico consultarExpediente (const Paciente& paciente);
        void registrarConsulta (const Paciente& paciente, const ConsultaMedica& consulta);

        // Mostrar Pacientes    -   Falta filtrado
        vector<Paciente*> mostrarPacientes ();
};


