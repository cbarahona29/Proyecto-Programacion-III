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
#include <iostream>
#include <string>
#include "Modulo de Gestion Medico/Medico/Medico.h"
#include "ConsultaMedica.h"

using std::string;
 
class ExpedienteMedico {
    private: 

    public:
        string visualizarExpediente ();
        
        void crearConsulta (Medico medico, string motivo, string diagnostico, string tratamiento, string notas, string fecha);
        
        ConsultaMedica buscarConsulta (string fecha) ;
        ConsultaMedica buscarConsulta (string palabraClave);

        string generarReporteClinico ();

        
};