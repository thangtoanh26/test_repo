#include <stdio.h>

struct Process {
    char name[20];
    int arrival_time;
    int burst_time;
    int response_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
};

int main() {
    int n;
    printf("Nhap so luong process: ");
    scanf("%d", &n);
    printf("--------------\n");

    struct Process p[100];
    for (int i = 0; i < n; i++) {
        printf("Nhap ten process %d: ", i + 1);
        scanf("%s", p[i].name);
        printf("Nhap arrival time: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Nhap burst time: ", i + 1);
        scanf("%d", &p[i].burst_time);
        printf("--------------\n");
        p[i].is_completed = 0; // 0 la false
    }

    int current_time = 0;
    int completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed != n) {
        int min_index = -1;
        int min_bt = 999999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].is_completed == 0) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    min_index = i;
                } else if (p[i].burst_time == min_bt) {
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
            p[min_index].turnaround_time = current_time - p[min_index].arrival_time;
            p[min_index].is_completed = 1;

            total_wt += p[min_index].waiting_time;
            total_tat += p[min_index].turnaround_time;
            completed++;
        } else {
            current_time++;
        }
    }

    // In ket qua
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
