#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrival(const Process &p1, const Process &p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

void calculateTimes(vector<Process> &processes) {
    int n = processes.size();
    vector<int> completionTime(n);
    vector<int> turnaroundTime(n);
    vector<bool> executed(n, false);

    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        int highestResponseRatioProcess = -1;
        double highestResponseRatio = -1;

        for (int j = 0; j < n; ++j) {
            if (!executed[j] && processes[j].arrivalTime <= currentTime) {
                double responseRatio = (currentTime - processes[j].arrivalTime + processes[j].burstTime) / (double)processes[j].burstTime;
                if (responseRatio > highestResponseRatio || (responseRatio == highestResponseRatio && processes[j].arrivalTime < processes[highestResponseRatioProcess].arrivalTime)) {
                    highestResponseRatio = responseRatio;
                    highestResponseRatioProcess = j;
                }
            }
        }

        if (highestResponseRatioProcess == -1) {
            currentTime++;
            i--;
            continue;
        }

        completionTime[highestResponseRatioProcess] = currentTime + processes[highestResponseRatioProcess].burstTime;
        turnaroundTime[highestResponseRatioProcess] = completionTime[highestResponseRatioProcess] - processes[highestResponseRatioProcess].arrivalTime;
        processes[highestResponseRatioProcess].waitingTime = turnaroundTime[highestResponseRatioProcess] - processes[highestResponseRatioProcess].burstTime;

        executed[highestResponseRatioProcess] = true;
        currentTime = completionTime[highestResponseRatioProcess];
    }

    // Updating process details
    for (int i = 0; i < n; ++i) {
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
    cout << "\n**Highest Response Ratio Next (HRRN) Scheduling Algorithm**" << endl;
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
        processes[i].pid = i + 1;
    }
    
    calculateTimes(processes);
    printProcessDetails(processes);

    return 0;
}
