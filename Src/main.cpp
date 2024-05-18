#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdio>
#include "../include/Include.h"

void imprimirEnPosicion(COORD posicion, const char *texto);
void imprimirNodo(cdllSemester::Materia *acceso);
int validarEntrada(int minimo, int maximo);
void manejarIzquierda(cdllSemester::Materia *&acceso);
bool vacio = false;

int main()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    cdllSemester::Materia *acceso = nullptr;
    cdllSemester semestre;
    char nombre[40], c, c1;
    int uc = 0;
    bool flag = true;
    COORD posicionEspecifica;
    do
    {
        system("cls");
        FlushConsoleInputBuffer(hStdin);
        posicionEspecifica = {10, 5};
        imprimirEnPosicion(posicionEspecifica, "1. Introducir una nueva materia.");
        posicionEspecifica = {10, 7};
        imprimirEnPosicion(posicionEspecifica, "2. Ver tarjetas de materias.");
        posicionEspecifica = {10, 9};
        imprimirEnPosicion(posicionEspecifica, "3. Cerrar programa.");
        posicionEspecifica = {10, 11};
        imprimirEnPosicion(posicionEspecifica, "OPCION: ");
        c = toupper(getchar());
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == '1')
        {
            system("cls");
            posicionEspecifica = {10, 5};
            imprimirEnPosicion(posicionEspecifica, "Nombre: ");
            std::cin.getline(nombre, 40);
            posicionEspecifica = {10, 7};
            imprimirEnPosicion(posicionEspecifica, "UC: ");
            uc = validarEntrada(1, 4);
            semestre.newNodo(acceso, nombre, uc);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            SHORT y = 0;
            std::string textoCompleto;
            std::string temario;
            for (int i = 0; i < uc; i++)
            {
                y = 9 + (i * 2);
                posicionEspecifica = {10, y};
                textoCompleto = "Temas del Parcial " + std::to_string(i + 1) + ": ";
                imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
                std::getline(std::cin, acceso->info.vectorUC[i]);
            }
        }
        else if (c == '2')
        {
            imprimirNodo(acceso);
            if (vacio)
            {
                system("cls");
                posicionEspecifica = {80, 24};
                imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
            }
            else
            {
                posicionEspecifica = {80, 20};
                imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
                posicionEspecifica = {80, 22};
                imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
                posicionEspecifica = {80, 24};
                imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
            }
            bool esperandoEntrada = false;

            while (true)
            {
                if (!esperandoEntrada)
                {
                    if (GetKeyState(VK_RIGHT) & 0x8000)
                    {
                        if (acceso == nullptr)
                        {
                            system("cls");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            acceso = acceso->sig;
                            imprimirNodo(acceso);
                            posicionEspecifica = {80, 20};
                            imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
                            posicionEspecifica = {80, 22};
                            imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
                        }
                    }

                    if (GetKeyState(VK_LEFT) & 0x8000)
                    {
                        if (acceso == nullptr)
                        {
                            system("cls");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            manejarIzquierda(acceso);
                        }
                    }
                    if (GetKeyState('C') & 0x8000)
                    {
                        imprimirNodo(acceso);
                        posicionEspecifica = {40, 19};
                        imprimirEnPosicion(posicionEspecifica, "Seleccione la propiedad que desea cambiar a continuacion:");
                        posicionEspecifica = {40, 21};
                        imprimirEnPosicion(posicionEspecifica, "N. Nombre.");
                        posicionEspecifica = {40, 23};
                        imprimirEnPosicion(posicionEspecifica, "U. UC.\n");
                    }
                    if (GetKeyState('D') & 0x8000)
                    {
                        semestre.deleteNodo(acceso);
                        if (acceso == nullptr)
                        {
                            system("cls");
                            posicionEspecifica = {80, 24};
                            imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista\n\n");
                        }
                        else
                        {
                            manejarIzquierda(acceso);
                        }
                    }
                    if (GetKeyState('S') & 0x8000)
                    {
                        break;
                    }
                }

                if ((GetKeyState('N') & 0x8000) && !esperandoEntrada)
                {
                    FlushConsoleInputBuffer(hStdin);
                    esperandoEntrada = true;
                    system("cls");
                    posicionEspecifica = {40, 7};
                    imprimirEnPosicion(posicionEspecifica, "Nombre: ");
                    std::cin.getline(acceso->nombre, 40);
                    esperandoEntrada = false;
                    manejarIzquierda(acceso);
                }
                if ((GetKeyState('U') & 0x8000) && !esperandoEntrada)
                {
                    FlushConsoleInputBuffer(hStdin);
                    esperandoEntrada = true;
                    system("cls");
                    posicionEspecifica = {40, 7};
                    imprimirEnPosicion(posicionEspecifica, "UC: ");
                    acceso->info.uc = validarEntrada(1, 4);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    esperandoEntrada = false;
                    FlushConsoleInputBuffer(hStdin);
                    manejarIzquierda(acceso);
                }
                Sleep(50);
            }
            FlushConsoleInputBuffer(hStdin);
        }
    } while (c != '3');

    FlushConsoleInputBuffer(hStdin);

    return 0;
}

void imprimirEnPosicion(COORD posicion, const char *texto)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, posicion);
    std::cout << texto;
}

void imprimirNodo(cdllSemester::Materia *acceso)
{
    system("cls");
    COORD posicionEspecifica = {20, 5};
    vacio = false;
    if (acceso == nullptr)
    {
        vacio = true;
        return;
    }
    SHORT y = 0;
    int _uc = acceso->info.uc;
    std::string textoCompleto = "Nombre: " + std::string(acceso->nombre);
    posicionEspecifica = {40, 5};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    textoCompleto = "UC: " + std::to_string(acceso->info.uc);
    posicionEspecifica = {40, 7};
    imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());

    for (int i = 0; i < _uc; i++)
    {
        y = 9 + (i * 2);
        posicionEspecifica = {40, y};
        textoCompleto = "Parcial " + std::to_string(i + 1) + ": " + acceso->info.vectorUC[i];
        imprimirEnPosicion(posicionEspecifica, textoCompleto.c_str());
    }
}

int validarEntrada(int minimo, int maximo)
{
    int numero;
    while (true)
    {
        std::cin >> numero;
        if (std::cin.fail() || numero < minimo || numero > maximo)
        {
            COORD posicionEspecifica = {10, 19};
            imprimirEnPosicion(posicionEspecifica, "Entrada invalida. Por favor, intente de nuevo: ");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }
    return numero;
}

void manejarIzquierda(cdllSemester::Materia *&acceso)
{
    acceso = acceso->ant;
    imprimirNodo(acceso);
    COORD posicionEspecifica = {80, 20};
    imprimirEnPosicion(posicionEspecifica, "Presione C para modificar el registro");
    posicionEspecifica = {80, 22};
    imprimirEnPosicion(posicionEspecifica, "Presione D para eliminar el registro");
    posicionEspecifica = {80, 24};
    imprimirEnPosicion(posicionEspecifica, "Presione S para salir de la vista");
}