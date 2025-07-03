#include <stdio.h>

struct process {
    int pid;
    int at, bt, prio;
    int ct, tat, wt;
};

void sort(struct process p[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void display(struct process p[], int n) {
    printf("\nP_ID\tAT\tBT\tPRIO\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].prio,
               p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    printf("Enter no. of process: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process id, arr. time, burst time, priority: ");
        scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].prio);
        p[i].ct = 0;
    }

    sort(p, n);

    int time = 0;
    int completed = 0, min;
    float avg_tat = 0, avg_wt = 0;

    while (completed < n) {
        min = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].ct == 0) {
                if (min == -1 || p[i].prio < p[min].prio) {
                    min = i;
                }
            }
        }

        if (min == -1) {
            time++;
        } else {
            p[min].ct = time + p[min].bt;
            p[min].tat = p[min].ct - p[min].at;
            p[min].wt = p[min].tat - p[min].bt;
            avg_tat += p[min].tat;
            avg_wt += p[min].wt;
            completed++;
            time += p[min].bt;
        }
    }

    avg_tat /= n;
    avg_wt /= n;

    display(p, n);

    printf("Average TAT = %.2f\n", avg_tat);
    printf("Average WT = %.2f\n", avg_wt);

    return 0;
}
