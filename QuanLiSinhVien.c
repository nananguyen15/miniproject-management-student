#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <errno.h> 

struct Student
{
  char fullName[100][100];
  char className[100];
  char fieldStudy[100];
  char studentCode[100]; //MSSV
  char birthDate[100];
};
typedef struct Student Student;


void checkValidSelection (int *select);
void checkValidNumberOfStudent (int *n);
void enterStudentInfo (Student *x,int n);
  void EnterFullName (int n, char fullName[][100]);
    int isValidName(char* str);

void checkValidNumberOfStudent (int *n) 
{
  while(1)
  {
    char input[1000];
    printf ("Enter the number of students: ");
    fgets (input,1000,stdin);
    input[strlen (input) - 1] = '\0';

    char *end;
    long long temp = strtol (input, &end, 10);
    if (end != input + strlen(input)) 
    {
      printf("%s is not a valid integer\n\n", input);
      continue;
    }
    else 
    {
      int i;
      for (i = 0; i < strlen(input); i++)
        if (i == 0 && input[i] == '-') continue;
      if (i < strlen(input)) continue;  // If a non-digit character was found, continue with the next iteration
    }
    if (temp <= 0)
    {
      printf("The number of students must be greater than 0.\n\n");
      continue;
    }
    else if (errno == ERANGE) 
    {
      printf("The number you entered is too large.\nPlease enter a number less then or equal to %d.\n\n",INT_MAX);
      continue;
    }
    else 
    {
      *n = (int)temp;
      break;
    }
  }
}

void checkValidSelection (int *select) 
{
  while (1)
  {
    printf("Enter your selection: ");
    char input [1000];
    fgets (input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';

    errno = 0; // Reset errno before calling strtol
    char *end;
    long long temp = strtol(input, &end,10);
    
    if (end != input + strlen(input)) 
    {
      printf("%s is not selection's number\n\n", input);
      continue;
    }
    else 
    {
      int i;
      for (i = 0; i < strlen(input); i++)
        if (!isdigit(input[i]) && (!i == 0 && input[i] == '-')) break;; // Check for non-digit characters
      
      if (i < strlen(input)) // If a non-digit character was found, continue with the next iteration
      {
        printf("%s is not a valid integer\n\n", input);
        continue;
      } ;  
    }
    if (errno == ERANGE) 
    {
      printf("The number you entered is too large !\nPlease enter a number from 1 to 7.\n\n");
      continue;
    }
    else if (temp <= 0 || temp >7)
    {
      printf("Please choose number in the menu.\n\n");
      continue;
    }
    else
    {
      *select = (int)temp;
      break;
    }
  }
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

void EnterFullName (int n, char fullName[][100])
{
  printf("Enter student fullName: \n");
  for (int i = 0; i < n; i++) {
    while (1) {
      printf("Student %d: ", i+1);
      fgets(fullName[i], sizeof(fullName[i]), stdin);
      fullName[i][strcspn(fullName[i], "\n")] = 0; // remove the newline character at the end

      if (isValidName(fullName[i]) == 1) {
        break;
      }
    }
  }
}

int chooseFieldStudy(Student* h)
{
  int c;
  int result;
  printf("\n-----List of the majors-----:\n");
  printf("\t1.KTPM\n\t2.MS\n\t3.NNA");
  do 
  {
    printf("\nPleases enter your choice: ");
    result=  scanf("%d",&c);
    // Clear the input buffer
    while (getchar() != '\n');
    if (result == EOF) 
    {
      printf("Invalid input.\nPlease enter a number.\n\n");
      continue;
    }
    switch(c) {
    case 1:
        printf("The subject: KTPM - Ky Thuat Phan Mem");
        strcpy(h->fieldStudy, "KTPM");
        break;
    case 2:
        printf("The subject: MS - Marketing So");
        strcpy(h->fieldStudy, "MS");
        break;
    case 3:
        printf("The subject: NNA - Ngon Ngu Anh");
        strcpy(h->fieldStudy, "NNA");
        break;
    default:
        printf("Invalid input.");
        continue;
    }
  } while(c < 1 || c > 3);
  return c;
}
void enterClassName (Student *s, int n) 
{
  while (1)
  {
    printf("Enter student's class ");
  }
}
// void enterStudentCode(Student* h,int ng)
// {
//   char*studentCode = h->studentCode;

//   while(1)
//   {
//   printf("\nEnter MSSV: ");
//   scanf("%[^\n]s",studentCode);
//   getchar();
//   removeSpaces(studentCode);
//   //viết hoa
//   for(int i = 0; studentCode[i]; i++){
//       studentCode[i] = toupper(studentCode[i]);
//   }
//   if(strlen(studentCode)==8)
//   {
//     if(isalpha(studentCode[0]) && isalpha(studentCode[1]) && studentCode[1]=='E')
//     {
//       int valid = 1;
//       switch(ng)
//       {
//         case 1:
//           if(studentCode[0]!='C') valid = 0;
//           break;
//         case 2 :
//           if(studentCode[0]!='B') valid = 0;
//           break;
//         case 3 :
//           if(studentCode[0]!='L') valid = 0;
//           break;
//         default:
//           valid = 0;
//       }
//       for(int i=2;i<strlen(studentCode);i++)
//       {
//         if(!isdigit(studentCode[i]))
//         {
//           valid = 0;
//           break;
//         }
//       }
//       if(valid) break;
//     }
//   }
//   printf("Invalid input. Please enter again.\n");
//   }
// }

void enterStudentInfo (Student *x, int n)
{
  EnterFullName(n,x->fullName); 
  chooseFieldStudy (x->fieldStudy);
  // enterStudentCode (x->studentCode);
  enterClassName (x->className,n);
}
void displayStudentInfo (Student x, int n)
{
  for (int i = 0; i < n; i++) {
  printf("\t%s\n",x.fullName[i]);
  printf("\t%s\n",x.fieldStudy[i]);
  printf("\t%s\n",x.studentCode[i]);
  }
}

int main ()
{
  int n = 0;
  Student x;
  Student a[n];
  while (1)
  {
    printf("\t*-------------------Management Student------------------*\n");
    printf("\t| 1. Enter list of student\t\t\t\t|\n");
    printf("\t| 2. Display the list of student\t\t\t|\n");
    printf("\t| 3. Add new student information\t\t\t|\n");
    printf("\t| 3. Search student\t\t\t\t\t|\n");
    printf("\t| 4. Delete student\t\t\t\t\t|\n");
    printf("\t| 5. Sort student\t\t\t\t\t|\n");
    printf("\t| 6. Change the list of student\t\t\t\t|\n");
    printf("\t| 7. Exit\t\t\t\t\t\t|\n");
    printf("\t*-------------------------------------------------------*\n");
    printf("\n");

    int select; 
    checkValidSelection(&select);

    switch(select)
    {
      case 1: // Enter list of student, including information.  
        checkValidNumberOfStudent (&n);
          enterStudentInfo (&a, n);
          printf("\n");
        break;
      case 2:
        printf("\tFull Name   |  Study Field   | ClassName    |   Student Code    |   Birth Date\n");
          displayStudentInfo (*a, n);
          printf("\n");
          break;
    }
  }
}
