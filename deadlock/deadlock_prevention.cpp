#include <iostream>
#include <vector>

using namespace std;

const int MAX_RESOURCES = 10; // Maximum number of resources
bool resourceAvailable[MAX_RESOURCES] = {true, true, true}; // Initial availability of resources

// Function to request resources by a process
bool requestResources(int processID, const vector<int>& requestedResources) {
    // Check if all requested resources are available
    for (int resource : requestedResources) {
        if (!resourceAvailable[resource]) {
            cout << "Process " << processID << " is waiting for resource " << resource << endl;
            return false; // Process waits if any resource is unavailable
        }
    }

    // Allocate the requested resources
    for (int resource : requestedResources) {
        resourceAvailable[resource] = false;
    }

    cout << "Resources allocated to process " << processID << endl;
    return true;
}

// Function to release resources by a process
void releaseResources(int processID, const vector<int>& releasedResources) {
    // Release the resources
    for (int resource : releasedResources) {
        resourceAvailable[resource] = true;
    }

    cout << "Resources released by process " << processID << endl;
}

int main() {
    // Sample process resource requests
    vector<vector<int>> processRequests = {
        {0},        // Process 0 requests resource 0
        {1, 2},     // Process 1 requests resources 1 and 2
        {0, 2},     // Process 2 requests resources 0 and 2
    };

    // Process resource releases
    vector<vector<int>> processReleases = {
        {0},        // Process 0 releases resource 0
        {1, 2},     // Process 1 releases resources 1 and 2
        {0, 2},     // Process 2 releases resources 0 and 2
    };

    // Simulate process resource requests and releases
    for (int i = 0; i < processRequests.size(); ++i) {
        if (requestResources(i, processRequests[i])) {
            // If resources are successfully allocated, simulate some processing
            // For simplicity, just print a message
            cout << "Processing by process " << i << endl;

            // After processing, release the resources
            releaseResources(i, processReleases[i]);
        }
    }

    return 0;
}
