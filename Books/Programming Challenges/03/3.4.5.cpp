#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1024;

void getNext(const string &T, int next[]) {
    int m = T.size();
    next[0] = m;
    // [pl, pr) 是当前与 T 前缀相同的最右区间
    int pl = 0, pr = 0;
    for (int k = 1; k < m; k++) {
        int j = k - pl;
        // 只有当已知匹配到达 pr 时，才需要继续比较
        if (k >= pr || k + next[j] >= pr) {
            if (k >= pr) pr = k;
            while (pr < m && T[pr] == T[pr - k]) pr++;
            next[k] = pr - k;
            pl = k;
        } else next[k] = next[j];
    }
}

void getExtend(const string &S, const string &T, int extend[], int next[]) {
    int n = S.size(), m = T.size();
    getNext(T, next);
    // [pl, pr) 是当前与 T 前缀相同的最右区间
    int pl = 0, pr = 0;
    for (int k = 0; k < n; k++) {
        int j = k - pl;
        if (k >= pr || k + next[j] >= pr) {
            if (k >= pr) pr = k;
            while (pr < n && pr - k < m && S[pr] == T[pr - k]) pr++;
            extend[k] = pr - k;
            pl = k;
        } else extend[k] = next[j];
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
