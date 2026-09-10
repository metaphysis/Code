// Reading a Quadtree
// UVa ID: 11948
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
char grid[MAXN][MAXN];
string tree;
int idx;

void buildTree(int r1, int c1, int r2, int c2) {
    char ch = tree[idx++];
    if (ch == '1') {
        for (int i = r1; i < r2; ++i)
            for (int j = c1; j < c2; ++j)
                grid[i][j] = '1';
    } else if (ch == '*') {
        int mr = (r1 + r2) / 2;
        int mc = (c1 + c2) / 2;
        buildTree(r1, c1, mr, mc);
        buildTree(r1, mc, mr, c2);
        buildTree(mr, c1, r2, mc);
        buildTree(mr, mc, r2, c2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        int L;
        cin >> L >> tree;
        if (L <= 0 || (L & (L - 1)) != 0) {
            cout << "Invalid length\n";
            continue;
        }
        for (int i = 0; i < L; ++i)
            for (int j = 0; j < L; ++j)
                grid[i][j] = '0';
        idx = 0;
        buildTree(0, 0, L, L);
        bool first = true;
        for (int i = 0; i < L; ++i) {
            int j = 0;
            while (j < L) {
                if (grid[i][j] == '0') {
                    ++j;
                    continue;
                }
                int start = j;
                while (j < L && grid[i][j] == '1') ++j;
                int end = j - 1;
                if (!first) cout << ',';
                first = false;
                if (start == end) cout << '(' << start + 1 << ',' << i + 1 << ')';
                else cout << '(' << start + 1 << '-' << end + 1 << ',' << i + 1 << ')';
            }
        }
        cout << '\n';
    }

    return 0;
}
