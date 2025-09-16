#include <stdio.h>

int main() {
    int n;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n], waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Input burst times
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Calculate waiting times
    waitingTime[0] = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    // Calculate turnaround times
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }

    // Print results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitingTime[i], turnaroundTime[i]);
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    printf("\nAverage waiting time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average turnaround time = %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
