/*###################################### 
# University of Information Technology # 
# IT007 Operating System               #
# To Anh Thang, 24521613               # 
# File: rr.c                          # 
######################################*/

#include <stdio.h>

struct Process {
    char name[20];
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed, in_queue;
};

struct Gantt {
    int p_id;
    int start;
    int stop;
};

int main() {
    int n, quantum;
    printf("Nhap so process: "); scanf("%d", &n);
    printf("Nhap quantum time: "); scanf("%d", &quantum);
    printf("--------------\n");

    struct Process p[100];
    for (int i = 0; i < n; i++) {
        printf("Nhap ten process %d: ", i + 1);
        scanf("%s", p[i].name);
        printf("Nhap arrival time: "); scanf("%d", &p[i].arrival_time);
        printf("Nhap burst time: "); scanf("%d", &p[i].burst_time);
        p[i].remaining_burst_time = p[i].burst_time;
        p[i].is_completed = 0;
        p[i].in_queue = 0;
        printf("--------------\n");
    }

    int q[1000];
    int front = 0, rear = 0;

    struct Gantt gantt[1000];
    int gantt_count = 0;

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        if (front == rear) {
            int min_at = 999999;
            for (int i = 0; i < n; i++) {
                if (p[i].is_completed == 0 && p[i].arrival_time < min_at) {
                    min_at = p[i].arrival_time;
                }
            }
            if (current_time < min_at) current_time = min_at;
            
            for (int i = 0; i < n; i++) {
                if (p[i].is_completed == 0 && p[i].in_queue == 0 
                        && p[i].arrival_time == current_time) {
                    q[rear++] = i;
                    p[i].in_queue = 1;
                }
            }
        }

        int idx = q[front++];
        
        // Tinh Response Time (lan chay dau)
        if (p[idx].remaining_burst_time == p[idx].burst_time) {
            p[idx].waiting_time = current_time - p[idx].arrival_time;
        }

        int start_time = current_time;
        int execute_time = (p[idx].remaining_burst_time < quantum) 
                                ? p[idx].remaining_burst_time : quantum;
        
        p[idx].remaining_burst_time -= execute_time;
        current_time += execute_time;

        gantt[gantt_count].p_id = idx;
        gantt[gantt_count].start = start_time;
        gantt[gantt_count].stop = current_time;
        gantt_count++;

        for (int t = start_time + 1; t <= current_time; t++) {
            for (int i = 0; i < n; i++) {
                if (p[i].is_completed == 0 && p[i].in_queue == 0 && p[i].arrival_time == t && i != idx) {
                    q[rear++] = i;
                    p[i].in_queue = 1;
                }
            }
        }

        if (p[idx].remaining_burst_time > 0) {
            q[rear++] = idx; // Ve cuoi hang cho
        } else {
            p[idx].is_completed = 1;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            completed++;
        }
    }

    printf("\n=== GANTT CHART ===\n");
    printf("---------------------------------------------------\n");
    printf("%-15s %-15s %-15s\n", "Process", "Start", "Stop");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < gantt_count; i++) {
        printf("%-15s %-15d %-15d\n", p[gantt[i].p_id].name, gantt[i].start, gantt[i].stop);
    }

    float total_wt = 0, total_tat = 0;
    printf("\n=== TABLE RESULT ===\n");
    printf("%-10s %-14s %-14s %-14s %-14s\n", "Name", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time");
    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        printf("%-10s %-14d %-14d %-14d %-14d\n", p[i].name, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
