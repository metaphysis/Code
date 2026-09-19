#include <bits/stdc++.h>
using namespace std;

struct Vec {
    int x, y, z;
};

struct Face {
    Vec n, u, v;
    bool used;
};

struct Shape {
    vector<pair<int, int>> cells;
    int maxR, maxC;
    int edge[6][6][2];
};

vector<Shape> shapes;
vector<pair<int, int>> buildCells;
set<string> shapeSet;

Vec negVec(Vec a) {
    return {-a.x, -a.y, -a.z};
}

Vec addVec(Vec a, Vec b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

bool sameVec(Vec a, Vec b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

vector<pair<int, int>> normalizeShape(vector<pair<int, int>> cells) {
    int minR = INT_MAX, minC = INT_MAX;
    for (auto p : cells) {
        minR = min(minR, p.first);
        minC = min(minC, p.second);
    }
    for (auto &p : cells) {
        p.first -= minR;
        p.second -= minC;
    }
    sort(cells.begin(), cells.end());
    return cells;
}

string getShapeKey(const vector<pair<int, int>> &cells) {
    string key;
    for (auto p : cells)
        key += to_string(p.first) + "," + to_string(p.second) + ";";
    return key;
}

Face getNextFace(Face cur, int dr, int dc) {
    Face next;
    next.used = true;
    if (dc == 1) {
        next.n = cur.u;
        next.u = negVec(cur.n);
        next.v = cur.v;
    } else if (dc == -1) {
        next.n = negVec(cur.u);
        next.u = cur.n;
        next.v = cur.v;
    } else if (dr == 1) {
        next.n = cur.v;
        next.u = cur.u;
        next.v = negVec(cur.n);
    } else {
        next.n = negVec(cur.v);
        next.u = cur.u;
        next.v = cur.n;
    }
    return next;
}

int getEdgeId(const Face &face, int side) {
    Vec p;
    if (side == 0)
        p = addVec(face.n, negVec(face.v));
    else if (side == 1)
        p = addVec(face.n, face.v);
    else if (side == 2)
        p = addVec(face.n, negVec(face.u));
    else
        p = addVec(face.n, face.u);
    return (p.x + 1) * 9 + (p.y + 1) * 3 + p.z + 1;
}

bool getFaces(const vector<pair<int, int>> &cells, vector<Face> &faces) {
    map<pair<int, int>, int> position;
    for (int i = 0; i < 6; i++)
        position[cells[i]] = i;
    faces.assign(6, {});
    for (auto &face : faces)
        face.used = false;
    faces[0] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}, true};
    static int dr[4] = {-1, 1, 0, 0};
    static int dc[4] = {0, 0, -1, 1};
    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int id = que.front();
        que.pop();
        int r = cells[id].first, c = cells[id].second;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            auto it = position.find({nr, nc});
            if (it == position.end())
                continue;
            int nextId = it->second;
            Face next = getNextFace(faces[id], dr[d], dc[d]);
            if (!faces[nextId].used) {
                faces[nextId] = next;
                que.push(nextId);
            } else if (!sameVec(faces[nextId].n, next.n) || !sameVec(faces[nextId].u, next.u) || !sameVec(faces[nextId].v, next.v)) {
                return false;
            }
        }
    }
    for (int i = 0; i < 6; i++)
        if (!faces[i].used)
            return false;
    for (int i = 0; i < 6; i++)
        for (int j = i + 1; j < 6; j++)
            if (sameVec(faces[i].n, faces[j].n))
                return false;
    return true;
}

void saveShape(const vector<pair<int, int>> &cells, const vector<Face> &faces) {
    Shape shape;
    shape.cells = cells;
    shape.maxR = shape.maxC = 0;
    for (auto p : cells) {
        shape.maxR = max(shape.maxR, p.first);
        shape.maxC = max(shape.maxC, p.second);
    }
    static int sideA[6] = {0, 2, 0, 0, 1, 2};
    static int sideB[6] = {1, 3, 2, 3, 3, 1};
    for (int i = 0; i < 6; i++) {
        int left = sideA[i], right = sideB[i];
        for (int j = 0; j < 6; j++) {
            shape.edge[j][i][0] = getEdgeId(faces[j], left);
            shape.edge[j][i][1] = getEdgeId(faces[j], right);
        }
    }
    shapes.push_back(shape);
}

void buildShapes() {
    if ((int)buildCells.size() == 6) {
        vector<pair<int, int>> cells = normalizeShape(buildCells);
        string key = getShapeKey(cells);
        if (!shapeSet.insert(key).second)
            return;
        vector<Face> faces;
        if (getFaces(cells, faces))
            saveShape(cells, faces);
        return;
    }
    static int dr[4] = {-1, 1, 0, 0};
    static int dc[4] = {0, 0, -1, 1};
    set<pair<int, int>> nextCells;
    for (auto p : buildCells) {
        for (int d = 0; d < 4; d++) {
            pair<int, int> next = {p.first + dr[d], p.second + dc[d]};
            bool exists = false;
            for (auto q : buildCells)
                if (q == next)
                    exists = true;
            if (!exists)
                nextCells.insert(next);
        }
    }
    for (auto p : nextCells) {
        buildCells.push_back(p);
        buildShapes();
        buildCells.pop_back();
    }
}

int findRoot(int x, int parent[]) {
    if (parent[x] == x)
        return x;
    return parent[x] = findRoot(parent[x], parent);
}

void unite(int x, int y, int parent[]) {
    x = findRoot(x, parent);
    y = findRoot(y, parent);
    if (x != y)
        parent[x] = y;
}

bool checkLoop(const Shape &shape, int sr, int sc, const vector<vector<int>> &grid) {
    int parent[27], degree[27] = {};
    for (int i = 0; i < 27; i++)
        parent[i] = i;
    for (int i = 0; i < 6; i++) {
        int r = sr + shape.cells[i].first;
        int c = sc + shape.cells[i].second;
        int type = grid[r][c];
        int a = shape.edge[i][type][0];
        int b = shape.edge[i][type][1];
        degree[a]++;
        degree[b]++;
        unite(a, b, parent);
    }
    int start = -1;
    for (int i = 0; i < 27; i++) {
        if (degree[i] != 0 && degree[i] != 2)
            return false;
        if (degree[i] != 0 && start == -1)
            start = i;
    }
    if (start == -1)
        return false;
    int root = findRoot(start, parent);
    for (int i = 0; i < 27; i++)
        if (degree[i] != 0 && findRoot(i, parent) != root)
            return false;
    return true;
}

long long solveCase(int rowCount, int colCount, const vector<vector<int>> &grid) {
    long long answer = 0;
    for (const auto &shape : shapes) {
        for (int sr = 0; sr + shape.maxR < rowCount; sr++)
            for (int sc = 0; sc + shape.maxC < colCount; sc++)
                if (checkLoop(shape, sr, sc, grid))
                    answer++;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildCells.push_back({0, 0});
    buildShapes();
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int rowCount, colCount;
        cin >> rowCount >> colCount;
        vector<vector<int>> grid(rowCount, vector<int>(colCount));
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                cin >> grid[i][j];
        cout << "Case " << caseId << ": " << solveCase(rowCount, colCount, grid) << '\n';
    }
    return 0;
}
