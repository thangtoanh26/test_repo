#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    string name;
    int at, bt, rem_bt;
    int ct, tat, wt, rt;
    bool is_completed = false;
    bool in_queue = false;
};

struct Gantt {
    string name;
    int start, stop;
};

int main() {
    int n, quantum;
    cout << "=== RR SCHEDULING (SUPPORT ARRIVAL TIME) ===" << endl;
    cout << "Nhap so luong process: "; cin >> n;
    cout << "Nhap quantum time: "; cin >> quantum;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " (Name AT BT): ";
        cin >> p[i].name >> p[i].at >> p[i].bt;
        p[i].rem_bt = p[i].bt;
    }

    // Sap xep theo thoi gian den de de quan ly
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    queue<int> q;
    vector<Gantt> gantt_chart;
    int current_time = 0;
    int completed = 0;
    
    // Day process dau tien vao queue
    q.push(0);
    p[0].in_queue = true;

    while (completed < n) {
        if (q.empty()) {
            // Neu queue trong nhung chua xong het, nhay thoi gian den process tiep theo
            for (int i = 0; i < n; i++) {
                if (!p[i].is_completed) {
                    current_time = p[i].at;
                    q.push(i);
                    p[i].in_queue = true;
                    break;
                }
            }
        }

        int idx = q.front();
        q.pop();

        // Ghi lai thong tin Gantt
        Gantt g;
        g.name = p[idx].name;
        g.start = current_time;

        // Tinh Response Time (lan dau tien duoc phuc vu)
        if (p[idx].rem_bt == p[idx].bt) {
            p[idx].rt = current_time - p[idx].at;
        }

        // Thuc thi theo Quantum
        int execute_time = min(p[idx].rem_bt, quantum);
        p[idx].rem_bt -= execute_time;
        current_time += execute_time;
        
        g.stop = current_time;
        gantt_chart.push_back(g);

        // Kiem tra xem trong luc dang chay co process nao moi den khong
        for (int i = 0; i < n; i++) {
            if (!p[i].is_completed && p[i].at <= current_time && !p[i].in_queue && i != idx) {
                q.push(i);
                p[i].in_queue = true;
            }
        }

        if (p[idx].rem_bt > 0) {
            // Neu chua xong thi quay lai hang doi
            q.push(idx);
        } else {
            // Neu da xong
            p[idx].is_completed = true;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    // In Gantt Chart
    cout << "\n=== GANTT CHART ===" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(15) << "Process" << setw(15) << "Start" << setw(15) << "Stop" << endl;
    cout << "---------------------------------------------------" << endl;
    for (const auto& item : gantt_chart) {
        cout << left << setw(15) << item.name << setw(15) << item.start << setw(15) << item.stop << endl;
    }

    // Tinh trung binh
    float total_wt = 0, total_tat = 0;
    cout << "\n=== TABLE RESULT ===" << endl;
    cout << left << setw(10) << "Name" << setw(10) << "AT" << setw(10) << "BT" 
         << setw(10) << "WT" << setw(10) << "TAT" << endl;
    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        cout << left << setw(10) << p[i].name << setw(10) << p[i].at << setw(10) << p[i].bt 
             << setw(10) << p[i].wt << setw(10) << p[i].tat << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;

    return 0;
}
