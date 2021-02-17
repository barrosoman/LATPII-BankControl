#pragma once

#define MAX_CHAR_NAME 128
#define INVALID_OPTION -1
#define FIRST_INDEX 1

typedef struct date{
    int year, month, day;
} Date_t;


typedef struct book {
    char name[MAX_CHAR_NAME];
    char autor[MAX_CHAR_NAME];
    bool isRented;
    struct date returnDate;
    struct book *prev, *next;
    struct book *prevRented, *nextRented;
} Book_t;


typedef struct user {
    char name[MAX_CHAR_NAME];
    /* struct book *firstRentedBook; */
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
    EDITNAME = 1,
    RETURNBOOK = 2,
    RENTBOOK = 3,
    DELETEUSER = 4,
};

enum OPTIONS {
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
void editName(User_t *user);
void returnBook(User_t *user);
Book_t *lookForBook(const int index);
void getBookName(Book_t *book);
void registerBook();
void printAllBooks();
void addBookToUser(User_t *user, Book_t *book);
void incRentedBookArray(User_t *user);
void exportToFile();
