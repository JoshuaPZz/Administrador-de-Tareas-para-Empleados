#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Tarea {
    string descripcion;
    bool completada = false;
};

struct MiembroEquipo {
    string nombre;
    vector<Tarea> tareas;
    int puntosMotivacion = 0;
};

class Equipo {
    vector<MiembroEquipo> miembros;

public:
    void cargarDatosDesdeArchivo(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo." << endl;
            return;
        }

        string nombre;
        string descripcion;
        while (getline(file, nombre)) {
            MiembroEquipo nuevoMiembro{nombre};
            miembros.push_back(nuevoMiembro);
            while (getline(file, descripcion) && !descripcion.empty()) {
                Tarea nuevaTarea{descripcion};
                miembros.back().tareas.push_back(nuevaTarea);
            }
        }

        file.close();
        cout << "Datos cargados desde el archivo." << endl;
    }

    void completarTarea(const string& nombre, int indiceTarea) {
        for (size_t i = 0; i < miembros.size(); ++i) {
            if (miembros[i].nombre == nombre) {
                if (indiceTarea >= 0 && indiceTarea < miembros[i].tareas.size()) {
                    miembros[i].tareas[indiceTarea].completada = true;
                    miembros[i].puntosMotivacion += 10;
                    cout << "Tarea completada por " << nombre << ". Puntos de motivacion: " << miembros[i].puntosMotivacion << endl;
                } else {
                    cout << "Indice de tarea invalido." << endl;
                }
                return;
            }
        }
        cout << "Miembro no encontrado." << endl;
    }

    void mostrarEmpleadosYTareas() const {
        cout << "Lista de empleados y sus tareas pendientes:" << endl;
        for (size_t i = 0; i < miembros.size(); ++i) {
            cout << "Empleado: " << miembros[i].nombre << endl;
            for (size_t j = 0; j < miembros[i].tareas.size(); ++j) {
                if (!miembros[i].tareas[j].completada) {
                    cout << "  Indice: " << j + 1 << " - Tarea: " << miembros[i].tareas[j].descripcion << " - Pendiente" << endl;
                }
            }
        }
    }

    void mostrarEmpleadosYRecompensas() const {
        cout << "Lista de empleados y sus recompensas:" << endl;
        for (size_t i = 0; i < miembros.size(); ++i) {
            cout << "Empleado: " << miembros[i].nombre << " - Puntos de motivacion: " << miembros[i].puntosMotivacion << endl;
        }
    }
};

int main() {
    Equipo equipo;
    string archivo = "empleados.txt";
    equipo.cargarDatosDesdeArchivo(archivo);

    int opcion;
    string nombre;
    int indiceTarea;

    do {
        cout << "\nMenu de administracion de equipo:\n";
        cout << "1. Marcar una tarea como completada\n";
        cout << "2. Ver la lista de empleados y sus tareas pendientes\n";
        cout << "3. Ver la lista de empleados con sus recompensas\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre del empleado: ";
                getline(cin, nombre);
                cout << "Ingrese el indice de la tarea a marcar como completada: ";
                cin >> indiceTarea;
                cin.ignore();
                equipo.completarTarea(nombre, indiceTarea - 1);
                break;

            case 2:
                equipo.mostrarEmpleadosYTareas();
                break;

            case 3:
                equipo.mostrarEmpleadosYRecompensas();
                break;

            case 4:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opcion invalida, por favor intente de nuevo." << endl;
                break;
        }

    } while (opcion != 4);

    return 0;
}

