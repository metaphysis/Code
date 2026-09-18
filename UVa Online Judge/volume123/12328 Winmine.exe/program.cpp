#include <bits/stdc++.h>
using namespace std;

const int mod = 1000003;
const int maxN = 105;
const int dr[8] = {0, 1, 0, -1, 1, -1, 1, -1};
const int dc[8] = {1, 0, -1, 0, 1, 1, -1, -1};

int n, m, mineTotal, grid[maxN][maxN], addOrder[maxN][maxN];
int boardTag[maxN][maxN], mineCnt[maxN][maxN], depMark[maxN][maxN];
int dfsTimer, globalTag, depTimer, freeCnt;
bool visited[maxN][maxN], touchEdge;
vector<pair<int, int>> aroundCells, numberCells, boundSeq;
vector<vector<pair<int, int>>> checkDeps;
vector<vector<pair<int, int>>> compWays;

bool inBoard(int r, int c) {
    return r >= 1 && r <= n && c >= 1 && c <= m;
}

int popCount(int mask) {
    return __builtin_popcount((unsigned)mask);
}

void extractComponent(int r, int c) {
    dfsTimer++;
    visited[r][c] = true;
    numberCells.push_back({r, c});
    if (r == 1 || r == n || c == 1 || c == m) touchEdge = true;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inBoard(nr, nc) && grid[nr][nc] == -1 && addOrder[nr][nc] == 0) {
            addOrder[nr][nc] = dfsTimer;
            aroundCells.push_back({nr, nc});
        }
    }
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inBoard(nr, nc) && grid[nr][nc] > 0 && !visited[nr][nc]) extractComponent(nr, nc);
    }
}

void clearAround(pair<int, int> cell) {
    int r = cell.first, c = cell.second;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inBoard(nr, nc)) mineCnt[nr][nc] = 0;
    }
}

void setAround(pair<int, int> cell) {
    int r = cell.first, c = cell.second;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inBoard(nr, nc)) mineCnt[nr][nc]++;
    }
}

bool checkAround(pair<int, int> cell) {
    int r = cell.first, c = cell.second;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inBoard(nr, nc) && grid[nr][nc] > 0 && grid[nr][nc] != mineCnt[nr][nc]) return false;
    }
    return true;
}

bool isIncluded(int r, int c, const vector<int>& ids) {
    for (int id : ids) {
        if (boundSeq[id].first == r && boundSeq[id].second == c) return true;
    }
    return false;
}

bool isCovered(int r, int c, const vector<int>& ids) {
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inBoard(nr, nc) && grid[nr][nc] == -1 && !isIncluded(nr, nc, ids)) return false;
    }
    return true;
}

vector<pair<int, int>> findDeps(const vector<int>& ids) {
    vector<pair<int, int>> deps;
    depTimer++;
    for (int id : ids) {
        int r = boundSeq[id].first, c = boundSeq[id].second;
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (!inBoard(nr, nc) || grid[nr][nc] <= 0 || depMark[nr][nc] == depTimer) continue;
            depMark[nr][nc] = depTimer;
            if (isCovered(nr, nc, ids)) deps.push_back({nr, nc});
        }
    }
    return deps;
}

bool checkAssign(const vector<int>& ids, const vector<int>& vals, const vector<pair<int, int>>& deps) {
    for (pair<int, int> cell : deps) mineCnt[cell.first][cell.second] = 0;
    for (int i = 0; i < (int)ids.size(); i++) {
        if (vals[i] == 0) continue;
        int r = boundSeq[ids[i]].first, c = boundSeq[ids[i]].second;
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (inBoard(nr, nc)) mineCnt[nr][nc]++;
        }
    }
    for (pair<int, int> cell : deps) {
        if (mineCnt[cell.first][cell.second] != grid[cell.first][cell.second]) return false;
    }
    return true;
}

bool checkHeadTail(int tailMask, int headMask) {
    int len = boundSeq.size();
    vector<int> ids(8), vals(8);
    for (int i = 0; i < 4; i++) {
        ids[i] = i;
        vals[i] = headMask >> i & 1;
        ids[i + 4] = len - 4 + i;
        vals[i + 4] = tailMask >> i & 1;
    }
    vector<pair<int, int>> deps = findDeps(ids);
    return checkAssign(ids, vals, deps);
}

bool checkWindow(int endPos, int mask) {
    vector<int> ids(5), vals(5);
    for (int i = 0; i < 5; i++) {
        ids[i] = endPos - 4 + i;
        vals[i] = mask >> i & 1;
    }
    return checkAssign(ids, vals, checkDeps[endPos]);
}

void buildBoundSequence() {
    int sr = aroundCells[0].first, sc = aroundCells[0].second;
    boundSeq.clear();
    if (touchEdge) {
        for (pair<int, int> cell : aroundCells) {
            int r = cell.first, c = cell.second;
            if (r == 1 || r == n || c == 1 || c == m) {
                sr = r;
                sc = c;
                break;
            }
        }
    }
    while (true) {
        boundSeq.push_back({sr, sc});
        boardTag[sr][sc] = -1;
        int nr = -1, nc = -1, bestDist = INT_MAX;
        for (int d = 0; d < 8; d++) {
            int tr = sr + dr[d], tc = sc + dc[d];
            if (boardTag[tr][tc] != globalTag) continue;
            int dist = abs(addOrder[tr][tc] - addOrder[sr][sc]);
            if (dist < bestDist) {
                bestDist = dist;
                nr = tr;
                nc = tc;
            }
        }
        if (nr == -1) break;
        sr = nr;
        sc = nc;
    }
}

void forceEnumerate() {
    int len = boundSeq.size(), stateCnt = 1 << len;
    vector<int> ways(min(len, mineTotal) + 1, 0);
    for (int mask = 0; mask < stateCnt; mask++) {
        for (pair<int, int> cell : boundSeq) clearAround(cell);
        for (int i = 0; i < len; i++) {
            if (mask >> i & 1) setAround(boundSeq[i]);
        }
        bool valid = true;
        for (pair<int, int> cell : boundSeq) {
            if (!checkAround(cell)) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        int cnt = popCount(mask);
        if (cnt <= mineTotal) {
            ways[cnt]++;
            if (ways[cnt] == mod) ways[cnt] = 0;
        }
    }
    vector<pair<int, int>> result;
    for (int i = 0; i < (int)ways.size(); i++) {
        if (ways[i] != 0) result.push_back({i, ways[i]});
    }
    compWays.push_back(result);
}

void makeCheckDeps() {
    int len = boundSeq.size();
    checkDeps.assign(len, vector<pair<int, int>>());
    for (int i = 4; i < len; i++) {
        vector<int> ids(5);
        for (int j = 0; j < 5; j++) ids[j] = i - 4 + j;
        checkDeps[i] = findDeps(ids);
    }
}

void runProfileDp() {
    int len = boundSeq.size();
    vector<int> ways(min(len, mineTotal) + 1, 0);
    vector<vector<char>> headTailOk(16, vector<char>(16, 0));
    vector<vector<int>> cur(mineTotal + 1, vector<int>(16, 0));
    vector<vector<int>> nxt(mineTotal + 1, vector<int>(16, 0));
    makeCheckDeps();
    for (int tailMask = 0; tailMask < 16; tailMask++) {
        for (int i = 0; i < 16; i++) headTailOk[tailMask][i] = checkHeadTail(tailMask, i);
    }
    for (int tailMask = 0; tailMask < 16; tailMask++) {
        for (int i = 0; i <= mineTotal; i++) fill(cur[i].begin(), cur[i].end(), 0);
        for (int headMask = 0; headMask < 16; headMask++) {
            if (!headTailOk[tailMask][headMask]) continue;
            int cnt = popCount(headMask);
            if (cnt <= mineTotal) cur[cnt][headMask] = 1;
        }
        for (int pos = 4; pos < len; pos++) {
            for (int i = 0; i <= mineTotal; i++) fill(nxt[i].begin(), nxt[i].end(), 0);
            int maxCnt = min(pos, mineTotal);
            for (int cnt = 0; cnt <= maxCnt; cnt++) {
                for (int mask = 0; mask < 16; mask++) {
                    if (cur[cnt][mask] == 0) continue;
                    int fiveMask = mask;
                    if (checkWindow(pos, fiveMask)) {
                        int nextMask = fiveMask >> 1;
                        nxt[cnt][nextMask] += cur[cnt][mask];
                        if (nxt[cnt][nextMask] >= mod) nxt[cnt][nextMask] -= mod;
                    }
                    if (cnt < mineTotal) {
                        fiveMask = mask | 16;
                        if (checkWindow(pos, fiveMask)) {
                            int nextMask = fiveMask >> 1;
                            nxt[cnt + 1][nextMask] += cur[cnt][mask];
                            if (nxt[cnt + 1][nextMask] >= mod) nxt[cnt + 1][nextMask] -= mod;
                        }
                    }
                }
            }
            cur.swap(nxt);
        }
        for (int cnt = 0; cnt < (int)ways.size(); cnt++) {
            ways[cnt] += cur[cnt][tailMask];
            if (ways[cnt] >= mod) ways[cnt] -= mod;
        }
    }
    vector<pair<int, int>> result;
    for (int i = 0; i < (int)ways.size(); i++) {
        if (ways[i] != 0) result.push_back({i, ways[i]});
    }
    compWays.push_back(result);
}

void processComponent() {
    if (aroundCells.empty()) return;
    globalTag++;
    for (pair<int, int> cell : aroundCells) boardTag[cell.first][cell.second] = globalTag;
    buildBoundSequence();
    if ((int)boundSeq.size() <= 8) {
        forceEnumerate();
    } else {
        runProfileDp();
    }
}

bool isFreeCell(int r, int c) {
    if (grid[r][c] != -1) return false;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (grid[nr][nc] != -1) return false;
    }
    return true;
}

void buildComponents() {
    memset(visited, 0, sizeof(visited));
    memset(addOrder, 0, sizeof(addOrder));
    memset(boardTag, -1, sizeof(boardTag));
    memset(depMark, 0, sizeof(depMark));
    compWays.clear();
    globalTag = 0;
    depTimer = 0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (r != 1 && r != n && c != 1 && c != m) continue;
            if (visited[r][c] || grid[r][c] <= 0) continue;
            aroundCells.clear();
            numberCells.clear();
            touchEdge = false;
            dfsTimer = 0;
            extractComponent(r, c);
            processComponent();
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (visited[r][c] || grid[r][c] <= 0) continue;
            aroundCells.clear();
            numberCells.clear();
            touchEdge = false;
            dfsTimer = 0;
            extractComponent(r, c);
            processComponent();
        }
    }
    freeCnt = 0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (isFreeCell(r, c)) freeCnt++;
        }
    }
}

long long modPow(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

vector<int> buildCombinations(int count) {
    vector<long long> fact(count + 1), invFact(count + 1);
    vector<int> comb(min(count, mineTotal) + 1);
    fact[0] = 1;
    for (int i = 1; i <= count; i++) fact[i] = fact[i - 1] * i % mod;
    invFact[count] = modPow(fact[count], mod - 2);
    for (int i = count; i >= 1; i--) invFact[i - 1] = invFact[i] * i % mod;
    for (int i = 0; i < (int)comb.size(); i++) comb[i] = fact[count] * invFact[i] % mod * invFact[count - i] % mod;
    return comb;
}

int calculateAnswer() {
    vector<int> dp(mineTotal + 1, 0), nxt(mineTotal + 1, 0);
    dp[0] = 1;
    for (const vector<pair<int, int>>& ways : compWays) {
        fill(nxt.begin(), nxt.end(), 0);
        for (int used = 0; used <= mineTotal; used++) {
            if (dp[used] == 0) continue;
            for (pair<int, int> state : ways) {
                int nextUsed = used + state.first;
                if (nextUsed > mineTotal) break;
                nxt[nextUsed] = (nxt[nextUsed] + (long long)dp[used] * state.second) % mod;
            }
        }
        dp.swap(nxt);
    }
    vector<int> comb = buildCombinations(freeCnt);
    long long answer = 0;
    for (int used = 0; used <= mineTotal; used++) {
        int remain = mineTotal - used;
        if (remain <= freeCnt) answer = (answer + (long long)dp[used] * comb[remain]) % mod;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    memset(grid, -1, sizeof(grid));
    for (int caseId = 1; caseId <= testCnt; caseId++) {
        cin >> n >> m >> mineTotal;
        memset(grid, -1, sizeof(grid));
        for (int r = 1; r <= n; r++) {
            for (int c = 1; c <= m; c++) {
                char ch;
                cin >> ch;
                grid[r][c] = ch == '.' ? -1 : ch - '0';
            }
        }
        buildComponents();
        cout << "Case #" << caseId << ": " << calculateAnswer() << '\n';
    }
    return 0;
}
