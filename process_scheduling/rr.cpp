#include <iostream>
#include <string>
#include <queue>
using namespace std;

/* Robin Round */

class Process{
    public:
        string pid;
        int arrivalTime;
        int burstTime;
    
    Process(string pid, int burstTime, int arrivalTime){
        this->pid = pid;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
    }
};

bool compareArrivalTime(Process p1, Process p2){
    return p1.arrivalTime < p2.arrivalTime;
}

void roundRobin(queue<Process> &readyQueue, int timeQuantum){
    queue<Process> waitingQueue;
    int currentTime = 0;

    while(!readyQueue.empty()){
        Process currentProcess = readyQueue.front();

        if(currentProcess.burstTime <= timeQuantum){
            currentTime += currentProcess.burstTime;

            readyQueue.pop();
            cout << "Process" << currentProcess.pid << " completed at " << currentTime << endl;
        }
        else{
            currentTime += timeQuantum;
            currentProcess.burstTime -= timeQuantum;

            readyQueue.push(currentProcess);
        }

        while(!waitingQueue.empty() && waitingQueue.front().arrivalTime <= currentTime){
            readyQueue.push(waitingQueue.front());
            waitingQueue.pop();
        }
    }
}

int main(){
    queue<Process> ready_queue;

    // Add some processes to the ready queue
    ready_queue.push(Process("A", 10, 0));
    ready_queue.push(Process("B", 5, 2));
    ready_queue.push(Process("C", 8, 4));

    // Set the time quantum
    int time_quantum = 2;

    roundRobin(ready_queue, time_quantum);

    return 0;
}