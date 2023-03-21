#include "ListaDoble.h"

int main() {
    Nodo* cabeza = NULL;
    cargarDesdeArchivo(cabeza, "hotel.txt");
    imprimirLista(cabeza);
    menu(cabeza);
    return 0;
}