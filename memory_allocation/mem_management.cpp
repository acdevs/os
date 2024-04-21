#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Memory block structure
struct MemoryBlock {
    int id; // Process ID
    int size; // Size of the memory block
    bool allocated; // Flag to indicate if the block is allocated
};

// Function to initialize memory blocks
void initializeMemory(vector<MemoryBlock>& memory) {
    for (int i = 0; i < memory.size(); ++i) {
        memory[i].id = -1; // -1 indicates no process is allocated
        memory[i].allocated = false;
    }
}

// Function to display memory state
void displayMemory(const vector<MemoryBlock>& memory) {
    cout << "Memory State:" << endl;
    for (const MemoryBlock& block : memory) {
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

// Best Fit Memory Allocation Algorithm
void bestFit(vector<MemoryBlock>& memory, int processId, int processSize) {
    int minSize = 2147483647;
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

// Worst Fit Memory Allocation Algorithm
void worstFit(vector<MemoryBlock>& memory, int processId, int processSize) {
    int maxSize = -2147483648;
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

// First Fit Memory Allocation Algorithm
void firstFit(vector<MemoryBlock>& memory, int processId, int processSize) {
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
    // Define memory blocks
    vector<MemoryBlock> memory = {
        {0, 50, false},
        {1, 100, false},
        {2, 200, false},
        {3, 150, false},
        {4, 300, false}
    };

    // Initialize memory
    initializeMemory(memory);

    // Display initial memory state
    displayMemory(memory);

    // Test memory allocation algorithms
    bestFit(memory, 1, 120);
    worstFit(memory, 2, 180);
    firstFit(memory, 3, 250);

    // Display final memory state
    displayMemory(memory);

    return 0;
}
