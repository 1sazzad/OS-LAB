#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to sort processes by burst time in descending order
void sortByBurstTime(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].burst_time < proc[j].burst_time) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void calculateTimes(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

// Function to print process details
void printProcesses(struct Process proc[], int n) {
    printf("\nProcess ID  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%9d  %10d  %12d  %14d\n", proc[i].id, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burst_time);
    }

    // Sort processes by burst time (LJF Scheduling)
    sortByBurstTime(proc, n);

    // Calculate waiting and turnaround times
    calculateTimes(proc, n);

    // Print process details
    printProcesses(proc, n);

    return 0;
}
