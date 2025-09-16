#include <stdio.h>
#include <limits.h>

struct Process {
    int id;            
    int at;            
    int bt;            
    int pr;            
    int rt;         
    int ct;          
    int tat;           
    int wt;           
    int finished;      
};

int main() {
    int n, i, time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].id = i + 1;
        p[i].rt = p[i].bt;
        p[i].finished = 0;
    }

    printf("\n--- Gantt Chart ---\n");

    while (completed != n) {
        int idx = -1;
        int highestPr = INT_MAX;

        
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].finished == 0 && p[i].rt > 0) {
                if (p[i].pr < highestPr) {
                    highestPr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            printf("| P%d ", p[idx].id);
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                p[idx].finished = 1;
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
            }
        } else {
            printf("| idle ");
            time++;
        }
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT\tPr\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}
