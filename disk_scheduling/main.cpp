#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to simulate First Come First Serve (FCFS) disk scheduling algorithm
int fcfs(const vector<int>& tracks, int head) {
    int totalSeek = 0;
    for (int track : tracks) {
        totalSeek += abs(head - track);
        head = track;
    }
    return totalSeek;
}

// Function to simulate SCAN disk scheduling algorithm
int scan(const vector<int>& tracks, int head, int size) {
    int totalSeek = 0;
    vector<int> sortedTracks = tracks;
    sortedTracks.push_back(0);
    sortedTracks.push_back(size - 1);
    sort(sortedTracks.begin(), sortedTracks.end());

    int idx = 0;
    while (idx < sortedTracks.size() && sortedTracks[idx] < head) {
        idx++;
    }

    // Scan towards the right
    for (int i = idx; i < sortedTracks.size(); ++i) {
        totalSeek += abs(head - sortedTracks[i]);
        head = sortedTracks[i];
    }

    // Scan towards the left
    for (int i = idx - 1; i >= 0; --i) {
        totalSeek += abs(head - sortedTracks[i]);
        head = sortedTracks[i];
    }

    return totalSeek;
}

// Function to simulate Circular SCAN (C-SCAN) disk scheduling algorithm
int cscan(const vector<int>& tracks, int head, int size) {
    int totalSeek = 0;
    vector<int> sortedTracks = tracks;
    sortedTracks.push_back(0);
    sortedTracks.push_back(size - 1);
    sort(sortedTracks.begin(), sortedTracks.end());

    int idx = 0;
    while (idx < sortedTracks.size() && sortedTracks[idx] < head) {
        idx++;
    }

    // Scan towards the right
    for (int i = idx; i < sortedTracks.size(); ++i) {
        totalSeek += abs(head - sortedTracks[i]);
        head = sortedTracks[i];
    }

    // Wrap around to the beginning and continue scanning towards the right
    totalSeek += abs(head - sortedTracks[0]);
    head = sortedTracks[0];

    for (int i = 1; i < idx; ++i) {
        totalSeek += abs(head - sortedTracks[i]);
        head = sortedTracks[i];
    }

    return totalSeek;
}

int main() {
    int numTracks;
    cout << "Enter Number of Tracks: ";
    cin >> numTracks;

    vector<int> tracks(numTracks);
    cout << "Enter Track Positions: ";
    for (int i = 0; i < numTracks; ++i) {
        cin >> tracks[i];
    }

    int head;
    cout << "Enter Initial Head Position: ";
    cin >> head;

    cout << "FCFS Total Seek Count: " << fcfs(tracks, head) << endl;
    cout << "SCAN Total Seek Count: " << scan(tracks, head, numTracks) << endl;
    cout << "C-SCAN Total Seek Count: " << cscan(tracks, head, numTracks) << endl;

    return 0;
}
