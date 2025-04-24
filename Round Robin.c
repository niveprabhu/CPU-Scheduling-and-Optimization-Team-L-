// Round Robin Code

/* Description: 
    • Asks for Arrival and Burst Time
    • Gives Waiting Time and Turnaround Time
    • Calculates Completion Time
*/

#include <stdio.h>

#define MAX 10  // max processes

int main() {
    int n, tq;                  // processes, time quantum
    int at[MAX], bt[MAX], rt[MAX]; // arrival, burst, and remaining time
    int t = 0;                  // current time
    int remain;                 // remaining processes
    int wt = 0, tat = 0;        // total waiting time and turnaround time
    int flag = 0;               // flag to check if a process just finished
    int cnt = 0;                // index for current process
    
    // input
    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    remain = n;
    
    printf("\nBelow you wil enter the times, please include a space inbetween.\n");
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // initialize remaining time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // output header
    printf("\nProcess\t| Turnaround Time | Waiting Time\n");

    // main Round Robin loop
    while (remain != 0) {
        if (rt[cnt] > 0 && at[cnt] <= t) {
            if (rt[cnt] <= tq) {
                // Ppocess finishes within this quantum
                t += rt[cnt];
                rt[cnt] = 0;
                flag = 1;
            } else {
                // process gets part of the CPU time
                rt[cnt] -= tq;
                t += tq;
            }

            if (rt[cnt] == 0 && flag == 1) {
                remain--;
                int turnaround = t - at[cnt];
                int waiting = turnaround - bt[cnt];
                printf("P[%d]\t| %9d       | %9d\n", cnt + 1, turnaround, waiting);
                wt += waiting;
                tat += turnaround;
                flag = 0;
            }
        }

        // move to next process
        cnt = (cnt + 1) % n;
    }
    
    int ct = wt + tat;// avg completion time
    
    // output averages
    printf("\nAverage Waiting Time = %.2f\n", (float)wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)tat / n);
    printf("Average Completion Time = %.2f\n", (float)ct / n);
    
    return 0;
}
