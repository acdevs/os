#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int turnaroundTime;
    int waitingTime;
};

void calculateTimes(std::vector<Process> &processes){
    int time = 0;
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;
    time += processes[0].burstTime;
    for (size_t i = 1; i < processes.size(); ++i){
        int k;
        for(k = i; k < processes.size(); ++k){
            if(processes[k].arrivalTime > time){
                break;
            }
        }
        sort(processes.begin() + i, processes.begin() + k, [](const Process &a, const Process &b){
            return a.burstTime < b.burstTime;
        });
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        time += processes[i].burstTime;
    }
}

pair<double, double> calculateAvgTime(const std::vector<Process> &processes){
    pair<double, double> avgTime;
    double totalTurnaroundTime = 0.0;
    double totalWaitingTime = 0.0;
    for (const auto &process : processes){
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;
    }
    double averageTurnaroundTime = totalTurnaroundTime / processes.size();
    double averageWaitingTime = totalWaitingTime / processes.size();
    return make_pair(averageTurnaroundTime, averageWaitingTime);
}

void printProcessDetails(vector<Process> &processes){
    pair<double, double> avgTime = calculateAvgTime(processes);
    int n = processes.size();
    cout << "\n**SJF Scheduling Algorithm**" << endl;
    cout << "PID\tArrivalTime\tBurstTime\tWaitingTime\tTurnaroundTime\n";
    for (int i = 0; i < n; ++i)
    {
        cout << processes[i].pid << "\t\t" << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
             << processes[i].turnaroundTime << endl;
    }
    cout << "Average Turnaround Time: " << avgTime.first << endl;
    cout << "Average Waiting Time: " << avgTime.second << endl;
}

int main()
{
    int n;
    cout << "# of Processes: ";
    cin >> n;
    vector<Process> processes(n);

    cout << "PID : ArrivalTime BurstTime" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << i + 1 << "   : ";
        cin >> processes[i].arrivalTime;
        cin >> processes[i].burstTime;
        processes[i].pid = i + 1;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    calculateTimes(processes);
    printProcessDetails(processes);
    return 0;
}
