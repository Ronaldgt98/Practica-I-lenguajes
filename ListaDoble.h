#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <string>
#include <fstream>

struct Nodo {
    std::string nombre;
    int numero_habitacion;
    Nodo* previo;
    Nodo* sgte;
};

void imprimirLista(Nodo* cabeza);
void agregarNodo(Nodo*& cabeza, std::string nombre, int numero_habitacion);
void menu(Nodo*& cabeza);
void nuevoHuesped(Nodo*& cabeza, std::string archivo);
std::string buscarPorNumeroHabitacion(Nodo* cabeza, int numero_habitacion);
int buscarPorNombre(Nodo *cabeza, std::string nombre);
void ordenarListaAlfabeticamente(Nodo*& cabeza);
void ordenarPorLlegada(Nodo*& cabeza);
void consultarVecinos(Nodo *cabeza, int numero_habitacion);
void cargarDesdeArchivo(Nodo*& cabeza, std::string archivo);

#endif // LISTADOBLE_H
