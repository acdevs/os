#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    string pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateRoundRobinTimes(vector<Process> &processes, int timeQuantum) {
    queue<Process> readyQueue;
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < processes.size()) {
        // Adding arriving processes to the ready queue
        for (size_t i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push(processes[i]);
            }
        }

        if (!readyQueue.empty()) {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();

            // Execute the process for the time quantum or the remaining time, whichever is smaller
            int executionTime = min(timeQuantum, currentProcess.remainingTime);
            currentProcess.remainingTime -= executionTime;
            currentTime += executionTime;

            // Check if the process is completed
            if (currentProcess.remainingTime == 0) {
                completedProcesses++;
                currentProcess.turnaroundTime = currentTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
            } else {
                // If not completed, push it back to the ready queue
                readyQueue.push(currentProcess);
            }
        } else {
            currentTime++;
        }
    }
}

pair<double, double> calculateAvgTime(const vector<Process> &processes) {
    double totalTurnaroundTime = 0.0;
    double totalWaitingTime = 0.0;

    for (const auto &process : processes) {
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;
    }

    double averageTurnaroundTime = totalTurnaroundTime / processes.size();
    double averageWaitingTime = totalWaitingTime / processes.size();

    return make_pair(averageTurnaroundTime, averageWaitingTime);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter process details (Arrival Time Burst Time):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> processes[i].pid >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    const int timeQuantum = 2; // Time Quantum for Round Robin

    // Calculate times using Round Robin algorithm
    calculateRoundRobinTimes(processes, timeQuantum);

    // Calculate average turnaround time and average waiting time
    pair<double, double> avgTime = calculateAvgTime(processes);

    // Print process details and average times
    cout << "\nProcess\tTurnaround Time\tWaiting Time" << endl;
    for (const auto &process : processes) {
        cout << process.pid << "\t" << process.turnaroundTime << "\t\t" << process.waitingTime << endl;
    }
    cout << "\nAverage Turnaround Time: " << avgTime.first << endl;
    cout << "Average Waiting Time: " << avgTime.second << endl;

    return 0;
}
