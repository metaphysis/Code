#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1024;

void getNext(string &T, int next[])
{
    int pl = 0, pr = 0, m = T.size();
    next[0] = m;
    for (int i = 1; i < m; i++) {
        if (i >= pr || i + next[i - pl] >= pr) {
            if (i >= pr) pr = i;
            while (pr < m && T[pr] == T[pr - i]) pr++;
            next[i] = pr - i, pl = i;
        }
        else next[i] = next[i - pl];
    }
}

void getExtend(string &S, string &T, int extend[], int next[])
{
    int pl = 0, pr = 0;
    int n = S.size(), m = T.size();
    getNext(T, next);
    for (int i = 0; i < n; i++) {
        if (i >= pr || i + next[i - pl] >= pr) {
            if (i >= pr) pr = i;
            while (pr < n && pr - i < m && S[pr] == T[pr - i]) pr++;
            extend[i] = pr - i, pl = i;
        }
        else extend[i] = next[i - pl];
    }
}

int main(int argc, char *argv[])
{
    string S, T;
    int next[MAXN], extend[MAXN];

    while (cin >> S >> T)
    {
        getExtend(S, T, extend, next);
        cout << "  next:";
        for (int i = 0; i < T.size(); i++) cout << ' ' << next[i];
        cout << '\n';
        cout << "extend:";
        for (int i = 0; i < S.size(); i++) cout << ' ' << extend[i];
        cout << '\n';
    }

    return 0;
}
