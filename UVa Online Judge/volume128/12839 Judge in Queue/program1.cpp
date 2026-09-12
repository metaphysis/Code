// Judge in Queue
// UVa ID: 12839
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseId = 1; caseId <= testCases; ++caseId) {
        int peopleCount, queueCount;
        cin >> peopleCount >> queueCount;
        vector<long long> waitedTime(peopleCount);
        vector<long long> serveTime(queueCount);
        for (long long &value : waitedTime) cin >> value;
        for (long long &value : serveTime) cin >> value;
        sort(waitedTime.begin(), waitedTime.end(), greater<long long>());
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> minHeap;
        for (long long value : serveTime) minHeap.push({0, value});
        long long answer = 0;
        for (int i = 0; i < peopleCount; ++i) {
            long long extraTime = minHeap.top().first;
            long long queueTime = minHeap.top().second;
            minHeap.pop();
            answer = max(answer, waitedTime[i] + extraTime);
            minHeap.push({extraTime + queueTime, queueTime});
        }
        cout << "Case " << caseId << ": " << answer << '\n';
    }
    return 0;
}
