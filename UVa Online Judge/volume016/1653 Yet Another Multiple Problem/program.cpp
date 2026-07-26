// Yet Another Multiple Problem
// UVa ID: 1653
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.060s
// https://blog.csdn.net/metaphysis/article/details/163173517

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000;
int parent[MAXN], digit[MAXN];          // 父余数、添加的数字
bool forbid[10];                        // 禁用标记

string buildAnswer(int r) {
    string ans;
    while (r != -1) {
        ans.push_back(char('0' + digit[r]));
        r = parent[r];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    int n, m, caseNo = 0;
    while (cin >> n >> m) {
        fill(forbid, forbid + 10, false);
        for (int i = 0; i < m; ++i) { int d; cin >> d; forbid[d] = true; }
        fill(parent, parent + n, -2);
        queue<int> q;
        bool found = false;
        string answer;
        for (int d = 1; d <= 9; ++d) {
            if (forbid[d]) continue;
            int r = d % n;
            if (r == 0) { answer = string(1, char('0' + d)); found = true; break; }
            if (parent[r] == -2) { parent[r] = -1; digit[r] = d; q.push(r); }
        }
        while (!found && !q.empty()) {
            int r = q.front(); q.pop();
            for (int d = 0; d <= 9; ++d) {
                if (forbid[d]) continue;
                int nr = (r * 10 + d) % n;
                if (parent[nr] != -2) continue;
                parent[nr] = r;
                digit[nr] = d;
                if (nr == 0) { answer = buildAnswer(nr); found = true; break; }
                q.push(nr);
            }
        }
        cout << "Case " << ++caseNo << ": " << (found ? answer : "-1") << '\n';
    }
    return 0;
}
