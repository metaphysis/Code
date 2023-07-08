// Shortest Names
// UVa ID: 12506
// Verdict: Accepted
// Submission Date: 2023-07-08
// UVa Run Time: 0.050s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000100, CHILDREN = 26, OFFSET = 'a';

struct Trie {
    int cnt, root, child[MAXN][CHILDREN], ending[MAXN];

    void initialize() {
        root = cnt = 1;
        memset(child[root], 0, sizeof(child[root]));
        ending[root] = 0;
    }

    void insert(const string s) {
        int *current = &root;
        for (auto c : s) {
            current = &child[*current][c - OFFSET];
            if (!(*current)) {
                *current = ++cnt;
                memset(child[cnt], 0, sizeof(child[cnt]));
                ending[*current] = 1;
            } else ending[*current]++;
        }
    }

    int query(const string s) {
        int *current = &root, length = 0;
        for (auto c : s) {
            current = &child[*current][c - OFFSET];
            length++;
            if (ending[*current] == 1) return length;
        }
    }
} t;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    while (T--) {
        t.initialize();
        cin >> n;
        string s[1010];
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            t.insert(s[i]);
        }
        int r = 0;
        for (int i = 0; i < n; i++) r += t.query(s[i]);
        cout << r << '\n';
    }
    return 0;
}
