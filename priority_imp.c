#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    int burst[n], priority[n], index[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time and Priority Value for Process %d: ", i + 1);
        scanf("%d %d", &burst[i], &priority[i]);
        index[i] = i + 1;
    }

    // Sort by priority (lower value = higher priority)
    for (int i = 0; i < n; i++) {
        int min_priority = priority[i], m = i;
        for (int j = i + 1; j < n; j++) {
            if (priority[j] < min_priority) {
                min_priority = priority[j];
                m = j;
            }
        }
        swap(&priority[i], &priority[m]);
        swap(&burst[i], &burst[m]);
        swap(&index[i], &index[m]);
    }

    int start_time = 0;
    int waiting_time[n], turnaround_time[n], completion_time[n];

    printf("\nOrder of process execution:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d is executed from %d to %d\n", index[i], start_time, start_time + burst[i]);
        waiting_time[i] = start_time;
        turnaround_time[i] = waiting_time[i] + burst[i];
        completion_time[i] = start_time + burst[i];
        start_time += burst[i];
    }

    printf("\nProcess ID | Burst Time | Priority | Waiting Time | Turnaround Time | Completion Time\n");
    float total_wt = 0, total_tat = 0, total_ct = 0;
    for (int i = 0; i < n; i++) {
        printf("P%-9d %-11d %-9d %-14d %-17d %-16d\n",
               index[i], burst[i], priority[i], waiting_time[i], turnaround_time[i], completion_time[i]);
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
        total_ct += completion_time[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Completion Time: %.2f\n", total_ct / n);

    return 0;
}
