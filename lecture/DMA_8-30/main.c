#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NationalPark
{
    char *pname; // park name
    int lat; // lattitude
    int lon; // longitude
}NationalPark;

// Creates array or box to store information for one national park
NationalPark* createOneNP(char name[])
{
    // Gives you: starting address of the box that stores the national park, that's why it's a national park pointer
    NationalPark *m = (NationalPark*)malloc(sizeof(NationalPark));
    
    // checking if memory was allocated properly
    if(m)
    {
        m -> lat = rand()%100;
        m -> lon = rand()%100;


        // Finding the length of the name and then allocating the necessary memory to store it.
        int len = strlen(name) + 1;
        m->pname = (char*)malloc(len * sizeof(char));
        
        // You made the box to store the name, now you need to store it
        m -> pname = (char*)malloc(len*sizeof(char));
        strcpy(m->pname, name);

        return m;
    }else
        return NULL;
}

void printOneNP(NationalPark *p)
{
    printf("%s %d %d", p->pname, p->lat, p->lon);
}

void release_mem(NationalPark* p)
{
    free(p -> pname);
    free(p);
}

/* Function recieves the size, n, and the names of the national park names
? You are sending a 2D character array becuase of the array of names which is just an array of arrays. 
? You don't know how many names so number of rows is empty, but the char limit is 50. */
NationalPark* createArrayOfNP(int n, char names[0][50])
{
    NationalPark* m = (NationalPark*)malloc(n * sizeof(NationalPark)); // multiplying by n gives you malloc for the number of structs
    for(int i = 0; i < n; i++){
        // We are using dot (.) because m[i] is not a national park POINTER it's the structure itself
        m[i].lat = rand()%100;
        m[i].lon = rand()%100;

        // we don't have space to store name, you need length.
        int len = strlen(names[i]) + 1;
        m[i].pname = malloc(sizeof(char) * len); //! Address of a national park
        strcpy(m[i].pname, names[i]);
    }

    return m;
}

void printArrayOfNP(int n, NationalPark* p)
{
    for(int i = 0; i < n; i++){
        printf("%s %d %d\n", p[i].pname, p[i].lat, p[i].lon);
    }
}

void release_mem_Arrys(int size, NationalPark* p)
{
    for(int i = 0; i < size; i++)
    {
        free(p[i].pname);
    }
    free(p);
}

NationalPark* createArrayOfNPPtr(int n, char name[][50])
{
    /*
    * We are using a double pointer because in this case we are storing the address of a national park POINTER.
    ! In the other function we stored the address of a national park that is NOT a pointer
    * We are creating a box to store POINTERS that will point to the box that has info about the national parks
    */
    NationalPark** b = (NationalPark**)malloc(n * sizeof(NationalPark*));

    for(int i = 0; i < n; i++)
    {
        //! Instead of doing all this work you can just call the function to create one multiple time 
        // m[i] = createArrayOfNP(*name);

        b[i] = malloc(sizeof(NationalPark));
        int len = strlen(name[i]) + 1;
        b[i] -> pname = malloc(len * sizeof(char));

        strcpy(b[i]->pname, name[i]);
        b[i]->lat = 50;
        b[i]->lon = 60;
    }

    return *b;
}

int main(void){

    char names[][10] = {"name1", "name2", "name3", "name4", "name5"};

    char pname[50] = "Bryce Canyon National Park";
    NationalPark* np = createOneNP(pname);

    createArrayOfNPPtr(5, names);
    printArrayOfNP(5, np);

    printOneNP(np);
}