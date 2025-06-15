#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int started; // flag for response time
} Process;

void fcfs(Process p[], int n) {
    int time = 0;
    float totalWT = 0, totalTAT = 0;

    // Sort by arrival time
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(p[j].arrivalTime > p[j+1].arrivalTime) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }

    printf("\nGantt Chart:\n|");
    for(int i = 0; i < n; i++) {
        if(time < p[i].arrivalTime) time = p[i].arrivalTime;
        p[i].completionTime = time + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        time = p[i].completionTime;
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;

        printf(" P%d |", p[i].pid);
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
    for(int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\n\nAverage Turnaround Time: %.2f", totalTAT/n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
}

void sjf(Process p[], int n) {
    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;
    int isCompleted[MAX] = {0};

    printf("\nGantt Chart:\n|");
    while(completed != n) {
        int idx = -1;
        int minBT = 9999;
        for(int i = 0; i < n; i++) {
            if(p[i].arrivalTime <= time && !isCompleted[i]) {
                if(p[i].burstTime < minBT) {
                    minBT = p[i].burstTime;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            time += p[idx].burstTime;
            p[idx].completionTime = time;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            isCompleted[idx] = 1;
            completed++;
            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;

            printf(" P%d |", p[idx].pid);
        } else {
            time++;
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
    for(int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\n\nAverage Turnaround Time: %.2f", totalTAT/n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
}

void roundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    for(int i = 0; i < n; i++) {
        p[i].remainingTime = p[i].burstTime;
        p[i].started = 0;
    }

    int queue[MAX], front = 0, rear = 0;
    int inQueue[MAX] = {0};

    queue[rear++] = 0;
    inQueue[0] = 1;

    printf("\nGantt Chart:\n|");

    while(completed < n) {
        int idx = queue[front++];
        if (front == MAX) front = 0;

        if(p[idx].remainingTime > 0) {
            int execTime = (p[idx].remainingTime >= quantum) ? quantum : p[idx].remainingTime;
            printf(" P%d |", p[idx].pid);
            time += execTime;
            p[idx].remainingTime -= execTime;

            // Add newly arrived processes
            for(int i = 0; i < n; i++) {
                if(i != idx && p[i].arrivalTime <= time && !inQueue[i] && p[i].remainingTime > 0) {
                    queue[rear++] = i;
                    if (rear == MAX) rear = 0;
                    inQueue[i] = 1;
                }
            }

            if(p[idx].remainingTime == 0) {
                p[idx].completionTime = time;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                totalWT += p[idx].waitingTime;
                totalTAT += p[idx].turnaroundTime;
                completed++;
            } else {
                queue[rear++] = idx;
                if (rear == MAX) rear = 0;
            }
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
    for(int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\n\nAverage Turnaround Time: %.2f", totalTAT/n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
}

void srtf(Process p[], int n) {
    int time = 0, completed = 0, minRT, idx = -1;
    float totalWT = 0, totalTAT = 0;
    int isCompleted[MAX] = {0};

    for (int i = 0; i < n; i++) {
        p[i].remainingTime = p[i].burstTime;
    }

    printf("\nGantt Chart:\n|");
    while (completed < n) {
        minRT = 1e9;
        idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && !isCompleted[i] && p[i].remainingTime < minRT && p[i].remainingTime > 0) {
                minRT = p[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            printf(" P%d |", p[idx].pid);
            p[idx].remainingTime--;
            time++;

            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = time;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                totalWT += p[idx].waitingTime;
                totalTAT += p[idx].turnaroundTime;
                isCompleted[idx] = 1;
                completed++;
            }
        } else {
            time++; // CPU idle
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\n\nAverage Turnaround Time: %.2f", totalTAT/n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
}


int main() {
    int n, choice, quantum;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &p[i].burstTime);
    }

    while(1) {
        printf("\nSelect Scheduling Algorithm:\n");
        printf("1. First Come First Serve (FCFS)\n");
        printf("2. Shortest Job First (SJF – Non-preemptive)\n");
        printf("3. Round Robin\n");
        printf("4. Shortest Remaining Time First (SRTF – Preemptive SJF)\n");

        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        // Copy fresh processes for each run
        Process temp[MAX];
        for(int i = 0; i < n; i++) temp[i] = p[i];

        switch(choice) {
            case 1: fcfs(temp, n); break;
            case 2: sjf(temp, n); break;
            case 3:
                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);
                roundRobin(temp, n, quantum);
                break;
            case 4: srtf(temp, n); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
