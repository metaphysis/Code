// Divide et Unita
// UVa ID: 772
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 2.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int M, N;                              // 方格总数，正方形边长
vector<pair<int,int>> pts;             // 每个编号对应的 (行, 列)
int adjMask[25];                       // 每个格子的邻居位掩码
int fullMask;                          // 所有格子的掩码

// 检查 mask 是否连通（位运算 BFS）
bool isConnected(int mask) {
    if (mask == 0) return false;
    int start = __builtin_ctz(mask);
    int visited = 1 << start;
    int stack = visited;
    while (stack) {
        int v = __builtin_ctz(stack);
        stack &= ~(1 << v);
        int neigh = adjMask[v] & mask & ~visited;
        while (neigh) {
            int w = __builtin_ctz(neigh);
            neigh &= ~(1 << w);
            visited |= (1 << w);
            stack |= (1 << w);
        }
    }
    return visited == mask;
}

// 计算 mask 的边界框 (最小/最大行、列)
void getBBox(int mask, int &minR, int &maxR, int &minC, int &maxC) {
    minR = maxR = minC = maxC = -1;
    bool first = true;
    for (int i = 0; i < M; ++i) if (mask & (1 << i)) {
        int r = pts[i].first, c = pts[i].second;
        if (first) { minR = maxR = r; minC = maxC = c; first = false; }
        else {
            if (r < minR) minR = r; if (r > maxR) maxR = r;
            if (c < minC) minC = c; if (c > maxC) maxC = c;
        }
    }
}

// 旋转坐标 (rot: 0,1,2,3 对应 0°,90°,180°,270°)
vector<pair<int,int>> rotateShape(const vector<pair<int,int>>& coords, int rot) {
    vector<pair<int,int>> res;
    for (auto p : coords) {
        int r = p.first, c = p.second;
        int nr, nc;
        if (rot == 0) { nr = r; nc = c; }
        else if (rot == 1) { nr = c; nc = -r; }
        else if (rot == 2) { nr = -r; nc = -c; }
        else { nr = -c; nc = r; }
        res.push_back({nr, nc});
    }
    return res;
}

// 检查 maskA 和 maskB 能否拼成正方形
bool canFormSquare(int maskA, int maskB) {
    // 提取 A 的归一化坐标
    int minR, maxR, minC, maxC;
    getBBox(maskA, minR, maxR, minC, maxC);
    vector<pair<int,int>> coordsA;
    for (int i = 0; i < M; ++i) if (maskA & (1 << i))
        coordsA.push_back({pts[i].first - minR, pts[i].second - minC});
    
    getBBox(maskB, minR, maxR, minC, maxC);
    vector<pair<int,int>> coordsB;
    for (int i = 0; i < M; ++i) if (maskB & (1 << i))
        coordsB.push_back({pts[i].first - minR, pts[i].second - minC});

    // 生成 B 的所有可能放置掩码
    unordered_set<int> setB;
    for (int rot = 0; rot < 4; ++rot) {
        vector<pair<int,int>> rotated = rotateShape(coordsB, rot);
        // 归一化旋转后的坐标
        int rMin = 100, rMax = -100, cMin = 100, cMax = -100;
        for (auto p : rotated) {
            rMin = min(rMin, p.first); rMax = max(rMax, p.first);
            cMin = min(cMin, p.second); cMax = max(cMax, p.second);
        }
        int h = rMax - rMin + 1, w = cMax - cMin + 1;
        if (h > N || w > N) continue;
        for (int tx = 0; tx <= N - h; ++tx) {
            for (int ty = 0; ty <= N - w; ++ty) {
                int mask = 0;
                bool ok = true;
                for (auto p : rotated) {
                    int r = p.first - rMin + tx;
                    int c = p.second - cMin + ty;
                    if (r < 0 || r >= N || c < 0 || c >= N) { ok = false; break; }
                    mask |= (1 << (r * N + c));
                }
                if (ok) setB.insert(mask);
            }
        }
    }
    if (setB.empty()) return false;

    // 枚举 A 的放置，检查剩余是否在 setB 中
    int fullSquare = (1 << (N * N)) - 1;
    for (int rot = 0; rot < 4; ++rot) {
        vector<pair<int,int>> rotated = rotateShape(coordsA, rot);
        int rMin = 100, rMax = -100, cMin = 100, cMax = -100;
        for (auto p : rotated) {
            rMin = min(rMin, p.first); rMax = max(rMax, p.first);
            cMin = min(cMin, p.second); cMax = max(cMax, p.second);
        }
        int h = rMax - rMin + 1, w = cMax - cMin + 1;
        if (h > N || w > N) continue;
        for (int tx = 0; tx <= N - h; ++tx) {
            for (int ty = 0; ty <= N - w; ++ty) {
                int mask = 0;
                bool ok = true;
                for (auto p : rotated) {
                    int r = p.first - rMin + tx;
                    int c = p.second - cMin + ty;
                    if (r < 0 || r >= N || c < 0 || c >= N) { ok = false; break; }
                    mask |= (1 << (r * N + c));
                }
                if (!ok) continue;
                int remain = fullSquare ^ mask;
                if (setB.find(remain) != setB.end()) return true;
            }
        }
    }
    return false;
}

// 处理单个测试用例
vector<string> solveCase(const vector<string>& grid) {
    // 提取星号坐标
    pts.clear();
    for (int i = 0; i < (int)grid.size(); ++i)
        for (int j = 0; j < (int)grid[i].size(); ++j)
            if (grid[i][j] == '*') pts.push_back({i, j});
    M = pts.size();
    N = (int)sqrt(M);          // 保证 M 为完全平方数
    fullMask = (1 << M) - 1;

    // 构建邻接掩码
    for (int i = 0; i < M; ++i) adjMask[i] = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = i + 1; j < M; ++j) {
            int dr = abs(pts[i].first - pts[j].first);
            int dc = abs(pts[i].second - pts[j].second);
            if ((dr == 1 && dc == 0) || (dr == 0 && dc == 1)) {
                adjMask[i] |= (1 << j);
                adjMask[j] |= (1 << i);
            }
        }
    }

    int ansMaskA = 0;
    bool found = false;
    // 枚举所有包含编号 0 的掩码 (非空且非全集)
    for (int mask = 1; mask < (1 << M); ++mask) {
        if (!(mask & 1)) continue;
        if (mask == fullMask) continue;
        // 边界框剪枝 (A)
        int minR, maxR, minC, maxC;
        getBBox(mask, minR, maxR, minC, maxC);
        int wA = maxR - minR + 1, hA = maxC - minC + 1;
        if (max(wA, hA) > N) continue;
        // 检查 A 连通
        if (!isConnected(mask)) continue;
        int maskB = fullMask ^ mask;
        // 边界框剪枝 (B)
        getBBox(maskB, minR, maxR, minC, maxC);
        int wB = maxR - minR + 1, hB = maxC - minC + 1;
        if (max(wB, hB) > N) continue;
        // 检查 B 连通
        if (!isConnected(maskB)) continue;
        // 拼图检查
        if (canFormSquare(mask, maskB)) {
            ansMaskA = mask;
            found = true;
            break;
        }
    }
    // 题目保证有解，此处 found 必为 true

    // 构造输出
    vector<string> out = grid;
    // 建立坐标到编号的映射
    map<pair<int,int>, int> id;
    for (int i = 0; i < M; ++i) id[pts[i]] = i;
    for (int i = 0; i < (int)out.size(); ++i) {
        for (int j = 0; j < (int)out[i].size(); ++j) {
            if (out[i][j] == '*') {
                int idx = id[{i, j}];
                out[i][j] = (ansMaskA & (1 << idx)) ? 'A' : 'B';
            }
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> cases;
    vector<string> cur;
    string line;
    while (getline(cin, line)) {
        // 去除末尾换行符
        if (!line.empty() && line.back() == '\r') line.pop_back();
        // 判断是否为空行（忽略空格）
        bool blank = true;
        for (char c : line) if (!isspace((unsigned char)c)) { blank = false; break; }
        if (blank) {
            if (!cur.empty()) {
                cases.push_back(cur);
                cur.clear();
            }
        } else {
            cur.push_back(line);
        }
    }
    if (!cur.empty()) cases.push_back(cur);

    bool firstCase = true;
    for (const auto& g : cases) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        vector<string> ans = solveCase(g);
        for (const string& s : ans) cout << s << '\n';
    }
    return 0;
}
