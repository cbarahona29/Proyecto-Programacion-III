#include <map>
#include <string>
#include "ColaPacientes.h"
#include "Paciente.h"

using namespace std;

class ColasPorEspecialidad{
    private:
        map <string, ColaPacientes> mapaColas;
    public:
    void agregarPaciente(){};
    bool estaVacia();
    Paciente* atenderSiguientePaciente();
    string mostrarColas();
};