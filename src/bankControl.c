#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bankControl.h"

Library_t library;

int main() {
    atexit(freeAll);
    system("clear");
    printf("Bem-vindo, o que deseja fazer?\n");
    menuLoop();
    return 0;
}
