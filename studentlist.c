/**********************************************************************
48430 Embedded C - Assignment 2
Name: Michael Codner
Student ID: 11989668
Date of submission:
A brief statement on what you could achieve (less than 50 words):


A brief statement on what you could NOT achieve (less than 50 words):


**********************************************************************/

/**********************************************************************
List of header files - you may use any standard C libraries.
List preprocessing directives - you may define your own.
List structs - you may define struct date and struct student only.
**********************************************************************/
#include <stdlib.h>
#include <stdio.h>

/* Maximum number of students in the class */
#define MAX_CLASS_SIZE 5
/* Maximum length of the string - student name. Note that all strings
in C are NULL terminated i.e. '\0' at the end of the string. Hence the
length of the actual name can be 10 characters at most*/
#define MAX_NAME_SIZE 11
/* Static file name of the text file where student list is stored */
#define DB_FILE_NAME "database"


/* struct date - contains
	day - unsigned integer between 1 and 31 (inclusive)
	month - unsigned integer between 1 and 12
	year - unsigned integer between 1800 and 2016
Note: do not worry about some months not having dates 29-31. That means
30-02-1900 is a real date, although the month of Feb does not have a
day30.
*/
struct date {
    int day;
    int month;
    int year;
};

struct student {
    char name[MAX_NAME_SIZE];
    float gpa;
    struct date birthday;
};

typedef struct student student_t;

/**********************************************************************
Function prototypes - do NOT change the given prototypes. However you
may define your own functions if required.
**********************************************************************/
void printmenu(void);

void addStudent(student_t[], int*);
void displayList(student_t[], int*);
void save(student_t[], int*);
void read(student_t[], int*);
int isNumber (char[]);
int isFloat (char[]);

/**********************************************************************
Main
**********************************************************************/
int main(void) {
    student_t studentlist[MAX_CLASS_SIZE];
    int listSize = 0;
    char choice;
    do {
        printmenu();
        printf("Enter your choice>");
        char temp[10];
        scanf("%1[^\n]", temp);
        choice = temp[0];
        while (getchar() != '\n') {
            choice = '0';
        }
        switch (choice){
            case '1':
                addStudent(studentlist, &listSize);
                break;
            case '2':
                if (listSize > 0)
                    listSize--;
                else
                    printf("Class is empty\n");
                break;
            case '3':
                displayList(studentlist, &listSize);
                break;
            case '4':
                save(studentlist, &listSize);
                break;
            case '5':
                read(studentlist, &listSize);
                break;
            case '6':
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
    while (choice != '6');
    return 1;
}

/**********************************************************************
Print 2 empty lines followed by the choices menu.
**********************************************************************/
void printmenu(void) {
    printf("\n\n"
                   "1. add student\n"
                   "2. delete last student\n"
                   "3. display student list\n"
                   "4. save the student list to the database\n"
                   "5. read the student list from the database\n"
                   "6. exit the program\n");
}

void addStudent(student_t list[], int* listSize) {
    if (*listSize >= MAX_CLASS_SIZE) {
        printf("Class is full\n");
    }
    else {
        student_t newStudent;
        int scanReturn;

        do {
            printf("Enter name>");
            scanReturn = scanf(" %10[^\n]", newStudent.name);
            while (getchar()!='\n');
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid day. ");
            printf("Enter birthday: Day>");
            char temp[100];
            scanf("%100[^\n]", temp);
            scanReturn = isNumber(temp);
            if (atoi(temp) < 1 || atoi(temp) > 31)
                scanReturn = 0;
            else
                newStudent.birthday.day = atoi(temp);
            while (getchar()!='\n');
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid month. ");
            printf("Enter birthday: Month>");
            char temp[100];
            scanf("%100[^\n]", temp);
            scanReturn = isNumber(temp);
            if (atoi(temp) < 1 || atoi(temp) > 12)
                scanReturn = 0;
            else
                newStudent.birthday.month = atoi(temp);
            while (getchar()!='\n');
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid year. ");
            printf("Enter birthday: Year>");
            char temp[100];
            scanf("%100[^\n]", temp);
            scanReturn = isNumber(temp);
            if (atoi(temp) < 1800 || atoi(temp) > 2016)
                scanReturn = 0;
            else
                newStudent.birthday.year = atoi(temp);
            while (getchar()!='\n');
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid GPA. ");
            printf("Enter GPA>");
            char temp[100];
            scanf("%100[^\n]", temp);
            scanReturn = isFloat(temp);
            if (atof(temp) < 0 || atof(temp) > 4)
                scanReturn = 0;
            else
                newStudent.gpa = atof(temp);
            while (getchar()!='\n');
        } while (scanReturn != 1);

        list[*listSize] = newStudent;
        *listSize += 1;
    }
}

void displayList(student_t list[], int* listSize) {
    if (*listSize == 0) {
        printf("Class is empty\n");
    }
    else {
        printf("Name       Birthday   GPA   \n");
        printf("---------- ---------- ------\n");
        int i;
        for (i = 0; i < *listSize; i++) {
            printf("%-10.10s %02d-%02d-%d %.4f\n", list[i].name, list[i].birthday.day, list[i].birthday.month, list[i].birthday.year, list[i].gpa);
        }
    }
}

void save(student_t list[], int* listSize) {
    FILE* db = fopen(DB_FILE_NAME, "w");
    int i;
    for (i = 0; i < *listSize; i++) {
        fprintf(db, "%11s %02d-%02d-%d %.4f\n", list[i].name, list[i].birthday.day, list[i].birthday.month, list[i].birthday.year, list[i].gpa);
    }
    fclose(db);
}

void read(student_t list[], int* listSize) {
    FILE* db = fopen(DB_FILE_NAME, "r");
    if (NULL == db)
    {
        printf("Read error\n");
    }
    else {
        int i = 0;
        while (EOF != fscanf(db, "%11s %02d-%02d-%d %f\n", list[i].name, &list[i].birthday.day, &list[i].birthday.month, &list[i].birthday.year, &list[i].gpa)) {
            i++;
        }

        *listSize = i;
    }

    fclose(db);
}

int isNumber (char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if ((int)str[i] < 48 || (int)str[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int isFloat (char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (((int)str[i] < 48 || (int)str[i] > 57) && (int)str[i] != 46) {
            return 0;
        }
    }
    return 1;
}