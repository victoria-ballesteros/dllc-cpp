#ifndef CDLLSEMESTER_H
#define CDLLSEMESTER_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <vector>

class cdllSemester
{
public:
    struct Atributos
    {
        int uc;
        std::vector<std::string> vectorUC;
        Atributos(int _uc) : uc(_uc), vectorUC(_uc) {}
    };

    struct Materia
    {
        char nombre[40];
        Atributos info;
        Materia *sig;
        Materia *ant;
        Materia(int _uc) : info(_uc) {}
    };

public:
    void newNodo(Materia *&acceso, char *_nombre, int _uc);
    void printAll(Materia *acceso);
    void deleteNodo(Materia *&acceso);
};

#endif