// Tic-Tac-Tough
// UVa ID: 11010
// Verdict: Accepted
// Submission Date: 2026-06-18
// UVa Run Time: 0.410s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int win[] = {7, 56, 73, 84, 146, 273, 292, 448};
int dp[513][513][2], taken[1001];

int dfs(int used, int mask, int turn) {
    if (~dp[used][mask][turn]) return dp[used][mask][turn];
    for (int i = 0; i < 8; i++) {
        if ((used & win[i]) == win[i]) {
            if ((mask & win[i]) == win[i]) return 1;
            else if ((mask & win[i]) == 0) return 0;
        }
    }
    if ((used & 511) == 511) return -1;
    int best = turn ^ 1, available = (~used & 511);
    while (available) {
        int bit = available & (~available + 1);
        available ^= bit;
        int r = dfs(used | bit, mask | (bit * turn), turn ^ 1);
        if (best != turn) {
            if (r == turn) best = turn;
            else if (r == -1) best = -1;
        }
    }
    return dp[used][mask][turn] = best;
}

struct Game {
    int ms, js, idx, priority;
    Game(int a = 0, int b = 0, int c = 0) : ms(a), js(b), idx(c) {
        if (a == 0 && b == 1) priority = 0;
        else if ((a == 0 && b == -1) || (a == -1 && b == 1)) priority = 1;
        else priority = 2;
    }
    bool operator<(const Game& o) const { return priority < o.priority; }
} johnny[1001], mary[1001];

int main() {
    memset(dp, -1, sizeof dp);
    string line;
    int n, cs = 1;
    while (cin >> n, n) {
        for (int i = 0; i < n; i++) {
            cin >> line;
            int used = 0, mask = 0;
            for (int p = 0; p < 9; p++)
                if (line[p] != '.') {
                    used |= (1 << p);
                    if (line[p] == 'X') mask |= (1 << p);
                }
            int a = dfs(used, mask, 0), b = dfs(used, mask, 1);
            mary[i] = {a, b, i};
            swap(a, b);
            if (~a) a = 1 - a;
            if (~b) b = 1 - b;
            johnny[i] = {a, b, i};
        }
        sort(mary, mary + n);
        sort(johnny, johnny + n);
        int score = 0, done = 0, pm = 0, pj = 0;
        memset(taken, 0, sizeof taken);
        while (done < n) {
            while (taken[johnny[pj].idx]) pj++;
            taken[johnny[pj].idx] = true;
            while (taken[mary[pm].idx]) pm++;
            taken[mary[pm].idx] = true;
            if (mary[pm].ms == 0) score--;
            else if (mary[pm].ms == 1) score++;
            if (johnny[pj].ms == 0) score++;
            else if (johnny[pj].ms == 1) score--;
            done += 2;
        }
        cout << "Case " << cs++ << ": ";
        if (score < 0) cout << "Mary wins.\n";
        else if (score > 0) cout << "Johnny wins.\n";
        else cout << "Draw.\n";
    }
    return 0;
}
