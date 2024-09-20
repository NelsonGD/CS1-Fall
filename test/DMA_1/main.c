#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    int student_id;
    float* quizzes;
};

struct Student* AllocateStudents(int n, int q)
{
    // allocating memory for array of student structs
    struct Student* student = malloc(sizeof(struct Student) * n);

    // Filling data for each student struct
    for(int i = 0; i < n; i++)
    {
        student[i].quizzes = malloc(sizeof(float) * q);
        printf("ID for student %d: ", i+1);
        scanf("%d", &student[i].student_id);
        for(int j = 0; j < q; j++)
        {
            printf("Score for quiz #%d of student %d: ", j+1, i+1);
            scanf("%f", &student[i].quizzes[j]);
        }
    }

    return student;
}

void printStudentInfo(struct Student* students, int numStudents, int numQuizzes)
{
    for(int i = 0; i < numStudents; i++)
    {
        printf("Quiz Scores for Student #%d (ID: %d):\n", i+1, students[i].student_id);
        for(int j = 0; j < numQuizzes; j++)
        {
            printf("Quiz #%d: %f\n", j+1, students[i].quizzes[j]);
        }
    }
}

void free_up_memory(struct Student* students, int n)
{
    for(int i = 0; i < n; i++)
    {
        free(students[i].quizzes);
    }
    free(students);
}

int main(void){
    int n, q;

    printf("How many students? ");
    scanf("%d", &n);
    printf("How many quizzes? ");
    scanf("%d", &q);

    struct Student* studentArr = AllocateStudents(n, q);

    printStudentInfo(studentArr, n, q);

    return 0;
}