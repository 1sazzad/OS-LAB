#include <stdio.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

// Function to check if the system is in a safe state
int isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    int work[R];
    int finish[P];
    int safeSeq[P];
    int count = 0;
    
    // Calculate Need matrix (Maximum - Allocation)
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Initialize work and finish arrays
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    for (int i = 0; i < P; i++) {
        finish[i] = 0; // 0 means not finished, 1 means finished
    }

    // Find a safe sequence
    while (count < P) {
        int found = 0;
        
        for (int p = 0; p < P; p++) {
            // Check if the process is not finished and can proceed
            if (finish[p] == 0) {
                int canProceed = 1;

                // Check if need <= work
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canProceed = 0;
                        break;
                    }
                }

                if (canProceed) {
                    // Add allocated resources of the process to work
                    for (int j = 0; j < R; j++) {
                        work[j] += allot[p][j];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                    break;
                }
            }
        }

        if (found == 0) {
            printf("System is not in a safe state.\n");
            return 0; // Not in a safe state
        }
    }

    // System is in a safe state, print the safe sequence
    printf("System is in a safe state.\nSafe Sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 1; // Safe state
}

int main() {
    int processes[] = {0, 1, 2, 3, 4}; // Process IDs
    
    int avail[] = {3, 3, 2}; // Available instances of resources

    // Maximum resources required by each process
    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources allocated to each process
    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Call the Banker's Algorithm
    isSafe(processes, avail, max, allot);

    return 0;
}
