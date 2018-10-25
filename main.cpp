///                      main.cpp
///
///     Practica 1 Informática industrial 2018/2019
///   Ingeniería Electrónica Industrial y automática.
///              Guillermo Sánchez Brizuela
///
///


#include <iostream> ///Entradas y salidas
#include <vector> ///Contenedor vector
#include <iomanip> ///setprecision() , fixed

#include "funciones.h"
#include "Dato.h"

using namespace std;

enum Opciones{Opcion1 = 1, Opcion2, Opcion3, Opcion4, Opcion5, Opcion6};

int main()
{
    int opcion = 0, iteracion = 0;
    cout << setprecision(2) << fixed; ///Fijamos la precision a dos decimales
    vector<Dato<float>> vDatos;

    leerFicheroDatos(vDatos); ///Cargamos los datos en el vector de datos
    cout << "Bienvenido, elige una de las siguientes opciones:" << endl;

    do{ ///Hacemos minimo una vez, luego preguntamos si quiere introducir otra opcion
        while(!opcion) ///Mientras la opcion no sea valida volvemos a preguntar
            opcion = mostrarMenu(iteracion);
        switch(opcion){
            case Opcion1: mostrarDatos(vDatos); break;
            case Opcion2: mostrarMaxMin(vDatos); break;
            case Opcion3: mostrarIntervaloTiempo(vDatos); break;
            case Opcion4: generarFichero(vDatos); break;
            case Opcion5: mostrarMediana(vDatos); break;
            case Opcion6: return 0; break;
        }
    }while(continuar(opcion, iteracion));

    return 0;
}
