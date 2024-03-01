#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int turnaroundTime;
    int waitingTime;
};

struct CompareProcesses{
    bool operator()(const Process &a, const Process &b) const{
        return (a.remainingTime > b.remainingTime) || ((a.remainingTime == b.remainingTime) && (a.priority > b.priority));
    }
};

void calculateTimes(vector<Process> &processes){
    priority_queue<Process, vector<Process>, CompareProcesses> readyQueue;
    int currentTime = 0;
    size_t completedProcesses = 0;
    while (completedProcesses < processes.size())
    {
        // Add arriving processes to the ready queue
        for (size_t i = 0; i < processes.size(); ++i){
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0){
                readyQueue.push(processes[i]);
            }
        }
        if (!readyQueue.empty()){
            Process currentProcess = readyQueue.top();
            readyQueue.pop();
            int executionTime = std::min(currentProcess.remainingTime, 1);
            currentProcess.remainingTime -= executionTime;
            currentTime += executionTime;
            if (currentProcess.remainingTime == 0) {
                completedProcesses++;
                currentProcess.turnaroundTime = currentTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
            }
            processes[currentProcess.pid - 1] = currentProcess;
        }
        else{
            currentTime++;
        }
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
    cout << "\n**SRTF Scheduling Algorithm**" << endl;
    cout << "PID\tArrivalTime\tBurstTime\tPriority\tWaitingTime\tTurnaroundTime\n";
    for (int i = 0; i < n; ++i)
    {
        cout << processes[i].pid << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].priority << "\t\t"
             << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
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

    cout << "PID : ArrivalTime BurstTime Priority" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << i + 1 << "   : ";
        cin >> processes[i].arrivalTime;
        cin >> processes[i].burstTime;
        cin >> processes[i].priority;
        processes[i].pid = i + 1;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    calculateTimes(processes);
    printProcessDetails(processes);
    return 0;
}
