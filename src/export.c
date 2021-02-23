#include "libraryControl.h"

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

void exportUsersToFile(const char *userFilename) {
    FILE *userFile = fopen(userFilename, "w");
    User_t *user = library.firstUser;
    while (user != NULL) {
        fprintf(userFile,
                "\n%s\
                \n%d",
                user->name, user->totalRentedBooks);

        for (int i = 0; i < user->totalRentedBooks; i++) {
            fprintf(userFile,
                    "%s\
                    \n%s\
                    \n%s\n",
                    user->rentedBooks[i]->name, user->rentedBooks[i]->author,
                    user->rentedBooks[i]->returnDate.dateString);
        }

        user = user->next;
    }

    fclose(userFile);
}

void exportBooksToFile(const char *bookFilename) {
    FILE *bookFile = fopen(bookFilename, "w");
    Book_t *book = library.firstBook;
    while (book != NULL) {
        if (book->isRented == false) {
            fprintf(bookFile,
                    "\n%s\
                    \n%s\
                    \n%d\
                    \n%s",
                    book->name, book->author, book->isRented,
                    book->returnDate.dateString);
        }
        book = book->next;
    }
}

void askForFilename(char *filename, const char *prompt) {
    printf(
        "Qual o nome do arquivo para salvar os %s?\
            \nArquivo: ",
        prompt);
    fgetsNoNewline(filename, MAX_CHAR_NAME, stdin);
}
