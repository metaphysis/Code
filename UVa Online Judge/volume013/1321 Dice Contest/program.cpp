#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);
const int stateCnt = 96;

struct Dice {
    int top, bottom, north, south, east, west;
};

int val[7], targetY, remDist;

int getId(int y, int o) {
    return (y - 1) * 24 + o;
}

void getState(int id, int &y, int &o) {
    y = id / 24 + 1;
    o = id % 24;
}

Dice rollDice(Dice d, int dir) {
    Dice t = d;
    if (dir == 0) {
        t.top = d.west;
        t.bottom = d.east;
        t.east = d.top;
        t.west = d.bottom;
    } else if (dir == 1) {
        t.top = d.east;
        t.bottom = d.west;
        t.east = d.bottom;
        t.west = d.top;
    } else if (dir == 2) {
        t.top = d.south;
        t.bottom = d.north;
        t.north = d.top;
        t.south = d.bottom;
    } else {
        t.top = d.north;
        t.bottom = d.south;
        t.north = d.bottom;
        t.south = d.top;
    }
    return t;
}

vector<Dice> buildDice() {
    vector<Dice> dice;
    map<array<int, 6>, int> mp;
    queue<Dice> que;
    Dice first = {1, 6, 5, 2, 4, 3};
    dice.push_back(first);
    que.push(first);
    mp[{first.top, first.bottom, first.north, first.south, first.east, first.west}] = 0;
    while (!que.empty()) {
        Dice cur = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            Dice nxt = rollDice(cur, i);
            array<int, 6> key = {nxt.top, nxt.bottom, nxt.north, nxt.south, nxt.east, nxt.west};
            if (!mp.count(key)) {
                mp[key] = dice.size();
                dice.push_back(nxt);
                que.push(nxt);
            }
        }
    }
    return dice;
}

vector<vector<long long>> mulMat(const vector<vector<long long>> &a, const vector<vector<long long>> &b) {
    vector<vector<long long>> c(stateCnt, vector<long long>(stateCnt, inf));
    for (int i = 0; i < stateCnt; i++)
        for (int k = 0; k < stateCnt; k++) {
            if (a[i][k] == inf) continue;
            for (int j = 0; j < stateCnt; j++) {
                if (b[k][j] == inf) continue;
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
            }
        }
    return c;
}

vector<long long> mulVec(const vector<long long> &a, const vector<vector<long long>> &b) {
    vector<long long> c(stateCnt, inf);
    for (int i = 0; i < stateCnt; i++) {
        if (a[i] == inf) continue;
        for (int j = 0; j < stateCnt; j++) {
            if (b[i][j] == inf) continue;
            c[j] = min(c[j], a[i] + b[i][j]);
        }
    }
    return c;
}

void dijkstra(int src, int bound, const vector<Dice> &dice, const vector<array<int, 4>> &nxt, vector<vector<long long>> &trans, vector<long long> &last) {
    int width = bound * 2 + 1, total = width * stateCnt;
    vector<long long> dis(total, inf);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> que;
    int start = bound * stateCnt + src;
    dis[start] = 0;
    que.push({0, start});
    while (!que.empty()) {
        long long cost = que.top().first;
        int node = que.top().second;
        que.pop();
        if (cost != dis[node]) continue;
        int x = node / stateCnt - bound, state = node % stateCnt;
        int y, o;
        getState(state, y, o);
        for (int dir = 0; dir < 4; dir++) {
            int nx = x, ny = y;
            if (dir == 0) nx++;
            else if (dir == 1) nx--;
            else if (dir == 2) ny++;
            else ny--;
            if (nx < -bound || nx > bound || ny < 1 || ny > 4) continue;
            int no = nxt[o][dir], ns = getId(ny, no);
            int to = (nx + bound) * stateCnt + ns;
            long long nd = cost + val[dice[no].top];
            if (nd < dis[to]) {
                dis[to] = nd;
                que.push({nd, to});
            }
        }
    }
    for (int i = 0; i < stateCnt; i++)
        trans[src][i] = dis[(bound + 4) * stateCnt + i];
    last[src] = inf;
    for (int o = 0; o < 24; o++)
        last[src] = min(last[src], dis[(bound + remDist) * stateCnt + getId(targetY, o)]);
}

bool sameMat(const vector<vector<long long>> &a, const vector<vector<long long>> &b) {
    for (int i = 0; i < stateCnt; i++)
        for (int j = 0; j < stateCnt; j++)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

bool sameVec(const vector<long long> &a, const vector<long long> &b) {
    for (int i = 0; i < stateCnt; i++)
        if (a[i] != b[i]) return false;
    return true;
}

void solve() {
    for (int i = 1; i <= 6; i++)
        cin >> val[i];
    long long x1, x2, dist;
    int y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    vector<Dice> dice = buildDice();
    map<array<int, 6>, int> mp;
    vector<array<int, 4>> rawNxt(24), nxt(24);
    for (int i = 0; i < 24; i++)
        mp[{dice[i].top, dice[i].bottom, dice[i].north, dice[i].south, dice[i].east, dice[i].west}] = i;
    for (int i = 0; i < 24; i++)
        for (int dir = 0; dir < 4; dir++) {
            Dice t = rollDice(dice[i], dir);
            rawNxt[i][dir] = mp[{t.top, t.bottom, t.north, t.south, t.east, t.west}];
        }
    dist = x2 - x1;
    int horDir = dist >= 0 ? 1 : -1;
    dist = abs(dist);
    long long blockCnt = dist / 4;
    targetY = y2;
    remDist = dist % 4;
    for (int i = 0; i < 24; i++) {
        nxt[i][0] = rawNxt[i][horDir == 1 ? 0 : 1];
        nxt[i][1] = rawNxt[i][horDir == 1 ? 1 : 0];
        nxt[i][2] = rawNxt[i][2];
        nxt[i][3] = rawNxt[i][3];
    }
    vector<vector<long long>> trans(stateCnt, vector<long long>(stateCnt, inf));
    vector<vector<long long>> prevTrans;
    vector<long long> last(stateCnt, inf), prevLast;
    int bound = 16;
    while (true) {
        for (int i = 0; i < stateCnt; i++)
            dijkstra(i, bound, dice, nxt, trans, last);
        if (!prevTrans.empty() && sameMat(trans, prevTrans) && sameVec(last, prevLast)) break;
        prevTrans = trans;
        prevLast = last;
        bound *= 2;
    }
    vector<long long> cur(stateCnt, inf);
    cur[getId(y1, 0)] = 0;
    while (blockCnt > 0) {
        if (blockCnt & 1) cur = mulVec(cur, trans);
        trans = mulMat(trans, trans);
        blockCnt >>= 1;
    }
    long long ans = inf;
    for (int i = 0; i < stateCnt; i++)
        ans = min(ans, cur[i] + last[i]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int i = 0; i < testCnt; i++) {
        if (i) cout << '\n';
        solve();
    }
    return 0;
}
