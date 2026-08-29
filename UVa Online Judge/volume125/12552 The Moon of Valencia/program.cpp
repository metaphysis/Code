#include <bits/stdc++.h>
using namespace std;

const long double INF = 1e100L;
const long double EPS = 1e-9L;
const long double GRADE_EPS = 0.1L;
const long double STAY_TIME = 15.0L;

struct Place {
    long double x, y, grade;
    string id;
};

struct State {
    unsigned long long used;
    int now;
    long double grade, time, heuristic;
    vector<int> path;
    bool operator <(const State &other) const {
        return heuristic > other.heuristic;
    }
};

int placeCount, targetNode;
long double totalTime, requiredGrade;
vector<Place> places;
vector<vector<int>> graph;
vector<vector<long double>> edgeTime, shortestTime;
unordered_map<string, int> idMap;

long double getDistance(int u, int v) {
    long double dx = places[u].x - places[v].x, dy = places[u].y - places[v].y;
    return sqrt(dx * dx + dy * dy);
}

long double parseTime(const string &text) {
    size_t pos = text.find(':');
    int hour = stoi(text.substr(0, pos)), minute = stoi(text.substr(pos + 1));
    return hour * 60.0L + minute;
}

void buildShortestTime() {
    shortestTime.assign(placeCount, vector<long double>(placeCount, INF));
    for (int i = 0; i < placeCount; ++i)
        shortestTime[i][i] = 0.0L;
    for (int u = 0; u < placeCount; ++u)
        for (int v : graph[u])
            shortestTime[u][v] = min(shortestTime[u][v], edgeTime[u][v]);
    for (int k = 0; k < placeCount; ++k) {
        for (int i = 0; i < placeCount; ++i) {
            if (shortestTime[i][k] >= INF / 2)
                continue;
            for (int j = 0; j < placeCount; ++j) {
                if (shortestTime[k][j] >= INF / 2)
                    continue;
                shortestTime[i][j] = min(shortestTime[i][j], shortestTime[i][k] + shortestTime[k][j]);
            }
        }
    }
}

long double getHeuristic(const State &state) {
    if (shortestTime[state.now][targetNode] >= INF / 2)
        return INF;
    long double optimisticGrade = state.grade - shortestTime[state.now][targetNode];
    return fabsl(requiredGrade - optimisticGrade);
}

bool canReachTarget(int node, long double currentTime) {
    if (shortestTime[node][targetNode] >= INF / 2)
        return false;
    return currentTime + shortestTime[node][targetNode] <= totalTime + EPS;
}

bool isValidAnswer(long double grade) {
    return fabsl(grade - requiredGrade) < GRADE_EPS;
}

bool solveArrival(int startNode, int endNode, long double targetGrade, State &answer) {
    targetNode = endNode;
    requiredGrade = targetGrade;
    priority_queue<State> pq;
    unsigned long long startBit = 1ULL << startNode;
    State withoutEntry, withEntry;
    withoutEntry.used = startBit;
    withoutEntry.now = startNode;
    withoutEntry.grade = withoutEntry.time = 0.0L;
    withoutEntry.path.push_back(startNode + 1);
    withoutEntry.heuristic = getHeuristic(withoutEntry);
    pq.push(withoutEntry);
    if (STAY_TIME <= totalTime + EPS) {
        withEntry.used = startBit;
        withEntry.now = startNode;
        withEntry.grade = places[startNode].grade;
        withEntry.time = STAY_TIME;
        withEntry.path.push_back(startNode + 1);
        withEntry.heuristic = getHeuristic(withEntry);
        pq.push(withEntry);
    }
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        if (current.now == targetNode && isValidAnswer(current.grade)) {
            answer = current;
            return true;
        }
        if (!canReachTarget(current.now, current.time))
            continue;
        for (int next : graph[current.now]) {
            unsigned long long bit = 1ULL << next;
            if (current.used & bit)
                continue;
            long double moveTime = edgeTime[current.now][next], arrivalTime = current.time + moveTime;
            if (arrivalTime > totalTime + EPS)
                continue;
            if (next == targetNode) {
                long double finalGrade = current.grade - moveTime;
                if (!isValidAnswer(finalGrade))
                    continue;
                State finalState = current;
                finalState.used |= bit;
                finalState.now = next;
                finalState.time = arrivalTime;
                finalState.grade = finalGrade;
                finalState.path.push_back(next + 1);
                finalState.heuristic = 0.0L;
                answer = finalState;
                return true;
            }
            unsigned long long nextUsed = current.used | bit;
            if (canReachTarget(next, arrivalTime)) {
                State passState = current;
                passState.used = nextUsed;
                passState.now = next;
                passState.time = arrivalTime;
                passState.grade = current.grade - moveTime;
                passState.path.push_back(-(next + 1));
                passState.heuristic = getHeuristic(passState);
                pq.push(passState);
            }
            long double enterTime = arrivalTime + STAY_TIME;
            if (enterTime > totalTime + EPS || !canReachTarget(next, enterTime))
                continue;
            State enterState = current;
            enterState.used = nextUsed;
            enterState.now = next;
            enterState.time = enterTime;
            enterState.grade = current.grade - moveTime + places[next].grade;
            enterState.path.push_back(next + 1);
            enterState.heuristic = getHeuristic(enterState);
            pq.push(enterState);
        }
    }
    return false;
}

void printAnswer(const State &answer) {
    cout << "PATH FOUND: " << fixed << setprecision(3) << static_cast<double>(answer.grade);
    for (int i = 0; i < static_cast<int>(answer.path.size()); ++i) {
        cout << ' ';
        int value = answer.path[i];
        if (value < 0)
            cout << '!';
        cout << places[abs(value) - 1].id;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string token, pendingMap;
    bool hasPendingMap = false;
    int caseNumber = 0;
    while (true) {
        if (hasPendingMap) {
            token = pendingMap;
            hasPendingMap = false;
        } else if (!(cin >> token)) {
            break;
        }
        if (token != "MAP")
            continue;
        int pathCount;
        cin >> placeCount >> pathCount;
        places.assign(placeCount, Place());
        graph.assign(placeCount, vector<int>());
        edgeTime.assign(placeCount, vector<long double>(placeCount, INF));
        idMap.clear();
        idMap.reserve(placeCount * 2);
        for (int i = 0; i < placeCount; ++i) {
            string description;
            cin >> places[i].x >> places[i].y >> places[i].grade >> places[i].id;
            getline(cin, description);
            idMap[places[i].id] = i;
        }
        for (int i = 0; i < pathCount; ++i) {
            string firstId, secondId;
            cin >> firstId >> secondId;
            int u = idMap[firstId], v = idMap[secondId];
            long double time = getDistance(u, v) * 15.0L;
            graph[u].push_back(v);
            graph[v].push_back(u);
            edgeTime[u][v] = min(edgeTime[u][v], time);
            edgeTime[v][u] = min(edgeTime[v][u], time);
        }
        cin >> token;
        buildShortestTime();
        cout << "MAP " << ++caseNumber << '\n';
        while (cin >> token) {
            if (token == "MAP") {
                pendingMap = token;
                hasPendingMap = true;
                break;
            }
            string departureTime = token, departureId, arrivalTime, arrivalId;
            long double targetGrade;
            cin >> departureId >> arrivalTime >> arrivalId >> targetGrade;
            long double begin = parseTime(departureTime), end = parseTime(arrivalTime);
            totalTime = end - begin;
            if (totalTime < 0.0L)
                totalTime += 24.0L * 60.0L;
            int startNode = idMap[departureId], endNode = idMap[arrivalId];
            State answer;
            if (solveArrival(startNode, endNode, targetGrade, answer))
                printAnswer(answer);
            else
                cout << "Impossible!\n";
        }
    }
    return 0;
}
