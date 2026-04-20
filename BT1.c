/*
######################################### 
# University of Information Technology  # 
# IT007 Operating System                #
# To Anh Thang - 24521613               # 
# File: sjf.c                           # 
#########################################
*/ 

#include <stdio.h>
#include <vector>
#include <iomanip>
#include <climits>
#include <cstring>

struct Process {
    char name[20];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int is_completed;
};

void Nhap(vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); i++) {
        scanf("Nhap ten process %d: %s", i + 1, processes[i].name);
        scanf("Nhap arrival time: %d", &processes[i].arrival_time);
        scanf("Nhap burst time: %d", &processes[i].burst_time);
    }
}

int main() {
    int n;
    printf("Nhap so luong process: ");
    scanf("%d", &n);

    vector<Process> p(n);
    Nhap(p);

    int current_time = 0;
    int completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed != n) {
        int min_index = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    min_index = i;
                }
                else if (p[i].burst_time == min_bt) {
                    if (p[i].arrival_time < p[min_index].arrival_time) {
                        min_index = i;
                    }
                }
            }
        }

        if (min_index != -1) {
            p[min_index].response_time = current_time - p[min_index].arrival_time;
            p[min_index].waiting_time = current_time - p[min_index].arrival_time;
            current_time += p[min_index].burst_time;
            p[min_index].completion_time = current_time;
            p[min_index].turnaround_time = p[min_index].completion_time - p[min_index].arrival_time;
            p[min_index].is_completed = true;
            
            total_wt += p[min_index].waiting_time;
            total_tat += p[min_index].turnaround_time;
            completed++;
        } else {
            current_time++;
        }
    }

    printf("\n-------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-15s %-15s\n", "Name", "Response Time", "Waiting Time", "Turnaround Time");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-15d %-15d %-15d\n", p[i].name, p[i].response_time, p[i].waiting_time, p[i].turnaround_time);
    }
    printf("-------------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
