#include "libraryControl.h"

/* Função que começa a exportação de dados */
void exportToFile() {
    char userFilename[MAX_CHAR_NAME];
    char bookFilename[MAX_CHAR_NAME];

    askForFilename(userFilename, "usuários");
    if (strcmp(userFilename, "\n") != 0) {
        exportUsersToFile(userFilename);
    }

    askForFilename(bookFilename, "livros");
    if (strcmp(userFilename, "\n") != 0) {
        exportBooksToFile(bookFilename);
    }
}

/* Exporta usuários para um arquivo */
void exportUsersToFile(const char *userFilename) {
    FILE *userFile = fopen(userFilename, "w");
    User_t *user = library.firstUser;
    while (user != NULL) {
        fprintf(userFile, "\n%s\n%d\n", user->name, user->totalRentedBooks);

        for (int i = 0; i < user->totalRentedBooks; i++) {
            fprintf(userFile, "%s\n%s\n%s\n", user->rentedBooks[i]->name,
                    user->rentedBooks[i]->author,
                    user->rentedBooks[i]->returnDate.dateString);
        }

        user = user->next;
    }

    fclose(userFile);
}

/* Exporta livros para um arquivo */
void exportBooksToFile(const char *bookFilename) {
    FILE *bookFile = fopen(bookFilename, "w");
    Book_t *book = library.firstBook;
    while (book != NULL) {
        if (book->isRented == false) {
            fprintf(bookFile, "%s\n%s\n", book->name, book->author);
        }
        book = book->next;
    }
    fclose(bookFile);
}
