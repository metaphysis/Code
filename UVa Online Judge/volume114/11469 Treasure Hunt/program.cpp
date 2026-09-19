#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
};

vector<vector<Edge>> graph;
vector<int> discover, low;
vector<char> isBridge;
int timeStamp;

void findBridge(int node, int parentEdge) {
    discover[node] = low[node] = ++timeStamp;
    for (const Edge &edge : graph[node]) {
        if (edge.id == parentEdge) continue;
        if (discover[edge.to] == 0) {
            findBridge(edge.to, edge.id);
            low[node] = min(low[node], low[edge.to]);
            if (low[edge.to] > discover[node]) isBridge[edge.id] = 1;
        } else low[node] = min(low[node], discover[edge.to]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        int roomCount, tunnelCount;
        cin >> roomCount >> tunnelCount;
        graph.assign(roomCount + 1, vector<Edge>());
        for (int edgeId = 0; edgeId < tunnelCount; ++edgeId) {
            int firstRoom, secondRoom;
            cin >> firstRoom >> secondRoom;
            graph[firstRoom].push_back(Edge{secondRoom, edgeId});
            graph[secondRoom].push_back(Edge{firstRoom, edgeId});
        }
        discover.assign(roomCount + 1, 0);
        low.assign(roomCount + 1, 0);
        isBridge.assign(tunnelCount, 0);
        timeStamp = 0;
        for (int node = 1; node <= roomCount; ++node) if (discover[node] == 0) findBridge(node, -1);
        vector<char> visited(roomCount + 1, 0);
        vector<int> answer;
        int bestSize = 0;
        for (int start = 1; start <= roomCount; ++start) {
            if (visited[start]) continue;
            vector<int> component;
            queue<int> roomQueue;
            roomQueue.push(start);
            visited[start] = 1;
            while (!roomQueue.empty()) {
                int node = roomQueue.front();
                roomQueue.pop();
                component.push_back(node);
                for (const Edge &edge : graph[node]) {
                    if (isBridge[edge.id] || visited[edge.to]) continue;
                    visited[edge.to] = 1;
                    roomQueue.push(edge.to);
                }
            }
            if ((int)component.size() > bestSize) {
                bestSize = (int)component.size();
                answer = component;
            } else if ((int)component.size() == bestSize) answer.insert(answer.end(), component.begin(), component.end());
        }
        sort(answer.begin(), answer.end());
        cout << "Case #" << caseIndex << ": " << bestSize << '\n';
        for (int index = 0; index < (int)answer.size(); ++index) {
            if (index > 0) cout << ' ';
            cout << answer[index];
        }
        cout << '\n';
    }
    return 0;
}
