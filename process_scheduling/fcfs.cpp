#include <iostream>
#include <string>
#include <queue>
using namespace std;

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

int main(){
}