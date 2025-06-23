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
#pragma once

#include <iostream>
#include <string>
#include "../../Modulo de Gestion Medico/Medico/Medico.h"

using std::string;

class ConsultaMedica {
    private:
        Medico medicoResponsable;
        string motivoConsulta, diagnostico, tratamiento, notasExtra, fechaConsulta;

    public:
        // Constructor
        ConsultaMedica(Medico medico, string motivo, string diagnostico, string tratamiento, string notas, string fecha)
        :   medicoResponsable(medico), 
            motivoConsulta(motivo), 
            diagnostico(diagnostico),
            tratamiento(tratamiento), 
            notasExtra(notas), 
            fechaConsulta(fecha) {}
        
        ConsultaMedica () {} // Al momento de leerlos del archivo binario se usa uno sin parametros

    // Getters & Setters
    void setMedicoResponsable(const Medico& medico) {
        medicoResponsable = medico;
    }

    string getMotivoConsulta() const {
        return motivoConsulta;
    }
    void setMotivoConsulta(const string& motivo) {
        motivoConsulta = motivo;
    }

    string getDiagnostico() const {
        return diagnostico;
    }
    void setDiagnostico(const string& diag) {
        diagnostico = diag;
    }

    string getTratamiento() const {
        return tratamiento;
    }
    void setTratamiento(const string& trat) {
        tratamiento = trat;
    }

    string getNotasExtra() const {
        return notasExtra;
    }
    void setNotasExtra(const string& notas) {
        notasExtra = notas;
    }

    string getFechaConsulta() const {
        return fechaConsulta;
    }
    void setFechaConsulta(const string& fecha) {
        fechaConsulta = fecha;
    }

    // sobrecarga de operadores para comparaciones
    bool operator== (const ConsultaMedica& otro) const {
        return fechaConsulta == otro.getFechaConsulta();
    }
};