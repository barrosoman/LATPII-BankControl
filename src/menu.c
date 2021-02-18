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
            selectBook();
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

void printEditUserMenu() {
    printf("O que deseja fazer?\
            \n1 - Editar nome.\
            \n2 - Devolver algum livro.\
            \n3 - Deletar usuário.\
            \n0 - Sair.\n");
}
