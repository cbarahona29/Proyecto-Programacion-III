/*
Clase Consulta Medica
- Informacion de cada consulta de un paciente
- Se guardan en la clase ExpedienteMedico de cada paciente individual

-  Atributos
    o Fecha de consulta 
    o Médico responsable 
    o Motivo de consulta 
    o Diagnóstico 
    o Tratamiento 
    o Notas adicionales

*/
#include <iostream>
#include <string>
#include <Medico/Medico.h>

using std::string;

class ConsultaMedica {
    private:
        Medico medicoResponsable;
        string motivoConsulta, diagnostico, tratamiento, notasExtra, fechaConsulta;

    public:
        // Constructor
        ConsultaMedica (Medico medico, string motivo, string diagnostico, string tratamiento, string notas, string fecha) {
            medicoResponsable = medico;
            motivoConsulta = motivo;
            this->diagnostico = diagnostico;
            this->tratamiento = tratamiento;
            notasExtra = notas;
            fechaConsulta = fecha;

        }

};