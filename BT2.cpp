#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    string name;
    int at, bt, ct, tat, wt, rt;
    int rem_bt; // Remaining Burst Time
    bool is_started = false;
};

int main() {
    int n;
    cout << "=== THUAT TOAN SRT (SHORTEST REMAINING TIME) ===" << endl;
    cout << "Nhap so luong process: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " (Name AT BT): ";
        cin >> p[i].name >> p[i].at >> p[i].bt;
        p[i].rem_bt = p[i].bt;
    }

    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed != n) {
        int min_index = -1;
        int min_rem_bt = INT_MAX;

        // Tim tien trinh da den co Remaining Time nho nhat
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rem_bt > 0) {
                if (p[i].rem_bt < min_rem_bt) {
                    min_rem_bt = p[i].rem_bt;
                    min_index = i;
                }
                else if (p[i].rem_bt == min_rem_bt) {
                    if (p[i].at < p[min_index].at) min_index = i;
                }
            }
        }

        if (min_index != -1) {
            // Neu lan dau tien duoc CPU phuc vu
            if (!p[min_index].is_started) {
                p[min_index].rt = current_time - p[min_index].at;
                p[min_index].is_started = true;
            }

            p[min_index].rem_bt--; // Thuc thi 1 don vi thoi gian
            current_time++;

            // Neu tien trinh hoan thanh
            if (p[min_index].rem_bt == 0) {
                completed++;
                p[min_index].ct = current_time;
                p[min_index].tat = p[min_index].ct - p[min_index].at;
                p[min_index].wt = p[min_index].tat - p[min_index].bt;

                total_wt += p[min_index].wt;
                total_tat += p[min_index].tat;
            }
        } else {
            current_time++; // CPU idle
        }
    }

    // In ket qua
    cout << "\n-------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Name" << setw(15) << "Response Time" 
         << setw(15) << "Waiting Time" << setw(15) << "Turnaround Time" << endl;
    cout << "-------------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << p[i].name << setw(15) << p[i].rt 
             << setw(15) << p[i].wt << setw(15) << p[i].tat << endl;
    }
    cout << "-------------------------------------------------------------------------\n";
    cout << "Average Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;

    return 0;
}
