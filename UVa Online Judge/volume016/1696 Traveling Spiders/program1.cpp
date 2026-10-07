// Traveling Spiders
// UVa ID: 1696
// Verdict: Accepted
// Submission Date: 2026-10-07
// UVa Run Time: 1.390s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, z;
};

int n, total;
vector<Point> points;
vector<vector<int>> graph;
unordered_map<long long, int> pointId;
mt19937 randomEngine((unsigned)chrono::steady_clock::now().time_since_epoch().count());

long long getKey(int x, int y, int z) {
    long long base = 2LL * n + 1;
    return (long long)x * base * base + (long long)y * base + z;
}

bool inRange(int x, int y, int z) {
    return 0 <= x && x <= 2 * n && 0 <= y && y <= 2 * n && 0 <= z && z <= 2 * n;
}

void buildPoints() {
    points.clear();
    pointId.clear();
    points.reserve(6 * n * n);
    pointId.reserve(12 * n * n);
    for (int face = 0; face < 6; face++) {
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                int x, y, z;
                if (face == 0) {
                    x = 2 * col + 1;
                    y = 2 * row + 1;
                    z = 2 * n;
                } else if (face == 1) {
                    x = 2 * col + 1;
                    y = 2 * n;
                    z = 2 * row + 1;
                } else if (face == 2) {
                    x = 0;
                    y = 2 * row + 1;
                    z = 2 * col + 1;
                } else if (face == 3) {
                    x = 2 * col + 1;
                    y = 2 * row + 1;
                    z = 0;
                } else if (face == 4) {
                    x = 2 * col + 1;
                    y = 0;
                    z = 2 * row + 1;
                } else {
                    x = 2 * n;
                    y = 2 * row + 1;
                    z = 2 * col + 1;
                }
                int id = (int)points.size();
                points.push_back({x, y, z});
                pointId[getKey(x, y, z)] = id;
            }
        }
    }
    total = (int)points.size();
}

void buildGraph() {
    graph.assign(total, {});
    const int directions[18][3] = {
        {-2, 0, 0}, {2, 0, 0}, {0, -2, 0}, {0, 2, 0}, {0, 0, -2}, {0, 0, 2},
        {-1, -1, 0}, {-1, 1, 0}, {1, -1, 0}, {1, 1, 0},
        {-1, 0, -1}, {-1, 0, 1}, {1, 0, -1}, {1, 0, 1},
        {0, -1, -1}, {0, -1, 1}, {0, 1, -1}, {0, 1, 1}
    };
    for (int id = 0; id < total; id++) {
        int x = points[id].x, y = points[id].y, z = points[id].z;
        for (const auto &direction : directions) {
            int nx = x + direction[0], ny = y + direction[1], nz = z + direction[2];
            if (!inRange(nx, ny, nz))
                continue;
            auto iter = pointId.find(getKey(nx, ny, nz));
            if (iter != pointId.end())
                graph[id].push_back(iter->second);
        }
    }
}

bool adjacent(int a, int b) {
    return find(graph[a].begin(), graph[a].end(), b) != graph[a].end();
}

vector<int> getFaceCycle(int offset) {
    vector<int> cycle;
    cycle.reserve(n * n);
    for (int col = 0; col < n; col++)
        cycle.push_back(offset + col);
    for (int row = 1; row < n; row++) {
        if (row % 2 == 1) {
            int begin = row == n - 1 ? 0 : 1;
            for (int col = n - 1; col >= begin; col--)
                cycle.push_back(offset + row * n + col);
        } else {
            for (int col = 1; col < n; col++)
                cycle.push_back(offset + row * n + col);
        }
    }
    for (int row = n - 2; row >= 1; row--)
        cycle.push_back(offset + row * n);
    return cycle;
}

vector<int> reverseCycle(const vector<int> &cycle) {
    vector<int> result = cycle;
    reverse(result.begin(), result.end());
    return result;
}

vector<int> spliceCycles(const vector<int> &first, int a, int b, const vector<int> &second, int c, int d) {
    int firstSize = (int)first.size(), secondSize = (int)second.size();
    int firstA = -1, firstB = -1, secondC = -1, secondD = -1;
    for (int i = 0; i < firstSize; i++) {
        if (first[i] == a)
            firstA = i;
        if (first[i] == b)
            firstB = i;
    }
    for (int i = 0; i < secondSize; i++) {
        if (second[i] == c)
            secondC = i;
        if (second[i] == d)
            secondD = i;
    }
    vector<int> result;
    result.reserve(firstSize + secondSize);
    result.push_back(a);
    result.push_back(c);
    int current = (secondC - 1 + secondSize) % secondSize;
    while (true) {
        result.push_back(second[current]);
        if (current == secondD)
            break;
        current = (current - 1 + secondSize) % secondSize;
    }
    result.push_back(b);
    current = (firstB + 1) % firstSize;
    while (current != firstA) {
        result.push_back(first[current]);
        current = (current + 1) % firstSize;
    }
    return result;
}

vector<int> mergeCycles(const vector<int> &first, const vector<int> &second) {
    int firstSize = (int)first.size(), secondSize = (int)second.size();
    for (int i = 0; i < firstSize; i++) {
        int a = first[i], b = first[(i + 1) % firstSize];
        for (int j = 0; j < secondSize; j++) {
            int c = second[j], d = second[(j + 1) % secondSize];
            if (adjacent(a, c) && adjacent(b, d))
                return spliceCycles(first, a, b, second, c, d);
            if (adjacent(a, d) && adjacent(b, c)) {
                vector<int> reversed = reverseCycle(second);
                return spliceCycles(first, a, b, reversed, d, c);
            }
        }
    }
    return {};
}

vector<int> buildHamiltonCycle() {
    if (n == 2)
        return {0, 9, 8, 10, 11, 2, 6, 4, 14, 12, 13, 15, 5, 7, 3, 23, 22, 20, 21, 1, 19, 17, 16, 18};
    int faceSize = n * n;
    vector<int> front = getFaceCycle(0), top = getFaceCycle(faceSize), left = getFaceCycle(2 * faceSize);
    vector<int> back = getFaceCycle(3 * faceSize), bottom = getFaceCycle(4 * faceSize), right = getFaceCycle(5 * faceSize);
    front = mergeCycles(front, top);
    front = mergeCycles(front, left);
    back = mergeCycles(back, bottom);
    back = mergeCycles(back, right);
    return mergeCycles(front, back);
}

vector<int> rotateCycleToStart(const vector<int> &cycle, int start) {
    int position = 0;
    while (cycle[position] != start)
        position++;
    vector<int> result;
    result.reserve(cycle.size());
    for (int i = 0; i < (int)cycle.size(); i++)
        result.push_back(cycle[(position + i) % cycle.size()]);
    return result;
}

bool checkPath(const vector<int> &path, int start, int target) {
    if ((int)path.size() != total || path.front() != start || path.back() != target)
        return false;
    vector<bool> used(total, false);
    for (int i = 0; i < total; i++) {
        int id = path[i];
        if (used[id])
            return false;
        used[id] = true;
        if (i > 0 && !adjacent(path[i - 1], id))
            return false;
    }
    return true;
}

bool findPath(int start, int target, const vector<int> &cycle, vector<int> &answer) {
    vector<int> initial = rotateCycleToStart(cycle, start);
    int maxStep = max(10000, total * 200);
    while (true) {
        vector<int> path = initial, position(total);
        for (int i = 0; i < total; i++)
            position[path[i]] = i;
        int endpoint = path.back();
        for (int step = 0; step < maxStep; step++) {
            if (endpoint == target && checkPath(path, start, target)) {
                answer = move(path);
                return true;
            }
            vector<int> choices;
            for (int neighbor : graph[endpoint]) {
                int index = position[neighbor];
                if (index < total - 2)
                    choices.push_back(index);
            }
            if (choices.empty())
                break;
            int index = choices[randomEngine() % choices.size()];
            int newEndpoint = path[index + 1];
            reverse(path.begin() + index + 1, path.end());
            for (int i = index + 1; i < total; i++)
                position[path[i]] = i;
            endpoint = newEndpoint;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> n;
        int sx, sy, sz, tx, ty, tz;
        cin >> sx >> sy >> sz >> tx >> ty >> tz;
        buildPoints();
        buildGraph();
        int start = pointId[getKey(sx, sy, sz)], target = pointId[getKey(tx, ty, tz)];
        vector<int> cycle = buildHamiltonCycle(), answer;
        findPath(start, target, cycle, answer);
        cout << 1 << '\n';
        for (int id : answer)
            cout << points[id].x << ' ' << points[id].y << ' ' << points[id].z << '\n';
    }
    return 0;
}
