/*

 Módulo de Control de Filas de Espera
Funcionalidades:
• Permitir que un paciente se inscriba en la fila de una especialidad médica.
• Mostrar la cola actual por especialidad.
• Llamar al siguiente paciente (FIFO).

Requerimientos técnicos:
• Implementar colas por especialidad (puede usarse una clase plantilla Cola<T>).
• Cada cola debe estar vinculada a una especialidad.
• Estructuras recomendadas: listas enlazadas, colas dinámicas.
• Uso de punteros para manejar dinámicamente la memoria de las colas.
*/

// Librerias Estandar
#include <iostream>
#include <string>

// Clases
#include "Paciente.h"
#include "ColasPorEspecialidad.h"

using std::string;

class FiladeEspera {
private:
    ColasPorEspecialidad colasEspecialidad;

public:

    FiladeEspera();  // <-- Agrega esto

    // Visualizar Colas
    string mostrarCola (); // Usar colas & colas por especialidad de Modulo Paciente
    string mostrarColaPorEspecialidad (string especialidad);

    //  Inscribir & Atender
    void inscribirPaciente (Paciente paciente, string especialidad);
    void asignarPaciente (Paciente paciente );
    bool removerPacienteDeFila (Paciente paciente, string especialidad);

};
