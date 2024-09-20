/*
Nelson Diaz
Lab 2
Program reads set of student information, processes it, and outputs
requested data.
*/  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define NAMEMAX 51

typedef struct student
{
    char *lname; // DMA to store string
    int assignment;
    int finalExam; // total score = sum of scores from M quizzes + score in the assignment + score in the final exam
    int total;
    int *quizzes; // DMA to store quizzes
}student;

// Using variables as pointers because we want to change the values inside the function, so pass by reference.
student** readCourses(int *C, int *N, int *M)
{
    student** coursesList;
    
    // read info for C, N, and M
    scanf("%d %d %d", C, N, M);
    
    // allocating course list
    coursesList = (student**)malloc(*C * sizeof(student*));
    int cn, qn, sn;

    // looping over based on the number of courses
    for(int cn = 0; cn < *C; cn++)
    {
        coursesList[cn] = (student*)malloc(*N * sizeof(student));
        for(sn = 0; sn < *N; sn++) // loop based on the number of students
        {
            int total = 0;

            // reading info for each student
            char lname[NAMEMAX];
            scanf("%s", lname); // getting the name
            int nameLen = strlen(lname); // finding the length
            coursesList[cn][sn].lname = malloc(nameLen * sizeof(char)); // DMA based on name length
            strcpy(coursesList[cn][sn].lname, lname); // copying name to appropiate location
            scanf("%d", &coursesList[cn][sn].assignment); // getting assignment score
            coursesList[cn][sn].quizzes = malloc(*M * sizeof(int));
            total += coursesList[cn][sn].assignment;
            for(qn = 0; qn < *M; qn++)
            {
                scanf("%d", &coursesList[cn][sn].quizzes[qn]);
                total += coursesList[cn][sn].quizzes[qn];
            }
            scanf("%d", &coursesList[cn][sn].finalExam);
            total += coursesList[cn][sn].finalExam;
            coursesList[cn][sn].total = total;
        }
    }
    
    return coursesList;
}

//release each quiz array for each student, their name, and studentts and the courses.
void release_memory(student** st, int C, int N, int M)
{
    for(int cn = 0; cn < C; cn++)
    {
        for(int sn = 0; sn < N; sn++)
        {
            free(st[cn][sn].lname);
            free(st[cn][sn].quizzes);
        }
        // rellease student in the course
        free(st[cn]);
    }
    free(st);
}

void printHighestTotal(student** coursesList, int C, int N, int M)
{
    int maxTotal = -1; // Value less than 0 so no conflicts are caused
    int highestStudentCourse = 0; // course where highest student is
    int highestStudentNum = 0; // highest student number

    for(int cn = 0; cn < C; cn++)
    {
        for(int sn = 0; sn < N; sn++)
        {
            if(coursesList[cn][sn].total > maxTotal)
            {
                maxTotal = coursesList[cn][sn].total;
                highestStudentCourse = cn;
                highestStudentNum = sn;
            }
        }
    }

    printf("Name: %s\n", coursesList[highestStudentCourse][highestStudentNum].lname);
    printf("Assignment: %d\n", coursesList[highestStudentCourse][highestStudentNum].assignment);
    // printing scores for quizzes
    for(int i = 0; i < M; i++)
    {
        printf("%d ", coursesList[highestStudentCourse][highestStudentNum].quizzes[i]);
    }
    printf("Final exam: %d\n", coursesList[highestStudentCourse][highestStudentNum].finalExam);
    printf("Total: %d\n", coursesList[highestStudentCourse][highestStudentNum].total);
    printf("Course number: %d", highestStudentCourse);
}


int main(void)
{
    atexit(report_mem_leak); //for memory leak detector. 
    
    student **courseList; 
    FILE *inFile, *outFile;
    //passing reference of C, N, and M so that we get to know what we have in the first line 
    int i, j,C, N, M; 
    
    courseList = readCourses(&C, &N, &M); 

    printHighestTotal(courseList, C, N, M); 

    release_memory(courseList, C, N, M);
    
    free(courseList);
    
    return 0;
}
