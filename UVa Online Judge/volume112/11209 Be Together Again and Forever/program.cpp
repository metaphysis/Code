// Be Together Again and Forever
// UVa ID: 11209
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

const int infinityValue = 1e9;

struct Edge {
    int to;
    int weight;
};

struct SearchState {
    int currentJ;
    int currentW;
    int lengthJ;
    int lengthW;
    array<unsigned long long, 4> visited;

    bool operator==(const SearchState &other) const {
        return currentJ == other.currentJ && currentW == other.currentW && lengthJ == other.lengthJ && lengthW == other.lengthW && visited == other.visited;
    }
};

struct SearchStateHash {
    size_t operator()(const SearchState &state) const {
        size_t result = state.currentJ;
        result = result * 233 + state.currentW;
        result = result * 233 + state.lengthJ;
        result = result * 233 + state.lengthW;
        for (unsigned long long value : state.visited)
            result ^= value + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
        return result;
    }
};

int cityCount;
int roadCount;
int startJ;
int startW;
int targetLength;
vector<vector<Edge>> graph;
vector<vector<int>> shortestDistance;
array<unsigned long long, 4> visitedMask;
vector<int> routeJ;
vector<int> routeW;
unordered_set<SearchState, SearchStateHash> failedStates;

bool isVisited(int city) {
    int index = city >> 6;
    int offset = city & 63;
    return (visitedMask[index] >> offset) & 1ULL;
}

void setVisited(int city, bool value) {
    int index = city >> 6;
    int offset = city & 63;
    if (value)
        visitedMask[index] |= 1ULL << offset;
    else
        visitedMask[index] &= ~(1ULL << offset);
}

bool canReachTarget(int currentJ, int currentW, int lengthJ, int lengthW) {
    for (int city = 1; city <= cityCount; city++)
        if (lengthJ + shortestDistance[currentJ][city] <= targetLength && lengthW + shortestDistance[currentW][city] <= targetLength)
            return true;
    return false;
}

bool searchRoute(int currentJ, int currentW, int lengthJ, int lengthW) {
    if (currentJ == currentW)
        return lengthJ == targetLength && lengthW == targetLength;
    if (lengthJ > targetLength || lengthW > targetLength)
        return false;
    if (!canReachTarget(currentJ, currentW, lengthJ, lengthW))
        return false;
    SearchState state;
    state.currentJ = currentJ;
    state.currentW = currentW;
    state.lengthJ = lengthJ;
    state.lengthW = lengthW;
    state.visited = visitedMask;
    if (failedStates.count(state))
        return false;
    if (lengthJ <= lengthW) {
        for (const Edge &edge : graph[currentJ]) {
            int nextLength = lengthJ + edge.weight;
            if (edge.to == currentW) {
                if (nextLength == targetLength && lengthW == targetLength) {
                    routeJ.push_back(edge.to);
                    return true;
                }
                continue;
            }
            if (isVisited(edge.to) || nextLength > targetLength)
                continue;
            setVisited(edge.to, true);
            routeJ.push_back(edge.to);
            if (searchRoute(edge.to, currentW, nextLength, lengthW))
                return true;
            routeJ.pop_back();
            setVisited(edge.to, false);
        }
    }
    if (lengthW <= lengthJ) {
        for (const Edge &edge : graph[currentW]) {
            int nextLength = lengthW + edge.weight;
            if (edge.to == currentJ) {
                if (nextLength == targetLength && lengthJ == targetLength) {
                    routeW.push_back(edge.to);
                    return true;
                }
                continue;
            }
            if (isVisited(edge.to) || nextLength > targetLength)
                continue;
            setVisited(edge.to, true);
            routeW.push_back(edge.to);
            if (searchRoute(currentJ, edge.to, lengthJ, nextLength))
                return true;
            routeW.pop_back();
            setVisited(edge.to, false);
        }
    }
    failedStates.insert(state);
    return false;
}

void buildShortestDistance() {
    shortestDistance.assign(cityCount + 1, vector<int>(cityCount + 1, infinityValue));
    for (int city = 1; city <= cityCount; city++)
        shortestDistance[city][city] = 0;
    for (int city = 1; city <= cityCount; city++)
        for (const Edge &edge : graph[city])
            shortestDistance[city][edge.to] = min(shortestDistance[city][edge.to], edge.weight);
    for (int middle = 1; middle <= cityCount; middle++)
        for (int from = 1; from <= cityCount; from++)
            for (int to = 1; to <= cityCount; to++)
                shortestDistance[from][to] = min(shortestDistance[from][to], shortestDistance[from][middle] + shortestDistance[middle][to]);
}

bool solveCase() {
    buildShortestDistance();
    int lowerBound = (shortestDistance[startJ][startW] + 1) / 2;
    int upperBound = 10 * (cityCount - 1);
    for (targetLength = lowerBound; targetLength <= upperBound; targetLength++) {
        visitedMask.fill(0);
        setVisited(startJ, true);
        setVisited(startW, true);
        routeJ.clear();
        routeW.clear();
        routeJ.push_back(startJ);
        routeW.push_back(startW);
        failedStates.clear();
        if (searchRoute(startJ, startW, 0, 0))
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 0;
    while (cin >> cityCount) {
        if (cityCount == 0)
            break;
        cin >> roadCount >> startJ >> startW;
        graph.assign(cityCount + 1, vector<Edge>());
        for (int i = 0; i < roadCount; i++) {
            int from;
            int to;
            int weight;
            cin >> from >> to >> weight;
            graph[from].push_back({to, weight});
            graph[to].push_back({from, weight});
        }
        for (int city = 1; city <= cityCount; city++)
            sort(graph[city].begin(), graph[city].end(), [](const Edge &first, const Edge &second) {
                return first.weight < second.weight;
            });
        solveCase();
        cout << "Case " << ++caseNumber << ": " << targetLength << '\n';
        cout << routeJ.size();
        for (int city : routeJ)
            cout << ' ' << city;
        cout << '\n';
        cout << routeW.size();
        for (int city : routeW)
            cout << ' ' << city;
        cout << '\n';
    }
    return 0;
}
