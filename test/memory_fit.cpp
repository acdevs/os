#include <iostream>
#include <vector>

using namespace std;

struct Memory {
    int id;
    int size;
    bool allocated;
};

void initializeMemory(vector<Memory>& memory) {
    for (int i = 0; i < memory.size(); ++i) {
        memory[i].id = -1;
        memory[i].allocated = false;
    }
}

void displayMemory(const vector<Memory>& memory) {
    cout << "Memory State:" << endl;
    for (const Memory& block : memory) {
        cout << "Block ID: " << block.id << ", Size: " << block.size;
        if (block.allocated) {
            cout << ", Allocated: Yes";
        } else {
            cout << ", Allocated: No";
        }
        cout << endl;
    }
    cout << endl;
}

void bestFit(vector<Memory>& memory, int processId, int processSize) {
    int minSize = INT32_MAX;
    int bestFitIdx = -1;

    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (memory[i].size < minSize) {
                minSize = memory[i].size;
                bestFitIdx = i;
            }
        }
    }

    if (bestFitIdx != -1) {
        memory[bestFitIdx].id = processId;
        memory[bestFitIdx].allocated = true;
        cout << "Process " << processId << " allocated to Block " << bestFitIdx << " using Best Fit." << endl;
    } else {
        cout << "Insufficient memory to allocate Process " << processId << " using Best Fit." << endl;
    }
}

void worstFit(vector<Memory>& memory, int processId, int processSize) {
    int maxSize = INT32_MIN;
    int worstFitIdx = -1;

    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (memory[i].size > maxSize) {
                maxSize = memory[i].size;
                worstFitIdx = i;
            }
        }
    }

    if (worstFitIdx != -1) {
        memory[worstFitIdx].id = processId;
        memory[worstFitIdx].allocated = true;
        cout << "Process " << processId << " allocated to Block " << worstFitIdx << " using Worst Fit." << endl;
    } else {
        cout << "Insufficient memory to allocate Process " << processId << " using Worst Fit." << endl;
    }
}

void firstFit(vector<Memory>& memory, int processId, int processSize) {
    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].id = processId;
            memory[i].allocated = true;
            cout << "Process " << processId << " allocated to Block " << i << " using First Fit." << endl;
            return;
        }
    }
    cout << "Insufficient memory to allocate Process " << processId << " using First Fit." << endl;
}

int main() {
    vector<Memory> memory = {
        {0, 50, false},
        {1, 100, false},
        {2, 200, false},
        {3, 150, false},
        {4, 300, false}
    };

    initializeMemory(memory);
    displayMemory(memory);

    bestFit(memory, 1, 120);
    worstFit(memory, 2, 180);
    firstFit(memory, 3, 250);

    displayMemory(memory);
    return 0;
}
