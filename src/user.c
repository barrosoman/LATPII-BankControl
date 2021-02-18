#include "bankControl.h"

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

    /* newUser->rentedBooks = NULL; */

    getUserName(newUser);
}

void getUserName(User_t *user) {
    printf("Qual o nome do novo usuário?\
            \nNome: ");
    fgetsNoNewline(user->name, MAX_CHAR_NAME, stdin);
}

void selectUser() {
    printf("\nQual usuário?\
            \nId: ");
    int userIndex = getNumberFromInput();
    if (userIndex == 0 || userIndex > library.totalUsers) {
        printf("Id inválido\n");
        return;
    }

    User_t *user = lookForUser(userIndex);
    int option;
    while (1) {
        printUser(user);
        putchar('\n');
        printEditUserMenu();
        option = getNumberFromInput();

        system("clear");
        if (userEditCommands(user, option) == QUIT) {
            return;
        }
    };
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
    Book_t *userBook = user->rentedBooks;
    printf("Livros Emprestados:\n");
    for (int i = 0; i < user->totalRentedBooks; i++) {
        printf("\n\t%d - ", i+1);
        printBook(&userBook[i]);
    }
}

User_t *lookForUser(const int index) {
    User_t *user = library.firstUser;
    if (index != FIRST_INDEX) {
        for (int i = FIRST_INDEX; i < index; i++) {
            user = user->next;
        }
    }
    return user;
}

int userEditCommands(User_t *user, const int option) {
    switch (option) {
        case EDITUSERNAME:
            editUserName(user);
            break;
        case RETURNBOOK:
            returnBook(user);
            break;
        case RENTBOOK:
            rentBook(user);
            break;
        case DELETEUSER:
            deleteUser(user);
        case QUIT:
            return QUIT;
        default:
            printf("Opção inválida");
            break;
    }
    return 1;
}

void deleteUser(User_t *user) {
    if (library.totalUsers == 1) {
        free(user);
        library.firstUser = library.lastUser = NULL;
        library.totalUsers--;
        return;
    }
    user->prev->next = user->next;
    user->next->prev = user->prev;
    free(user);
    library.totalUsers--;
}

void rentBook(User_t *user) {
    printAllBooks();
    printf("Qual livro a ser emprestado?\
            \nId: ");

    const int index = getNumberFromInput();
    if (index == 0 || index > library.totalBooks) {
        printf("Id inválido\n");
        return;
    }

    Book_t *book = lookForBook(index);
    addBookToUser(user, book);
    askForReturnDate(book);

}

void incRentedBookArray(User_t *user) {
    user->rentedBooks =
        (Book_t *)realloc(user->rentedBooks, sizeof(Book_t) * (user->totalRentedBooks));
}

void printUser(User_t *user) {
    printf("\n\tNome: %s\n", user->name);

    if (user->rentedBooks != NULL) {
        printUserBooks(user);
    }
}

void askForReturnDate(Book_t *book) {
    printf("Qual o a data de retorno?\
            \nEstilo \"DD/MM/AAAA\": ");
    scanf("%d/%d/%d", &book->returnDate.day, &book->returnDate.month, &book->returnDate.year);
}

void editUserName(User_t *user) {
    editGenericName("Nome", "Usuário", user->name);
}
