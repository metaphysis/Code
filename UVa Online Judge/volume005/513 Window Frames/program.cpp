// Window Frames
// UVa ID: 513
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Frame {
    int id, parent, d;
    char side;
    bool expand;
    int minW, minH;          // 最小尺寸
    int x, y, w, h;          // 实际位置和尺寸
    vector<int> children;    // 按打包顺序
};

vector<Frame> frames;
unordered_map<int, int> idToIdx;

// 递归计算最小尺寸（空腔初始可为0）
void computeMin(int u) {
    for (int v : frames[u].children) computeMin(v);

    int w = 0, h = 0;   // 空腔初始为0×0
    // 逆序处理子框架（打包的逆序）
    for (int i = (int)frames[u].children.size() - 1; i >= 0; --i) {
        int v = frames[u].children[i];
        if (frames[v].side == 'L' || frames[v].side == 'R') {
            w += frames[v].minW;
            h = max(h, frames[v].minH);
        } else { // 'T' or 'B'
            h += frames[v].minH;
            w = max(w, frames[v].minW);
        }
    }

    if (u == 0) { // 根框架
        frames[u].minW = w;
        frames[u].minH = h;
    } else {
        if (frames[u].side == 'L' || frames[u].side == 'R') {
            frames[u].minW = max(frames[u].d, w);
            frames[u].minH = max(1, h);
        } else { // 'T' or 'B'
            frames[u].minW = max(1, w);
            frames[u].minH = max(frames[u].d, h);
        }
    }
}

// 递归分配实际空间，正向模拟打包
void allocate(int u, int x, int y, int W, int H) {
    frames[u].x = x;
    frames[u].y = y;
    frames[u].w = W;
    frames[u].h = H;

    if (frames[u].children.empty()) return;

    vector<int> vChildren, hChildren;
    for (int v : frames[u].children) {
        if (frames[v].side == 'L' || frames[v].side == 'R')
            vChildren.push_back(v);
        else
            hChildren.push_back(v);
    }

    int xExtra = W - frames[u].minW;
    int yExtra = H - frames[u].minH;

    int n = 0, m = 0;
    for (int v : vChildren) if (frames[v].expand) ++n;
    for (int v : hChildren) if (frames[v].expand) ++m;

    // 分配额外宽度给垂直子框架
    int q = 0, r = 0;
    if (n > 0) { q = xExtra / n; r = xExtra % n; }
    int remR = r;
    for (int v : vChildren) {
        int addW = 0;
        if (frames[v].expand && n > 0) {
            addW = q + (remR > 0 ? 1 : 0);
            if (remR > 0) --remR;
        }
        frames[v].w = frames[v].minW + addW;   // 实际宽度
    }

    // 分配额外高度给水平子框架
    int p = 0, s = 0;
    if (m > 0) { p = yExtra / m; s = yExtra % m; }
    int remS = s;
    for (int v : hChildren) {
        int addH = 0;
        if (frames[v].expand && m > 0) {
            addH = p + (remS > 0 ? 1 : 0);
            if (remS > 0) --remS;
        }
        frames[v].h = frames[v].minH + addH;   // 实际高度
    }

    // 正向模拟打包，维护空腔左上角(cx,cy)和尺寸(CW,CH)
    int cx = x, cy = y;
    int CW = W, CH = H;

    for (int v : frames[u].children) {
        if (frames[v].side == 'L') {
            frames[v].x = cx;
            frames[v].y = cy;
            frames[v].h = CH;
            cx += frames[v].w;
            CW -= frames[v].w;
        } else if (frames[v].side == 'R') {
            frames[v].x = cx + CW - frames[v].w;
            frames[v].y = cy;
            frames[v].h = CH;
            CW -= frames[v].w;
            // cx 不变
        } else if (frames[v].side == 'T') {
            frames[v].x = cx;
            frames[v].y = cy;
            frames[v].w = CW;
            cy += frames[v].h;
            CH -= frames[v].h;
        } else { // 'B'
            frames[v].x = cx;
            frames[v].y = cy + CH - frames[v].h;
            frames[v].w = CW;
            CH -= frames[v].h;
            // cy 不变
        }
    }

    // 递归处理子框架
    for (int v : frames[u].children)
        allocate(v, frames[v].x, frames[v].y, frames[v].w, frames[v].h);
}

// DFS 收集输出顺序（深度优先）
void collect(int u, vector<int>& order) {
    if (u != 0) order.push_back(u);
    for (int v : frames[u].children) collect(v, order);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    int caseNo = 0;

    while (cin >> M >> N && (M || N)) {
        frames.clear();
        idToIdx.clear();

        frames.push_back(Frame());
        frames[0].id = 0;
        frames[0].parent = -1;
        frames[0].side = 0;
        frames[0].d = 0;
        frames[0].expand = false;
        idToIdx[0] = 0;

        for (int i = 0; i < M; ++i) {
            int n, p, d, e;
            char s;
            cin >> n >> p >> s >> d >> e;

            int idx = frames.size();
            frames.push_back(Frame());
            frames[idx].id = n;
            frames[idx].parent = p;
            frames[idx].side = s;
            frames[idx].d = d;
            frames[idx].expand = (e == 1);
            idToIdx[n] = idx;

            int pIdx = idToIdx[p];
            frames[pIdx].children.push_back(idx);
        }

        computeMin(0);
        int rootMinW = frames[0].minW;
        int rootMinH = frames[0].minH;

        if (caseNo) cout << '\n';
        cout << "Root Frame #" << ++caseNo << "\n";
        cout << "--------------------------------------------\n";

        for (int i = 0; i < N; ++i) {
            int c, r;
            cin >> c >> r;
            cout << "  Display: " << c << " X " << r;
            if (c < rootMinW || r < rootMinH) {
                cout << " is too small\n";
            } else {
                cout << '\n';
                allocate(0, 0, 0, c, r);
                vector<int> order;
                collect(0, order);
                for (int idx : order) {
                    cout << "   Frame: " << frames[idx].id << "  ("
                         << frames[idx].x << "," << frames[idx].y << ")  ("
                         << frames[idx].x + frames[idx].w - 1 << ","
                         << frames[idx].y + frames[idx].h - 1 << ")\n";
                }
            }
            cout << "--------------------------------------------\n";
        }
    }
    return 0;
}
