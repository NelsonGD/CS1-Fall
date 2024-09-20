/* THIS SERVES AS A CODE TEMPLATE FOR CS1 LAB1 ASSIGNMENT */

/*This program demonstrates an example structure, function, and pointer to
strcture. It reads data for N number of student's id numbers and their scores
for 3 courses. The program reads those scores and output the same information
and average score. Then it finds the maximum average and the student who
obtained the max average
Sample data:
5
861022 65 72 56
851102 78 45 80
860501 55 75 90
841205 75 80 95
850630 40 50 48
*/
#include <stdio.h>
#include "main.h"
#define MAXSIZE 500

// struct Student {
// 	int student_ID;
// 	int g1, g2, g3;
// 	float average;
// };

struct Student getMaxAverageStudent(struct Student *s, int n) {
  
  //declare int variables for i and for max index
  //declare a float variable to store the current max average

  
  //loop through the number of students
	

      //if a better average is found, update max and max index         accordingly



  //return student whose avergae is the best
	
}

void readData(struct Student *students, int *c) {
  
	// read first line using scanf and assuming n<=MAXSIZE

  //loop through number of students, 
	for (int i = 0; i < *c; i++) {
    //read the student's id
    
    //read the student's 3 grades
		
    //compute the student's average, prevent integer division

    //print the student's values
		
}

int main() {
  
  //declare an array of students of MAXSIZE
	

	// call readData, passing references
	// after coming back from the function, the array should be filled up and n will also get value.

  //call getMaxAverageStudent and store result

  //print the best student's result and ID

	return 0;
}