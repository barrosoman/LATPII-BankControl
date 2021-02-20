#include "libraryControl.h"
Library_t library;
/* Book_t teste1 = {.name = "teste1\0", */
/*                  .author = "autor1\0", */
/*                  .isRented = true, */
/*                  .returnDate = {"30002010\0", 3000, 20, 10}, */
/*                  .prev = NULL, */
/*                  .next = &teste2}; */
/* Book_t teste2 = {.name = "teste2\0", */
/*                  .author = "autor2\0", */
/*                  .isRented = true, */
/*                  .returnDate = {"20002010\0", 2000, 20, 10}, */
/*                  .prev = &teste1, */
/*                  .next = &teste3}; */
/* Book_t teste3 = {.name = "teste3\0", */
/*                  .author = "autor3\0", */
/*                  .isRented = true, */
/*                  .returnDate = {"10002010\0", 1000, 20, 10}, */
/*                  .prev = &teste2, */
/*                  .next = NULL}; */
int main() {
    atexit(freeAll);
    /* library.firstBook = &teste1; */
    system(clean);
    printf("Bem-vindo, o que deseja fazer?\n");
    menuLoop();
    return 0;
}
