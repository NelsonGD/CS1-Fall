// Example of DMA from Foundation Exam

/*
Write a function `createEmployees()` that takes the list of employees' names, 
list of their salaries, and length of the list (`empCount`) as the parameters, 
**and returns a pointer to a dynamically allocated array of Employee storing the 
relevant information for empCount employees. The function dynamically allocates 
memory for `empCount` number of employees and assigns the name and salaries for each 
of them from the input parameters. During this process, the names are stored in the 
dynamically allocated memory of `StringType`, and also make sure you assign the length 
of the name appropriately. Your code should use the exact amount of memory needed to 
store the corresponding names. You may assume no name is longer than 49 characters.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLENGTH 49

typedef struct StringType{
    char *string;
    int length;
} StringType;

typedef struct Employee{
    StringType *ename;
    double salary;
} Employee;

Employee* createEmployees(char names[][50], double *salaries, int empCount)
{
    // DMA for each employee
    Employee* employees = malloc(sizeof(Employee) * empCount);
    for(int i = 0; i < empCount; i++)
    {
        // DMA for each employee salary and ename
        employees[i].salary = salaries[i];
        employees[i].ename = malloc(sizeof(StringType));

        // find length of name
        int len = strlen(names[i]+1);
        employees[i].ename->string = malloc(sizeof(char) * len);
        // You are saying names[i] and not names[][i] because you want the row, each column of that ROW has each letter from the name
        strcpy(employees[i].ename->string, names[i]);
        employees[i].ename->length = len - 1; // remember to substract 1 because you added 1 before because you wanted the array size that needs the terminator "\0" but in this case you want the string length which doesn't take in count the terminator "\0"
    } 

    return employees;
}

void freeMem(Employee* e, int empCount)
{
    for(int i = 0; i < empCount; i++)
    {
        free(e[i].ename->string);
        free(e[i].ename);
    }
    free(e);
}

int main()
{
    // array of employees' name
    char nameList[][50] = {"Adam", "Josh","Kyle", "Ali", "Mohammed"};
    // array of salaries,, where 15.80 is the salary of Adam, 13.50 is the salary of Josh, etc.
    double salaries[5] = {15.80, 13.5, 20.9, 12.99, 10.5};
    Employee *employees = createEmployees(nameList, salaries, 5);
    // Other code here...
 
    return 0;
}