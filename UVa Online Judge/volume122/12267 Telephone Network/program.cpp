#include <bits/stdc++.h>
using namespace std;

struct Request {
    int id, in, out;
};

void colorFrom(int start, const vector<int>& edgeU, const vector<int>& edgeV, const vector<vector<int>>& graph, vector<int>& color) {
    int node = start, nowColor = 0;
    while (true) {
        int edge = -1;
        for (int id : graph[node])
            if (color[id] == -1) {
                edge = id;
                break;
            }
        if (edge == -1)
            break;
        color[edge] = nowColor;
        node = edgeU[edge] == node ? edgeV[edge] : edgeU[edge];
        nowColor ^= 1;
    }
}

void route(int level, const vector<Request>& requests, vector<int>& answer) {
    if (level == 0)
        return;
    int half = 1 << (level - 1), nodeCount = half * 2, requestCount = requests.size();
    vector<int> edgeU(requestCount), edgeV(requestCount), color(requestCount, -1);
    vector<vector<int>> graph(nodeCount);
    for (int i = 0; i < requestCount; i++) {
        edgeU[i] = requests[i].in % half;
        edgeV[i] = half + requests[i].out % half;
        graph[edgeU[i]].push_back(i);
        graph[edgeV[i]].push_back(i);
    }
    for (int i = 0; i < nodeCount; i++)
        if (graph[i].size() == 1)
            colorFrom(i, edgeU, edgeV, graph, color);
    for (int i = 0; i < requestCount; i++)
        if (color[i] == -1)
            colorFrom(edgeU[i], edgeU, edgeV, graph, color);
    vector<Request> first, second;
    for (int i = 0; i < requestCount; i++) {
        int id = requests[i].id;
        answer[id] |= color[i] << (level - 1);
        Request nextRequest = {id, requests[i].in % half, requests[i].out % half};
        if (color[i] == 0)
            first.push_back(nextRequest);
        else
            second.push_back(nextRequest);
    }
    route(level - 1, first, answer);
    route(level - 1, second, answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n, m;
        cin >> n >> m;
        vector<Request> requests(m);
        for (int i = 0; i < m; i++) {
            requests[i].id = i;
            cin >> requests[i].in >> requests[i].out;
        }
        vector<int> answer(m, 0);
        route(n, requests, answer);
        for (int i = 0; i < m; i++) {
            if (i > 0)
                cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
    return 0;
}
