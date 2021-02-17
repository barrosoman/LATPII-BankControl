#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bankControl.h"

Book_t *lookForBook(const int index) {
    Book_t *book = library.firstBook;
    if (index != FIRST_INDEX) {
        for (int i = FIRST_INDEX; i < index; i++) {
            book = book->next;
        }
    }
    return book;
}

void getBookName(Book_t *book) {
    printf("Qual o nome do novo livro?\
            \nNome: ");
    fgets(book->name, MAX_CHAR_NAME, stdin);
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
    newBook->prevRented = NULL;
    newBook->nextRented = NULL;
    getBookName(newBook);
}

void printAllBooks() {
    Book_t *book = library.firstBook;
    while (book != NULL) {
        printBook(book);
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

    user->rentedBooks[index] = *book;
    book->isRented = true;
}
