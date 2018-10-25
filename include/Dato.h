///                      Dato.h
///
///     Practica 1 Informática industrial 2018/2019
///   Ingeniería Electrónica Industrial y automática.
///              Guillermo Sánchez Brizuela
///
///

#ifndef DATO_H
#define DATO_H

///Librerias
#include <iostream>
#include <fstream>
#include <vector>

///Definicion de la clase
template <typename T>
class Dato{
private:
    T mLectura;
    std::string mReferencia;
    time_t mSegundos;
public:
    ///Constructores
    Dato(T lec, std::string refe, time_t seg) : mLectura(lec), mReferencia(refe), mSegundos(seg) {};
    Dato() : mLectura(0.0), mReferencia(""), mSegundos(0) {};
    ///Gets
    T getLectura(){return mLectura;}
    time_t getSegundos(){return mSegundos;}
    std::string getReferencia(){return mReferencia;}
    ///Sobrecarga de operadores
    template <typename U> friend std::ostream& operator<< (std::ostream&, const Dato<U>&);
    template <typename U> friend std::ifstream& operator>> (std::ifstream&, Dato<U>&);
    template <typename U> friend bool operator> (const Dato<U>&, const Dato<U>&);
    template <typename U> friend bool operator< (const Dato<U>&, const Dato<U>&);
};

///operator<<
///Devuelve: Una referencia a la cadena de salida
///Argumentos: Una referencia a la cadena de salida y una referencia al dato de la clase Dato
///Sobrecargamos el operador << para imprimir por terminal el dato
///
///Guillermo Sánchez Brizuela
template <typename T>
std::ostream& operator<< (std::ostream& out, const Dato<T>& dato){
    time_t segEpoch = dato.mSegundos;
    out << "\t" << dato.mReferencia << "\t\t" << dato.mLectura << "\t\t" << ctime(&segEpoch);
    return out;
}

///operator>>
///Devuelve: Una referencia a la cadena de entrada
///Argumentos: Una referencia a la cadena de entrada y una referencia al dato de la clase Dato
///Sobrecargamos el operador >> para cargar los datos directamente desde el fichero
///
///Guillermo Sánchez Brizuela
template <typename T>
std::ifstream& operator>> (std::ifstream& in, Dato<T>& dato){
    in >> dato.mLectura;
    in >> dato.mReferencia;
    in >> dato.mSegundos;
    return in;
}

///operator>
///Devuelve: Un booleano (comparacion verdadera o falsa)
///Argumentos: Dos referencias a datos de la clase Dato
///Sobrecargamos el operador > para comparar los valores numericos de cada dato
///
///Guillermo Sánchez Brizuela
template <typename T>
bool operator> (const Dato<T>& dato1, const Dato<T>& dato2){
    return (dato1.mLectura > dato2.mLectura)? true : false;
}

///operator<
///Devuelve: Un booleano (comparacion verdadera o falsa)
///Argumentos: Dos referencias a datos de la clase Dato
///Sobrecargamos el operador < para comparar los valores numericos de cada dato
///
///Guillermo Sánchez Brizuela
template <typename T>
bool operator< (const Dato<T>& dato1, const Dato<T>& dato2){
    return (dato1.mLectura < dato2.mLectura)? true : false;
}

#endif // DATO_H
