// OmniGravity
// UVa ID: 12282
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 全局障碍物
bool obs[8][8];

// 方向：上、下、左、右
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

// 判断一个2x2方块左上角为(r,c)时是否合法（不越界、不碰障碍、不与已占格子重叠）
bool canPlace(int r, int c, bool occupied[8][8]) {
    if (r < 0 || r > 6 || c < 0 || c > 6) return false;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            if (occupied[r + i][c + j]) return false;
    return true;
}

// 标记一个2x2方块占据的格子
void markOccupied(int r, int c, bool occupied[8][8]) {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            occupied[r + i][c + j] = true;
}

// 对当前状态执行一次重力（方向dir），直接修改pos数组
void applyGravity(int pos[4][2], int dir) {
    int cur[4][2];
    memcpy(cur, pos, sizeof(cur));

    bool occupied[8][8];
    memset(occupied, 0, sizeof(occupied));
    // 障碍物视为永远占据
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            if (obs[r][c]) occupied[r][c] = true;

    int order[4] = {0, 1, 2, 3};
    // 按重力方向排序：靠近终点的先处理
    if (dir == 0) // 上：行从小到大
        sort(order, order + 4, [&](int a, int b) { return cur[a][0] < cur[b][0]; });
    else if (dir == 1) // 下：行从大到小
        sort(order, order + 4, [&](int a, int b) { return cur[a][0] > cur[b][0]; });
    else if (dir == 2) // 左：列从小到大
        sort(order, order + 4, [&](int a, int b) { return cur[a][1] < cur[b][1]; });
    else // 右：列从大到小
        sort(order, order + 4, [&](int a, int b) { return cur[a][1] > cur[b][1]; });

    for (int idx = 0; idx < 4; ++idx) {
        int i = order[idx];
        int r = cur[i][0], c = cur[i][1];
        // 沿方向逐格滑动直到不能移动
        while (true) {
            int nr = r + dr[dir], nc = c + dc[dir];
            if (canPlace(nr, nc, occupied)) {
                r = nr; c = nc;
            } else break;
        }
        cur[i][0] = r; cur[i][1] = c;
        markOccupied(r, c, occupied);
    }
    memcpy(pos, cur, sizeof(cur));
}

// 将四个坐标编码为uint64_t
uint64_t encode(int pos[4][2]) {
    uint64_t code = 0;
    for (int i = 0; i < 4; ++i) {
        int idx = pos[i][0] * 7 + pos[i][1]; // 0..48
        code |= (uint64_t)idx << (48 - 16 * i); // 每16位存放一个索引
    }
    return code;
}

// 解码
void decode(uint64_t code, int pos[4][2]) {
    for (int i = 0; i < 4; ++i) {
        int idx = (code >> (48 - 16 * i)) & 0xFFFF;
        pos[i][0] = idx / 7;
        pos[i][1] = idx % 7;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        // 读入8行，cin >> 会自动跳过空白行
        string line;
        memset(obs, 0, sizeof(obs));
        // 记录每个字母出现的位置，用于确定2x2方块的左上角
        vector<pair<int,int>> cells[4]; // A,B,C,D
        for (int r = 0; r < 8; ++r) {
            cin >> line;
            for (int c = 0; c < 8; ++c) {
                char ch = line[c];
                if (ch == '#') obs[r][c] = true;
                else if (ch >= 'A' && ch <= 'D') {
                    cells[ch - 'A'].push_back({r, c});
                }
            }
        }

        int startPos[4][2];
        for (int i = 0; i < 4; ++i) {
            // 2x2方块，左上角坐标是出现位置中行最小、列最小
            int minR = 8, minC = 8;
            for (auto &p : cells[i]) {
                minR = min(minR, p.first);
                minC = min(minC, p.second);
            }
            startPos[i][0] = minR;
            startPos[i][1] = minC;
        }

        uint64_t startCode = encode(startPos);
        unordered_set<uint64_t> visited;
        unordered_set<uint64_t> reached; // 通过至少一次重力到达的状态
        queue<uint64_t> q;
        visited.insert(startCode);
        q.push(startCode);

        while (!q.empty()) {
            uint64_t curCode = q.front(); q.pop();
            int curPos[4][2];
            decode(curCode, curPos);

            for (int d = 0; d < 4; ++d) {
                int nxtPos[4][2];
                memcpy(nxtPos, curPos, sizeof(nxtPos));
                applyGravity(nxtPos, d);
                uint64_t nxtCode = encode(nxtPos);

                // 执行了一次重力，将结果状态加入reached集合
                reached.insert(nxtCode);

                if (visited.find(nxtCode) == visited.end()) {
                    visited.insert(nxtCode);
                    q.push(nxtCode);
                }
            }
        }

        cout << "Case " << caseNo << ": " << reached.size() << '\n';
    }
    return 0;
}
