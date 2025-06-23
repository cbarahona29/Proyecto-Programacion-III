/*
Plantilla para los expedientes de cada paciente,
tiene las sieguientes funciones:

-  Crear una nueva entrada para cada consulta con:
    o Fecha de consulta
    o Médico responsable
    o Motivo de consulta
    o Diagnóstico
    o Tratamiento
    o Notas adicionales

- Visualizar el historial clínico completo del paciente.

- Buscar consultas pasadas por fecha o palabra clave.

- Generar reportes clínicos por paciente.
*/
#pragma once // por error de inclusiones multiples

//
#include <iostream>
#include <vector>
#include <string>

//
#include "Medico.h"
#include "ConsultaMedica.h"


using std::string;
using std::vector;

class ExpedienteMedico {
private:
    vector<ConsultaMedica> consultas;
public:
    ExpedienteMedico () {}

    vector<ConsultaMedica> visualizarExpediente ();

    void agregarConsulta (const ConsultaMedica& consulta);
    void agregarConsulta (Medico medico, string motivo, string diagnostico, string tratamiento, string notas, string fecha);

    ConsultaMedica buscarConsulta (string fecha) ;
    // ConsultaMedica buscarConsulta (string palabraClave); segun el compilador ambos son lo mismo por los parametros

};
