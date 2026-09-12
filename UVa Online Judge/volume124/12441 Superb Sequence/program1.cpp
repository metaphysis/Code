#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxN = 101;
const int maxL = 301;
const int maxState = maxN * maxN * maxL;
const unsigned char inf = 255;

string strA, strB, strC;
int n, m, l, width;
int baseId[maxN][maxN];
int posA[maxN][maxL], posB[maxN][maxL];
unsigned char dis[maxState];
int ways[maxState];

void buildBase() {
    width = l + 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            baseId[i][j] = (i * (m + 1) + j) * width;
}

void buildPos() {
    for (int i = 0; i < n; i++) {
        posA[i][l] = -1;
        for (int k = l - 1; k >= 0; k--) {
            posA[i][k] = posA[i][k + 1];
            if (strC[k] == strA[i]) posA[i][k] = k;
        }
    }
    for (int j = 0; j < m; j++) {
        posB[j][l] = -1;
        for (int k = l - 1; k >= 0; k--) {
            posB[j][k] = posB[j][k + 1];
            if (strC[k] == strB[j]) posB[j][k] = k;
        }
    }
}

void buildDp() {
    int total = (n + 1) * (m + 1) * width;
    memset(dis, inf, total * sizeof(unsigned char));
    memset(ways, 0, total * sizeof(int));
    int endBase = baseId[n][m];
    for (int k = 0; k <= l; k++) {
        dis[endBase + k] = 0;
        ways[endBase + k] = 1;
    }
    for (int i = n; i >= 0; i--)
        for (int j = m; j >= 0; j--) {
            if (i == n && j == m) continue;
            bool hasA = i < n;
            bool hasB = j < m;
            bool same = hasA && hasB && strA[i] == strB[j];
            int curBase = baseId[i][j];
            int aBase = -1, bBase = -1;
            if (hasA) aBase = baseId[i + 1][j + same];
            if (hasB && !same) bBase = baseId[i][j + 1];
            for (int k = l - 1; k >= 0; k--) {
                int best = inf, count = 0;
                if (hasA) {
                    int p = posA[i][k];
                    if (p != -1) {
                        int to = aBase + p + 1;
                        if (dis[to] != inf) {
                            int value = dis[to] + 1;
                            if (value < best) {
                                best = value;
                                count = ways[to];
                            } else if (value == best) {
                                count += ways[to];
                                if (count >= mod) count -= mod;
                            }
                        }
                    }
                }
                if (bBase != -1) {
                    int p = posB[j][k];
                    if (p != -1) {
                        int to = bBase + p + 1;
                        if (dis[to] != inf) {
                            int value = dis[to] + 1;
                            if (value < best) {
                                best = value;
                                count = ways[to];
                            } else if (value == best) {
                                count += ways[to];
                                if (count >= mod) count -= mod;
                            }
                        }
                    }
                }
                dis[curBase + k] = best;
                ways[curBase + k] = count;
            }
        }
}

string getAnswer() {
    string ans;
    int i = 0, j = 0, k = 0;
    while (i < n || j < m) {
        int cur = baseId[i][j] + k;
        int best = 256, ni = -1, nj = -1, nk = -1;
        if (i < n) {
            int p = posA[i][k];
            if (p != -1) {
                int ti = i + 1;
                int tj = j + (j < m && strA[i] == strB[j]);
                int to = baseId[ti][tj] + p + 1;
                if (dis[to] != inf && dis[to] + 1 == dis[cur] && (unsigned char)strA[i] < best) {
                    best = (unsigned char)strA[i];
                    ni = ti;
                    nj = tj;
                    nk = p + 1;
                }
            }
        }
        if (j < m && (i == n || strA[i] != strB[j])) {
            int p = posB[j][k];
            if (p != -1) {
                int ti = i;
                int tj = j + 1;
                int to = baseId[ti][tj] + p + 1;
                if (dis[to] != inf && dis[to] + 1 == dis[cur] && (unsigned char)strB[j] < best) {
                    best = (unsigned char)strB[j];
                    ni = ti;
                    nj = tj;
                    nk = p + 1;
                }
            }
        }
        ans.push_back((char)best);
        i = ni;
        j = nj;
        k = nk;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> strA >> strB >> strC;
        n = strA.size();
        m = strB.size();
        l = strC.size();
        width = l + 1;
        buildBase();
        buildPos();
        buildDp();
        int start = baseId[0][0];
        cout << "Case " << tc << ": " << ways[start] << '\n';
        if (dis[start] == inf)
            cout << "NOT FOUND\n";
        else
            cout << getAnswer() << '\n';
    }
    return 0;
}
