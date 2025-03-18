#include <stdio.h>
#include <stdlib.h>

#define N 4  // Number of processes

int processno[N], AT[N], BT[N], BTbackup[N], WT[N], TAT[N], CT[N], completed[N];
int totaltime = 0;

// Sorting processes by Arrival Time
void sortByArrival() {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (AT[j] > AT[j + 1]) {
                // Swapping all corresponding values
                int temp;
                temp = AT[j]; AT[j] = AT[j + 1]; AT[j + 1] = temp;
                temp = BT[j]; BT[j] = BT[j + 1]; BT[j + 1] = temp;
                temp = BTbackup[j]; BTbackup[j] = BTbackup[j + 1]; BTbackup[j + 1] = temp;
                temp = processno[j]; processno[j] = processno[j + 1]; processno[j + 1] = temp;
            }
        }
    }
}

// Finding the process with the largest remaining Burst Time among available processes
int findLargest(int time) {
    int maxIndex = -1;
    for (int i = 0; i < N; i++) {
        if (AT[i] <= time && BT[i] > 0) {
            if (maxIndex == -1 || BT[i] > BT[maxIndex]) {
                maxIndex = i;
            }
        }
    }
    return maxIndex;
}

void findCT() {
    int completed_processes = 0;
    while (completed_processes < N) {
        int index = findLargest(totaltime);
        if (index == -1) {
            totaltime++;
            continue;
        }
        
        printf("Process executing at time %d is: P%d\n", totaltime, processno[index]);
        BT[index]--;
        totaltime++;

        if (BT[index] == 0) {
            CT[index] = totaltime;
            completed_processes++;
            printf("Process P%d is completed at %d\n", processno[index], totaltime);
        }
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        processno[i] = i + 1;
        AT[i] = i + 1;
        BT[i] = 2 * (i + 1);
        BTbackup[i] = BT[i];
        completed[i] = 0;
    }

    printf("PNo\tAT\tBT\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t%d\n", processno[i], AT[i], BT[i]);
    }
    printf("\n");

    sortByArrival();
    totaltime = AT[0];
    findCT();

    int totalWT = 0, totalTAT = 0;
    for (int i = 0; i < N; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BTbackup[i];
        totalWT += WT[i];
        totalTAT += TAT[i];
    }

    printf("After execution of all processes ... \n");
    printf("PNo\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processno[i], AT[i], BTbackup[i], CT[i], TAT[i], WT[i]);
    }
    printf("\n");
    printf("Total TAT = %d\n", totalTAT);
    printf("Average TAT = %.2f\n", totalTAT / (float)N);
    printf("Total WT = %d\n", totalWT);
    printf("Average WT = %.2f\n", totalWT / (float)N);
    
    return 0;
}
