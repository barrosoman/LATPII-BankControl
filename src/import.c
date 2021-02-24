#include "libraryControl.h"

/* Função que começa a importação de dados */
void importFromFile() {
    char userFilename[MAX_CHAR_NAME];
    char bookFilename[MAX_CHAR_NAME];

    printf("Qual o nome do arquivo dos usuários?\n");
    fgetsNoNewline(userFilename, MAX_CHAR_NAME, stdin);
    importUsers(userFilename);

    printf("Qual o nome do arquivo dos livros?\n");
    fgetsNoNewline(bookFilename, MAX_CHAR_NAME, stdin);
    importBooks(bookFilename);
}


/* Responsável para importar dados do arquivo de usuários */
void importUsers(const char *userFilename) {
    FILE *userFile = fopen(userFilename, "r");
    char aux[MAX_CHAR_NAME];

    while (fgets(aux, MAX_CHAR_NAME, userFile)) {
        importUser(userFile);
    }
    fclose(userFile);
}

/* Importa informações de um usuário do arquivo de usuários */
void importUser(FILE *userFile) {
    User_t *newUser = (User_t *)malloc(sizeof(User_t));
    library.totalUsers++;
    char line[MAX_CHAR_NAME];

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

    fgetsNoNewline(newUser->name, MAX_CHAR_NAME, userFile);
    newUser->totalRentedBooks = atoi(fgets(line, MAX_CHAR_NAME, userFile));
    if (newUser->totalRentedBooks > 0) {
        incRentedBookArray(newUser);
        for (int i = 0; i < newUser->totalRentedBooks; i++) {
            newUser->rentedBooks[i] = importUserRentedBook(userFile);
        }
    }
}

/* Importa livros já emprestados do arquivo de usuários */
Book_t *importUserRentedBook(FILE *userFile) {
    Book_t *newBook = (Book_t *)malloc(sizeof(Book_t));
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

    newBook->isRented = true;
    fgetsNoNewline(newBook->name, MAX_CHAR_NAME, userFile);
    fgetsNoNewline(newBook->author, MAX_CHAR_NAME, userFile);
    fgetsNoNewline(newBook->returnDate.dateString, MAX_CHAR_NAME, userFile);
    getReturnDateFromString(newBook, newBook->returnDate.dateString);
    return newBook;
}

int isAlreadyRegistred(const char *bookName) {
    Book_t *book = library.firstBook;
    while (book == NULL) {
        if (isStrEqual(bookName, book->name)) {
            return 1;
        }
        book = book->next;
    }
    return 0;
}

/* Organiza os dados para importação de um livro */
void importBook(FILE *bookFile) {
    Book_t *newBook = (Book_t *)malloc(sizeof(Book_t));
    library.totalBooks++;

    if (library.firstBook == NULL) {
        library.firstBook = library.lastBook = newBook;
        newBook->next = NULL;
        newBook->prev = NULL;
    } else {
        library.lastBook->next = newBook;
        newBook->prev = library.lastBook;
        newBook->next = NULL;
        library.lastBook = newBook;
    }

    newBook->isRented = false;
    fgetsNoNewline(newBook->name, MAX_CHAR_NAME, bookFile);
    fgetsNoNewline(newBook->author, MAX_CHAR_NAME, bookFile);
    getc(bookFile);
}

/* Responsável para importar dados do arquivo de livros */
void importBooks(const char *bookFilename) {
    FILE *bookFile = fopen(bookFilename, "r");

    while (!feof(bookFile)) {
        importBook(bookFile);
    }
    fclose(bookFile);
}
