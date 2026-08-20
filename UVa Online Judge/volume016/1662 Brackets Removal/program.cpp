// Brackets Removal
// UVa ID: 1662
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct Bracket {
    int l, r, len;
    bool operator<(const Bracket& other) const {
        if (len != other.len) return len < other.len;
        return l < other.l;
    }
};

char expr[MAXN];
int vis[MAXN];
Bracket brackets[MAXN];

int getOpType(int pos) {
    if (expr[pos] == '+') return 1;
    if (expr[pos] == '-') return 2;
    if (expr[pos] == '*') return 3;
    if (expr[pos] == '/') return 4;
    return -1;
}

void solve() {
    memset(vis, 0, sizeof(vis));
    int len = strlen(expr + 1);
    stack<int> st;
    int cnt = 0;

    for (int i = 1; i <= len; ++i) {
        if (expr[i] == '(') st.push(i);
        else if (expr[i] == ')') {
            int l = st.top(); st.pop();
            brackets[cnt].l = l;
            brackets[cnt].r = i;
            brackets[cnt].len = i - l + 1;
            ++cnt;
        }
    }

    sort(brackets, brackets + cnt);

    for (int i = 0; i < cnt; ++i) {
        int L = brackets[i].l, R = brackets[i].r;
        int leftOp = getOpType(L - 1);
        int rightOp = getOpType(R + 1);
        bool canRemove = true;

        if (leftOp == 3 || leftOp == 4 || rightOp == 3 || rightOp == 4) {
            for (int j = L + 1; j < R; ++j) {
                if (vis[j] == -1) continue;
                if (expr[j] == '+' || expr[j] == '-') {
                    canRemove = false;
                    break;
                }
            }
            if (!canRemove) {
                for (int j = L; j <= R; ++j) {
                    if (vis[j] == 0) vis[j] = -1;
                }
            }
        }

        if (!canRemove) continue;

        if (leftOp == -1 || leftOp == 1) {
            vis[L] = vis[R] = 1;
        } else if (leftOp == 2) {
            vis[L] = vis[R] = 1;
            for (int j = L + 1; j < R; ++j) {
                if (vis[j] == -1) continue;
                if (expr[j] == '+') expr[j] = '-';
                else if (expr[j] == '-') expr[j] = '+';
            }
        } else if (leftOp == 3) {
            vis[L] = vis[R] = 1;
        } else if (leftOp == 4) {
            vis[L] = vis[R] = 1;
            for (int j = L + 1; j < R; ++j) {
                if (vis[j] == -1) continue;
                if (expr[j] == '*') expr[j] = '/';
                else if (expr[j] == '/') expr[j] = '*';
            }
        }
    }

    for (int i = 1; i <= len; ++i) {
        if (vis[i] != 1) putchar(expr[i]);
    }
    putchar('\n');
}

int main() {
    while (scanf("%s", expr + 1) == 1) {
        solve();
    }
    return 0;
}
