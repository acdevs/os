#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateTimes(vector<Process> &processes, int timeQuantum) {
    int n = processes.size();
    vector<int> remainingTime(n);
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<bool> executed(n, false);
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !executed[i]) {
                if (processes[i].remainingTime > 0) {
                    if (processes[i].remainingTime <= timeQuantum) {
                        currentTime += processes[i].remainingTime;
                        processes[i].remainingTime = 0;
                        completed++;
                        turnaroundTime[i] = currentTime - processes[i].arrivalTime;
                    } else {
                        processes[i].remainingTime -= timeQuantum;
                        currentTime += timeQuantum;
                    }
                }
            }
        }
    }

    // Calculating waiting times
    for (int i = 0; i < n; ++i) {
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
    }

    // Updating process details
    for (int i = 0; i < n; ++i) {
        processes[i].waitingTime = waitingTime[i];
        processes[i].turnaroundTime = turnaroundTime[i];
    }
}

pair<double, double> calculateAvgTime(const vector<Process> &processes) {
    pair<double, double> avgTime;
    double totalTurnaroundTime = 0.0;
    double totalWaitingTime = 0.0;
    for (const auto &process : processes) {
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;
    }
    avgTime.first = totalTurnaroundTime / processes.size();
    avgTime.second = totalWaitingTime / processes.size();
    return avgTime;
}

void printProcessDetails(const vector<Process> &processes) {
    int n = processes.size();
    cout << "\n**Round Robin Scheduling Algorithm**" << endl;
    cout << "PID\tArrivalTime\tBurstTime\tWaitingTime\tTurnaroundTime\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].pid << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t"
             << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }
}

int main() {
    int n;
    cout << "# of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "PID : ArrivalTime BurstTime" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << "   : ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].pid = i + 1;
    }
    const int timeQuantum = 2;
    calculateTimes(processes, timeQuantum);
    printProcessDetails(processes);

    return 0;
}
