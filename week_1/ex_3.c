/*
That asks number of students and creates an array of that many integers.

Program then initializes the array elements to -1.

Then the program asks user to enter student number in range 1 – nr of students or zero to stop. If
valid non zero number is given the program asks user to enter grade in the range 0-5 or -1 to not
enter a grade for the student.

When user stops by entering 0 then program prints student numbers followed by grade or N/A if
grade is -1.
*/

#include <stdio.h>

int main(void)
{
    int numberOfStudents = 0;

    printf("How many students: ");
    scanf("%d", &numberOfStudents);

    int studentGrades[numberOfStudents];

    for (int i = 0; i < numberOfStudents; i++)
    {
        studentGrades[i] = -1;
    }

    int selectedStudentNumber = 0;

    do
    {
        printf("\nEnter student number (1 - %d) or 0 to stop: ", numberOfStudents);
        if (scanf("%d", &selectedStudentNumber) == 1)
        {
            if (selectedStudentNumber > 0 && selectedStudentNumber <= numberOfStudents)
            {
                int selectedStudentGrade = -1;
                do
                {
                    printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", selectedStudentNumber);
                    if (scanf("%d", &selectedStudentGrade) == 1)
                    {
                        if (selectedStudentGrade >= 0 && selectedStudentGrade <= 5)
                        {
                            studentGrades[selectedStudentNumber - 1] = selectedStudentGrade;
                            selectedStudentGrade = -1;
                        }
                        else if (selectedStudentGrade != -1)
                        {
                            printf("Invalid grade!\n");
                        }
                    }
                    else
                    {
                        while (getchar() != '\n')
                            ;
                        printf("Invalid grade!\n");
                    }
                } while (selectedStudentGrade != -1);
            }
            else if (selectedStudentNumber != 0)
            {
                printf("Invalid student number!\n");
            }
        }
        else
        {
            while (getchar() != '\n')
                ;
            printf("Invalid student number!\n");
        }

    } while (selectedStudentNumber != 0);

    printf("\nStudent\tGrade\n");
    for (int i = 0; i < numberOfStudents; i++)
    {
        studentGrades[i] == -1 ? printf("%d\tN/A\n", i + 1) : printf("%d\t%d\n", i + 1, studentGrades[i]);
    }

    return 0;
}