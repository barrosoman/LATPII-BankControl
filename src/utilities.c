#include "libraryControl.h"

int getNumberFromInput() {
    char buffer[MAX_CHAR_NAME];
    fgetsNoNewline(buffer, MAX_CHAR_NAME, stdin);
    if (isNumeric(buffer)) {
        return atoi(buffer);
    }
    return 0;
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

int isStrEqual(const char *string1, const char *string2) {
    if (strcmp(string1, string2) == 0) {
        return 1;
    }
    return 0;
}

void getReturnDateFromString(Book_t *book, const char *string) {
    Date_t *returnDate = &book->returnDate;
    sscanf(string, "%4d%2d%2d", &returnDate->year, &returnDate->month,
           &returnDate->day);
}
