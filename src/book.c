#include "libraryControl.h"

Book_t *lookForBook(const int index) {
    Book_t *book = library.firstBook;
    if (index != FIRST_INDEX) {
        for (int i = FIRST_INDEX; i < index; i++) {
            book = book->next;
        }
    }
    return book;
}

void editBookName(Book_t *book) {
    editGenericName("Nome", "livro", book->name);
}

void editBookAuthor(Book_t *book) {
    editGenericName("Autor", "livro", book->author);
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

    newBook->isRented = false;
    editBookName(newBook);
    editBookAuthor(newBook);
}

void printAllBooks() {
    Book_t *book = library.firstBook;
    int index = 1;
    while (book != NULL) {
        printf("%d - ", index);
        printBook(book);
        index++;
        book = book->next;
    }
}

void addBookToUser(User_t *user, Book_t *book) {
    const int index = user->totalRentedBooks;
    if (book->isRented) {
        printf("Livro ja está emprestado");
        return;
    }

    user->totalRentedBooks++;
    incRentedBookArray(user);

    user->rentedBooks[index] = book;
    book->isRented = true;
}

void printBook(Book_t *book) {
    printf("\n\tNome: %s\
            \n\tAutor: %s\n", book->name, book->author);

    if (book->isRented) {
        printf("\tDia de retorno: %d/%d/%d\n",
                book->returnDate.day, book->returnDate.month, book->returnDate.year);
    }
}

void selectBook() {
    printAllBooks();
    printf("\nQual livro?\
            \nId: ");
    int bookIndex = getNumberFromInput();

    system(clean);

    if (bookIndex == 0 || bookIndex > library.totalBooks) {
        printf("Id inválido\n");
        return;
    }

    Book_t *book = lookForBook(bookIndex);
    int option;
    while (1) {
        printBook(book);
        printEditBookMenu();
        option = getNumberFromInput();

        system(clean);
        if (bookEditCommands(book, option) == QUIT) {
            return;
        }
    };
}

void printEditBookMenu() {
    printf("O que deseja fazer?\
            \n1 - Editar nome.\
            \n2 - Editar autor.\
            \n3 - Deletar livro.\
            \n0 - Sair.\n");
}

int bookEditCommands(Book_t *book, const int option) {
    switch (option) {
        case EDITBOOKNAME:
            editBookName(book);
            break;
        case EDITBOOKAUTHOR:
            editBookAuthor(book);
            break;
        case DELETEBOOK:
            if (deleteBook(book) == QUIT) {
                return QUIT;
            }
            break;
        case QUIT:
            return QUIT;
        default:
            printf("Opção inválida");
            break;
    }
    return 1;
}

int deleteBook(Book_t *book) {
    char answer[MAX_CHAR_NAME];
    while (answer[0] != 's') {
        printf("\nQuer mesmo deletar o livro?\
                \nResposta(n = não, s = sim): ");
        fgets(answer, MAX_CHAR_NAME, stdin);
        if (answer[0] == 'n') {
            return 1;
        }
    }

    if (library.totalBooks == 1) {
        free(book);
        library.firstBook = library.lastBook = NULL;
        library.totalBooks--;
    } else {
        book->prev->next = book->next;
        book->next->prev = book->prev;
        free(book);
        library.totalBooks--;
    }
    return QUIT;
}
