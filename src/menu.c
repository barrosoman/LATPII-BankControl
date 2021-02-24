#include "libraryControl.h"

void printBooksMenu() {
    int totalRentedBooks;
    if (library.firstBook != NULL) {
        totalRentedBooks = getRentedBooks();
    }

    if (library.rentedBooks == NULL) {
        printAllBooks();
        free(library.rentedBooks);
        return;
    }

    printBooksMenuOptions();
    const int option = getNumberFromInput();
    system(clean);

    printBooksCases(option, totalRentedBooks);
}

/* Opçãos do menu de impressão dos dados de livros */
void printBooksCases(const int option, const int totalRentedBooks) {
    switch (option) {
        /* Mostrar todos livros sem ordenação */
        case ALLBOOKS:
            printAllBooks();
            break;
        /* Mostrar todos livros emprestados ordenados crescentemente */
        case RENTEDCRES:
            sortBooksCres(totalRentedBooks);
            printSortedBooks(totalRentedBooks);
            break;
        /* Mostrar todos livros emprestados ordenados decrescentemente */
        case RENTEDDECRES:
            sortBooksDecres(totalRentedBooks);
            printSortedBooks(totalRentedBooks);
            break;
        default:
            break;
    }
}

/* Organiza todos livros emprestados em um array */
int getRentedBooks() {
    int i = 0;
    Book_t *auxBook = library.firstBook;
    while (auxBook != NULL) {
        if (auxBook->isRented == true) {
            library.rentedBooks = (Book_t **)realloc(library.rentedBooks,
                                                     sizeof(Book_t *) * i + 1);
            library.rentedBooks[i] = auxBook;
            i++;
        }
        auxBook = auxBook->next;
    }
    return i;
}

/* Imprime os livros sorteados */
void printSortedBooks(const int totalRentedBooks) {
    for (int i = 0; i < totalRentedBooks; i++) {
        printBook(library.rentedBooks[i]);
    }
}

void printBooksMenuOptions() {
    printf(
        "\nO que deseja fazer?\
            \n1 - Mostrar todos os livros.\
            \n2 - Mostrar os livros emprestados em ordem crescente de data de retorno.\
            \n3 - Mostrar os livros emprestados em ordem decrescente de data de retorno.\
            \nOpção: ");
}

/* Loop do menu principal */
void menuLoop() {
    int option;
    while (1) {
        showMenu();
        option = getNumberFromInput();
        system("clear");
        menuCases(option);
    }
}

/* Mostra as opções do menu principal */
void showMenu() {
    printf(
        "\
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
            \nOpção: ");
}

/* Opções do menu principal */
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
        case PRINTBOOKSMENU:
            printBooksMenu();
            break;
        case CREATEBOOK:
            registerBook();
            break;
        case SELECTBOOK:
            selectBook();
            break;
        case IMPORT:
            importFromFile();
            break;
        case EXPORT:
            exportToFile();
            break;
        case QUIT:
            free(library.rentedBooks);
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

/* Mostra as opções de edição de um usuário */
void printEditUserMenu() {
    printf(
        "O que deseja fazer?\
            \n1 - Editar nome.\
            \n2 - Pegar um livro emprestado.\
            \n3 - Devolver algum livro.\
            \n4 - Deletar usuário.\
            \n0 - Sair.\n");
}

/* Opções do menu de edição de um usuário */
int userEditCases(User_t *user, const int option) {
    switch (option) {
        case EDITUSERNAME:
            editUserName(user);
            break;
        case RENTBOOK:
            rentBook(user);
            break;
        case RETURNBOOK:
            returnBookFromUser(user);
            break;
        case DELETEUSER:
            if (deleteUser(user) == QUIT) {
                return QUIT;
            }
            break;
        case QUIT:
            return QUIT;
        default:
            printf("Opção inválida");
            break;
    }
    return 1;
}

/* Mostra as opções de edição de um usuário */
void printEditBookMenu() {
    printf(
        "O que deseja fazer?\
            \n1 - Editar nome.\
            \n2 - Editar autor.\
            \n3 - Deletar livro.\
            \n0 - Sair.\n");
}

/* Opções de edição de um usuário */
int bookEditCommands(Book_t *book, const int option) {
    switch (option) {
        case EDITBOOKNAME:
            editBookName(book);
            break;
        case EDITBOOKAUTHOR:
            editBookAuthor(book);
            break;
        case DELETEBOOK:
            if (deleteBook(book) == QUIT) {
                return QUIT;
            }
            break;
        case QUIT:
            return QUIT;
        default:
            printf("Opção inválida");
            break;
    }
    return 1;
}
