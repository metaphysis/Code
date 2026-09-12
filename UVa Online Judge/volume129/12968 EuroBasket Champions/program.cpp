#include <bits/stdc++.h>
using namespace std;

int score[10][12];
vector<int> cur, ans;
__int128 bestScore;

void dfs(int pos, int cnt) {
    if (cnt == 5) {
        __int128 teamScore = 1;
        for (int j = 0; j < 12; j++) {
            int mx = 0;
            for (int k : cur)
                mx = max(mx, score[k][j]);
            teamScore *= mx;
        }
        if (ans.empty() || teamScore > bestScore) {
            bestScore = teamScore;
            ans = cur;
        }
        return;
    }
    for (int i = pos; i < 10; i++) {
        cur.push_back(i);
        dfs(i + 1, cnt + 1);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    while (test--) {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 12; j++)
                cin >> score[i][j];
        cur.clear();
        ans.clear();
        dfs(0, 0);
        for (int i = 0; i < 5; i++) {
            if (i > 0)
                cout << ' ';
            cout << ans[i] + 4;
        }
        cout << '\n';
    }
    return 0;
}
