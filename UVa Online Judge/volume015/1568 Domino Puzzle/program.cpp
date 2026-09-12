#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long dis, pre;
    int x, y;
};

int deg[7], fa[7];

int findSet(int x) {
    if (fa[x] == x) return x;
    return fa[x] = findSet(fa[x]);
}

long long getKey(int lab[], int mask) {
    long long code = 0;
    for (int i = 5; i >= 0; i--)
        code = code * 7 + lab[i];
    return code * 64 + mask;
}

void decodeKey(long long key, int lab[], int &mask) {
    mask = key % 64;
    key /= 64;
    for (int i = 0; i < 6; i++) {
        lab[i] = key % 7;
        key /= 7;
    }
}

void normalize(int lab[]) {
    int mp[8] = {}, cnt = 0;
    for (int i = 0; i < 6; i++) {
        if (lab[i] && !mp[lab[i]]) mp[lab[i]] = ++cnt;
        if (lab[i]) lab[i] = mp[lab[i]];
    }
}

long long mergeState(long long key, int x, int y) {
    int lab[6], mask, a, b;
    decodeKey(key, lab, mask);
    if (!lab[x]) lab[x] = 7;
    if (!lab[y]) lab[y] = 7;
    a = lab[x];
    b = lab[y];
    if (a != b) {
        for (int i = 0; i < 6; i++)
            if (lab[i] == b) lab[i] = a;
    }
    normalize(lab);
    mask ^= 1 << x;
    mask ^= 1 << y;
    return getKey(lab, mask);
}

bool isValid(long long key) {
    int lab[6], mask, root = 0, odd = 0;
    decodeKey(key, lab, mask);
    for (int i = 0; i < 6; i++) {
        if (lab[i] && !root) root = lab[i];
        if (lab[i] && lab[i] != root) return false;
        if (mask & (1 << i)) odd++;
    }
    return odd <= 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        memset(deg, 0, sizeof(deg));
        for (int i = 1; i <= 6; i++) fa[i] = i;
        for (int i = 0; i < n; i++) {
            int x, y, fx, fy;
            cin >> x >> y;
            deg[x]++;
            deg[y]++;
            fx = findSet(x);
            fy = findSet(y);
            if (fx != fy) fa[fx] = fy;
        }
        int lab[6] = {}, mp[7] = {}, cnt = 0, mask = 0;
        for (int i = 1; i <= 6; i++) {
            if (deg[i]) {
                int rt = findSet(i);
                if (!mp[rt]) mp[rt] = ++cnt;
                lab[i - 1] = mp[rt];
            }
            if (deg[i] & 1) mask |= 1 << (i - 1);
        }
        long long start = getKey(lab, mask), endKey = -1;
        unordered_map<long long, Info> dis;
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
        dis[start] = {0, -1, -1, -1};
        pq.push({0, start});
        while (!pq.empty()) {
            long long curDis = pq.top().first, key = pq.top().second;
            pq.pop();
            if (dis[key].dis != curDis) continue;
            if (isValid(key)) {
                endKey = key;
                break;
            }
            for (int i = 0; i < 6; i++) {
                for (int j = i + 1; j < 6; j++) {
                    long long nxt = mergeState(key, i, j);
                    long long nxtDis = curDis + i + j + 2;
                    if (!dis.count(nxt) || nxtDis < dis[nxt].dis) {
                        dis[nxt] = {nxtDis, key, i, j};
                        pq.push({nxtDis, nxt});
                    }
                }
            }
        }
        long long targetKey = endKey, minCost = dis[targetKey].dis, curKey = targetKey;
        pair<int, int> ans[20000];
        int ansCnt = 0;
        while (curKey != start) {
            Info cur = dis[curKey];
            ans[ansCnt++] = {cur.x + 1, cur.y + 1};
            curKey = cur.pre;
        }
        cout << minCost << '\n';
        cout << ansCnt << '\n';
        for (int i = ansCnt - 1; i >= 0; i--)
            cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
    return 0;
}
