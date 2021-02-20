#include "libraryControl.h"

User_t *lookForUser(const int index) {
    User_t *user = library.firstUser;
    if (index != FIRST_INDEX) {
        for (int i = FIRST_INDEX; i < index; i++) {
            user = user->next;
        }
    }
    return user;
}

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
    if (userIndex == 0 || userIndex > library.totalUsers) {
        printf("Id inválido\n");
        return;
    }
    if (selectUserWhile(userIndex) == QUIT) {
        return;
    }
}

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

void printUserBooks(User_t *user) {
    Book_t **userBook = user->rentedBooks;
    printf("\tLivros Emprestados:\n");
    for (int i = 0; i < user->totalRentedBooks; i++) {
        printf("\n\t%d - ", i + 1);
        printBook(userBook[i]);
    }
}

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

void rentBook(User_t *user) {
    if (library.totalBooks == 0) {
        return;
    }
    printAllBooks();
    printf(
        "Qual livro a ser emprestado?\
            \nId: ");

    const int index = getNumberFromInput();
    if (index == 0 || index > library.totalBooks) {
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

void incRentedBookArray(User_t *user) {
    user->rentedBooks = (Book_t **)realloc(
        user->rentedBooks, sizeof(Book_t *) * (user->totalRentedBooks));
}

void printUser(User_t *user) {
    printf("\n\tNome: %s\n", user->name);

    if (user->rentedBooks != NULL) {
        printUserBooks(user);
    }
}

void askForReturnDate(Book_t *book) {
    char date[MAX_CHAR_NAME];

    printf(
        "Qual o a data de retorno?\
            \nEstilo \"DD/MM/AAAA\": ");

    fgetsNoNewline(date, MAX_CHAR_NAME, stdin);
    sscanf(date, "%s/%s/%s", book->returnDate.day, book->returnDate.month,
           book->returnDate.year);
    sprintf(book->returnDate.dateString, "%s%s%s", book->returnDate.year,
            book->returnDate.month, book->returnDate.day);
}

void editUserName(User_t *user) {
    editGenericName("Nome", "Usuário", user->name);
}

void returnBookFromUser(User_t *user) {
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

void returnBook(User_t *user, const int rentedBookIndex) {
    Book_t *returnedBook = user->rentedBooks[rentedBookIndex];
    returnedBook->isRented = false;
}

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
