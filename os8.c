#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, quantum;
    int i;   

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    int *bt = malloc(n * sizeof(int));    
    int *rem = malloc(n * sizeof(int));   
    int *wt = malloc(n * sizeof(int));    
    int *tat = malloc(n * sizeof(int)); 

    if (!bt || !rem || !wt || !tat) {
        printf("Memory allocation failed.\n");
        free(bt); free(rem); free(wt); free(tat);
        return 1;
    }

    printf("Enter burst times of processes:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        wt[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int t = 0; 

    
    while (1) {
        int done = 1;
        for (i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = 0;
                if (rem[i] > quantum) {
                    t += quantum;
                    rem[i] -= quantum;
                } else {
                    t += rem[i];
                    wt[i] = t - bt[i];
                    rem[i] = 0;
                }
            }
        }
        if (done) break;
    }

    
    int total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    
    printf("\nProcesses\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf(" P%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (double)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (double)total_tat / n);

    free(bt); free(rem); free(wt); free(tat);
    return 0;
}