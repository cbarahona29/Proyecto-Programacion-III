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

#include "ExpedienteMedico.h"

/*Retorna el vector de todas las consultas (expediente)
*/
vector<ConsultaMedica> ExpedienteMedico::visualizarExpediente () {
    return consultas;
}
    
/* Agrega una consulta al expediente
    @param ConsultaMedica consulta
*/
void ExpedienteMedico::agregarConsulta (const ConsultaMedica& consulta) {
    consultas.push_back(consulta);
}

/* Agrega una consulta al expediente
    @param Medico medico
    @param std::string motivo
    @param std::string diagnostico
    @param std::string tratamiento
    @param std::string notas
    @param std::string fecha
*/
void ExpedienteMedico::agregarConsulta (Medico medico, string motivo, string diagnostico, string tratamiento, string notas, string fecha)
{
    consultas.push_back(ConsultaMedica(medico, motivo, diagnostico, tratamiento, notas, fecha));
}

/* Busca una consulta dentro del expediente segun la fecha
    @param std::string fecha
*/
ConsultaMedica ExpedienteMedico::buscarConsulta (string fecha) {
    for (auto& consulta : consultas) {
        if (consulta.getFechaConsulta() == fecha){
            return consulta;
        }
    }
    return ConsultaMedica (); // retorna uno vacio
}

// ConsultaMedica buscarConsulta (string palabraClave); segun el compilador ambos son lo mismo por los parametros

