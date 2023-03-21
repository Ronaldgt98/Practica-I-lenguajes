#include "ListaDoble.h"
#include <iostream>

using namespace std;

void imprimirLista(Nodo *cabeza)
{
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        cout << actual->nombre << " - " << actual->numero_habitacion << endl;
        actual = actual->sgte;
    }
}

void agregarNodo(Nodo *&cabeza, string nombre, int numero_habitacion)
{
    // Creamos un nuevo nodo para el huésped actual
    Nodo *nuevo = new Nodo;
    nuevo->nombre = nombre;
    nuevo->numero_habitacion = numero_habitacion;
    nuevo->previo = NULL;
    nuevo->sgte = NULL;

    if (cabeza == NULL)
    {
        // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
        cabeza = nuevo;
    }
    else
    {
        // Si la lista no está vacía, agregamos el nuevo nodo al final
        Nodo *actual = cabeza;
        while (actual->sgte != NULL)
        {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;
        nuevo->previo = actual;
    }
}

void menu(Nodo *&cabeza)
{
    int opcion;
    do
    {
        cout << "-----MENU-----" << endl;
        cout << "1. Ingresar nuevo huesped" << endl;
        cout << "2. Imprimir lista de huespedes" << endl;
        cout << "3. Buscar huespedes" << endl;
        cout << "4. Ordenar la lista alfabeticamente" << endl;
        cout << "5. Ordenar la lista por orden de llegada" << endl;
        cout << "6. Consultar vecinos" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;
        cout << endl;

        switch (opcion)
        {
            case 1:
            {
                nuevoHuesped(cabeza, "hotel.txt");
                break;
            }
            case 2:
            {
                imprimirLista(cabeza);
                break;
            }
            case 3:
            {
                int opcionBusqueda;
                cout << "Seleccione el tipo de busqueda:" << endl;
                cout << "1. Buscar por numero de habitacion" << endl;
                cout << "2. Buscar por nombre" << endl;
                cin >> opcionBusqueda;
                switch (opcionBusqueda)
                {
                    case 1:
                    {
                        int numero_habitacion;
                        cout << "Ingrese el numero de habitacion: ";
                        cin >> numero_habitacion;
                        string nombre = buscarPorNumeroHabitacion(cabeza, numero_habitacion);
                        cout << "Nombre del huesped: " << nombre << endl;
                        break;
                    }
                    case 2:
                    {
                        string nombre;
                        int numero_habitacion;
                        std::cout << "Ingrese el nombre del huesped a buscar: ";
                        std::cin >> nombre;
                        numero_habitacion = buscarPorNombre(cabeza, nombre);
                        if (numero_habitacion != -1)
                        {
                            std::cout << "El huesped " << nombre << " se encuentra en la habitacion " << numero_habitacion << std::endl;
                        }
                        else
                        {
                            std::cout << "No se encontro ese huesped." << std::endl;
                        }
                        break;
                    }
                    default:
                        cout << "Opcion invalida" << endl;
                }
            break;
            }
            case 4:
            {
                ordenarListaAlfabeticamente(cabeza);
                imprimirLista(cabeza);
                break;
            }
            case 5:
            {
                ordenarPorLlegada(cabeza);
                imprimirLista(cabeza);
                break;
            }
            case 6:
            {
                int numero_habitacion;
                cout << "Ingrese el numero de habitacion: ";
                cin >> numero_habitacion;
                consultarVecinos(cabeza, numero_habitacion);
                break;
            }
            case 7:
            {
                cout << "Saliendo..." << endl;
                break;
            }
            default:
            {
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
            }
        }
    } while (opcion != 7);
}

void nuevoHuesped(Nodo *&cabeza, std::string archivo)
{
    std::string nombre;
    int numerohabitacion;

    // Solicitamos los datos del nuevo huésped al usuario
    std::cout << "Ingrese el nombre del nuevo huesped: ";
    std::cin >> nombre;
    std::cout << "Ingrese el numero de habitacion: ";
    std::cin >> numerohabitacion;

    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->numero_habitacion == numerohabitacion) {
            // Habitación ocupada, ofrecer habitación anterior o siguiente
            Nodo* anterior = actual->previo;
            Nodo* siguiente = actual->sgte;
            if (anterior != NULL && anterior->numero_habitacion != numerohabitacion) {
                // Habitación anterior disponible
                numerohabitacion = anterior->numero_habitacion;
                break;
            } else if (siguiente != NULL && siguiente->numero_habitacion != numerohabitacion) {
                // Habitación siguiente disponible
                numerohabitacion = siguiente->numero_habitacion;
                break;
            } else {
                // Ambas habitaciones ocupadas, pedir nuevo número
                std::cout << "La habitacion elegida esta ocupada. Por favor, elija otra habitacion: ";
                std::cin >> numerohabitacion;
                actual = cabeza; // Volver a revisar toda la lista desde el principio
            }
        }
        actual = actual->sgte;
    }

    // Agregar nuevo huésped
    agregarNodo(cabeza, nombre, numerohabitacion);

    std::cout << "El huesped " << nombre << " ha sido agregado a la habitacion " << numerohabitacion << std::endl;

    // Abrimos el archivo en modo de escritura y agregamos los datos del nuevo huésped
    std::ofstream archivoSalida(archivo.c_str(), std::ios::app);
    if (archivoSalida.fail())
    {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }
    archivoSalida << nombre << " " << numerohabitacion << std::endl;
    archivoSalida.close();
}

string buscarPorNumeroHabitacion(Nodo *cabeza, int numero_habitacion)
{
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->numero_habitacion == numero_habitacion)
        {
            return actual->nombre;
        }
        actual = actual->sgte;
    }
    return "no se encontro ese huesped";
}

int buscarPorNombre(Nodo *cabeza, std::string nombre)
{
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->nombre == nombre)
        {
            return actual->numero_habitacion;
        }
        actual = actual->sgte;
    }
    return -1;
}

void ordenarListaAlfabeticamente(Nodo *&cabeza)
{
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        Nodo *siguiente = actual->sgte;
        while (siguiente != NULL)
        {
            if (actual->nombre > siguiente->nombre)
            {
                // Intercambiamos los valores de los nodos actual y siguiente
                std::swap(actual->nombre, siguiente->nombre);
                std::swap(actual->numero_habitacion, siguiente->numero_habitacion);
            }
            siguiente = siguiente->sgte;
        }
        actual = actual->sgte;
    }
}

void ordenarPorLlegada(Nodo *&cabeza)
{
    if (cabeza == NULL || cabeza->sgte == NULL)
    {
        // La lista está vacía o solo tiene un elemento, no es necesario ordenarla
        return;
    }

    Nodo *actual = cabeza->sgte;
    while (actual != NULL)
    {
        Nodo *anterior = actual->previo;
        while (anterior != NULL && anterior->nombre > actual->nombre)
        {
            // Intercambiamos los nodos si el nodo anterior llegó después del nodo actual
            anterior->sgte = actual->sgte;
            if (actual->sgte != NULL)
            {
                actual->sgte->previo = anterior;
            }
            actual->previo = anterior->previo;
            actual->sgte = anterior;
            anterior->previo = actual;
            if (actual->previo == NULL)
            {
                cabeza = actual;
            }
            else
            {
                actual->previo->sgte = actual;
            }
            anterior = actual->previo;
        }
        actual = actual->sgte;
    }
}

void consultarVecinos(Nodo *cabeza, int numero_habitacion)
{
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->numero_habitacion == numero_habitacion)
        {
            if (actual->previo != NULL)
            {
                cout << "Huésped anterior: " << actual->previo->nombre << endl;
            }
            else
            {
                cout << "No hay huésped anterior" << endl;
            }
            if (actual->sgte != NULL)
            {
                cout << "Huésped siguiente: " << actual->sgte->nombre << endl;
            }
            else
            {
                cout << "No hay huésped siguiente" << endl;
            }
            return;
        }
        actual = actual->sgte;
    }
    cout << "No se encontró el número de habitación" << endl;
}

void cargarDesdeArchivo(Nodo *&cabeza, string archivo)
{
    // Abrimos el archivo de texto y leemos la información de los huéspedes
    ifstream archivoEntrada(archivo.c_str());
    if (archivoEntrada.fail())
    {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return;
    }

    string nombre;
    int numero_habitacion;

    while (archivoEntrada >> nombre >> numero_habitacion)
    {
        agregarNodo(cabeza, nombre, numero_habitacion);
    }

    archivoEntrada.close();
}
