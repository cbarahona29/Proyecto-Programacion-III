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
*/
#include <iostream>
#include <Paciente/Paciente.h>
#include <string>

using using std::string;

class gestorPaciente {
    private:

    public:
        // Busqueda de Pacientes
        Paciente buscarPaciente (int ID);
        Paciente buscarPaciente (int numIdentidad);
        Paciente buscarPaciente (string nombre);

        // Registro de Pacientes
        void registrarPaciente (int ID, string nombre, string fechaNacimiento,string direccion, int numIdentidad, int numTelefono, string eMail, string genero);

        // 
        bool eliminarPaciente (Paciente paciente);

        // Asociar expediente medico (asaber que es eso)
};

class nodoPaciente {
    Paciente nodo;

    //
    Paciente getPaciente ();

    //
    void siguientePaciente ();
    void pacienteAnterior ();
};