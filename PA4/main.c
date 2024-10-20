#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Useless since program will
always give correct inputs. */
#define maxX 1000 // max X coordinate
#define maxY 1000 // max Y coordinate
#define maxN 1000000 // max number of garages
#define maxS 200000 // max number of points to search for
#define maxT 30 // max threshold for picking Merge Sort or Insertion Sort

typedef struct garage{
    int x;
    int y;
    double distanceFromOrigin;
} Garage;

void insertionSort(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int hand = arr[i];
        for(int j = i-1; j >= 0; j--)
        {
            if(arr[j] > hand) // replace with if(compareTo(hand), arr[i]), using this for recombining merge sort array
            {
                arr[j+1] = arr[j]; // not losing number because you have it in your hand
            }else{
                break; // By this point you already found the place.
            }

            // insert value
            arr[j+1] = arr[j];
        }
    }    
}

// Dealing directly with reference of array
void merge(int a[], int l, int mid, int r)
{
    int i, j, k; // trackers

    // size of left array
    int n1 = mid-l+1;

    // size of right array
    int n2= r-mid;

    int *L = malloc(sizeof(int) * n1);
    int *R = malloc(sizeof(int) * n2);

    for(i=0; i < n1; i++)
    {
        L[i] = a[l+i];
    }

    for(j=0; j<n2; i++)
    {
        R[j] = a[mid+1+j]; 
    }

    i = 0; // left array
    j = 0; // right array
    k = l;

    // keep doing until outside of arr
    while(i < n1 && j < n2)
    {
        // compare data for trackers
        if(L[i] < R[j])
        {
            a[k] = L[i];
            i++;
            k++;
        }else{
            a[k] = R[j];
            j++;
            k++;
        }
    }

    while(i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }
    
    while(i < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    free(R);
    free(L);
}

// Merge Sort function
void mergeSort(int a[], int l, int r)
{
    if(r>1)
    {
        int mid = (l+r)/2;

        mergeSort(a, l, r);
        mergeSort(a, mid+1, r);

        merge(a, l, mid, r);
    }
}

int compareTo(int* ptrPt1, int* ptrPt2)
{

}

/* Function will allocate memory for the
array of garages to store their coordinates. 
Then it will take in the values for the X 
and Y coordinates of each garage. Returns
pointer to array of garage coordinates. */
Garage* createGarages(int numOfGarages)
{
    Garage* garageCoordinates = malloc(sizeof(Garage) * numOfGarages);

    for(int i = 0; i < numOfGarages; i++)
    {
        scanf("%d %d", &garageCoordinates[i].x, &garageCoordinates[i].y);
        calculateDistance();
    }

    return garageCoordinates;
}

/* Function find the distance from the given
garage to the origin. It then returns it. */
double calculateDistance()
{

}

/* Function prints coordinates of given garage. */
void printGarageCoordinates(Garage garage)
{
    printf("%d %d\n", garage.x, garage.y);
}

/* Function prints all garage coordinates */
void readData(Garage* allGarages, int numOfGarages)
{
    for(int i = 0; i < numOfGarages; i++)
    {
        printGarageCoordinates(allGarages[i]);
    }
}



int main(void){
    
    // Variable Declaration
    int userLocationX, 
        userLocationY, 
        numberOfGarages, 
        pointsToSearach, 
        threshold;

    // Take input
    scanf("%d %d %d %d %d",
        &userLocationX, 
        &userLocationY,
        &numberOfGarages,
        &pointsToSearach,
        &threshold );
    
    // Call function to create garages.
    Garage* garages = createGarages(numberOfGarages);

    // Sort Function

    // print all garage coordinates
    readData(garages, numberOfGarages);


    return 0;
}

// Comparison function: Calculate the distances between each garage and the origin.