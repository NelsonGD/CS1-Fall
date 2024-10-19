/*
Write a function 
videogame_t* getDiscountGames(videogame_t* inventory, int n, double discount, int* ptrNumGames) 
that takes an array of videogame_t structures, its length (n), and a discount percentage (discount). 
The function should return a newly dynamically allocated array storing only the games where the 
price is above $20 after applying the discount. Update the variable pointed to by ptrNumGames with 
the size of the array returned. Make sure to perform a deep copy of each game in the new array, 
including dynamically allocating memory for the game name.
*/

#include <stdio.h>
#include <stdlib.h>

// function prototypes
typedef struct {   
    char * name;
    int year;
    double price;
} videogame_t;

videogame_t* getClassicGames(videogame_t * inventory, int n, int* ptrNumGames){
    videogame_t* res = malloc(n*sizeof(videogame_t));
    int nG = 0;

    for(int i = 0; i < n; i++){
        if(inventory[i].year >= 1980 && inventory[i].year < 1990)
        {
            res[nG].name = malloc(sizeof(char) * strlen(inventory[i].name)+1);
            strcpy(res[nG].name, inventory[i].name);
            res[nG].price = inventory[i].price;
            res[nG].year = inventory[i].year;
            nG++;
        }
    }

    res = realloc(res, nG * sizeof(videogame_t));
    *ptrNumGames = nG;
    return res;
}

int main(void){



    return 0;
}

