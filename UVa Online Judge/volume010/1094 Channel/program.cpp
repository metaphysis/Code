#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int maxN = 21, maxM = 10, maxS = 10010, hashSize = 13131;

int n, m, pre[maxN][maxM][maxS];
unsigned char opt[maxN][maxM][maxS];
char mp[maxN][maxM + 1];

struct HashMap {
    int head[hashSize], val[maxS], nxt[maxS], size;
    ull state[maxS];
    void init() {
        memset(head, -1, sizeof(head));
        size = 0;
    }
    void insert(ull s, int v, int x, int y, int id, int o) {
        int h = s % hashSize;
        for (int i = head[h]; i != -1; i = nxt[i]) {
            if (state[i] == s) {
                if (v > val[i]) {
                    val[i] = v;
                    pre[x][y][i] = id;
                    opt[x][y][i] = o;
                }
                return;
            }
        }
        state[size] = s;
        val[size] = v;
        pre[x][y][size] = id;
        opt[x][y][size] = o;
        nxt[size] = head[h];
        head[h] = size++;
    }
} hm[2];

HashMap *cur, *last;
int code[11], path[11], num[8], pathOut;

void decode(ull s) {
    for (int i = 0; i <= m; ++i) {
        code[i] = s & 7;
        path[i] = s & 8;
        s >>= 4;
    }
    pathOut = s & 8;
}

ull encode() {
    ull ret = pathOut;
    int cnt = 0;
    memset(num, -1, sizeof(num));
    for (int i = m; i >= 0; --i) {
        if (code[i] == 0) ret = (ret << 4) | path[i];
        else {
            if (num[code[i]] == -1) num[code[i]] = ++cnt;
            ret = (ret << 4) | num[code[i]] | path[i];
        }
    }
    return ret;
}

void add(ull s, int v, int x, int y, int id, int o) {
    cur->insert(s, v, x, y, id, o);
}

void update(int x, int y, int v, int id) {
    int lc = y == 0 ? 0 : code[y], uc = x == 0 ? 0 : code[y + 1];
    int lp = y == 0 ? 0 : path[y - 1], lup = x == 0 || y == 0 ? 0 : pathOut;
    int up = x == 0 ? 0 : path[y + 1], urp = x == 0 || y == m - 1 ? 0 : path[y + 2];
    pathOut = path[y + 1];
    if (x == 0 && y == 0) {
        path[y] = 8;
        code[y] = 7;
        code[y + 1] = 0;
        add(encode(), v + 1, x, y, id, 1);
        path[y] = 8;
        code[y] = 0;
        code[y + 1] = 7;
        add(encode(), v + 1, x, y, id, 1);
        return;
    }
    if (x == n - 1 && y == m - 1) {
        if (lc == 0 || uc == 0) {
            if (lc == 0) {
                if (lp) return;
                path[y] = 8;
                code[y] = code[y + 1] = 0;
                add(encode(), v + 1, x, y, id, 1);
            } else {
                if (up) return;
                path[y] = 8;
                code[y] = code[y + 1] = 0;
                add(encode(), v + 1, x, y, id, 1);
            }
        }
        return;
    }
    if (mp[x][y] == '#') {
        if (lc == 0 && uc == 0) {
            path[y] = 0;
            code[y] = code[y + 1] = 0;
            add(encode(), v, x, y, id, 0);
        }
        return;
    }
    if (lc == 0 && uc == 0) {
        path[y] = 0;
        code[y] = code[y + 1] = 0;
        add(encode(), v, x, y, id, 0);
        if (x == n - 1 || y == m - 1) return;
        if (lp || lup || up) return;
        path[y] = 8;
        code[y] = code[y + 1] = 7;
        add(encode(), v + 1, x, y, id, 1);
    } else if (lc == 0 || uc == 0) {
        if (lc) {
            if (up) return;
            if (y < m - 1) {
                path[y] = 8;
                code[y] = 0;
                code[y + 1] = lc;
                add(encode(), v + 1, x, y, id, 1);
            }
            if (x < n - 1) {
                if (urp) return;
                path[y] = 8;
                code[y] = lc;
                code[y + 1] = 0;
                add(encode(), v + 1, x, y, id, 1);
            }
        } else {
            if (lp) return;
            if (y < m - 1) {
                path[y] = 8;
                code[y] = 0;
                code[y + 1] = uc;
                add(encode(), v + 1, x, y, id, 1);
            }
            if (x < n - 1) {
                path[y] = 8;
                code[y] = uc;
                code[y + 1] = 0;
                add(encode(), v + 1, x, y, id, 1);
            }
        }
    } else if (lc != uc) {
        path[y] = 8;
        for (int i = 0; i <= m; ++i)
            if (code[i] == uc) code[i] = lc;
        code[y] = code[y + 1] = 0;
        add(encode(), v + 1, x, y, id, 1);
    }
}

void solve() {
    cur = &hm[0];
    last = &hm[1];
    last->init();
    last->insert(0, 0, 0, 0, 0, 0);
    int bit1 = (m + 1) * 4, bit2 = m * 4;
    for (int i = 0; i < n; ++i) {
        int size = last->size;
        for (int j = 0; j < size; ++j) {
            ull s = last->state[j];
            last->state[j] = (s & (1ULL << bit1)) | ((s & ((1ULL << bit2) - 1)) << 4);
        }
        for (int j = 0; j < m; ++j) {
            cur->init();
            size = last->size;
            for (int k = 0; k < size; ++k) {
                decode(last->state[k]);
                update(i, j, last->val[k], k);
            }
            swap(cur, last);
        }
    }
    int ans = 0, id = 0;
    for (int i = 0; i < last->size; ++i) {
        decode(last->state[i]);
        bool ok = true;
        for (int j = 0; j <= m; ++j) {
            if (code[j]) {
                ok = false;
                break;
            }
        }
        if (ok && last->val[i] > ans) {
            ans = last->val[i];
            id = i;
        }
    }
    for (int i = n - 1; i >= 0; --i)
        for (int j = m - 1; j >= 0; --j) {
            if (opt[i][j][id]) mp[i][j] = 'C';
            id = pre[i][j][id];
        }
    for (int i = 0; i < n; ++i) printf("%s\n", mp[i]);
    putchar('\n');
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int test = 0;
    while (scanf("%d%d", &n, &m) == 2 && n + m) {
        for (int i = 0; i < n; ++i) scanf("%s", mp[i]);
        printf("Case %d:\n", ++test);
        solve();
    }
    return 0;
}
