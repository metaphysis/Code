#include <bits/stdc++.h>
using namespace std;

using Vec = array<int, 3>;

struct Edge {
    int to, pos, fold;
};

struct Pose {
    Vec pos, u, v;
};

Vec addVec(const Vec &a, const Vec &b) {
    return Vec{a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

Vec subVec(const Vec &a, const Vec &b) {
    return Vec{a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

Vec mulVec(const Vec &a, int k) {
    return Vec{a[0] * k, a[1] * k, a[2] * k};
}

Vec crossVec(const Vec &a, const Vec &b) {
    return Vec{
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    };
}

Pose getPose(const Pose &cur, int pos, int fold) {
    Pose next = cur;
    if (fold != 0) {
        Vec dir = mulVec(crossVec(cur.u, cur.v), fold == 1 ? 1 : -1);
        if (pos == 0) next.v = dir;
        else if (pos == 1) next.u = mulVec(dir, -1);
        else if (pos == 2) next.v = mulVec(dir, -1);
        else next.u = dir;
    }
    if (pos == 0) next.pos = addVec(cur.pos, cur.v);
    else if (pos == 1) next.pos = subVec(cur.pos, next.u);
    else if (pos == 2) next.pos = subVec(cur.pos, next.v);
    else next.pos = addVec(cur.pos, cur.u);
    return next;
}

int solve(const vector<vector<Edge>> &graph) {
    int n = static_cast<int>(graph.size());
    vector<Pose> poses(n);
    vector<int> vis(n, 0);
    queue<int> poseQue;
    poses[0] = Pose{Vec{0, 0, 0}, Vec{1, 0, 0}, Vec{0, 1, 0}};
    vis[0] = 1;
    poseQue.push(0);
    while (!poseQue.empty()) {
        int cur = poseQue.front();
        poseQue.pop();
        for (const Edge &edge : graph[cur]) {
            Pose next = getPose(poses[cur], edge.pos, edge.fold);
            if (!vis[edge.to]) {
                poses[edge.to] = next;
                vis[edge.to] = 1;
                poseQue.push(edge.to);
            } else if (poses[edge.to].pos != next.pos || poses[edge.to].u != next.u || poses[edge.to].v != next.v) return -1;
        }
    }
    vector<array<Vec, 4>> vertices(n);
    Vec minPos = {0, 0, 0}, maxPos = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        vertices[i][0] = poses[i].pos;
        vertices[i][1] = addVec(poses[i].pos, poses[i].u);
        vertices[i][2] = addVec(poses[i].pos, poses[i].v);
        vertices[i][3] = addVec(vertices[i][1], poses[i].v);
        for (const Vec &point : vertices[i]) {
            for (int axis = 0; axis < 3; axis++) {
                minPos[axis] = min(minPos[axis], point[axis]);
                maxPos[axis] = max(maxPos[axis], point[axis]);
            }
        }
    }
    Vec size = subVec(maxPos, minPos), offset;
    for (int axis = 0; axis < 3; axis++) {
        size[axis] += 2;
        offset[axis] = 1 - minPos[axis];
    }
    for (auto &square : vertices) for (Vec &point : square) point = addVec(point, offset);
    int cellCnt = size[0] * size[1] * size[2];
    vector<int> wall(cellCnt * 3, 0), edgeCnt(cellCnt * 3, 0), color(cellCnt, -1);
    auto getId = [&](const Vec &point) -> int {
        return (point[0] * size[1] + point[1]) * size[2] + point[2];
    };
    auto getEdgeKey = [&](const Vec &a, const Vec &b) -> int {
        Vec low;
        int axis = 0;
        for (int k = 0; k < 3; k++) {
            low[k] = min(a[k], b[k]);
            if (a[k] != b[k]) axis = k;
        }
        return getId(low) * 3 + axis;
    };
    const int edgeStart[4] = {0, 0, 1, 2}, edgeEnd[4] = {1, 2, 3, 3};
    const int hingeStart[4] = {2, 0, 0, 1}, hingeEnd[4] = {3, 2, 1, 3};
    for (int i = 0; i < n; i++) {
        Vec low = vertices[i][0];
        int axis = 0;
        for (int k = 0; k < 3; k++) {
            for (int j = 1; j < 4; j++) low[k] = min(low[k], vertices[i][j][k]);
            if (poses[i].u[k] == 0 && poses[i].v[k] == 0) axis = k;
        }
        // 面记录在法向坐标较小的格子的正方向上
        low[axis]--;
        int key = getId(low) * 3 + axis;
        if (wall[key]) return -1;
        wall[key] = 1;
        for (int j = 0; j < 4; j++) {
            int edgeKey = getEdgeKey(vertices[i][edgeStart[j]], vertices[i][edgeEnd[j]]);
            edgeCnt[edgeKey]++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (const Edge &edge : graph[i]) {
            if (edge.fold != 0 || i > edge.to) continue;
            int key = getEdgeKey(vertices[i][hingeStart[edge.pos]], vertices[i][hingeEnd[edge.pos]]);
            if (edgeCnt[key] == 4) return -1;
        }
    }
    queue<Vec> cellQue;
    color[0] = 0;
    cellQue.push(Vec{0, 0, 0});
    while (!cellQue.empty()) {
        Vec cur = cellQue.front();
        int curId = getId(cur);
        cellQue.pop();
        for (int axis = 0; axis < 3; axis++) {
            for (int step = -1; step <= 1; step += 2) {
                Vec next = cur;
                next[axis] += step;
                if (next[axis] < 0 || next[axis] >= size[axis]) continue;
                int nextId = getId(next), wallId = (step == 1 ? curId : nextId) * 3 + axis;
                int nextColor = color[curId] ^ wall[wallId];
                if (color[nextId] == -1) {
                    color[nextId] = nextColor;
                    cellQue.push(next);
                } else if (color[nextId] != nextColor) return -1;
            }
        }
    }
    int volume = 0;
    for (int value : color) if (value == 1) volume++;
    return volume;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    while (testCnt--) {
        int n, e;
        cin >> n >> e;
        vector<vector<Edge>> graph(n);
        for (int i = 0; i < e; i++) {
            int a, b, pos, fold;
            cin >> a >> b >> pos >> fold;
            graph[a].push_back(Edge{b, pos, fold});
            graph[b].push_back(Edge{a, (pos + 2) % 4, fold});
        }
        int volume = solve(graph);
        if (volume < 0) cout << "Not a closed surface\n";
        else cout << "Closed surface, volume=" << volume << '\n';
    }
    return 0;
}
