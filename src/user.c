#include "libraryControl.h"

/* Procura por um usuário a partir de um index e retorna o endereço dele */
User_t *lookForUser(const int index) {
    User_t *user = library.firstUser;
    if (index != FIRST_INDEX) {
        for (int i = FIRST_INDEX; i < index; i++) {
            user = user->next;
        }
    }
    return user;
}

/* Aloca e estabelece um usuário "limpo" na lista */
void registerUser() {
    User_t *newUser = (User_t *)malloc(sizeof(User_t));
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

    editUserName(newUser);
}

/* Seleciona um usuário para visualização/editar */
void selectUser() {
    if (library.firstUser == NULL) {
        printf("Não há usuários cadastrados.\n");
        return;
    }

    printAllUsers();
    printf(
        "\nQual usuário?\
            \nId: ");
    int userIndex = getNumberFromInput();
    if (userIndex <= 0 || userIndex > library.totalUsers) {
        printf("Id inválido\n");
        return;
    }
    if (selectUserWhile(userIndex) == QUIT) {
        return;
    }
}

/* Roda o menu de editação até que o usuário queira sair dele */
int selectUserWhile(const int userIndex) {
    User_t *user = lookForUser(userIndex);
    int option;
    while (1) {
        printUser(user);
        putchar('\n');
        printEditUserMenu();
        option = getNumberFromInput();

        system(clean);
        if (userEditCases(user, option) == QUIT) {
            return QUIT;
        }
        system(clean);
    }
}

/* Printa as informações de todos usuários cadastrados */
void printAllUsers() {
    User_t *user = library.firstUser;
    int index = 1;
    while (user != NULL) {
        printf("\n%d - ", index);
        printUser(user);
        index++;
        user = user->next;
    }
}

/* Printa todos livros emprestados a um usuários */
void printUserBooks(User_t *user) {
    Book_t **userBook = user->rentedBooks;
    printf("\tLivros Emprestados:\n");
    for (int i = 0; i < user->totalRentedBooks; i++) {
        printf("\n\t%d - ", i + 1);
        printBook(userBook[i]);
    }
}

/* Desregistra um usuário da livraria */
int deleteUser(User_t *user) {
    if (user->rentedBooks != NULL) {
        printf("O usuário ainda tem livros a devolver.");
        return 1;
    }

    char answer[MAX_CHAR_NAME];
    while (answer[0] != 's') {
        printf(
            "\nQuer mesmo deletar o usuário?\
                \nResposta(n = não, s = sim): ");
        fgets(answer, MAX_CHAR_NAME, stdin);
        if (answer[0] == 'n') {
            return 1;
        }
    }

    if (library.totalUsers == 1) {
        free(user);
        library.firstUser = library.lastUser = NULL;
        library.totalUsers--;
    } else {
        user->prev->next = user->next;
        user->next->prev = user->prev;
        free(user);
        library.totalUsers--;
    }
    return QUIT;
}

/* Empresta um livro para um usuários */
void rentBook(User_t *user) {
    if (library.totalBooks == 0) {
        return;
    }
    printAllBooks();
    printf(
        "Qual livro a ser emprestado?\
            \nId: ");

    const int index = getNumberFromInput();
    if (index <= 0 || index > library.totalBooks) {
        printf("Id inválido\n");
        return;
    }

    Book_t *book = lookForBook(index);
    if (book->isRented == true) {
        printf("Livro já está sendo emprestado");
        return;
    }
    addBookToUser(user, book);
    askForReturnDate(book);
}

/* Imprime informações de um usuário */
void printUser(User_t *user) {
    printf("\n\tNome: %s\n", user->name);

    if (user->rentedBooks != NULL) {
        printUserBooks(user);
    }
}

/* Pede do usuário a data de retorno de um livro emprestado */
void askForReturnDate(Book_t *book) {
    char date[MAX_CHAR_NAME], day[MAX_CHAR_NAME], month[MAX_CHAR_NAME],
        year[MAX_CHAR_NAME];

    printf(
        "Qual o a data de retorno?\
            \nEstilo \"DD/MM/AAAA\": ");

    fgetsNoNewline(date, MAX_CHAR_NAME, stdin);
    sscanf(date, "%2s/%2s/%4s", day, month, year);

    sprintf(book->returnDate.dateString, "%s%s%s", year, month, day);
    book->returnDate.day = atoi(day);
    book->returnDate.month = atoi(month);
    book->returnDate.year = atoi(year);
}

/* Usado para editar o nome de um usuário */
void editUserName(User_t *user) {
    editGenericName("Nome", "Usuário", user->name);
}

/* Retorna um livro de um usuário */
void returnBookFromUser(User_t *user) {
    if (user->totalRentedBooks == 0) {
        return;
    }
    printUserBooks(user);
    printf(
        "\nQual livro a devolver?\
            \nId: ");
    const int option = getNumberFromInput();
    if (option <= 0 || option > user->totalRentedBooks) {
        printf("Id inválido");
        return;
    }
    returnBook(user, option - 1);
    removeBookFromUser(user, option - 1);
}

/* Registra que o livro não está sendo mais emprestado */
void returnBook(User_t *user, const int rentedBookIndex) {
    Book_t *returnedBook = user->rentedBooks[rentedBookIndex];
    returnedBook->isRented = false;
}

/* Remove o livro do array de livros emprestados do usuário */
void removeBookFromUser(User_t *user, const int bookIndex) {
    if (user->totalRentedBooks == 1) {
        user->totalRentedBooks = 0;
        free(user->rentedBooks);
        user->rentedBooks = NULL;
        return;
    }

    if (user->rentedBooks[bookIndex + 1] == NULL) {
        user->rentedBooks[bookIndex] = NULL;
        user->totalRentedBooks--;
        return;
    }

    for (int i = bookIndex; i < user->totalRentedBooks + 1; i++) {
        user->rentedBooks[i] = user->rentedBooks[i + 1];
    }
    user->totalRentedBooks--;
    incRentedBookArray(user);
}
