/*
Modulo de gestion de medicos
Tiene como funcionalidades:
Registrar médicos con los siguientes datos:
   ~ ID de médico (autogenerado)
   ~ Nombre completo
   ~ Especialidad (cardiología, pediatría, medicina general, etc.)
   ~ Estado (disponible / ocupado)
   ~ Número de colegiación
- Editar la información de un médico.
- Buscar médicos por ID, nombre o especialidad.
- Marcar como disponible u ocupado (al asignar consultas).
-Listar todos los médicos o por especialidad
*/
#include <iostream>
#include <string>

// Inclusion de Objetos de Medicos
#include "Medico/Medico.h"

// Inclusion de Objetos de Colas
#include "Cola/ColaPorEspecialidad.h"

class gestorMedico(){
    private:
        ColaPorEspecialidad colaEspecialidad;
    public:

    // Busqueda de Medico
        Medico buscarMedico (int ID);
        Medico buscarMedico (int numIdentidad);
        Medico buscarMedico (const string& nombre);

    // Registro de Pacientes o Modificar
        void registrarMedico (int ID, int colegiacion, int numIdentidad, int numTelefono, string nombre, string especialidad, string fechaNacimiento, string eMail);


    //Verificar si esta ocupado
        bool estaOcupado(bool disponible); 

};