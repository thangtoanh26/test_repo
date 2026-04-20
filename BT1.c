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
            if (p[i].at <= current_time && !p[i].is_completed) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    min_index = i;
                }
                else if (p[i].bt == min_bt) {
                    if (p[i].at < p[min_index].at) {
                        min_index = i;
                    }
                }
            }
        }

        if (min_index != -1) {
            p[min_index].rt = current_time - p[min_index].at;
            p[min_index].wt = current_time - p[min_index].at;
            current_time += p[min_index].bt;
            p[min_index].ct = current_time;
            p[min_index].tat = p[min_index].ct - p[min_index].at;
            p[min_index].is_completed = true;
            
            total_wt += p[min_index].wt;
            total_tat += p[min_index].tat;
            completed++;
        } else {
            current_time++;
        }
    }

    printf("\n-------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-15s %-15s\n", "Name", "Response Time", "Waiting Time", "Turnaround Time");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-15d %-15d %-15d\n", p[i].name, p[i].rt, p[i].wt, p[i].tat);
    }
    printf("-------------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
