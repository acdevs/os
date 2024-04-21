#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

// Function to simulate FIFO page replacement algorithm
int fifoPageReplacement(const vector<int>& pages, int numFrames) {
    unordered_map<int, bool> inMemory;
    queue<int> fifoQueue;
    int pageFaults = 0;

    for (int page : pages) {
        if (inMemory.find(page) == inMemory.end()) {
            pageFaults++;
            if (fifoQueue.size() == numFrames) {
                inMemory.erase(fifoQueue.front());
                fifoQueue.pop();
            }
            fifoQueue.push(page);
            inMemory[page] = true;
        }
    }

    return pageFaults;
}

// Function to simulate LRU page replacement algorithm
int lruPageReplacement(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> recentUse; // Map to store recent use of pages
    int pageFaults = 0;

    for (int page : pages) {
        if (recentUse.find(page) == recentUse.end()) {
            pageFaults++;
            if (recentUse.size() == numFrames) {
                // Find the least recently used page
                auto it = min_element(recentUse.begin(), recentUse.end(),
                                       [](const pair<int, int>& p1, const pair<int, int>& p2) {
                                           return p1.second < p2.second;
                                       });
                recentUse.erase(it->first);
            }
        }
        recentUse[page] = pageFaults;
    }

    return pageFaults;
}

// Function to simulate Optimal page replacement algorithm
int optimalPageReplacement(const vector<int>& pages, int numFrames) {
    vector<int> frames(numFrames, -1); // Represents memory frames
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        if (find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
            // Page fault occurs, replace a page
            pageFaults++;
            int pos = numeric_limits<int>::min();
            int replaceIdx = -1;
            for (int j = 0; j < frames.size(); ++j) {
                int nextPagePos = find(pages.begin() + i, pages.end(), frames[j]) - pages.begin();
                if (nextPagePos == pages.size()) {
                    replaceIdx = j;
                    break;
                }
                if (nextPagePos > pos) {
                    pos = nextPagePos;
                    replaceIdx = j;
                }
            }
            frames[replaceIdx] = pages[i];
        }
    }

    return pageFaults;
}

int main() {
    vector<int> pages = {1, 3, 0, 3, 5, 6, 3}; // Page reference string
    int numFrames = 3; // Number of frames

    cout << "FIFO Page Replacement - Number of Page Faults: " << fifoPageReplacement(pages, numFrames) << endl;
    cout << "LRU Page Replacement - Number of Page Faults: " << lruPageReplacement(pages, numFrames) << endl;
    cout << "Optimal Page Replacement - Number of Page Faults: " << optimalPageReplacement(pages, numFrames) << endl;

    return 0;
}
