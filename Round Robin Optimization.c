#include <stdio.h>
#define MAX 100

int main() {
    int n, tq;
    int at[MAX], bt[MAX], rt[MAX], ct[MAX];
    int wt[MAX], tat[MAX];
    int time = 0, remain = 0;
    int completed = 0;

    int queue[MAX], front = 0, rear = 0, visited[MAX] = {0};

    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    printf("\nMake sure to include a space inbetween your Arrival and Burst Time\n");
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // Push first arrived processes into queue
    for (int i = 0; i < n; i++) {
        if (at[i] == 0 && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nProcess | Arrival | Burst | Completion | Turnaround | Waiting\n");

    while (completed < n) {
        if (front == rear) {
            // If queue is empty, jump to next arrival
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    time = at[i];
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }

        int idx = queue[front++];
        
        int exec_time = (rt[idx] < tq) ? rt[idx] : tq;
        time += exec_time;
        rt[idx] -= exec_time;

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (!visited[i] && at[i] <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (rt[idx] > 0) {
            queue[rear++] = idx; // re-queue if not done
        } else {
            completed++;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            printf("P[%d]    | %7d | %5d | %10d | %10d | %7d\n", 
                   idx + 1, at[idx], bt[idx], ct[idx], tat[idx], wt[idx]);
        }
    }

    // Calculate Averages
    float avg_wt = 0, avg_tat = 0, avg_ct = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_ct += ct[i];
    }

    printf("\nAverage Waiting Time    = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Completion Time = %.2f\n", avg_ct / n);

    return 0;
}
