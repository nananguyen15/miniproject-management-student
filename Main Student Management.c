//MEMBER INFORMATION:
// Nguyen Thi Nha Tuyen (leader) - CE190631
// Phan Hong Tai - CE181490
// Tran Khanh Duy - CE180366
// Huynh Ngoc Diem Quynh - 180806
// Pham Kha Vy - CE182254
// Dong Minh Quang - CE182250

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <errno.h>

#define MAX_STUDENTS 100 // define the maximum number of students to avoid magic numbers

struct Student
{
    char name[100][100];
    char major[50];
    char studentCode[20];
    char dateOfBirth[20];
    char class [50];
};

struct Student studentList[MAX_STUDENTS]; // create an array to store students
int studentCount = 0;                     // keep track of the number of students
int input;
int n;
int ID = 1;

void printMenu();
void addStudent();
void printMajorOptions();
int isStudentCodeUnique(const char *studentCode);
int validateStudentCode(const char *major, const char *studentCode);
int isLeapYear(int year);
int validateDateOfBirth(const char *dateOfBirth);
void displayStudent();
void generateTableHead();
void generateTableLine(int id, char *name, char *class, char *major, char *studentCode, char *dateOfBirth);
void generateTableTail();
void searchStudent();
void deleteStudent();
void sortStudent();
void printSortOptions();
int validateStudentClass(const char *major, const char *class);
int isStudentClassUnique(const char *class);
void deleteAllStudent(char **name, char **class, char **major, char **studentCode, char **dateOfBirth, int *studentCount);
int validateStudentClass(const char *major, const char *classe);
int isStudentClassUnique(const char *class);
void ReadFile(int*studentCount,int*ID,char*name[],int*class[],int*major[],char*studentCode[],char*dateOfBirth[]);
void WriteFile(int*studentCount,int*ID,char*name[],int*class,int*major,char*studentCode[],char*dateOfBirth);

int main()
{
    char **name = (char**)calloc(100,sizeof(char*));
	char **class = (char**)calloc(100,sizeof(char*));
	char **major = (char**)calloc(100,sizeof(char*));
    char **studentCode = (char**)calloc(100,sizeof(char*));
    char **dateOfBirth = (char**)calloc(100,sizeof(char*));
        // Allocate memory for the strings
    for(int i = 0; i < 100; i++) {
        name[i] = (char*)calloc(100, sizeof(char));
        class[i] = (char*)calloc(100, sizeof(char));
        major[i] = (char*)calloc(100, sizeof(char));
        studentCode[i] = (char*)calloc(100, sizeof(char));
        dateOfBirth[i] = (char*)calloc(100, sizeof(char));
    }

    printf("\n\n\n\n\n\n\n\n\t\tWELCOME TO THE STUDENT MANAGEMENT PROGRAM!\n");
    do
    {
        struct Student student[n];
        printMenu();
        switch (input)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            if (studentCount == 0) {
            printf("No students to delete.\n");
            } else {
              deleteAllStudent(name,class,major,studentCode,dateOfBirth,&studentCount);
              printf("All students have been deleted.\n");
            }
            break;
        case 6:
            sortStudent();
            break;
        case 7:
            printf("The program will exit !!!\n");
            exit(1);
        default:
            printf("Invalid input\n");
            break;
        }
    } while (input != 7); // continue the loop until the user chooses to exit (option 7)

    return 0;
}

void printMenu()
{
    printf("\t*-------------------Management Student------------------*\n");
    printf("\t| 1. Add student\t\t\t\t\t|\n");
    printf("\t| 2. Display the list of student\t\t\t|\n");
    printf("\t| 3. Search student\t\t\t\t\t|\n");
    printf("\t| 4. Delete student\t\t\t\t\t|\n");
    printf("\t| 5. Delete all student\t\t\t\t\t|\n");
    printf("\t| 6. Sort student\t\t\t\t\t|\n");
    printf("\t| 7. Exit\t\t\t\t\t\t|\n");
    printf("\t*-------------------------------------------------------*\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%d", &input);
    getchar();
}

void addStudent()
{
    if (studentCount < MAX_STUDENTS)
    {
        char name[100];
        struct Student newStudent;
            while (1) {
                printf("Enter student full name: ");
                fgets(name, sizeof(name), stdin); // Get the name from user input
                name[strlen(name)-1] = '\0'; // Remove the newline character at the end
                if (isValidName(name) == 1) {
                    strncpy(newStudent.name, name, sizeof(newStudent.name));
                    break;
                }
            }

        int majorChoice;
        while (1)
        {
            // display and select major options
            printMajorOptions();

            // check if scanf successfully reads an integer
            if (scanf("%d", &majorChoice) != 1)
            {
                int c;
                // clear the input buffer if a non-integer input is detected
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Invalid input. Please enter a number (1-3) for the major choice: ");
            }
            else if (majorChoice >= 1 && majorChoice <= 3)
                // valid major choice
                break;
            else
                printf("Invalid major choice. Please try again.\n\n");
        }

        switch (majorChoice)
        {
        case 1:
            strcpy(newStudent.major, "KTPM");
            break;
        case 2:
            strcpy(newStudent.major, "MS");
            break;
        case 3:
            strcpy(newStudent.major, "NNA");
            break;
        }

        printf("\n**NOTE:\n");
            printf("- If student's major is KTPM (Ky Thuat Phan Mem), 2 first character of student's class will be SE.\n");
            printf("- If student's major is MS (Maketing So), 2 first character of student's class will be DM.\n");
            printf("- If student's major is NNA (Ngon Ngu Anh), 2 first character of student's class will be EL.\n");
            printf("- student's class must have 6 characters.\n");
        while (1)
        {
            printf("\nEnter student's class: ");
            scanf("%s", newStudent.class);
             for(int i = 0; newStudent.class[i]; i++){
           	 newStudent.class[i] = toupper(newStudent.class[i]);}
            if (validateStudentClass(newStudent.major, newStudent.class))
                break; // valid and unique student code
            else
                printf("Invalid or non-unique student class for the chosen major. Please enter a valid and unique student class.\n\n");
        }

        // validate and input student code until a valid, unique format is entered
        printf("\n**NOTE:\n");
            printf("- If student's major is KTPM (Ky Thuat Phan Mem), 2 first character of student code will be CE.\n");
            printf("- If student's major is MS (Maketing So), 2 first character of student code will be CS.\n");
            printf("- If student's major is NNA (Ngon Ngu Anh), 2 first character of student code will be CA.\n");
            printf("- Student code must have 8 characters.\n");
        while (1)
        {
            printf("\nEnter student code: ");
            scanf("%s", newStudent.studentCode);
             for(int i = 0; newStudent.studentCode[i]; i++){
            	newStudent.studentCode[i] = toupper(newStudent.studentCode[i]);}
            if (validateStudentCode(newStudent.major, newStudent.studentCode))
                break; // valid and unique student code
            else
                printf("Invalid or non-unique student code for the chosen major. Please enter a valid and unique student code.\n\n");
        }

        // validate and input date of birth until a valid format is entered
        while (1)
        {
            printf("Enter date of birth (dd/mm/yyyy): ");
            scanf("%s", newStudent.dateOfBirth);
            if (validateDateOfBirth(newStudent.dateOfBirth))
            {
                getchar();
                break; // valid date format
            }
            else
                printf("Invalid date format, values, or future date. Please enter the date in 'dd/mm/yyyy' format.\n\n");
        }
        // add the new student to the array
        studentList[studentCount] = newStudent;
        studentCount++;
        printf("Student added successfully!\n");
    }
}

void printMajorOptions()
{
    printf("\n\t\t*--------List of the majors--------*\n");
    printf("\t\t|   1. KTPM (Ky Thuat Phan Mem)\t   |\n");
    printf("\t\t|   2. MS (Maketing So)\t\t   |\n");
    printf("\t\t|   3. NNA (Ngon Ngu Anh)\t   |\n");
    printf("\t\t*----------------------------------*\n");
    printf("Enter the number corresponding to the major: ");
}

int validateStudentClass(const char *major, const char *class)
{
    if (strcmp(major, "KTPM") == 0)
    {
        // major is 'KTPM', so student code should start with 'CE'
        if (strncmp(class, "SE", 2) == 0 && strlen(class) == 6)
            return 1; // valid and unique student code
    }
    else if (strcmp(major, "MS") == 0)
    {
        // major is 'MS', so student code should start with 'CS'
        if (strncmp(class, "DM", 2) == 0 && strlen(class) == 6)
            return 1; // valid and unique student code
    }
    else if (strcmp(major, "NNA") == 0)
    {
        // major is 'NNA', so student code should start with 'CA'
        if (strncmp(class, "EL", 2) == 0 && strlen(class) == 6)
            return 1; // valid and unique student code
    }
    return 0; // invalid or non-unique student code for the chosen major
}

int isStudentCodeUnique(const char *studentCode)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(studentList[i].studentCode, studentCode) == 0)
            return 0; // student code already exists
    }
    return 1; // student code is unique
}

int validateStudentCode(const char *major, const char *studentCode)
{
    if (strcmp(major, "KTPM") == 0)
    {
        // major is 'KTPM', so student code should start with 'CE'
        if (strncmp(studentCode, "CE", 2) == 0 && strlen(studentCode) == 8 && isStudentCodeUnique(studentCode))
            return 1; // valid and unique student code
    }
    else if (strcmp(major, "MS") == 0)
    {
        // major is 'MS', so student code should start with 'CS'
        if (strncmp(studentCode, "CS", 2) == 0 && strlen(studentCode) == 8 && isStudentCodeUnique(studentCode))
            return 1; // valid and unique student code
    }
    else if (strcmp(major, "NNA") == 0)
    {
        // major is 'NNA', so student code should start with 'CA'
        if (strncmp(studentCode, "CA", 2) == 0 && strlen(studentCode) == 8 && isStudentCodeUnique(studentCode))
            return 1; // valid and unique student code
    }
    return 0; // invalid or non-unique student code for the chosen major
}


int isValidName (char name[])
{
  //Kiem tra xem co nhan phim enter khong
  if (strlen(name) == 0 || strspn(name, " ") == strlen(name))
  {
    printf("Name cannot be empty. Please enter again !\n\n");
    return 0;
  }
  // Count consecutive spaces
  int consecutiveSpaces = 0;
  for (int i = 0; i < strlen(name); i++) {
    if (name[i] == ' ') {
      consecutiveSpaces++;
    } else {
      consecutiveSpaces = 0;
    }
    // Reject if more than one consecutive space
    if (consecutiveSpaces > 1) {
      printf("No more than one consecutive space allowed!\n\n");
      return 0;
    }
  }
  //Kiem tra xem co nhap so hay ki tu dac biet khong
  for (int i = 0; i < strlen(name); i++)
  {
    if (!isalpha(name[i]) && name[i] != ' ')
    {
      printf ("Accept only letters !\n\n");
      return 0; // Return 0 immediately if a non-alphabet character is found
    }
    //Kiem tra xem co nhap nhieu dau cach trong ten hay co ki tu trong ten bi trung hay ko
    else if (i < strlen(name) - 1 && name[i] == name[i+1] && name[i] != ' ')
    {
      printf("No consecutive repeated characters allowed!\n\n");
      return 0;
    }
  }
  name[0] = toupper(name[0]); //viet hoa chu cai dau
  for (int i = 1; i < strlen(name);i++)
    name[i] = tolower(name[i]);

  return 1;
}

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 1; // leap year
    }
    return 0; // not a leap year
}

int validateDateOfBirth(const char *dateOfBirth)
{
    int day, month, year;
    if (sscanf(dateOfBirth, "%d/%d/%d", &day, &month, &year) == 3)
    {
        if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12)
        {
            int maxDay = 31; // default to maximum days in a month
            if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                maxDay = 30; // April, June, September, November have 30 days
            }
            else if (month == 2)
            {
                maxDay = isLeapYear(year) ? 29 : 28; // February has 28 or 29 days depending on leap year
            }

            if (day >= 1 && day <= maxDay)
            {
                // check if the entered date is not in the future
                // stolen from https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program#1442131
                time_t current_time;
                struct tm *current_date;
                time(&current_time);
                current_date = localtime(&current_time);

                if (year < (current_date->tm_year + 1900) || (year == (current_date->tm_year + 1900) &&
                                                            (month < (current_date->tm_mon + 1) ||
                                                            (month == (current_date->tm_mon + 1) &&
                                                            day <= current_date->tm_mday))))
                {
                    return 1; // valid date format and values
                }
            }
        }
    }
    return 0; // invalid date format or values
}
void sortStudentByDateOfBirth()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }

    // create a temporary list of students for sorting
    struct Student tempStudentList[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++)
        tempStudentList[i] = studentList[i];

    // perform sorting based on date of birth
    int swapped;
    struct Student temp;

    do
    {
        swapped = 0;
        for (int i = 0; i < studentCount - 1; i++)
        {
            // Convert date of birth strings to integers for comparison
            int day1, month1, year1, day2, month2, year2;
            sscanf(tempStudentList[i].dateOfBirth, "%d/%d/%d", &day1, &month1, &year1);
            sscanf(tempStudentList[i + 1].dateOfBirth, "%d/%d/%d", &day2, &month2, &year2);

            if (year1 > year2 || (year1 == year2 && (month1 > month2 || (month1 == month2 && day1 > day2))))
            {
                temp = tempStudentList[i];
                tempStudentList[i] = tempStudentList[i + 1];
                tempStudentList[i + 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);

    // print the sorted results
    printf("Students sorted by date of birth:\n");
    generateTableHead();
    for (int i = 0; i < studentCount; i++)
    {
        generateTableLine(i + 1, tempStudentList[i].name, tempStudentList[i].major, tempStudentList[i].class, tempStudentList[i].studentCode, tempStudentList[i].dateOfBirth);
    }
    generateTableTail();
}
void displayStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
    }
    else
    {
        printf("\nList of students:\n");
        generateTableHead();
        for (int i = 0; i < studentCount; i++)
        {
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
        }
        generateTableTail();
    }
}

void generateTableHead()
{
    printf("+------+--------------------+----------------+----------------+----------------+-----------------+\n");
    printf("|  ID  |    Student Name    |     Major      |     Class      |  Student Code  |  Date of Birth  |\n");
    printf("+------+--------------------+----------------+----------------+----------------+-----------------+\n");
}

void generateTableLine(int id, char *name, char *major, char *class, char *studentCode, char *dateOfBirth)
{
    printf("| %2d   | %-18s | %-14s | %-14s | %-14s | %-14s  |\n", id, name, major, class, studentCode, dateOfBirth);
}

void generateTableTail()
{
    printf("+------+--------------------+----------------+----------------+----------------+----------------+\n");
}

void searchStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }

    int option;
    printSearchOptions();
    printf("Enter the number corresponding to the searching option: ");
    scanf("%d", &option);

    if (option < 1 || option > 5)
    {
        printf("Invalid sorting option.\n");
        return;
    }

    char searchQuery[100];
    printf("Enter part of the student's name: ");
    scanf("%s", searchQuery);
    int found = 0;
    for (int i = 0; i < studentCount; i++)
    {
        switch (option){
        case 1: // Search by name
            if (strstr(studentList[i].name, searchQuery) != NULL) {
                if (!found)
                {
                    printf("Students found:\n");
                    generateTableHead();
                    found = 1;
                }
                generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
            }
        case 2:
            if (strstr(studentList[i].major, searchQuery) != NULL) {
                if (!found) {
                    printf("Students found:\n");
                    generateTableHead();
                    found = 1;
                }
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
            }
            break;
        case 3:
            if (strstr(studentList[i].class, searchQuery) != NULL) {
                if (!found) {
                    printf("Students found:\n");
                    generateTableHead();
                    found = 1;
                }
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
            }
            break;
        case 4:
                if (strstr(studentList[i].studentCode, searchQuery) != NULL) {
                if (!found) {
                    printf("Students found:\n");
                    generateTableHead();
                    found = 1;
                }
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
            }
            break;
        case 5:
            if (strstr(studentList[i].dateOfBirth, searchQuery) != NULL) {
                if (!found) {
                printf("Students found:\n");
                generateTableHead();
                found = 1;
                }
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
            }
            break;
        default:
            printf("Invalid sorting option.\n");
            return;
        }
        if (!found) printf("No matching students found.\n");
        else generateTableTail();
    }
}

void deleteStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }

    generateTableHead();
    for (int i = 0; i < studentCount; i++)
    {
        generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
    }
    generateTableTail();

    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);
    for (int i = id - 1; i < studentCount - 1; i++)
    {
        studentList[i] = studentList[i + 1];
    }
    studentCount--;
    printf("Student deleted successfully.\n");

    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }
    else
    {
        generateTableHead();
        for (int i = 0; i < studentCount; i++)
        {
            generateTableLine(i + 1, studentList[i].name, studentList[i].major, studentList[i].class, studentList[i].studentCode, studentList[i].dateOfBirth);
        }
        generateTableTail();
    }
}

void sortStudent()
{
    if (studentCount == 0)
    {
        printf("No students added yet.\n");
        return;
    }

    int option;
    printSortOptions();
    printf("Enter the number corresponding to the sorting option: ");
    scanf("%d", &option);

    if (option < 1 || option > 5)
    {
        printf("Invalid sorting option.\n");
        return;
    }

    // create a temporary list of students for sorting
    struct Student tempStudentList[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++)
        tempStudentList[i] = studentList[i];

    // perform sorting based on the selected option
    int swapped;
    struct Student temp;

    do
    {
        swapped = 0;
        for (int i = 0; i < studentCount - 1; i++)
        {
            int compareResult = 0;
            switch (option)
            {
            case 1:
                compareResult = strcmp(tempStudentList[i].name, tempStudentList[i + 1].name);
                break;
            case 2:
                compareResult = strcmp(tempStudentList[i].major, tempStudentList[i + 1].major);
                break;
            case 3:
                compareResult = strcmp(tempStudentList[i].class, tempStudentList[i + 1].class);
                break;
            case 4:
                compareResult = strcmp(tempStudentList[i].studentCode, tempStudentList[i + 1].studentCode);
                break;
            case 5:
                sortStudentByDateOfBirth();
                break;
            default:
                printf("Invalid sorting option.\n");
                return;
            }

            if (compareResult > 0)
            {
                temp = tempStudentList[i];
                tempStudentList[i] = tempStudentList[i + 1];
                tempStudentList[i + 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);

    // print the sorted results
    printf("Students sorted in ascending order:\n");
    generateTableHead();
    for (int i = 0; i < studentCount; i++)
    {
        generateTableLine(i + 1, tempStudentList[i].name, tempStudentList[i].major,tempStudentList[i].class, tempStudentList[i].studentCode, tempStudentList[i].dateOfBirth);
    }
    generateTableTail();
}

void printSortOptions()
{
    printf("Select a sorting option:\n");
    printf("1. Name\n");
    printf("2. Major\n");
    printf("3. Class\n");
    printf("4. Student code\n");
    printf("5. Date of birth\n");
}

void printSearchOptions()
{
    printf("Select a searching option:\n");
    printf("1. Name\n");
    printf("2. Major\n");
    printf("3. Class\n");
    printf("4. Student code\n");
    printf("5. Date of birth\n");
}
void deleteAllStudent(char *name[], char *class[], char *major[], char *studentCode[], char *dateOfBirth[], int *studentCount)
{
    (*studentCount) = 0;
    char **Names_ = realloc(name, 0 * sizeof(char *));
    char **Classes_ = realloc(class, 0 * sizeof(char *));
    char **Majors_ = realloc(major, 0 * sizeof(char *));
    char **StudentCodes_ = realloc(studentCode, 0 * sizeof(char *));
    char **DateOfBirths_ = realloc(dateOfBirth, 0 * sizeof(char *));
    free(Names_);
    free(Classes_);
    free(Majors_);
    free(StudentCodes_);
    free(DateOfBirths_);
}

/*void updateStudent(int n, struct Student *students) {
    if (n == 0) {
        printf("No students added yet.\n");
        return;
    }
    int studentIndex;
    printf("Enter the index of the student to update (1 to %d): ", n);
    scanf("%d", &studentIndex);

    if (studentIndex < 1 || studentIndex > n) {
        printf("Invalid student index.\n");
        return;
    }

    struct Student *studentToUpdate = &students[studentIndex - 1];
    printf("Enter new information for student %d:\n", studentIndex);

    // Call functions to update specific fields
    printf("Enter full name: ");
    scanf("%s", studentToUpdate->name);

    // Add or modify other fields as needed

    printf("Student information updated successfully!\n");
}*/
// void ReadFile(int*studentCount,int*ID,char*name[],int*class[],int*major[],char*studentCode[],char*dateOfBirth[])
// {
//     char getName[20], getMajor[20], getClass[20], getStudentCode[20], getDateOfBirth[20];
//     int id;
//     FILE* fp;
//     fp = fopen("qlsv2.txt", "w");
//     if(fp) {
//         while(fscanf(fp, "%10d %20[^\n] %20[^\n] %20[^\n] %20[^\n] %10[^\n]\n", &id, getName, getMajor, getClass, getStudentCode, getDateOfBirth) == 6) {
//             name[*studentCount] = malloc(strlen(getName) + 1);
//             major[*studentCount] = malloc(strlen(getMajor) + 1);
//             class[*studentCount] = malloc(strlen(getClass) + 1);
//             studentCode[*studentCount] = malloc(strlen(getStudentCode) + 1);
//             dateOfBirth[*studentCount] = malloc(strlen(getDateOfBirth) + 1);
//             ID[*studentCount] = id;
//             strcpy(name[*studentCount], getName);
//             strcpy(major[*studentCount], getMajor);
//             strcpy(class[*studentCount], getClass);
//             strcpy(studentCode[*studentCount], getStudentCode);
//             strcpy(dateOfBirth[*studentCount], getDateOfBirth);
//             (*studentCount)++;
//             /* Read until end of file */
//             if(feof(fp)) {
//                 break;
//             }
//         }
//     }
//     fclose(fp);
// }

//  void WriteFile(int*studentCount,int*ID,char*name[],int*class,int*major,char*studentCode[],char*dateOfBirth)
// {
//     char fName[26];
//     printf("Enter FileName: ");
//     fgets(fName, sizeof(fName), stdin);  // Use fgets instead of gets
//     // Remove newline character if present
//     size_t len = strlen(fName);
//     if (len > 0 && fName[len-1] == '\n') {
//         fName[len-1] = '\0';
//     }
//     FILE* fp = fopen(fName, "w");
//     if(fp == NULL) {
//         printf("Could not open file %s",fName);
//         return;
//     }
//     int i;
//     for(i = 0; i < *studentCount; i++) {
//         fprintf(fp, "%-10d %-20s %-10d %-10d %-20s %-20s \n",ID[i], name[i], major[i], class[i], studentCode[i], dateOfBirth[i]);
//     }
//     fclose(fp);
// }


