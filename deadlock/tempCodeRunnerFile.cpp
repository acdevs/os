#include <iostream>
#include <vector>

using namespace std;

const int MAX_RESOURCES = 4; // Maximum number of resources

// Function to check if granting a request will result in a safe state
bool isSafeState(vector<vector<int>>& maxResources,
                 vector<vector<int>>& allocatedResources,
                 vector<int>& availableResources,
                 int processID, const vector<int>& request) {
    // Step 1: Check if the request is less than or equal to the need and available resources
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (request[i] > maxResources[processID][i] - allocatedResources[processID][i] ||
            request[i] > availableResources[i]) {
            return false; // Request cannot be granted
        }
    }

    // Step 2: Simulate resource allocation to check for safety
    vector<int> work = availableResources;
    vector<bool> finish(allocatedResources.size(), false);

    // Try to allocate the resources and update work and finish vectors accordingly
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] -= request[i];
        allocatedResources[processID][i] += request[i];
    }

    // Check if the system is in a safe state
    bool safeState = true;
    for (int i = 0; i < allocatedResources.size(); ++i) {
        if (!finish[i]) {
            bool canFinish = true;
            for (int j = 0; j < MAX_RESOURCES; ++j) {
                if (allocatedResources[i][j] > work[j]) {
                    canFinish = false;
                    break;
                }
            }
            if (canFinish) {
                finish[i] = true;
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    work[j] += allocatedResources[i][j];
                }
                safeState = true;
                i = -1; // Restart the loop to check newly finished processes
            }
        }
    }

    // Step 3: Restore the state of allocated resources
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        allocatedResources[processID][i] -= request[i];
    }

    return safeState;
}

// Function to allocate resources to a process
void allocateResources(int processID, vector<vector<int>>& allocatedResources,
                       vector<int>& availableResources, const vector<int>& request) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        allocatedResources[processID][i] += request[i];
        availableResources[i] -= request[i];
    }
}

// Function to release resources held by a process
void releaseResources(int processID, vector<vector<int>>& allocatedResources,
                      vector<int>& availableResources, const vector<int>& release) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        allocatedResources[processID][i] -= release[i];
        availableResources[i] += release[i];
    }
}

int main() {
    // Define the system's maximum available resources
    vector<int> availableResources = {3, 1, 1, 2};

    // Define the maximum resources that each process can request
    vector<vector<int>> maxResources = {
        {3, 3, 2, 2},
        {1, 2, 3, 4},
        {1, 3, 5, 0}
    };

    // Define the currently allocated resources for each process
    vector<vector<int>> allocatedResources = {
        {1, 2, 2, 1},
        {1, 0, 3, 3},
        {1, 2, 1, 0}
    };

    // Define the requests made by each process
    vector<vector<int>> requests = {
        {0, 1, 0, 0}, // Process P1 requests {0, 1, 0, 0}
        {0, 0, 0, 0}, // Process P2 requests {0, 0, 0, 0}
        {0, 0, 0, 0}  // Process P3 requests {0, 0, 0, 0}
    };

    // Simulate requests and check for deadlock avoidance
    for (int i = 0; i < requests.size(); ++i) {
        if (isSafeState(maxResources, allocatedResources, availableResources, i, requests[i])) {
            // Request can be granted without causing deadlock
            cout << "Request by Process P" << i+1 << " can be granted safely." << endl;
            allocateResources(i, allocatedResources, availableResources, requests[i]);
        } else {
            // Request cannot be granted to avoid deadlock
            cout << "Request by Process P" << i+1 << " cannot be granted to avoid deadlock." << endl;
        }
    }

    return 0;
}
