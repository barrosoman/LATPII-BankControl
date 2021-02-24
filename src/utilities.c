#include "libraryControl.h"

/* Pede uma string ao usuário e sendo ela um número,
   a função o retorna com atoi() */
int getNumberFromInput() {
    char buffer[MAX_CHAR_NAME];
    fgetsNoNewline(buffer, MAX_CHAR_NAME, stdin);
    if (isNumeric(buffer)) {
        return atoi(buffer);
    }
    return -1;
}

/* Libera toda memória alocada */
void freeAll() {
    freeUsers();
    freeBooks();
}

/* Libera memória alocada a livros */
void freeBooks() {
    Book_t *book = library.firstBook;
    Book_t *aux;
    while (book != NULL) {
        aux = book;
        book = book->next;
        free(aux);
    }
}

/* Libera memória alocada a usuários */
void freeUsers() {
    User_t *user = library.firstUser;
    User_t *aux;
    while (user != NULL) {
        aux = user;
        user = user->next;
        free(aux);
    }
}

/* Verifica se uma string é um número */
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

/* Função base para outras que pedem um nome */
void editGenericName(const char *prompt, const char *bookOrUser, char *field) {
    printf("%s do %s: ", prompt, bookOrUser);
    fgetsNoNewline(field, MAX_CHAR_NAME, stdin);
}

/* Fgets sem pegar o '\n' da linha */
void fgetsNoNewline(char *s, int size, FILE *stream) {
    fgets(s, size, stream);
    s = strtok(s, "\n");
}

/* Verifica se duas string são iguais */
int isStrEqual(const char *string1, const char *string2) {
    if (strcmp(string1, string2) == 0) {
        return 1;
    }
    return 0;
}

/* Analisa uma string AAAAMMDD e insere em dia, mês e ano do
   dia de retorno de algum livro emprestado */
void getReturnDateFromString(Book_t *book, const char *string) {
    Date_t *returnDate = &book->returnDate;
    sscanf(string, "%4d%2d%2d", &returnDate->year, &returnDate->month,
           &returnDate->day);
}

/* Aloca memória a mais para o array de livros emprestados de um usuários */
void incRentedBookArray(User_t *user) {
    user->rentedBooks = (Book_t **)realloc(
        user->rentedBooks, sizeof(Book_t *) * (user->totalRentedBooks));
}

/* Pede um nome de um arquivo */
void askForFilename(char *filename, const char *prompt) {
    printf(
        "Qual o nome do arquivo para salvar os %s?\
            \nArquivo: ",
        prompt);
    fgetsNoNewline(filename, MAX_CHAR_NAME, stdin);
}
