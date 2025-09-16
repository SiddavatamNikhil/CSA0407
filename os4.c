#include <stdio.h>

int main() {
    int n, i, j;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], proc[n], wt[n], tat[n];

    // Input burst times
    for (i = 0; i < n; i++) {
        proc[i] = i + 1; // Process IDs
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    // Sort by burst time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (burst[i] > burst[j]) {
                int temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // Waiting time calculation
    wt[0] = 0; // first process has no wait
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + burst[i - 1];
    }

    // Turnaround time calculation
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + burst[i];
    }

    // Display results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", proc[i], burst[i], wt[i], tat[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
