#include "libraryControl.h"
Library_t library;

int main() {
    atexit(freeAll);
    system(clean);
    printf("Bem-vindo, o que deseja fazer?\n");
    menuLoop();
    return 0;
}
