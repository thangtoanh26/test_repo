#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    string name;
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
    int rt; // Response Time
    bool is_completed = false;
};

int main() {
    int n;
    cout << "=== THUAT TOAN SJF (SHORTEST JOB FIRST) ===" << endl;
    cout << "Nhap so luong process: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " (Name AT BT): ";
        cin >> p[i].name >> p[i].at >> p[i].bt;
    }

    int current_time = 0;
    int completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed != n) {
        int min_index = -1;
        int min_bt = INT_MAX;

        // Tim tien trinh da den co Burst Time nho nhat
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].is_completed) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    min_index = i;
                }
                // Neu Burst Time bang nhau, uu tien tien trinh den truoc
                else if (p[i].bt == min_bt) {
                    if (p[i].at < p[min_index].at) {
                        min_index = i;
                    }
                }
            }
        }

        if (min_index != -1) {
            // Process duoc CPU xu ly
            p[min_index].rt = current_time - p[min_index].at;
            p[min_index].wt = current_time - p[min_index].at;
            current_time += p[min_index].bt; // Thuc thi xong
            p[min_index].ct = current_time;
            p[min_index].tat = p[min_index].ct - p[min_index].at;
            p[min_index].is_completed = true;
            
            total_wt += p[min_index].wt;
            total_tat += p[min_index].tat;
            completed++;
        } else {
            // Khong co tien trinh nao trong Ready Queue, CPU nghi
            current_time++;
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
