#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;
constexpr int MAX_N = 101;
constexpr int MAX_L = 301;
constexpr int MAX_STATE = MAX_N * MAX_N * MAX_L;
constexpr uint16_t INF = 0x3fff;

string a, b, c;
int n, m, l, width;
int baseId[MAX_N][MAX_N];
int posA[MAX_N][MAX_L], posB[MAX_N][MAX_L];
uint16_t distDp[MAX_STATE];
int ways[MAX_STATE];

void buildBase() {
    width = l + 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            baseId[i][j] = (i * (m + 1) + j) * width;
}

void buildNextPositions() {
    for (int i = 0; i < n; ++i) {
        posA[i][l] = -1;
        for (int k = l - 1; k >= 0; --k) {
            posA[i][k] = posA[i][k + 1];
            if (c[k] == a[i]) posA[i][k] = k;
        }
    }
    for (int j = 0; j < m; ++j) {
        posB[j][l] = -1;
        for (int k = l - 1; k >= 0; --k) {
            posB[j][k] = posB[j][k + 1];
            if (c[k] == b[j]) posB[j][k] = k;
        }
    }
}

void buildDp() {
    const int total = (n + 1) * (m + 1) * width;
    fill(distDp, distDp + total, INF);
    fill(ways, ways + total, 0);
    const int endBase = baseId[n][m];
    for (int k = 0; k <= l; ++k) {
        distDp[endBase + k] = 0;
        ways[endBase + k] = 1;
    }
    for (int i = n; i >= 0; --i) {
        for (int j = m; j >= 0; --j) {
            if (i == n && j == m) continue;
            const bool hasA = i < n;
            const bool hasB = j < m;
            const bool same = hasA && hasB && a[i] == b[j];
            const int curBase = baseId[i][j];
            int aBase = -1;
            int bBase = -1;
            if (hasA) aBase = baseId[i + 1][j + same];
            if (hasB && !same) bBase = baseId[i][j + 1];
            // 至少需要 max(n - i, m - j) 个字符，超出 C 的剩余长度的状态必然无解。
            const int need = max(n - i, m - j);
            const int firstK = l - need;
            for (int k = firstK; k >= 0; --k) {
                int best = INF;
                int count = 0;
                if (hasA) {
                    const int p = posA[i][k];
                    if (p != -1) {
                        const int to = aBase + p + 1;
                        if (distDp[to] != INF) {
                            const int value = distDp[to] + 1;
                            if (value < best) {
                                best = value;
                                count = ways[to];
                            } else if (value == best) {
                                count += ways[to];
                                if (count >= MOD) count -= MOD;
                            }
                        }
                    }
                }
                if (bBase != -1) {
                    const int p = posB[j][k];
                    if (p != -1) {
                        const int to = bBase + p + 1;
                        if (distDp[to] != INF) {
                            const int value = distDp[to] + 1;
                            if (value < best) {
                                best = value;
                                count = ways[to];
                            } else if (value == best) {
                                count += ways[to];
                                if (count >= MOD) count -= MOD;
                            }
                        }
                    }
                }
                distDp[curBase + k] = static_cast<uint16_t>(best);
                ways[curBase + k] = count;
            }
        }
    }
}

string buildAnswer() {
    string answer;
    int i = 0, j = 0, k = 0;
    while (i < n || j < m) {
        const int current = baseId[i][j] + k;
        int bestChar = 256;
        int nextI = -1, nextJ = -1, nextK = -1;
        if (i < n) {
            const int p = posA[i][k];
            if (p != -1) {
                const int ni = i + 1;
                const int nj = j + (j < m && a[i] == b[j]);
                const int to = baseId[ni][nj] + p + 1;
                if (distDp[to] != INF && distDp[to] + 1 == distDp[current] &&
                    static_cast<unsigned char>(a[i]) < bestChar) {
                    bestChar = static_cast<unsigned char>(a[i]);
                    nextI = ni;
                    nextJ = nj;
                    nextK = p + 1;
                }
            }
        }
        if (j < m && (i == n || a[i] != b[j])) {
            const int p = posB[j][k];
            if (p != -1) {
                const int ni = i;
                const int nj = j + 1;
                const int to = baseId[ni][nj] + p + 1;
                if (distDp[to] != INF && distDp[to] + 1 == distDp[current] &&
                    static_cast<unsigned char>(b[j]) < bestChar) {
                    bestChar = static_cast<unsigned char>(b[j]);
                    nextI = ni;
                    nextJ = nj;
                    nextK = p + 1;
                }
            }
        }
        answer.push_back(static_cast<char>(bestChar));
        i = nextI;
        j = nextJ;
        k = nextK;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> a >> b >> c;
        n = static_cast<int>(a.size());
        m = static_cast<int>(b.size());
        l = static_cast<int>(c.size());
        buildBase();
        buildNextPositions();
        buildDp();
        const int start = baseId[0][0];
        cout << "Case " << tc << ": " << ways[start] << '\n';
        if (distDp[start] == INF)cout << "NOT FOUND\n";
        else cout << buildAnswer() << '\n';
    }
    return 0;
}
