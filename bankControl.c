#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_NAME 128
#define INVALID_OPTION -1

typedef struct date{
    int year, month, day;
} Date_t;

typedef struct user {
    char name[MAX_CHAR_NAME];
    int index;
    struct book **rentedBooks;
    struct user *prev, *next;
} User_t;

typedef struct book {
    char name[MAX_CHAR_NAME];
    int index;
    _Bool isRented;
    struct date returnDate;
    struct book *prev, *next;
} Book_t;

typedef struct library {
    User_t *firstUser;
    User_t *lastUser;
    Book_t *firstBook;
    Book_t *lastBook;
    int totalUsers;
    int totalBooks;
} Library_t;
Library_t library;

enum OPTIONS {
    QUIT,
    SHOWUSERS,
    CREATEUSER,
    SELECTUSER,
    SHOWBOOKS,
    CREATEBOOK,
    SELECTBOOK,
    IMPORT,
    EXPORT,
};

void registerUser();
void removeUser();
void registerBook();
void removeBook();
void rentBookToUser();
void returnBookFromUser();
void listAllUsers();
void listAllBooks();
void sortCres();
void sortUncres();
void importFromFile();
void exportToFile();
void showMenu();
void menuLoop();
void menuCases(int option);
void selectUser();
int getOptionFromInput();
void printUser(User_t *user);
void printBook(Book_t *book);
void getUserName(User_t *user);
void printUserBooks(User_t *user);
void freeBooks();
void freeUsers();
void freeAll();

int main() {
    atexit(freeAll);
    system("clear");
    printf("Bem-vindo, o que deseja fazer?\n");
    menuLoop();
    return 0;
}

void menuLoop() {
    int option;
    while (1) {
        showMenu();
        option = getOptionFromInput();
        system("clear");
        menuCases(option);
    }
}

int getOptionFromInput() {
    int option = INVALID_OPTION;
    char buffer[MAX_CHAR_NAME];

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %d", &option);

    return option;
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

void menuCases(int option) {
    switch (option) {
        case SHOWUSERS:
            listAllUsers();
            break;
        case CREATEUSER:
            registerUser();
            break;
        case SELECTUSER:
            selectUser();
            break;
        case SHOWBOOKS:
            listAllBooks();
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

void registerUser() {
    User_t *newUser = (User_t *) malloc(sizeof(User_t));
    library.totalUsers++;

    if (library.firstUser == NULL) {
        library.firstUser = library.lastUser = newUser;
        newUser->next = NULL;
        newUser->prev = NULL;
    } else {
        library.lastUser->next = newUser;
        newUser->prev = library.lastUser;
        newUser->next = NULL;
        library.lastUser = newUser;
    }

    newUser->rentedBooks = NULL;
    newUser->index = library.totalUsers;

    getUserName(newUser);
}

void getUserName(User_t *user) {
    printf("Qual o nome do novo usuário?\
            \nNome: ");
    fgets(user->name, MAX_CHAR_NAME, stdin);
}

void getBookName(Book_t *book) {
    printf("Qual o nome do novo livro?\
            \nNome: ");
    fgets(book->name, MAX_CHAR_NAME, stdin);
}

void selectUser() {
}

void removeUser() {
}

void registerBook() {
    Book_t *newBook = (Book_t *) malloc(sizeof(Book_t));
    library.totalBooks++;

    if (library.firstBook == NULL) {
        library.firstBook = library.lastBook = newBook;
        newBook->next = NULL;
        newBook->prev = NULL;
    } else {
        library.lastBook->next = newBook;
        library.lastBook = newBook;
        newBook->prev = library.lastBook;
        newBook->next = NULL;
    }

    newBook->index = library.totalBooks;
    newBook->isRented = 0;
    getBookName(newBook);
}

void removeBook() {
}

void rentBookToUser() {
    int index;
    printf("Qual livro a emprestar?");
    scanf("%d", &index);



}

void returnBookFromUser() {
}

void listAllUsers() {
    User_t *user = library.firstUser;
    while (user != NULL) {
        printUser(user);
        user = user->next;
    }
}

void printUser(User_t *user) {
    printf("\n%d - \
            \n\tNome: %s\n", user->index, user->name);

    if (user->rentedBooks != NULL) {
        printUserBooks(user);
    }
}

void printUserBooks(User_t *user) {
    int i = 0;
    Book_t *userBook = user->rentedBooks[i];
    while (userBook != NULL) {
        printBook(userBook);
        i++;
        userBook = user->rentedBooks[i];;
    }
}

void printBook(Book_t *book) {
    printf("\n%d - \
            \n\tNome: %s\n", book->index, book->name);

    if (book->isRented) {
    }
}

void listAllBooks() {
    Book_t *book = library.firstBook;
    while (book != NULL) {
        printBook(book);
        book = book->next;
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

void freeBooks() {
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
