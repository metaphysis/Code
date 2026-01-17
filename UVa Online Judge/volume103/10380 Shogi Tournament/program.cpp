// Shogi Tournament
// UVa ID: 10380
// Verdict: Accepted
// Submission Date: 2026-01-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 64, MAXV = 2600, MAXE = 20010;

int m, p;
string board[MAXN][MAXN];

struct Arc { int to, capacity, next; } arcs[MAXE * 2];
int head[MAXV], idx, source, sink;
int level[MAXV], current[MAXV];

void addEdge(int from, int to, int capacity) {
    arcs[idx] = {to, capacity, head[from]};
    head[from] = idx++;
    arcs[idx] = {from, 0, head[to]};
    head[to] = idx++;
}

bool bfs() {
    memset(level, -1, sizeof level);
    queue<int> q;
    level[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = arcs[i].next) {
            int v = arcs[i].to;
            if (arcs[i].capacity > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                q.push(v);
                if (v == sink) return true;
            }
        }
    }
    return level[sink] != -1;
}

int dfs(int u, int flow) {
    if (u == sink) return flow;
    int volume = 0;
    for (int& i = current[u]; ~i; i = arcs[i].next) {
        int v = arcs[i].to, r = arcs[i].capacity;
        if (level[v] == level[u] + 1 && r > 0) {
            int volume = dfs(v, min(r, flow));
            if (volume > 0) {
                arcs[i].capacity -= volume;
                arcs[i ^ 1].capacity += volume;
                return volume;
            }
        }
    }
    return 0;
}

int maxFlow() {
    int flow = 0;
    while (bfs()) {
        for (int i = 0; i < MAXV; i++) current[i] = head[i];
        while (int delta = dfs(source, INF))
            flow += delta;
    }
    return flow;
}

bool check(int W, int d) {
    idx = 0;
    memset(head, -1, sizeof head);
    int matches = m * (m - 1), players = m;
    source = 0;
    sink = matches + players + 1;
    // 在源点和比赛之间连边
    int idxer = 1;
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++) {
            // 根据比赛得分情况在赛事和选手之间连边
            for (int k = 0; k < 2; k++) {
                int matchIdx = 2 * idxer - 1 + k;
                // 每次比赛可以提供 1 分
                addEdge(source, matchIdx, 1);
                char c = board[i][j][k];
                // 结果未定，则选手 i 和选手 j 都可得 1 分
                if (c == '-') {
                    addEdge(matchIdx, matches + i, 1);
                    addEdge(matchIdx, matches + j, 1);
                } else {
                    // 选手 i 获胜
                    if (c == '1') addEdge(matchIdx, matches + i, 1);
                    // 选手 j 获胜
                    else addEdge(matchIdx, matches + j, 1);
                }
            }
            idxer++;
        }
    // 在选手和汇点之间建边
    for (int i = 1; i <= m; i++) {
        // 选手 p 的得分为 W
        if (i == p) addEdge(matches + i, sink, W);
        // 其他选手的得分最大为 W - d
        else addEdge(matches + i, sink, W - d);
    }
    // 检查是否可以满流
    return maxFlow() == m * (m - 1);
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        // 读入数据
        cin >> m >> p;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                cin >> board[i][j];
        // 确定选手 p 的最大可能得分
        int W = 0;
        for (int i = 1; i <= m; i++) {
            if (i == p) continue;
            // 统计选手 p 的得分
            for (int j = 0; j < 2; j++) {
                if (board[p][i][j] == '-' || board[p][i][j] == '1') W++;
                // 将选手 p 未进行的比赛设置为获胜
                if (board[p][i][j] == '-') {
                    board[p][i][j] = '1';
                    board[i][p][j] = '0';
                }
            }
        }
        // 检查选手 p 所有未进行比赛均获胜是否能够获胜
        if (!check(W, 0)) cout << "Player " << p << " can't win!\n";
        else {
            int low = 0, high = W, answer = -1;
            while (low <= high) {
                int middle = (low + high) >> 1;
                if (check(W, middle)) {
                    answer = middle;
                    low = middle + 1;
                } else high = middle - 1;
            }
            check(W, answer);
            cout << "Player " << p << " can win with " << answer << " point(s).\n";
            cout << '\n';
            // 根据最终流网络中比赛到选手的有向弧流量状态来构建输出
            int idxer = 1;
            for (int i = 1; i <= m; i++)
                for (int j = i + 1; j <= m; j++) {
                        for (int k = 0; k < 2; k++) {
                            int matchIdx = 2 * idxer - 1 + k;
                            // 只记录正向弧
                            Arc arc;
                            for (int x = head[matchIdx]; ~x; x = arcs[x].next) {
                                if (x % 2 == 1) continue;
                                if (arcs[x].to == m * (m - 1) + i) arc = arcs[x];
                            }
                            // 如果正向弧流量已使用，则表明对应的选手获胜
                            if (board[i][j][k] == '-') {
                                board[i][j][k] = arc.capacity ? '0' : '1';
                                board[j][i][k] = arc.capacity ? '1' : '0';
                            }
                        }
                    idxer++;
                }
            for (int i = 1; i <= m; i++) {
                int points = 0;
                for (int j = 1; j <= m; j++) {
                    if (j > 1) cout << ' ';
                    cout << board[i][j];
                    for (int k = 0; k < 2; k++)
                        if (board[i][j][k] == '1')
                            points++;
                }
                cout << " : " << points << '\n';
            }
        }
        if (T) cout << '\n';
    }
    return 0;
}
