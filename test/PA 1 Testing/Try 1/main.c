#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXGARAGELEN 22
#define MAXNAMELEN 22
#define MAXPLATELEN 22

typedef struct RegisteredVehicle // for one registered vehicle
{
    char *license_plate; // to be used for string license plate# of the vehicle
    char *owner_name;    // to be used for storing owner name
} RegisteredVehicle;

typedef struct Garage // for one garage
{                                        
    char *garage_name;                   // to be used for garage name
    int total_capacity;                  // total capacity of the garage
    int current_count;                   // number of vehicles in the garage in a particular time
    RegisteredVehicle **parked_vehicles; // list of parked vehicles in a particular time
} Garage;

typedef struct Campus
{
    Garage **garages;                        // list of garages in campus
    int total_garages;                       // number of garages in the campus
    RegisteredVehicle **registered_vehicles; // list of registered vehicles
    int total_registered_vehicles;           // total number of registered vehicles
} Campus;

int main(void)
{
    // number of garages, vehicles, and commands
    int g, v, c; 

    // malloc campus, load values, test if loaded properly
    Campus* campus = malloc(sizeof(campus)); // allocated campus
    scanf("%d %d %d", &g, &v, &c);
    if(campus == NULL)
        printf("Campus not loaded properly");
    
    // malloc campus garages, load values, test if done properly
    campus->garages = malloc(sizeof(Garage*) * g); // allocated POINTER for each garage storage box
    campus->total_garages = g;
    if(campus->garages == NULL)
        printf("Campus Garages not loaded properly");

    // Looping and taking in the names of each garage and their capacity
    //! GARAGES DMA
    for(int i = 0; i < g; i++)
    {
        campus->garages[i] = malloc(sizeof(Garage)); // allocated each garage storage box 
        char garageName[MAXNAMELEN];
        scanf("%s %d", garageName, &campus->garages[i]->total_capacity);
        campus->garages[i]->garage_name = malloc(sizeof(char) * strlen(&garageName[i]) + 1);
        strcpy(campus->garages[i]->garage_name, garageName);
        printf("%s %d", campus->garages[i]->garage_name, campus->garages[i]->total_capacity);
    }

    return 0;
}
