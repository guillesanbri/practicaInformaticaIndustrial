///                      funciones.h
///
///     Practica 1 Informática industrial 2018/2019
///   Ingeniería Electrónica Industrial y automática.
///              Guillermo Sánchez Brizuela
///
///

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector> ///Contenedor vector (Ya incluida en Dato.h)
#include <ctime> ///Para covertir los segundos desde epoch a una fecha legible
#include <cstring> ///strtok()
#include <algorithm> ///Para ordenar los vectores
//#include <string> ///Para trabajar mejor con strings

#include "Dato.h"

using namespace std;

const int numeroOpciones = 6; ///Numero de opciones del menu

enum Errores{ERROR_LECTURA, ERROR_ESCRITURA}; ///Errores valorados en el programa

///Declaracion de funciones
int mostrarMenu(int&);
bool continuar(int&, int&);
template <typename T> void leerFicheroDatos(vector<Dato<T>>&);
template <typename T> void mostrarDatos(const vector<Dato<T>>&);
template <typename T> void mostrarMaxMin(vector<Dato<T>>&);
template <typename T> void mostrarIntervaloTiempo(vector<Dato<T>>&);
template <typename T> void generarFichero(vector<Dato<T>>&);
template <typename T> void mostrarMediana(vector<Dato<T>>&);
void pasarMayus(string&);

///mostrarMenu()
///Devuelve: Un int (Opcion elegida)
///Argumentos: Un int por referencia (El numero de iteraciones)
///Mostramos el menú, actualizamos el numero de veces que se ha intentado meter una opcion, y devolvemos la opcion elegida.
///
///Guillermo Sánchez Brizuela
int mostrarMenu(int& iteracion){
    int opcionElegida = 0;
    if(!iteracion){ /// Solo si es la primera iteracion, mostramos las opciones
        cout << "1 - Sacar por pantalla todos los datos del contenedor de entrada." << endl;
        cout << "2 - Mostrar la maxima y minima lectura y sus respectivos sensores." << endl;
        cout << "3 - Mostrar el intervalo de tiempo en que han sido adquiridos los datos que figuran en el contenedor de entrada." << endl;
        cout << "4 - Generar fichero con los datos correspondientes a una determinada referencia de sensor" << endl;
        cout << "5 - Mostrar por pantalla la mediana de los valores recogidos por un determinado sensor." << endl;
        cout << "6 - Salir." << endl;
        cout << "Para seleccionar, introduce a continuacion el numero de la opcion que deseas: ";
        cin >> opcionElegida;
        iteracion++;
    }
    else{
        cout << "Recuerda que tienes que introducir una opcion valida: ";
        cin >> opcionElegida;
    }
    return (opcionElegida > 0 && opcionElegida <= numeroOpciones)? opcionElegida : 0; /// Devolvemos una opcion valida o cero (opcion nula)
}

///continuar()
///Devuelve: Un bool (Continuar o no)
///Argumentos: Dos int por referencia (La opcion elegida y el numero de iteraciones)
///Preguntamos al usuario si quiere continuar en el programa
///
///Guillermo Sánchez Brizuela
bool continuar(int& opcion, int& iteracion){
    cout << "Quieres elegir otra opcion? (s/n): ";
    char eleccion;
    cin >> eleccion;
    if(eleccion == 's' || eleccion == 'S'){
        opcion = 0;
        iteracion = 0;
        return true;
    }
    else
        return false;
}

///leerFicheroDatos()
///Devuelve: void
///Argumentos: Un vector de datos de la clase Dato por referencia
///Leemos el fichero y lo cargamos en el vector de datos
///Si hay error de lectura lanza un ERROR_LECTURA
///Guillermo Sánchez Brizuela
template <typename T>
void leerFicheroDatos(vector<Dato<T>>& v){
    try{
        ifstream ficheroLectura("datos.txt");
        if(!ficheroLectura){
            throw ERROR_LECTURA;
        }
        while(!ficheroLectura.eof()){
          Dato<T> dato;
          ficheroLectura >> dato;
          v.push_back(dato);
        }
        ficheroLectura.close();
    }
    catch(Errores e){
        cout << endl << "Ha habido un error en la lectura del fichero y no se han cargado los datos" << endl << endl;
    }
}

///mostrarDatos()
///Devuelve: void
///Argumentos: Un vector de datos de la clase Dato por referencia
///Imprimimos por pantalla todos los datos del vector
///
///Guillermo Sánchez Brizuela
template <typename T>
void mostrarDatos(const vector<Dato<T>>& v){
    cout << endl << "Mostrando por pantalla todas las lecturas:" << endl;
    cout << endl << "     Referencia" << "\t       Lectura" << "\t\t      Fecha y hora" << endl;;
    for(size_t i=0; i<v.size(); i++)
        cout << v[i] << endl;
}

///mostrarMaxMin()
///Devuelve: void
///Argumentos: Un vector de datos de la clase Dato por referencia
///Mostramos la lectura maxima y minima registrada por los sensores
///
///Guillermo Sánchez Brizuela
template <typename T>
void mostrarMaxMin(vector<Dato<T>>& v){
    int iMax = 0, iMin = 0;
    for(size_t i=0; i<v.size(); i++){ /// Buscamos los indices de los mayores y menores
        iMax = (v[iMax] < v[i])? i : iMax;
        iMin = (v[iMin] > v[i])? i : iMin;
    }
    cout << endl;
    cout << "El maximo ha sido: " << v[iMax].getLectura() << " y ha sido recogido por el sensor " << v[iMax].getReferencia() << endl;
    cout << "El minimo ha sido: " << v[iMin].getLectura() << " y ha sido recogido por el sensor " << v[iMin].getReferencia() << endl;
    cout << endl;
}

///mostrarIntervaloTiempo()
///Devuelve: void
///Argumentos: Un vector de datos de la clase Dato por referencia
///Buscamos el mayor y el menor tiempo de lectura
///
///Guillermo Sánchez Brizuela
template <typename T>
void mostrarIntervaloTiempo(vector<Dato<T>>& v){
    time_t maximo = v[0].getSegundos(), minimo = v[0].getSegundos();
    for(size_t i=0; i<v.size(); i++){
        maximo = (maximo < v[i].getSegundos())? (v[i].getSegundos()) : maximo;
        minimo = (minimo > v[i].getSegundos())? (v[i].getSegundos()) : minimo;
    }
    cout << endl << "Los valores se han recogido entre " << strtok(ctime(&minimo), "\n"); /// Usamos strtok para recortar el salto de linea del ctime
    cout << " y " << ctime(&maximo) << endl;
}

///generarFichero()
///Devuelve: void
///Argumentos: Un vector de datos de la clase Dato por referencia
///Generamos un fichero a partir de las lecturas de un solo sensor pedido al usuario
///Si no se puede generar o escribir el fichero lanza un error ERROR_ESCRITURA
///Guillermo Sánchez Brizuela
template <typename T>
void generarFichero(vector<Dato<T>>& v){
    cout << endl << "Introduce la referencia del sensor que quieres leer (Ej: S006): ";
    string sensor, nombreFichero;
    cin >> sensor;
    pasarMayus(sensor); /// Pasamos el string a mayusculas para evitar problemas con la entrada por teclado
    nombreFichero = "datos" + sensor + ".txt";
    try{
        ofstream fSalida(nombreFichero);
        if(!fSalida){
            throw ERROR_ESCRITURA;
        }
        time_t actual = time(NULL);
        fSalida << "Datos del sensor " << sensor << " a fecha " << ctime(&actual) << endl;
        fSalida << "       Lectura" << "        Fecha y hora" << endl;
        for(size_t i=0; i<v.size(); i++){
            if(v[i].getReferencia() == sensor){
                time_t t = v[i].getSegundos();
                fSalida << "\t" << v[i].getLectura() << "\t" << ctime(&t) << endl;
            }
        }
        cout << endl << "Se ha creado el fichero con exito" << endl << endl;
        fSalida.close();
    }
    catch(Errores r){
        cout << endl << "No se ha podido crear el fichero de salida" << endl << endl;
    }
}

///mostrarMediana()
///Devuelve: void
///Argumentos: Un vector de datos de la clase Dato por referencia
///Mostramos la mediana de uno de los sensores, previamente pedido al usuario
///
///Guillermo Sánchez Brizuela
template <typename T>
void mostrarMediana(vector<Dato<T>>& v){
    cout << endl << "Introduce la referencia del sensor del que quieres la lectura mediana (Ej: S006): ";
    string sensor;
    cin >> sensor;
    pasarMayus(sensor);
    vector<float> recogidosSensor; /// Metemos en un vector los valores leidos por el sensor en concreto
    for(size_t i=0; i<v.size(); i++){
        if(v[i].getReferencia() == sensor){
            recogidosSensor.push_back(v[i].getLectura());
        }
    }
    size_t mediana = floor(recogidosSensor.size()/2);
    sort(recogidosSensor.begin(), recogidosSensor.end());
    float lecturaMediana;
    /// Aqui variamos la forma de obtener la mediana dependiendo de que el numero de elementos sea par o impar
    if(recogidosSensor.size()%2 == 0){
        lecturaMediana = (recogidosSensor[mediana-1] + recogidosSensor[mediana])/2;
    }
    else{
        lecturaMediana = recogidosSensor[mediana];
    }
    cout << endl << "La mediana recogida de los valores recogidos por el sensor " << sensor << " es: " << lecturaMediana << endl << endl;
}

///pasarMayus()
///Devuelve: void
///Argumentos: Un string por referencia (La palabra a modificar)
///Pasamos una palabra a mayusculas
///
///Guillermo Sánchez Brizuela
void pasarMayus(string& palabra){
    for(size_t i=0; i<palabra.size(); i++){
        palabra[i] = toupper(palabra[i]);
    }
}

#endif // FUNCIONES_H
