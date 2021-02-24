#include "libraryControl.h"

/* Procura por um livro a partir de um index e retorna o endereço dele */
Book_t *lookForBook(const int index) {
    Book_t *book = library.firstBook;
    if (index != FIRST_INDEX) {
        for (int i = FIRST_INDEX; i < index; i++) {
            book = book->next;
        }
    }
    return book;
}

/* Usado para editar o nome de um livro */
void editBookName(Book_t *book) {
    editGenericName("Nome", "livro", book->name);
}

/* Usado para editar o autor de um livro */
void editBookAuthor(Book_t *book) {
    editGenericName("Autor", "livro", book->author);
}

/* Aloca e estabelece um livro "limpo" na lista */
void registerBook() {
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

    newBook->isRented = false;
    editBookName(newBook);
    editBookAuthor(newBook);
}

/* Sorteia crescentemente o array de livros emprestados */
void sortBooksCres(const int totalRentedBooks) {
    int j;
    for (int i = 1; i < totalRentedBooks; i++) {
        Book_t *temp = library.rentedBooks[i];
        j = i - 1;
        while ((j >= 0) &&
               (atoi(temp->returnDate.dateString) <
                atoi(library.rentedBooks[j]->returnDate.dateString))) {
            library.rentedBooks[j + 1] = library.rentedBooks[j];
            j = j - 1;
        }
        library.rentedBooks[j + 1] = temp;
    }
}

/* Sorteia decrescentemente o array de livros emprestados */
void sortBooksDecres(const int totalRentedBooks) {
    int j;
    for (int i = 1; i < totalRentedBooks; i++) {
        Book_t *temp = library.rentedBooks[i];
        j = i - 1;
        while ((j >= 0) &&
               (atoi(temp->returnDate.dateString) >
                atoi(library.rentedBooks[j]->returnDate.dateString))) {
            library.rentedBooks[j + 1] = library.rentedBooks[j];
            j = j - 1;
        }
        library.rentedBooks[j + 1] = temp;
    }
}

/* Printa as informações de todos livros cadastrados */
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

/* Coloca um livro especificado no array de livros emprestados de um usuário */
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

/* Imprime informações de um livro */
void printBook(Book_t *book) {
    printf(
        "\n\tNome: %s\
            \n\tAutor: %s\n",
        book->name, book->author);

    /* Se estiver emprestado, mostre a data de retorno */
    if (book->isRented) {
        printf("\tDia de retorno: %d/%d/%d\n", book->returnDate.day,
               book->returnDate.month, book->returnDate.year);
    }
}

/* Seleciona um livro para visualização/editar */
void selectBook() {
    if (library.firstBook == NULL) {
        printf("Não há livros cadastrados.\n");
        return;
    }
    printAllBooks();
    printf(
        "\nQual livro?\
            \nId: ");
    int bookIndex = getNumberFromInput();

    system(clean);

    if (bookIndex <= 0 || bookIndex > library.totalBooks) {
        printf("Id inválido\n");
        return;
    }

    if (selectBookWhile(bookIndex) == QUIT) {
        return;
    }
}

/* Roda o menu de editação até que o usuário queira sair dele */
int selectBookWhile(const int bookIndex) {
    Book_t *book = lookForBook(bookIndex);
    int option;
    while (1) {
        printBook(book);
        printEditBookMenu();
        option = getNumberFromInput();

        system(clean);
        if (bookEditCommands(book, option) == QUIT) {
            return QUIT;
        }
        system(clean);
    }
}

/* Desregistra um livro somente se não estiver emprestado */
int deleteBook(Book_t *book) {
    char answer[MAX_CHAR_NAME];
    if (book->isRented == true) {
        printf("O livro está emprestado ainda!");
        return 1;
    }
    while (answer[0] != 's') {
        printf(
            "\nQuer mesmo deletar o livro?\
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
