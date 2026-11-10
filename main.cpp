#include <iostream>
#include "GameController.h"
#ifdef _WIN32
#include <windows.h>
#endif
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::cout << " СРЕДИЗЕМЬЕ: ДЕМОНСТРАЦИЯ ЛАБОРАТОРНОЙ \n";
    GameController game;
    game.runDemos();
    std::cout << "\nДемонстрация завершена.\n";
    return 0;
}
