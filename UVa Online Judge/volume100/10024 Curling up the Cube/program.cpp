// Curling up the Cube
// UVa ID: 10024
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 方向：四连通
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

// 检查连通性
bool isConnected(const vector<vector<int>>& grid) {
    int n = 6;
    int cntOnes = 0;
    int sx = -1, sy = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                cntOnes++;
                if (sx == -1) {
                    sx = i;
                    sy = j;
                }
            }
        }
    }
    if (cntOnes != 6) return false;

    // BFS
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    int found = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        found++;
        for (int d = 0; d < 4; d++) {
            int nx = p.first + dx[d];
            int ny = p.second + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && grid[nx][ny] == 1) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return found == 6;
}

// 旋转 90 度
vector<vector<int>> rotate(const vector<vector<int>>& mat) {
    int n = 6;
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[j][n - 1 - i] = mat[i][j];
        }
    }
    return res;
}

// 镜像
vector<vector<int>> mirror(const vector<vector<int>>& mat) {
    int n = 6;
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][n - 1 - j] = mat[i][j];
        }
    }
    return res;
}

// 标准化：平移到左上角
vector<vector<int>> normalize(const vector<vector<int>>& mat) {
    int n = 6;
    int minRow = n, minCol = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                minRow = min(minRow, i);
                minCol = min(minCol, j);
            }
        }
    }
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                res[i - minRow][j - minCol] = 1;
            }
        }
    }
    return res;
}

// 检查两个形状是否相同
bool sameShape(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = 6;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// 预定义的 11 种立方体展开图（标准化后的）
vector<vector<vector<int>>> nets;

// 初始化 nets
void initNets() {
    // 正确的11种立方体展开图
    vector<vector<vector<int>>> rawNets = {
        {
            {1,0,0,0,0,0},
            {1,1,1,1,0,0},
            {1,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,0,0,0,0,0},
            {1,1,1,1,0,0},
            {0,1,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,0,0,0,0,0},
            {1,1,1,1,0,0},
            {0,0,1,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,0,0,0,0,0},
            {1,1,1,1,0,0},
            {0,0,0,1,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {0,1,0,0,0,0},
            {1,1,1,1,0,0},
            {0,0,1,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {0,1,0,0,0,0},
            {1,1,1,1,0,0},
            {0,1,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,1,0,0,0,0},
            {0,1,1,1,0,0},
            {0,1,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,1,0,0,0,0},
            {0,1,1,1,0,0},
            {0,0,1,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,1,0,0,0,0},
            {0,1,1,1,0,0},
            {0,0,0,1,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,1,1,0,0,0},
            {0,0,1,1,1,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        },
        {
            {1,1,0,0,0,0},
            {0,1,1,0,0,0},
            {0,0,1,1,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0}
        }
    };
    
    // 标准化所有形状
    for (const auto& net : rawNets) {
        nets.push_back(normalize(net));
    }
}

bool isCubeNet(vector<vector<int>> grid) {
    // 生成所有旋转和镜像
    vector<vector<vector<int>>> variants;
    variants.push_back(grid);
    variants.push_back(rotate(grid));
    variants.push_back(rotate(rotate(grid)));
    variants.push_back(rotate(rotate(rotate(grid))));
    auto m = mirror(grid);
    variants.push_back(m);
    variants.push_back(rotate(m));
    variants.push_back(rotate(rotate(m)));
    variants.push_back(rotate(rotate(rotate(m))));

    // 标准化所有变体
    for (auto& v : variants) {
        v = normalize(v);
    }

    // 与预定义 nets 比较
    for (const auto& net : nets) {
        for (const auto& var : variants) {
            if (sameShape(var, net)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // 初始化标准化的 nets
    initNets();
    
    int t;
    cin >> t;

    while (t--) {
        vector<vector<int>> grid(6, vector<int>(6));
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cin >> grid[i][j];
            }
        }

        if (isConnected(grid) && isCubeNet(grid)) {
            cout << "correct" << endl;
        } else {
            cout << "incorrect" << endl;
        }

        if (t > 0) {
            cout << endl;
        }
    }

    return 0;
}
