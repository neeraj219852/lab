#include <stdio.h>

struct process {
    int pid;
    int at, bt;
    int ct, tat, wt;
    int remaining_bt;
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

int queue[100];
int fr = -1, rear = -1;

void enqueue(int data) {
    if (fr == -1) {
        fr = 0;
    }
    queue[++rear] = data;
}

int dequeue() {
    if (fr == rear) {
        int temp = queue[fr];
        fr = -1;
        rear = -1;
        return temp;
    }
    return queue[fr++];
}

int is_in_queue(int data) {
    for (int i = fr; i <= rear; i++) {
        if (queue[i] == data) {
            return 1;
        }
    }
    return 0;
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
        p[i].remaining_bt = p[i].bt;
    }

    sort(p, n);

    int time = 0, quanta, completed = 0;
    printf("Enter time quanta: ");
    scanf("%d", &quanta);

    while (completed < n) {
        if (fr == -1) {
            int found = 0;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].remaining_bt > 0) {
                    enqueue(i);
                    found = 1;
                }
            }
            if (!found) {
                for (int i = 0; i < n; i++) {
                    if (p[i].remaining_bt > 0) {
                        time = p[i].at;
                        enqueue(i);
                        break;
                    }
                }
            }
        } else {
            int current_process = dequeue();

            if (p[current_process].remaining_bt <= quanta) {
                time += p[current_process].remaining_bt;
                p[current_process].remaining_bt = 0;
                p[current_process].ct = time;
                p[current_process].tat = p[current_process].ct - p[current_process].at;
                p[current_process].wt = p[current_process].tat - p[current_process].bt;
                completed++;
            } else {
                p[current_process].remaining_bt -= quanta;
                time += quanta;
            }

            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].remaining_bt > 0 && !is_in_queue(i) && i != current_process) {
                    enqueue(i);
                }
            }

            if (p[current_process].remaining_bt > 0) {
                enqueue(current_process);
            }
        }
    }

    display(p, n);

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("Average TAT: %.2f\n", avg_tat);
    printf("Average WT: %.2f\n", avg_wt);

    return 0;
}
