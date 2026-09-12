// Ecology
// UVa ID: 12795
// Verdict: Accepted
// Submission Date: 2026-08-05
// UVa Run Time: 5.620s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator < (const Point &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator == (const Point &other) const {
        return x == other.x && y == other.y;
    }
};

set<string> shapeSet;
vector<vector<Point>> shapes;
int dirX[4] = {-1, 1, 0, 0};
int dirY[4] = {0, 0, -1, 1};

vector<Point> normalizeShape(vector<Point> shape) {
    int minX = INT_MAX, minY = INT_MAX;
    for (const Point &p : shape) {
        minX = min(minX, p.x);
        minY = min(minY, p.y);
    }
    for (Point &p : shape) {
        p.x -= minX;
        p.y -= minY;
    }
    sort(shape.begin(), shape.end());
    return shape;
}

string encodeShape(const vector<Point> &shape) {
    string code;
    for (const Point &p : shape) {
        code += to_string(p.x);
        code += ',';
        code += to_string(p.y);
        code += ';';
    }
    return code;
}

vector<Point> transformShape(const vector<Point> &shape, int type) {
    vector<Point> res;
    for (const Point &p : shape) {
        int x = p.x, y = p.y;
        int nx = 0, ny = 0;
        if (type == 0) {
            nx = x;
            ny = y;
        } else if (type == 1) {
            nx = x;
            ny = -y;
        } else if (type == 2) {
            nx = -x;
            ny = y;
        } else if (type == 3) {
            nx = -x;
            ny = -y;
        } else if (type == 4) {
            nx = y;
            ny = x;
        } else if (type == 5) {
            nx = y;
            ny = -x;
        } else if (type == 6) {
            nx = -y;
            ny = x;
        } else {
            nx = -y;
            ny = -x;
        }
        res.push_back({nx, ny});
    }
    return normalizeShape(res);
}

string canonicalShape(const vector<Point> &shape) {
    string best;
    for (int i = 0; i < 8; i++) {
        vector<Point> cur = transformShape(shape, i);
        string code = encodeShape(cur);
        if (best.empty() || code < best) best = code;
    }
    return best;
}

void generateShapes(int target) {
    vector<Point> start = {{0, 0}};
    shapeSet.insert(encodeShape(start));
    vector<vector<Point>> current;
    current.push_back(start);
    for (int size = 1; size < target; size++) {
        set<string> nextSet;
        vector<vector<Point>> next;
        for (const vector<Point> &shape : current) {
            set<pair<int, int>> used;
            for (const Point &p : shape) used.insert({p.x, p.y});
            set<pair<int, int>> candidates;
            for (const Point &p : shape) {
                for (int d = 0; d < 4; d++) {
                    int nx = p.x + dirX[d];
                    int ny = p.y + dirY[d];
                    if (!used.count({nx, ny})) candidates.insert({nx, ny});
                }
            }
            for (const auto &cell : candidates) {
                vector<Point> added = shape;
                added.push_back({cell.first, cell.second});
                added = normalizeShape(added);
                string code = canonicalShape(added);
                if (nextSet.insert(code).second) next.push_back(added);
            }
        }
        current.swap(next);
    }
    shapes = current;
}

int solve() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        if (shapes.empty() || (int)shapes[0].size() != m) {
            shapes.clear();
            shapeSet.clear();
            generateShapes(m);
        }
        int ans = 0;
        for (const vector<Point> &base : shapes) {
            set<string> usedDirection;
            vector<vector<Point>> directions;
            for (int type = 0; type < 8; type++) {
                vector<Point> cur = transformShape(base, type);
                string code = encodeShape(cur);
                if (usedDirection.insert(code).second) directions.push_back(cur);
            }
            for (const vector<Point> &shape : directions) {
                int maxX = 0, maxY = 0;
                for (const Point &p : shape) {
                    maxX = max(maxX, p.x);
                    maxY = max(maxY, p.y);
                }
                for (int i = 0; i + maxX < n; i++) {
                    for (int j = 0; j + maxY < n; j++) {
                        int sum = 0;
                        for (const Point &p : shape)
                            sum += a[i + p.x][j + p.y];
                        ans = max(ans, sum);
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
