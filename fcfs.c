#include <stdio.h>

struct process {
    int pid;
    int at, bt;
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
    printf("\nP_ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    printf("Enter no. of process: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process id, arr. time, burst time: ");
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    sort(p, n);

    int time = 0;
    float avg_tat = 0, avg_wt = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at;
        }

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time += p[i].bt;
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    avg_tat /= n;
    avg_wt /= n;

    display(p, n);
    printf("Average TAT = %.2f\n", avg_tat);
    printf("Average WT = %.2f\n", avg_wt);

    return 0;
}
