#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

struct Road {
    int from, to;
    int cost[5];
};

struct Path {
    unsigned long long low, high;
    long long cost;
    vector<int> roads;
};

int n, m, k;
Road roadList[105];
int sourceCity[5], targetCity[5];
vector<int> graph[16];
vector<Path> pathList[5];
vector<int> currentRoads;
vector<int> currentOrder;
vector<int> currentPath[5];
vector<int> answerPath[5];
unsigned long long currentLow, currentHigh;
long long bestCost;
long long suffixCost[6];
int visitMask;
int pathType;

void enumeratePath(int city, long long cost) {
    if (city == targetCity[pathType]) {
        Path path;
        path.low = 0;
        path.high = 0;
        path.cost = cost;
        path.roads = currentRoads;
        for (int edgeId : currentRoads) {
            if (edgeId < 64)
                path.low |= 1ULL << edgeId;
            else
                path.high |= 1ULL << (edgeId - 64);
        }
        pathList[pathType].push_back(path);
        return;
    }
    for (int edgeId : graph[city]) {
        int nextCity = roadList[edgeId].to;
        if ((visitMask >> nextCity) & 1)
            continue;
        visitMask |= 1 << nextCity;
        currentRoads.push_back(edgeId);
        enumeratePath(nextCity, cost + roadList[edgeId].cost[pathType]);
        currentRoads.pop_back();
        visitMask ^= 1 << nextCity;
    }
}

void removeDuplicatePath(int type) {
    map<pair<unsigned long long, unsigned long long>, Path> bestMap;
    for (const Path &path : pathList[type]) {
        pair<unsigned long long, unsigned long long> key = make_pair(path.low, path.high);
        if (!bestMap.count(key) || path.cost < bestMap[key].cost)
            bestMap[key] = path;
    }
    pathList[type].clear();
    for (auto &item : bestMap)
        pathList[type].push_back(item.second);
    sort(pathList[type].begin(), pathList[type].end(), [](const Path &a, const Path &b) {
        return a.cost < b.cost;
    });
}

void findAnswer(int index, long long cost) {
    if (index == k) {
        if (cost < bestCost) {
            bestCost = cost;
            for (int type = 0; type < k; type++)
                answerPath[type] = currentPath[type];
        }
        return;
    }
    if (cost + suffixCost[index] >= bestCost)
        return;
    int type = currentOrder[index];
    for (const Path &path : pathList[type]) {
        if ((path.low & currentLow) || (path.high & currentHigh))
            continue;
        if (cost + path.cost + suffixCost[index + 1] >= bestCost)
            continue;
        unsigned long long oldLow = currentLow, oldHigh = currentHigh;
        currentLow |= path.low;
        currentHigh |= path.high;
        currentPath[type] = path.roads;
        findAnswer(index + 1, cost + path.cost);
        currentLow = oldLow;
        currentHigh = oldHigh;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> k) {
        if (n == 0 && m == 0 && k == 0)
            break;
        for (int i = 0; i < n; i++)
            graph[i].clear();
        for (int i = 0; i < m; i++) {
            cin >> roadList[i].from >> roadList[i].to;
            roadList[i].from--;
            roadList[i].to--;
            for (int j = 0; j < k; j++)
                cin >> roadList[i].cost[j];
            graph[roadList[i].from].push_back(i);
        }
        for (int i = 0; i < k; i++) {
            cin >> sourceCity[i] >> targetCity[i];
            sourceCity[i]--;
            targetCity[i]--;
        }
        bool possible = true;
        for (int type = 0; type < k; type++) {
            pathList[type].clear();
            currentRoads.clear();
            pathType = type;
            visitMask = 1 << sourceCity[type];
            enumeratePath(sourceCity[type], 0);
            removeDuplicatePath(type);
            if (pathList[type].empty())
                possible = false;
        }
        if (!possible) {
            cout << -1 << '\n';
            continue;
        }
        currentOrder.clear();
        for (int type = 0; type < k; type++)
            currentOrder.push_back(type);
        sort(currentOrder.begin(), currentOrder.end(), [](int a, int b) {
            return pathList[a].size() < pathList[b].size();
        });
        suffixCost[k] = 0;
        for (int i = k - 1; i >= 0; i--)
            suffixCost[i] = suffixCost[i + 1] + pathList[currentOrder[i]][0].cost;
        bestCost = inf;
        currentLow = 0;
        currentHigh = 0;
        for (int type = 0; type < k; type++) {
            currentPath[type].clear();
            answerPath[type].clear();
        }
        findAnswer(0, 0);
        if (bestCost == inf) {
            cout << -1 << '\n';
            continue;
        }
        cout << bestCost << '\n';
        for (int type = 0; type < k; type++) {
            cout << answerPath[type].size();
            for (int edgeId : answerPath[type])
                cout << ' ' << edgeId + 1;
            cout << '\n';
        }
    }
    return 0;
}
