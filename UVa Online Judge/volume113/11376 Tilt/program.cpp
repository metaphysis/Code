#include <bits/stdc++.h>
using namespace std;

struct Node {
    int pos, pre;
    uint32_t mask;
    char op;
};

int n;
int wall[10][10], bitId[10][10];
int dx[4] = {0, -1, 1, 0};
int dy[4] = {1, 0, 0, -1};
int side[4] = {4, 8, 2, 1};
char dirName[4] = {'E', 'N', 'S', 'W'};
uint32_t gainMask[100][4];
int nextPos[100][4];

void buildMove() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            int pos = x * n + y;
            for (int d = 0; d < 4; d++) {
                int a = x, b = y;
                uint32_t mask = 0;
                while (!(wall[a][b] & side[d])) {
                    a += dx[d];
                    b += dy[d];
                    if (bitId[a][b] != -1) mask |= 1U << bitId[a][b];
                }
                nextPos[pos][d] = a * n + b;
                gainMask[pos][d] = mask;
            }
        }
    }
}

string solve(int sx, int sy, int cnt) {
    uint32_t full = (1U << cnt) - 1;
    uint32_t startMask = 0;
    if (bitId[sx][sy] != -1) startMask |= 1U << bitId[sx][sy];
    vector<Node> nodes;
    unordered_map<unsigned long long, int> seen;
    queue<int> que;
    int start = sx * n + sy;
    unsigned long long key = ((unsigned long long)startMask << 7) | start;
    nodes.push_back({start, -1, startMask, 0});
    seen[key] = 0;
    que.push(0);
    int endId = -1;
    while (!que.empty()) {
        int id = que.front();
        que.pop();
        if (nodes[id].mask == full) {
            endId = id;
            break;
        }
        for (int d = 0; d < 4; d++) {
            int to = nextPos[nodes[id].pos][d];
            if (to == nodes[id].pos) continue;
            uint32_t mask = nodes[id].mask | gainMask[nodes[id].pos][d];
            unsigned long long nxtKey = ((unsigned long long)mask << 7) | to;
            if (seen.count(nxtKey)) continue;
            int nxtId = nodes.size();
            seen[nxtKey] = nxtId;
            nodes.push_back({to, id, mask, dirName[d]});
            que.push(nxtId);
        }
    }
    string ans;
    while (nodes[endId].pre != -1) {
        ans += nodes[endId].op;
        endId = nodes[endId].pre;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    int p = 0;
    while (p < (int)lines.size()) {
        stringstream ss(lines[p++]);
        ss >> n;
        if (n == 0) break;
        memset(bitId, -1, sizeof(bitId));
        for (int i = 0; i < n; i++) {
            string s = lines[p++];
            for (int j = 0; j < n; j++) {
                if ('0' <= s[j] && s[j] <= '9') wall[i][j] = s[j] - '0';
                else wall[i][j] = toupper(s[j]) - 'A' + 10;
            }
        }
        int sx, sy;
        ss.clear();
        ss.str(lines[p++]);
        ss >> sx >> sy;
        sx--;
        sy--;
        int cnt = 0;
        while (p < (int)lines.size()) {
            stringstream ts(lines[p]);
            vector<int> val;
            int x;
            while (ts >> x) val.push_back(x);
            if (val.size() != 2) break;
            p++;
            bitId[val[0] - 1][val[1] - 1] = cnt++;
        }
        buildMove();
        cout << solve(sx, sy, cnt) << '\n';
    }
    return 0;
}
