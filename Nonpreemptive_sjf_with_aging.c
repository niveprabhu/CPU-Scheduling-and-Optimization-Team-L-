#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a process
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int waiting_time;
    int turnaround_time;
    int priority; // Lower value means higher priority
    int waiting_since; // Time when the process started waiting
} Process;

// Function to compare processes for sorting based on arrival time
int compareArrival(const void *a, const void *b) {
    return ((Process *)a)->arrival_time - ((Process *)b)->arrival_time;
}

// Function to find the process with the highest priority (shortest remaining burst time, considering aging)
int findHighestPriorityProcess(Process processes[], int n, int current_time, int aging_rate) {
    int highest_priority = INT_MAX;
    int highest_priority_index = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
            // Calculate dynamic priority considering remaining burst time and aging
            int current_priority = processes[i].remaining_burst_time - (current_time - processes[i].waiting_since) / aging_rate;

            if (current_priority < highest_priority) {
                highest_priority = current_priority;
                highest_priority_index = i;
            }
        }
    }
    return highest_priority_index;
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d:\n", processes[i].pid);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_burst_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].priority = 0; // Initial priority (can be used for other criteria if needed)
        processes[i].waiting_since = 0;
    }

    // Sort processes by arrival time
    qsort(processes, n, sizeof(Process), compareArrival);

    int current_time = 0;
    int completed_processes = 0;
    int *finish_time = (int *)malloc(n * sizeof(int));
    int aging_rate = 2; // Adjust this value to control the rate of aging

    printf("\nProcessing Order:\n");

    while (completed_processes < n) {
        int shortest_job_index = findHighestPriorityProcess(processes, n, current_time, aging_rate);

        if (shortest_job_index == -1) {
            current_time++;
        } else {
            // If the process was waiting, update its waiting since time if it's the first time it runs
            if (processes[shortest_job_index].remaining_burst_time == processes[shortest_job_index].burst_time) {
                processes[shortest_job_index].waiting_since = current_time;
            }

            printf("Time %d: Running Process %d (Remaining: %d)\n", current_time, processes[shortest_job_index].pid, processes[shortest_job_index].remaining_burst_time);
            processes[shortest_job_index].remaining_burst_time--;

            if (processes[shortest_job_index].remaining_burst_time == 0) {
                completed_processes++;
                finish_time[shortest_job_index] = current_time + 1;
                processes[shortest_job_index].turnaround_time = finish_time[shortest_job_index] - processes[shortest_job_index].arrival_time;
                processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            }
            current_time++;
        }

        // Increment waiting time for all waiting processes for aging
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0 && i != shortest_job_index) {
                // No explicit increment here; the priority calculation in findHighestPriorityProcess handles aging
            }
        }
    }

    printf("\n--- Process Scheduling Results ---\n");
    printf("PID\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               finish_time[i], processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Calculate and print average waiting time and turnaround time
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);

    free(finish_time);
    return 0;
}
