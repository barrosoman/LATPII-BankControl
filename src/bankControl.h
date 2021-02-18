#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

typedef struct date{
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
    struct book *rentedBooks;
} User_t;

typedef struct library {
    User_t *firstUser;
    User_t *lastUser;
    Book_t *firstBook;
    Book_t *lastBook;
    int totalUsers;
    int totalBooks;
} Library_t;
extern Library_t library;

enum USER_EDIT_OPTIONS {
    EDITUSERNAME = 1,
    RETURNBOOK = 2,
    RENTBOOK = 3,
    DELETEUSER = 4,
};

enum BOOK_EDIT_OPTIONS {
    EDITBOOKNAME = 1,
    EDITBOOKAUTHOR = 2,
    DELETEBOOK = 3,
};

enum MENU_OPTIONS {
    QUIT,
    SHOWUSERS,
    CREATEUSER,
    SELECTUSER,
    SHOWBOOKS,
    CREATEBOOK,
    SELECTBOOK,
    IMPORT,
    EXPORT,
};

void registerUser();
void getUserName(User_t *user);
void selectUser();
void printAllUsers();
void printUserBooks(User_t *user);
User_t *lookForUser(const int index);
int userEditCommands(User_t *user, const int option);
void deleteUser(User_t *user);
void rentBook(User_t *user);
void menuLoop();
int getNumberFromInput();
void showMenu();
void menuCases(const int option);
void printUser(User_t *user);
void printBook(Book_t *book);
void freeAll();
void freeBooks ();
void freeUsers();
void sort();
int isNumeric(const char *buffer);
void printEditUserMenu();
void returnBook(User_t *user);
Book_t *lookForBook(const int index);
void getBookName(Book_t *book);
void registerBook();
void printAllBooks();
void addBookToUser(User_t *user, Book_t *book);
void incRentedBookArray(User_t *user);
void exportToFile();
void askForReturnDate(Book_t *book);
void getBookAuthor(Book_t *book);
void removeNewLine(char *string);
void editUserName(User_t *user);
void editGenericName(const char *prompt, const char *bookOrUser, char *field);
void printEditBookMenu();
int bookEditCommands(Book_t *book, const int option);
void selectBook();
void editBookAuthor(Book_t *book);
void editBookName(Book_t *book);
void deleteBook(Book_t *book);
void fgetsNoNewline(char *s, int size, FILE *stream);
