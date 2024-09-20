#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXGSTRINGLEN 22

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

// Function frees all the allocated memory from the program when it's done executing
void freeMem(Campus* campus, int g, int v)
{
    // Accessing memory reverse order of allocation and freeing from last to first
    // looping through garage structures freeing each one
    for(int i = 0; i < g; i++)
    {   
        free(campus->garages[i]->garage_name);
        free(campus->garages[i]->parked_vehicles);
        free(campus->garages[i]);
    }
    // freeing garge pointer array
    free(campus->garages);

    // looping through vehicles freeing each one
    for(int i = 0; i < v; i++)
    {
        free(campus->registered_vehicles[i]->license_plate);
        free(campus->registered_vehicles[i]->owner_name);

        free(campus->registered_vehicles[i]);
    }
    // freeing registered vehicle pointers array
    free(campus->registered_vehicles);

    // freeing campus DMA
    free(campus);
}

void generateGarageUtilizationReport(const Campus* campus) 
{
    float minUtilization = 100.0;
    int minUtilizationIndex = -1;

    for (int i = 0; i < campus->total_garages; i++) {
        Garage* garage = campus->garages[i];
        float utilization = ((float)garage->current_count / garage->total_capacity) * 100.0;
        printf("Garage: %s, Capacity: %d, Occupied: %d, Utilization: %.2f%%\n",
               garage->garage_name, garage->total_capacity, garage->current_count, utilization);

        if (utilization < minUtilization) {
            minUtilization = utilization;
            minUtilizationIndex = i;
        }
    }

    if (minUtilizationIndex != -1) {
        printf("Least Utilized: %s\n", campus->garages[minUtilizationIndex]->garage_name);
    }
}

/* Creates a new  garage with the specified name and capacity
and  initializes  other  variables  and  makes  parked  vehicles 
array  based  on  the  capacity. Function checks if DMA was done
properly, if any failure at any point it will automatically
free the malloced memory due to the garage not being useful
if everything is not malloced properly */
Garage* createGarage(const char* name, int capacity) 
{
    Garage* newGarage = (Garage*)malloc(sizeof(Garage));
    if (newGarage == NULL) {
        printf("Error: Failed to allocate memory for garage %s\n", name);
        return NULL;
    }

    newGarage->garage_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    if (newGarage->garage_name == NULL) {
        printf("Error: Failed to allocate memory for garage name %s\n", name);
        free(newGarage);
        return NULL;
    }
    strcpy(newGarage->garage_name, name);

    newGarage->total_capacity = capacity;
    newGarage->current_count = 0;
    newGarage->parked_vehicles = (RegisteredVehicle**)malloc(sizeof(RegisteredVehicle*) * capacity);
    if (newGarage->parked_vehicles == NULL) {
        printf("Error: Failed to allocate memory for parked vehicles in garage %s\n", name);
        free(newGarage->garage_name);
        free(newGarage);
        return NULL;
    }

    return newGarage;
}

/* Create a new vehicle with the given license plate and owner.  */
RegisteredVehicle* createRegisteredVehicle(const char* license, const char* owner) 
{
    RegisteredVehicle* newVehicle = (RegisteredVehicle*)malloc(sizeof(RegisteredVehicle));
    if (newVehicle == NULL) {
        printf("Error: Failed to allocate memory for vehicle %s\n", license);
        return NULL;
    }

    newVehicle->license_plate = (char*)malloc(sizeof(char) * (strlen(license) + 1));
    if (newVehicle->license_plate == NULL) {
        printf("Error: Failed to allocate memory for license plate %s\n", license);
        free(newVehicle);
        return NULL;
    }
    strcpy(newVehicle->license_plate, license);

    newVehicle->owner_name = (char*)malloc(sizeof(char) * (strlen(owner) + 1));
    if (newVehicle->owner_name == NULL) {
        printf("Error: Failed to allocate memory for owner name %s\n", owner);
        free(newVehicle->license_plate);
        free(newVehicle);
        return NULL;
    }
    strcpy(newVehicle->owner_name, owner);

    return newVehicle;
}

// Function to park a vehicle in a garage
void parkVehicle(Garage* garage, RegisteredVehicle* vehicle) {
    if (garage->current_count < garage->total_capacity) 
    {
        garage->parked_vehicles[garage->current_count] = vehicle;
        garage->current_count++;
        printf("PARKED\n");
    } else {
        printf("FULL\n");
    }
}

/*Registers a new vehicle on campus. Function does this by resizing
the array of registered vehicle pointers, then it will assign
the taken values to the be stored in the new created space, and
of course have it be pointed by the new registeredVehicle 
pointer.*/
void registerVehicle(Campus* campus, const char* license, const char* owner) 
{
    for (int i = 0; i < campus->total_registered_vehicles; i++) {
        if (strcmp(campus->registered_vehicles[i]->license_plate, license) == 0) {
            return;
        }
    }

    RegisteredVehicle* newVehicle = createRegisteredVehicle(license, owner);
    if (newVehicle == NULL) {
        return;
    }

    campus->registered_vehicles = (RegisteredVehicle**)realloc(campus->registered_vehicles, sizeof(RegisteredVehicle*) * (campus->total_registered_vehicles + 1));
    if (campus->registered_vehicles == NULL) {
        printf("Error: Failed to reallocate memory for registered vehicles.\n");
        free(newVehicle);
        return;
    }

    campus->registered_vehicles[campus->total_registered_vehicles] = newVehicle;
    campus->total_registered_vehicles++;
    printf("REGISTERED\n");
}

int removeVehicleFromGarage(Garage* garage, const char* license) 
{
    for (int i = 0; i < garage->current_count; i++) {
        if (strcmp(garage->parked_vehicles[i]->license_plate, license) == 0) {
            for (int j = i; j < garage->current_count - 1; j++) {
                garage->parked_vehicles[j] = garage->parked_vehicles[j + 1];
            }
            garage->current_count--;
            return 1;
        }
    }
    return 0;
}

/*
Function takes in specific garage that needs to be resized
for a new capacity and the new capacity itself. Realloc
for this new capacity by creating a new Registe
*/
int resizeGarage(Garage* garage, int new_capacity) {
    if (new_capacity < garage->current_count) {
        printf("FAIL. TOO SMALL TO ACCOMMODATE EXISTING VEHICLES.\n");
        return 0;
    }

    RegisteredVehicle** newParkingArray = realloc(garage->parked_vehicles, sizeof(RegisteredVehicle*) * new_capacity);
    if (newParkingArray == NULL) {
        printf("Error: Failed to reallocate memory for resizing the garage.\n");
        return 0;
    }

    garage->parked_vehicles = newParkingArray;
    garage->total_capacity = new_capacity;
    printf("SUCCESS\n");
    return 1;
}

/*Function loops through array of garages and as it loops, it looks
inside each garage for the vehicle that has the machine license
plate, if found then it will just return it's pointer. Else
it will return null */
RegisteredVehicle* searchVehicleByLicense(const Campus* campus, const char* license) 
{
    for(int i = 0; i < campus->total_garages; i++)
    {
        for(int j = 0; j < campus->garages[i]->current_count; i++)
        {
            if(strcmp(campus->garages[i]->parked_vehicles[j]->license_plate, license) == 0)
                return campus->garages[i]->parked_vehicles[j];
        }
    }

    
    return NULL;
}

RegisteredVehicle* searchVehicleRegistry(const Campus* campus, const char* license) 
{
    for (int i = 0; i < campus->total_registered_vehicles; i++) 
    {   
        if(strcmp(campus->registered_vehicles[i]->license_plate, license) == 0)
            return campus->registered_vehicles[i];
    }
    return NULL;
}

void displayVehiclesByOwner(const Campus* campus, const char* owner_name) {
    int found = 0; // Flag to track if the owner has any registered vehicles

    // Loop through all registered vehicles
    for (int i = 0; i < campus->total_registered_vehicles; i++) {
        // Check if the owner matches the given owner_name
        if (strcmp(campus->registered_vehicles[i]->owner_name, owner_name) == 0) {
            found = 1; // We found at least one vehicle

            int parked = 0; // Flag to check if the vehicle is parked on campus

            // Check all garages to find where the vehicle is parked
            for (int j = 0; j < campus->total_garages; j++) {
                for (int k = 0; k < campus->garages[j]->current_count; k++) {
                    // If the vehicle is found in the current garage
                    if (campus->garages[j]->parked_vehicles[k] == campus->registered_vehicles[i]) {
                        printf("%s %s\n", campus->registered_vehicles[i]->license_plate, campus->garages[j]->garage_name);
                        parked = 1; // Mark as parked
                        break; // No need to continue once we found where the car is parked
                    }
                }
            }

            // If the vehicle is not parked in any garage, print NOT ON CAMPUS
            if (!parked) {
                printf("%s NOT ON CAMPUS\n", campus->registered_vehicles[i]->license_plate);
            }
        }
    }

    // If no vehicle found for the owner
    if (!found) {
        printf("NO REGISTERED CAR BY THIS OWNER\n");
    }
}

// Returns total number of vehicles parked
int countTotalVehicles(const Campus* campus){
    int totalParkedVehicles = 0;
    for(int i = 0; i < campus->total_garages; i++)
    {
        totalParkedVehicles += campus->garages[i]->current_count;
    }

    return totalParkedVehicles;
}

int removeGarage(Campus* campus, const char* garage_name)
{    
    int garageIndex = -1;

    // Step 1: Find the garage by name
    for (int i = 0; i < campus->total_garages; i++) {
        if (strcmp(campus->garages[i]->garage_name, garage_name) == 0) {
            garageIndex = i;
            break;
        }
    }

    // Step 2: If the garage is not found, return NOT FOUND
    if (garageIndex == -1) {
        printf("%s NOT FOUND\n", garage_name);
        return 0;
    }

    // Step 3: Free the memory associated with the garage
    free(campus->garages[garageIndex]->garage_name);
    free(campus->garages[garageIndex]->parked_vehicles);
    free(campus->garages[garageIndex]);

    // Step 4: Shift the remaining garages to fill the gap
    for (int i = garageIndex; i < campus->total_garages - 1; i++) {
        campus->garages[i] = campus->garages[i + 1];
    }

    // Step 5: Decrement the number of garages
    campus->total_garages--;

    // Step 6: Reallocate the garages array to fit the new size (optional, but good practice)
    if (campus->total_garages > 0) {
        campus->garages = realloc(campus->garages, sizeof(Garage*) * campus->total_garages);
        if (campus->garages == NULL) {
            printf("Memory reallocation error during garage removal.\n");
            return 0;
        }
    } else {
        free(campus->garages);  // Free the garages array if there are no more garages
        campus->garages = NULL;
    }

    // Step 7: Print that the garage was removed
    printf("%s REMOVED\n", garage_name);

    return 1;
}

/* Relocates a vehicle from one garage to another. If the vehicle not found,
it prints the message like point 7 above. If target garage is not found,
it should print "[G] NOT FOUND". If target garage is full, prints "[G] IS FULL". 
Function returns 1 or 0 depending on whether the task was successful or not.*/
int relocateVehicle(Campus* campus, const char* license, const char* target_garage_name) {
    RegisteredVehicle* vehicle = searchVehicleByLicense(campus, license);
    if (vehicle == NULL) {
        printf("%s NOT IN CAMPUS\n", license);
        return 0;
    }

    int target_garage_index = -1;
    for (int i = 0; i < campus->total_garages; i++) {
        if (strcmp(campus->garages[i]->garage_name, target_garage_name) == 0) {
            target_garage_index = i;
            break;
        }
    }

    if (target_garage_index == -1) {
        printf("%s NOT FOUND\n", target_garage_name);
        return 0;
    }

    if (campus->garages[target_garage_index]->current_count == campus->garages[target_garage_index]->total_capacity) {
        printf("%s IS FULL\n", target_garage_name);
        return 0;
    }

    for (int i = 0; i < campus->total_garages; i++) {
        if (removeVehicleFromGarage(campus->garages[i], license)) {
            parkVehicle(campus->garages[target_garage_index], vehicle);
            printf("RELOCATION SUCCESSFUL\n");
            return 1;
        }
    }
    return 0;
}

int findRegisteredVehicleIndex(Campus *campus, const char *licensePlate) {
    for (int i = 0; i < campus->total_registered_vehicles; i++) {
        if (strcmp(campus->registered_vehicles[i]->license_plate, licensePlate) == 0) {
            return i; // Return the index of the registered vehicle
        }
    }
    return -1; // Return -1 if not found
}

int main(void)
{
    freopen("output.txt", "w", stdout);

    // number of garages, vehicles, and commands
    int g, v, c; 

    // malloc campus, load values, test if loaded properly
    Campus* campus = malloc(sizeof(Campus));
    if (campus == NULL) {
        printf("Campus not loaded properly\n");
        return 1; // Exit since nothing else can be done if this isn't allocated properly    
    }

    // Initialize total garages and total registered vehicles to 0
    campus->total_garages = 0;
    campus->total_registered_vehicles = 0;

    // Initialize arrays to NULL to avoid undefined problems
    campus->garages = NULL;
    campus->registered_vehicles = NULL;

    scanf("%d %d %d", &g, &v, &c);


    // malloc campus garages, load values, test if done properly
    campus->garages = malloc(sizeof(Garage*) * g);
    campus->total_garages = g;
    if(campus->garages == NULL)
    {
        printf("Campus Garages not loaded properly\n");
        freeMem(campus, g, v);
        return 1;
    }
    
    // malloc campus registered vehicles, load value, and test if done correctly
    campus->registered_vehicles = malloc(sizeof(RegisteredVehicle*) * v);
    campus->total_registered_vehicles = v;

    if(campus->registered_vehicles == NULL) {
        printf("Campus Registered Vehicles not loaded properly\n");
        freeMem(campus, g, v);
        return 1;
    }
    
    //! GARAGES DMA
    /*
    Code will loop for the amount of garages that were given in the input.
    Then it will allocate memory for each garage, after it will check if
    memory was  allocated properly, if not it will output an error message.
    Then it will create a static array everytime it loops, this one will
    hold the char array for the garage name. Then it will strlen for size
    malloc using this one and check if dma was done properly. Then it will
    strcpy into the dynamic array for name in garage pointer array. At the
    end it allocates memory for the array of pointers for parked vehicles
    and then it also allocates memory for the parked vehicles licenses
    and owner names. Also throws error if anything is wrong
    */
    for(int i = 0; i < g; i++)
    {
        char garageName[MAXGSTRINGLEN]; // temp holder of names
        int capacity;
        scanf("%s %d", garageName, &capacity);

        // Call the createGarage function to allocate and initialize a new garage
        campus->garages[i] = createGarage(garageName, capacity);
        if(campus->garages[i] == NULL)
        {
            printf("Garage %s couldn't be created.\n", garageName);
            // Free any previously allocated garages and memory
            freeMem(campus, i, v); // Free memory up to the index it fails at
            return 1; // Exit due to failure in creating garage
        }
    }

    //! VEHICLES DMA
    /*
    This function loops for the amount of registered vehicels in campus.
    Then it will amlloc for these, after loading the information given
    by the user into dynamically allocated memory. It does this by 
    taking input for the license plate and owner name into temporary
    variables which will be re-initialized everytime the loop runs.
    After these are copied into the corresponding dynamic memory
    location. It send the appropiate error message if any memory
    wasn't allocated correctly.
    */
    for (int i = 0; i < v; i++)
    {
        char licensePlate[MAXGSTRINGLEN], vehicleOwner[MAXGSTRINGLEN]; // temp holders of names and plates
        scanf("%s %s", licensePlate, vehicleOwner);
        
        // Call createRegisteredVehicle function to allocate and initialize a new vehicle
        campus->registered_vehicles[i] = createRegisteredVehicle(licensePlate, vehicleOwner);
        if (campus->registered_vehicles[i] == NULL)
        {
            printf("Error creating vehicle with license plate %s.\n", licensePlate);
            freeMem(campus, g, i); // Free memory up to the point it fails
            return 1; // Exit due to failure in creating a vehicle
        }
    }
    
    // taking input for commands
    // Processing commands
    for(int i = 0; i < c; i++) {
        char command[MAXGSTRINGLEN];
        scanf("%s", command);

        // Logic for PARK command
        if (strcmp(command, "PARK") == 0) {
            char licensePlate[MAXGSTRINGLEN], gName[MAXGSTRINGLEN];
            scanf("%s %s", licensePlate, gName);

            int garageIndex = 0;
            // Iterate through garage names and update index until garage is found
            while (garageIndex < campus->total_garages && strcmp(gName, campus->garages[garageIndex]->garage_name) != 0) {
                garageIndex++;
            }

            if (garageIndex == campus->total_garages) {
                // If the garage isn't found, print the error
                printf("%s NOT FOUND\n", gName);
                continue;
            }

            // Find the vehicle by license plate
            RegisteredVehicle* vehicle = searchVehicleByLicense(campus, licensePlate);
            if (vehicle == NULL) {
                printf("Vehicle not found\n");
                continue;
            }

            // Call parkVehicle function
            parkVehicle(campus->garages[garageIndex], vehicle);
        }

        // UTILIZATION_REPORT command
        else if(strcmp(command, "UTILIZATION_REPORT") == 0) {
            generateGarageUtilizationReport(campus);
        }

        // REGISTER command to add a new vehicle to campus
        else if(strcmp(command, "REGISTER") == 0) {
            char newPlate[MAXGSTRINGLEN], newOwner[MAXGSTRINGLEN];
            scanf("%s %s", newPlate, newOwner);
            registerVehicle(campus, newPlate, newOwner);
        }

        // REMOVE_VEHICLE_GARAGE command
        else if(strcmp(command, "REMOVE_VEHICLE_GARAGE") == 0) {
            char plateVehicleToRemove[MAXGSTRINGLEN];
            scanf("%s", plateVehicleToRemove);

            // Look for vehicle in the campus and remove it from the respective garage
            int garageIndex = -1;
            for (int i = 0; i < campus->total_garages; i++) {
                for (int j = 0; j < campus->garages[i]->current_count; j++) {
                    if (strcmp(campus->garages[i]->parked_vehicles[j]->license_plate, plateVehicleToRemove) == 0) {
                        garageIndex = i;
                        break;
                    }
                }
                if (garageIndex != -1) break;
            }

            if (garageIndex != -1) {
                int removed = removeVehicleFromGarage(campus->garages[garageIndex], plateVehicleToRemove);
                if (removed) {
                    printf("REMOVED FROM %s\n", campus->garages[garageIndex]->garage_name);
                }
            } else {
                printf("NOT FOUND IN CAMPUS\n");
            }
        }

        // RESIZE command
        else if (strcmp(command, "RESIZE") == 0) {
            char gResize[MAXGSTRINGLEN];
            int newCapacity;
            scanf("%s %d", gResize, &newCapacity);

            int garageIndex = -1;
            for (int i = 0; i < campus->total_garages; i++) {
                if (strcmp(gResize, campus->garages[i]->garage_name) == 0) {
                    garageIndex = i;
                    break;
                }
            }

            if (garageIndex != -1) {
                int resized = resizeGarage(campus->garages[garageIndex], newCapacity);
                if (!resized) {
                    printf("FAIL. TOO SMALL TO ACCOMMODATE EXISTING VEHICLES\n");
                }
            } else {
                printf("%s NOT FOUND\n", gResize);
            }
        }

        // RELOCATE command
        else if (strcmp(command, "RELOCATE") == 0) {
            char reloPlate[MAXGSTRINGLEN], reloG[MAXGSTRINGLEN];
            scanf("%s %s", reloPlate, reloG);

            // Perform relocation
            relocateVehicle(campus, reloPlate, reloG);
        }

        // COUNT_TOTAL command
        else if (strcmp(command, "COUNT_TOTAL") == 0) {
            int totalParkedVehicles = countTotalVehicles(campus);
            printf("%d\n", totalParkedVehicles);
        }

        // REMOVE_GARAGE command
        else if (strcmp(command, "REMOVE_GARAGE") == 0) {
            char garageToRemove[MAXGSTRINGLEN];
            scanf("%s", garageToRemove);

            int removed = removeGarage(campus, garageToRemove);
            if (!removed) {
                printf("%s NOT FOUND\n", garageToRemove);
            }
        }

        // displayVehicleByOwner COMMAND
        else if(strcmp(command, "SEARCH_OWNER") == 0)
        {
            char findOwner[MAXGSTRINGLEN];
            scanf("%s", findOwner);
            displayVehiclesByOwner(campus, findOwner);
        }
    }

    freeMem(campus, g, v);

    return 0;
}

