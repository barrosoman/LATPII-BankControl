#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define clean "cls"
#elif __linux
#define clean "clear"
#else
#define clean ""
#endif

#define MAX_CHAR_NAME 128
#define INVALID_OPTION -1
#define FIRST_INDEX 1

typedef struct date {
    char dateString[MAX_CHAR_NAME];
    int year, month, day;
} Date_t;

typedef struct book {
    char name[MAX_CHAR_NAME];
    char author[MAX_CHAR_NAME];
    bool isRented;
    struct date returnDate;
    struct book *prev, *next;
} Book_t;

typedef struct user {
    char name[MAX_CHAR_NAME];
    struct user *prev, *next;

    int totalRentedBooks;
    struct book **rentedBooks;
} User_t;

typedef struct library {
    User_t *firstUser;
    User_t *lastUser;
    Book_t *firstBook;
    Book_t *lastBook;
    Book_t **rentedBooks;
    int totalUsers;
    int totalBooks;
} Library_t;
extern Library_t library;

enum USER_EDIT_OPTIONS {
    EDITUSERNAME = 1,
    RENTBOOK = 2,
    RETURNBOOK = 3,
    DELETEUSER = 4,
};

enum BOOK_EDIT_OPTIONS {
    EDITBOOKNAME = 1,
    EDITBOOKAUTHOR = 2,
    DELETEBOOK = 3,
};

enum PRINT_BOOKS_OPTIONS {
    ALLBOOKS = 1,
    RENTEDCRES = 2,
    RENTEDDECRES = 3,
};

enum MENU_OPTIONS {
    QUIT,
    SHOWUSERS,
    CREATEUSER,
    SELECTUSER,
    PRINTBOOKSMENU,
    CREATEBOOK,
    SELECTBOOK,
    IMPORT,
    EXPORT,
};

void registerUser();
void selectUser();
void printAllUsers();
void printUserBooks(User_t *user);
User_t *lookForUser(const int index);
int userEditCases(User_t *user, const int option);
int deleteUser(User_t *user);
void rentBook(User_t *user);
void menuLoop();
int getNumberFromInput();
void showMenu();
void menuCases(const int option);
void printUser(User_t *user);
void printBook(Book_t *book);
void freeAll();
void freeBooks();
void freeUsers();
void sort();
int isNumeric(const char *buffer);
void printEditUserMenu();
void returnBook(User_t *user, const int option);
Book_t *lookForBook(const int index);
void registerBook();
void printAllBooks();
void addBookToUser(User_t *user, Book_t *book);
void incRentedBookArray(User_t *user);
void exportToFile();
void askForReturnDate(Book_t *book);
void removeNewLine(char *string);
void editUserName(User_t *user);
void editGenericName(const char *prompt, const char *bookOrUser, char *field);
void printEditBookMenu();
int bookEditCommands(Book_t *book, const int option);
void selectBook();
void editBookAuthor(Book_t *book);
void editBookName(Book_t *book);
int deleteBook(Book_t *book);
void fgetsNoNewline(char *s, int size, FILE *stream);
void removeBookFromUser(User_t *user, const int bookIndex);
void returnBookFromUser(User_t *user);
void incRentedBooks(long total);
void printBooksMenuOptions();
void printBooksMenu();
void sortBooksCres(const int totalRentedBooks);
void allocateMemoryToRentedBooks(int *totalRentedBooks);
void printSortedBooks(const int totalRentedBooks);
int getRentedBooks();
void printBooksCases(const int option, const int totalRentedBooks);
void sortBooksDecres(const int totalRentedBooks);
int selectUserWhile(const int userIndex);
int selectBookWhile(const int bookIndex);

void exportToFile();
void exportUsersToFile(const char *userFilename);
void askForFilename(char *filename, const char *prompt);
void exportBooksToFile(const char *bookFilename);

Book_t *importUserRentedBook(FILE *userFile);
void importUser(FILE *userFile);
void importUsers(const char *userFilename);
void importFromFile();
void getReturnDateFromString(Book_t *book, const char *string);
int isAlreadyRegistred(const char *bookName);
int isStrEqual(const char *string1, const char *string2);
void importBooks(const char *bookFilename);
void importBook(FILE *bookFile);
