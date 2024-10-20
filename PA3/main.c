/* COP 3502C Assignment 3
This program is written by: Your Full Name */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXGARAGES 8
#define MAXGARAGENAME 21

typedef struct Garage {
    int x, y;
    char* name;
} Garage;

Garage* arrGarages[2 * MAXGARAGES]; // Global variable for array of garages
int bestPairs[2 * MAXGARAGES];      // Global variable for best pairing indices

double distanceCache[2 * MAXGARAGES][2 * MAXGARAGES]; // Cache distances

void precomputeDistances(int totalGarages) {
    for (int i = 0; i < totalGarages; i++) {
        for (int j = i + 1; j < totalGarages; j++) {
            double dx = arrGarages[i]->x - arrGarages[j]->x;
            double dy = arrGarages[i]->y - arrGarages[j]->y;
            distanceCache[i][j] = sqrt(dx * dx + dy * dy);
            distanceCache[j][i] = distanceCache[i][j];
        }
    }
}

void findMinDistance(int usedMask, double currentDistance, int depth, int n, double* minDistance, int currentPairs[]) {
    if (currentDistance >= *minDistance) {
        return; // Prune branches that exceed current minDistance
    }

    if (depth == n) {
        // All pairs have been made
        *minDistance = currentDistance;
        memcpy(bestPairs, currentPairs, sizeof(int) * 2 * n);
        return;
    }

    // Find the first unused garage
    int first;
    for (first = 0; first < 2 * n; first++) {
        if (!(usedMask & (1 << first))) {
            break;
        }
    }

    // Try pairing the first unused garage with every other unused garage
    for (int second = first + 1; second < 2 * n; second++) {
        if (!(usedMask & (1 << second))) {
            // Mark garages as used
            int newUsedMask = usedMask | (1 << first) | (1 << second);

            // Add the distance between these two garages
            double pairDistance = distanceCache[first][second];

            // Store the current pair
            currentPairs[2 * depth] = first;
            currentPairs[2 * depth + 1] = second;

            // Recurse to the next depth
            findMinDistance(newUsedMask, currentDistance + pairDistance, depth + 1, n, minDistance, currentPairs);
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n); // Number of garage pairs

    int totalGarages = 2 * n;

    // Read garage data
    for (int i = 0; i < totalGarages; i++) {
        int givenX, givenY;
        char garageName[MAXGARAGENAME];

        scanf("%d %d %s", &givenX, &givenY, garageName);
        arrGarages[i] = malloc(sizeof(Garage));
        arrGarages[i]->x = givenX;
        arrGarages[i]->y = givenY;
        arrGarages[i]->name = malloc(strlen(garageName) + 1);
        strcpy(arrGarages[i]->name, garageName);
    }

    // Precompute distances
    precomputeDistances(totalGarages);

    double minDistance = INFINITY;
    int currentPairs[2 * MAXGARAGES];

    findMinDistance(0, 0.0, 0, n, &minDistance, currentPairs);

    // Output results
    printf("%.3f\n", minDistance);
    for (int i = 0; i < n; i++) {
        int idx1 = bestPairs[2 * i];
        int idx2 = bestPairs[2 * i + 1];

        // Ensure the "from garage" appeared first in the input
        if (idx1 > idx2) {
            int temp = idx1;
            idx1 = idx2;
            idx2 = temp;
        }

        printf("(%s, %s, %.3f)\n", arrGarages[idx1]->name, arrGarages[idx2]->name, distanceCache[idx1][idx2]);
    }

    // Free memory
    for (int i = 0; i < totalGarages; i++) {
        free(arrGarages[i]->name);
        free(arrGarages[i]);
    }

    return 0;
}