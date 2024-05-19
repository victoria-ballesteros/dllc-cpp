#ifndef BINARYFILES_H
#define BINARYFILES_H

#include <iostream>
#include <stdlib.h>
#include <fstream>

class binaryFiles
{
public:
    void save(const char *nombreArchivo, const void *datos, size_t size);
    void read(const char *nombreArchivo, const size_t size, int indice, void *datos);
    size_t getSize(const char *nombreArchivo, const size_t size);
    bool isEmpty(const std::string &nombreArchivo);
};

#endif