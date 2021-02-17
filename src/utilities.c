#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bankControl.h"

void menuLoop() {
    int option;
    while (1) {
        showMenu();
        option = getNumberFromInput();
        system("clear");
        menuCases(option);
    }
}

int getNumberFromInput() {
    char buffer[MAX_CHAR_NAME];
    fgets(buffer, MAX_CHAR_NAME, stdin);
    if (isNumeric(buffer)) {
        return atoi(buffer);
    }
    return 0;
}

void showMenu() {
    printf("\
            \n1 - Mostrar os alunos cadastrados;\
            \n2 - Registar um aluno novo;\
            \n3 - Selecionar um aluno;\
            \n\
            \n4 - Mostrar livros cadastrados;\
            \n5 - Registrar um livro novo;\
            \n6 - Selecionar um livro novo;\
            \n\
            \n7 - Importar dados;\
            \n8 - Exportar dados;\
            \n\
            \n0 - Sair;\
            \n\n");
}

void menuCases(const int option) {
    switch (option) {
        case SHOWUSERS:
            printAllUsers();
            break;
        case CREATEUSER:
            registerUser();
            break;
        case SELECTUSER:
            selectUser();
            break;
        case SHOWBOOKS:
            printAllBooks();
            break;
        case CREATEBOOK:
            registerBook();
            break;
        case SELECTBOOK:
            break;
        case IMPORT:
            break;
        case EXPORT:
            exportToFile();
            break;
        case QUIT:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}



void printUser(User_t *user) {
    printf("\n\tNome: %s\n", user->name);

    if (user->rentedBooks != NULL) {
        printUserBooks(user);
    }
}

void printBook(Book_t *book) {
    printf("\tNome: %s\n", book->name);

    if (book->isRented) {
    }
}

void sortBooksCres() {
}

void sortBooksUncres() {
}

void importFromFile() {
}

void exportToFile() {
}

void freeAll() {
    freeUsers();
    freeBooks();
}

void freeBooks () {
    Book_t *book = library.firstBook;
    Book_t *aux;
    while (book != NULL) {
        aux = book;
        book = book->next;
        free(aux);
    }
}

void freeUsers() {
    User_t *user = library.firstUser;
    User_t *aux;
    while (user != NULL) {
        aux = user;
        user = user->next;
        free(aux);
    }
}

void sort() {
}

int isNumeric(const char *buffer) {
    char *foo;

    /* Transforma buffer em um número e insere o valor em foo  */
    strtof(buffer, &foo);

    /* Se foo for igual a buffer, o texto em buffer é um número */
    if (foo == buffer) {
        return 0;
    }

    /* Se não, o texto é só uma palavra */
        return 1;
}


void printEditUserMenu() {
    printf("O que deseja fazer?\
            \n1 - Editar nome.\
            \n2 - Devolver algum livro.\
            \n3 - Deletar usuário.\
            \n0 - Sair.\n");
}

void editName(User_t *user) {
    fgets(user->name, MAX_CHAR_NAME, stdin);
}

void returnBook(User_t *user) {
}
