#include "cdllSemester.h"

void cdllSemester::newNodo(Materia *&acceso, char *_nombre, int _uc)
{
    Materia *nuevo_nodo = new Materia(_uc);
    strncpy(nuevo_nodo->nombre, _nombre, sizeof(nuevo_nodo->nombre) - 1);
    nuevo_nodo->nombre[sizeof(nuevo_nodo->nombre) - 1] = '\0';
    nuevo_nodo->info.uc = _uc;

    if (acceso == nullptr)
    {
        acceso = nuevo_nodo;
        acceso->sig = acceso;
        acceso->ant = acceso;
    }
    else
    {
        nuevo_nodo->sig = acceso;
        nuevo_nodo->ant = acceso->ant;
        nuevo_nodo->ant->sig = nuevo_nodo;
        acceso->ant = nuevo_nodo;
        acceso = nuevo_nodo;
    }
}

void cdllSemester::printAll(Materia *acceso)
{
    Materia *actual = acceso;
    do
    {
        std::cout << actual->nombre << "\n";
        actual = actual->sig;
    } while (actual != acceso);
}

void cdllSemester::deleteNodo(Materia *&acceso)
{
    if (acceso == nullptr)
    {
        return;
    }

    if (acceso->sig == acceso)
    {
        delete acceso;
        acceso = nullptr;
    }
    else
    {
        Materia *auxiliar = acceso;
        acceso = acceso->ant;
        acceso->sig = auxiliar->sig;
        auxiliar->sig->ant = acceso;
        delete auxiliar;
    }
}
