#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>

// Estructuras para almacenar datos del sistema médico
struct Paciente {
    QString id;
    QString nombre;
    QString edad;
    QString telefono;
    QString direccion;
};

struct Medico {
    QString id;
    QString nombre;
    QString especialidad;
    QString telefono;
};

struct CitaAgendada {
    QString paciente;
    QString medico;
    QString fecha;
    QString hora;
    QString tipo;
};

#endif // ESTRUCTURAS_H
