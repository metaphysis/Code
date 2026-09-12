#include <bits/stdc++.h>
using namespace std;

const int MOD = 100007;
struct Edge { int v, d, id; };
int N, M, outCnt[10], roomMask[10], personPos[9], doorState, bestCnt, bestNum, bestComb[1 << 11], groupCnt[11], group[11][1 << 9], memoCnt[MOD];
long long memo[MOD][107], powN[10];
bool reach[10][10], seenComb[1 << 11];
Edge edges[10][10];

void calcReach() {
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) reach[i][j] = false;
    for (int s = 0; s < N; s++) {
        bool vis[10] = {false};
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            reach[s][u] = true;
            for (int k = 0; k < outCnt[u]; k++) {
                int v = edges[u][k].v;
                if (!vis[v]) dfs(v);
            }
        };
        dfs(s);
    }
}

bool dfs() {
    int possible = 0;
    for (int p = 0; p < 9; p++) if (reach[personPos[p]][N - 1]) possible++;
    if (possible < bestCnt) return false;
    int escaped = __builtin_popcount(roomMask[N - 1]);
    if (escaped > bestCnt) { bestCnt = escaped; bestNum = 0; memset(seenComb, false, sizeof(seenComb)); }
    if (escaped == bestCnt && bestCnt > 0) {
        int cmb = roomMask[N - 1];
        if (!seenComb[cmb]) { seenComb[cmb] = true; bestComb[bestNum++] = cmb; }
    }
    if (bestCnt == 9) return true;
    long long posCode = 0;
    for (int p = 0; p < 9; p++) posCode = posCode * N + personPos[p];
    long long st = (long long)doorState * powN[9] + posCode;
    int h = st % MOD;
    for (int i = 0; i < memoCnt[h]; i++) if (memo[h][i] == st) return false;
    memo[h][memoCnt[h]++] = st;
    for (int i = 0; i < N; i++) {
        if (!reach[i][N - 1]) continue;
        if (roomMask[i] == 0) continue;
        for (int e = 0; e < outCnt[i]; e++) {
            int v = edges[i][e].v, d = edges[i][e].d, id = edges[i][e].id;
            if (d > 0 && (doorState & (1 << id))) continue;
            for (int gi = 0; gi < groupCnt[d]; gi++) {
                int sub = group[d][gi];
                if ((roomMask[i] & sub) != sub) continue;
                int oldDoor = doorState, oldMaskI = roomMask[i], oldMaskV = roomMask[v];
                int oldPos[9];
                for (int p = 0; p < 9; p++) if (sub & (1 << p)) oldPos[p] = personPos[p];
                roomMask[i] ^= sub;
                roomMask[v] |= sub;
                for (int p = 0; p < 9; p++) if (sub & (1 << p)) personPos[p] = v;
                if (d > 0) doorState |= (1 << id);
                if (dfs()) return true;
                doorState = oldDoor;
                for (int p = 0; p < 9; p++) if (sub & (1 << p)) personPos[p] = oldPos[p];
                roomMask[i] = oldMaskI;
                roomMask[v] = oldMaskV;
            }
        }
    }
    return false;
}

int main() {
    memset(groupCnt, 0, sizeof(groupCnt));
    for (int s = 1; s < (1 << 9); s++) {
        int cnt = 0, sum = 0;
        for (int i = 0; i < 9; i++) if (s & (1 << i)) { cnt++; sum += i + 1; }
        if (cnt < 3 || cnt > 5) continue;
        int root = sum;
        while (root >= 10) { int tmp = 0; while (root) { tmp += root % 10; root /= 10; } root = tmp; }
        group[root][groupCnt[root]++] = s;
    }
    for (int i = 0; i < 9; i++) group[0][groupCnt[0]++] = 1 << i;
    while (scanf("%d%d", &N, &M) == 2) {
        memset(outCnt, 0, sizeof(outCnt));
        for (int i = 0; i < M; i++) { int u, v, d; scanf("%d%d%d", &u, &v, &d); u--; v--; edges[u][outCnt[u]++] = {v, d, i}; }
        calcReach();
        powN[0] = 1;
        for (int i = 1; i <= 9; i++) powN[i] = powN[i - 1] * N;
        memset(roomMask, 0, sizeof(roomMask));
        roomMask[0] = (1 << 9) - 1;
        for (int i = 0; i < 9; i++) personPos[i] = 0;
        doorState = 0; bestCnt = 0; bestNum = 0;
        memset(seenComb, false, sizeof(seenComb));
        memset(memoCnt, 0, sizeof(memoCnt));
        dfs();
        vector<string> out;
        for (int i = 0; i < bestNum; i++) {
            int cmb = bestComb[i];
            string s;
            for (int j = 0; j < 9; j++) if (cmb & (1 << j)) s.push_back('1' + j);
            out.push_back(s);
        }
        sort(out.begin(), out.end());
        printf("%d", bestCnt);
        for (auto &s : out) printf(" %s", s.c_str());
        printf("\n");
    }
    return 0;
}
