#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long len;
};

int nodeCnt;
long long edgeLen;
vector<vector<Edge>> graph;
vector<long long> pos, plusVal, minusVal;
vector<int> plusOrder, minusOrder;

int getFar(int start, vector<long long>& dist, vector<int>& parent, vector<int>& order) {
    dist.assign(nodeCnt + 1, 0);
    parent.assign(nodeCnt + 1, 0);
    order.clear();
    order.push_back(start);
    int farNode = start;
    for (int i = 0; i < (int)order.size(); i++) {
        int cur = order[i];
        if (dist[cur] > dist[farNode]) farNode = cur;
        for (const Edge& edge : graph[cur]) {
            if (edge.to == parent[cur]) continue;
            parent[edge.to] = cur;
            dist[edge.to] = dist[cur] + edge.len;
            order.push_back(edge.to);
        }
    }
    return farNode;
}

bool canReach(long long limit) {
    int pathCnt = pos.size(), addIdx = 0;
    long long inf = 1LL << 62;
    long long minMinus = inf, maxPlus = -inf;
    long long sumLow = 0, sumHigh = 2 * pos.back();
    long long diffLow = 0, diffHigh = pos.back();
    for (int cur : plusOrder) {
        while (addIdx < pathCnt && minusVal[minusOrder[addIdx]] < plusVal[cur] - limit) {
            int prev = minusOrder[addIdx++];
            minMinus = min(minMinus, minusVal[prev]);
            maxPlus = max(maxPlus, plusVal[prev]);
        }
        if (addIdx == 0) continue;
        sumLow = max(sumLow, maxPlus + plusVal[cur] + edgeLen - limit);
        sumHigh = min(sumHigh, minMinus + minusVal[cur] + limit - edgeLen);
        diffLow = max(diffLow, plusVal[cur] - minMinus + edgeLen - limit);
        diffHigh = min(diffHigh, minusVal[cur] - maxPlus + limit - edgeLen);
        if (sumLow > sumHigh || diffLow > diffHigh) return false;
    }
    int sumIdx = pathCnt, diffIdx = 0;
    for (int leftIdx = 0; leftIdx < pathCnt; leftIdx++) {
        long long leftPos = pos[leftIdx];
        while (sumIdx > 0 && pos[sumIdx - 1] >= sumLow - leftPos) sumIdx--;
        while (diffIdx < pathCnt && pos[diffIdx] < diffLow + leftPos) diffIdx++;
        int rightIdx = max(leftIdx, max(sumIdx, diffIdx));
        if (rightIdx == pathCnt) continue;
        long long rightPos = pos[rightIdx];
        if (leftPos + rightPos <= sumHigh && rightPos - leftPos <= diffHigh) return true;
    }
    return false;
}

long long solve() {
    vector<long long> dist;
    vector<int> parent, order, pathNodes;
    int start = getFar(1, dist, parent, order);
    int finish = getFar(start, dist, parent, order);
    for (int cur = finish; cur != 0; cur = parent[cur]) pathNodes.push_back(cur);
    reverse(pathNodes.begin(), pathNodes.end());
    int pathCnt = pathNodes.size();
    vector<int> pathId(nodeCnt + 1, -1);
    vector<long long> height(pathCnt, 0);
    pos.resize(pathCnt);
    plusVal.resize(pathCnt);
    minusVal.resize(pathCnt);
    plusOrder.resize(pathCnt);
    minusOrder.resize(pathCnt);
    for (int i = 0; i < pathCnt; i++) {
        pathId[pathNodes[i]] = i;
        pos[i] = dist[pathNodes[i]];
    }
    for (int cur : order) {
        if (pathId[cur] == -1) pathId[cur] = pathId[parent[cur]];
        int idx = pathId[cur];
        height[idx] = max(height[idx], dist[cur] - pos[idx]);
    }
    long long low = 0, high = pos.back();
    for (int i = 0; i < pathCnt; i++) {
        plusVal[i] = pos[i] + height[i];
        minusVal[i] = pos[i] - height[i];
        plusOrder[i] = i;
        minusOrder[i] = i;
        low = max(low, 2 * height[i]);
    }
    sort(plusOrder.begin(), plusOrder.end(), [](int first, int second) {
        return plusVal[first] < plusVal[second];
    });
    sort(minusOrder.begin(), minusOrder.end(), [](int first, int second) {
        return minusVal[first] < minusVal[second];
    });
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (canReach(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> nodeCnt >> edgeLen && (nodeCnt != 0 || edgeLen != 0)) {
        graph.assign(nodeCnt + 1, vector<Edge>());
        for (int i = 1; i < nodeCnt; i++) {
            int from, to;
            long long len;
            cin >> from >> to >> len;
            graph[from].push_back({to, len});
            graph[to].push_back({from, len});
        }
        cout << solve() << '\n';
    }
    return 0;
}
