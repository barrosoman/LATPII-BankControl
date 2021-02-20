#include "libraryControl.h"

int getNumberFromInput() {
    char buffer[MAX_CHAR_NAME];
    fgetsNoNewline(buffer, MAX_CHAR_NAME, stdin);
    if (isNumeric(buffer)) {
        return atoi(buffer);
    }
    return 0;
}

void importFromFile() {}

void exportToFile() {
    char userFilename[MAX_CHAR_NAME];
    askForFilename(userFilename, "usuários");
    /* char bookFilename[MAX_CHAR_NAME] = askForUserFile(); */

    exportUsersToFile(userFilename);
}

void exportUsersToFile(const char *userFilename) {
    FILE *userFile = fopen(userFilename, "w");
    User_t *user = library.firstUser;
    while (user != NULL) {
        fprintf(userFile,
                "%s\
                \n%d\
                \n\
                \n",
                user->name, user->totalRentedBooks);
        user = user->next;
    }
}

void askForFilename(char *filename, char *prompt) {
    printf("Qual o nome do arquivo para salvar os %s?\
            \nArquivo: ", prompt);
    fgetsNoNewline(filename, MAX_CHAR_NAME, stdin);
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

void sort() {}

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

void editGenericName(const char *prompt, const char *bookOrUser, char *field) {
    printf("%s do %s: ", prompt, bookOrUser);
    fgetsNoNewline(field, MAX_CHAR_NAME, stdin);
}

void fgetsNoNewline(char *s, int size, FILE *stream) {
    fgets(s, size, stream);
    s = strtok(s, "\n");
}
