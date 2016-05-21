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
    int listSize = 0; /* This is used to keep track of how many students are in the list*/
    char choice; /* This is used to store the menu choice */
    do {
        printmenu();
        printf("Enter your choice>");
        char temp[2]; /* Used as a temporary return for the scanf */
        int scanReturn = scanf("%1[^\n]", temp); /* This accepts at most 1 character until it sees a new line */
        choice = temp[0]; /* Choice is set to the first character of the temp string */
        if (!scanReturn)
            choice = '0';
        while (getchar() != '\n') { /* This gets rid of any extra characters after the scanf because they are still in the input stream */
            choice = '0'; /* If there are any characters after the first one, then choice is set to an invalid value */
        }
        switch (choice){
            case '1':
                addStudent(studentlist, &listSize);
                break;
            case '2':
                if (listSize > 0)
                    listSize--; /* Can't remove an element from the array but can decrement the counter */
                else
                    printf("Class is empty\n"); /* Can't delete from an empty list */
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


/*
 *  This function accepts the list of students and a pointer to the list size.
 *  It will add a new student to the list while not accepting invalid inputs
 * */
void addStudent(student_t list[], int* listSize) {
    if (*listSize >= MAX_CLASS_SIZE) {
        printf("Class is full\n"); /* Can't add more than 5 people to the class */
    }
    else {
        student_t newStudent; /* Used to store the new student until it is added to the list */
        int scanReturn; /* Used to check the number of valid values returned from scanf */

        do {
            printf("Enter name>");
            scanReturn = scanf(" %10[^\n]", newStudent.name); /* This will put at most 10 characters into the name of the new student */
            while (getchar()!='\n'); /* This clears any remaining characters in the input stream */
        } while (scanReturn != 1); /* Loop until we receive a valid input (really, only once but need to be sure) */

        do {
            if (scanReturn == 0)
                printf("Invalid day. "); /* Display error for invalid input */
            printf("Enter birthday: Day>");
            char temp[10];
            scanf("%2[^\n]", temp); /* Accept up to 2 characters until you see \n */
            scanReturn = isNumber(temp); /* Check for valid integer */
            if (atoi(temp) < 1 || atoi(temp) > 31) /* Check for correct input range */
                scanReturn = 0;
            else
                newStudent.birthday.day = atoi(temp); /* If valid, set to input */
            while (getchar()!='\n'); /* Clear the input stream of remaining characters */
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid month. "); /* Display error for invalid input */
            printf("Enter birthday: Month>");
            char temp[10];
            scanf("%2[^\n]", temp); /* Accept up to 2 characters until you see \n */
            scanReturn = isNumber(temp); /* Check for valid integer */
            if (atoi(temp) < 1 || atoi(temp) > 12) /* Check for correct input range */
                scanReturn = 0;
            else
                newStudent.birthday.month = atoi(temp); /* If valid, set to input */
            while (getchar()!='\n'); /* Clear the input stream of remaining characters */
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid year. "); /* Display error for invalid input */
            printf("Enter birthday: Year>");
            char temp[10];
            scanf("%4[^\n]", temp); /* Accept up to 4 characters until you see \n */
            scanReturn = isNumber(temp); /* Check for valid integer */
            if (atoi(temp) < 1800 || atoi(temp) > 2016) /* Check for correct input range */
                scanReturn = 0;
            else
                newStudent.birthday.year = atoi(temp); /* If valid, set to input */
            while (getchar()!='\n'); /* Clear the input stream of remaining characters */
        } while (scanReturn != 1);

        do {
            if (scanReturn == 0)
                printf("Invalid GPA. "); /* Display error for invalid input */
            printf("Enter GPA>");
            char temp[10];
            scanf("%6[^\n]", temp); /* Accept up to 6 characters until you see \n */
            scanReturn = isFloat(temp); /* Check for valid float */
            if (atof(temp) < 0 || atof(temp) > 4) /* Check for correct input range */
                scanReturn = 0;
            else
                newStudent.gpa = atof(temp); /* If valid, set to input */
            while (getchar()!='\n'); /* Clear the input stream of remaining characters */
        } while (scanReturn != 1);

        list[*listSize] = newStudent;
        *listSize += 1; /* Increment the list because we just added a student */
    }
}

/*
 *  This function accepts the list of students and a pointer to the list size.
 *  It will
 * */
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

/*
 *  This function accepts the list of students and a pointer to the list size.
 *  It will
 * */
void save(student_t list[], int* listSize) {
    FILE* db = fopen(DB_FILE_NAME, "w"); /* Opens the database file with write permissions */
    int i;
    for (i = 0; i < *listSize; i++) {
        /* Print each student to the database with the same format as printing to console to keep it simple */
        fprintf(db, "%11s %02d-%02d-%d %.4f\n", list[i].name, list[i].birthday.day, list[i].birthday.month, list[i].birthday.year, list[i].gpa);
    }
    fclose(db); /* Close the file */
}

/*
 *  This function accepts the list of students and a pointer to the list size.
 *  It will
 * */
void read(student_t list[], int* listSize) {
    FILE* db = fopen(DB_FILE_NAME, "r");
    if (NULL == db)
    {
        /* Display error if we can't read the database (usually means it doesn't exist) */
        printf("Read error\n");
    }
    else {
        int i = 0;
        /* Loops over every line of the file and sets the current index in the list to values from the database */
        while (EOF != fscanf(db, "%11s %02d-%02d-%d %f\n", list[i].name, &list[i].birthday.day, &list[i].birthday.month, &list[i].birthday.year, &list[i].gpa)) {
            i++;
        }

        *listSize = i; /* Set the list size to the number of rows in the database */
    }

    fclose(db); /* Close the file */
}

/*
 * This function accepts a string and returns whether it is a valid integer
 * */
int isNumber (char str[]) {
    int i; /* Used as the loop index */
    for (i = 0; str[i] != '\0'; i++) { /* Loop over each character of the string until we see the null character */
        /* Check the ascii value is within the range of the ascii values for 0-9 */
        if ((int)str[i] < 48 || (int)str[i] > 57) {
            return 0;
        }
    }
    return 1;
}

/*
 * This function accepts a string and returns whether it is a valid float
 * */
int isFloat (char str[]) {
    int i; /* Used as the loop index */
    for (i = 0; str[i] != '\0'; i++) { /* Loop over each character of the string until we see the null character */
        /* Check the ascii value is within the range of the ascii values for 0-9 or is a decimal point */
        if (((int)str[i] < 48 || (int)str[i] > 57) && (int)str[i] != 46) {
            return 0;
        }
    }
    return 1;
}