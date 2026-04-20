#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Process {
    string name;
    int bt, rem_bt;
    int tat, wt;
};

struct GanttRecord {
    string name;
    int start_time;
    int stop_time;
};

int main() {
    int n, quantum;
    cout << "=== THUAT TOAN ROUND ROBIN (AT = 0) ===" << endl;
    cout << "Nhap so process: ";
    cin >> n;
    cout << "Nhap quantum time: ";
    cin >> quantum;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " (Name BT): ";
        cin >> p[i].name >> p[i].bt;
        p[i].rem_bt = p[i].bt;
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    bool all_done = false;
    vector<GanttRecord> gantt;

    while (!all_done) {
        all_done = true;

        for (int i = 0; i < n; i++) {
            if (p[i].rem_bt > 0) {
                all_done = false; // Van con tien trinh chua xong
                
                GanttRecord record;
                record.name = p[i].name;
                record.start_time = current_time;

                if (p[i].rem_bt > quantum) {
                    current_time += quantum;
                    p[i].rem_bt -= quantum;
                } else {
                    // Chay not phan con lai neu < quantum
                    current_time += p[i].rem_bt;
                    p[i].wt = current_time - p[i].bt; // AT = 0 nen WT = CT - BT
                    p[i].tat = current_time;          // AT = 0 nen TAT = CT
                    p[i].rem_bt = 0;

                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                }
                record.stop_time = current_time;
                gantt.push_back(record);
            }
        }
    }

    // In Gantt Chart
    cout << "\n=== GANTT CHART ===" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(15) << "Process Name" << setw(20) << "Start Processor" 
         << setw(20) << "Stop Processor" << endl;
    cout << "---------------------------------------------------" << endl;
    for (const auto& rec : gantt) {
        cout << left << setw(15) << rec.name << setw(20) << rec.start_time 
             << setw(20) << rec.stop_time << endl;
    }
    cout << "---------------------------------------------------\n";

    // In thong so trung binh
    cout << "Average Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;

    return 0;
}
