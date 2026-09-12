#include <bits/stdc++.h>
using namespace std;

vector<array<int, 3>> pats;
int cardCnt[9], cardUse[9], ans;

int getVal(string s) {
    if (s == "um") return 0;
    if (s == "dois") return 1;
    return 2;
}

int getFig(string s) {
    if (s == "circulo" || s == "circulos") return 0;
    if (s == "quadrado" || s == "quadrados") return 1;
    return 2;
}

bool isSet(int a, int b, int c) {
    int na = a / 3, nb = b / 3, nc = c / 3;
    int fa = a % 3, fb = b % 3, fc = c % 3;
    bool numOk = (na == nb && nb == nc) || (na != nb && na != nc && nb != nc);
    bool figOk = (fa == fb && fb == fc) || (fa != fb && fa != fc && fb != fc);
    return numOk && figOk;
}

void buildPats() {
    pats.clear();
    for (int i = 0; i < 9; ++i)
        for (int j = i + 1; j < 9; ++j)
            for (int k = j + 1; k < 9; ++k) {
                if (isSet(i, j, k)) pats.push_back({i, j, k});
            }
}

void dfs(int pos, int mixCnt) {
    if (pos == (int)pats.size()) {
        int cur = mixCnt;
        for (int i = 0; i < 9; ++i)
            cur += (cardCnt[i] - cardUse[i]) / 3;
        ans = max(ans, cur);
        return;
    }
    dfs(pos + 1, mixCnt);
    auto p = pats[pos];
    for (int t = 1; t <= 2; ++t) {
        bool ok = true;
        for (int i = 0; i < 3; ++i)
            if (cardUse[p[i]] + t > cardCnt[p[i]]) ok = false;
        if (!ok) break;
        for (int i = 0; i < 3; ++i) cardUse[p[i]] += t;
        dfs(pos + 1, mixCnt + t);
        for (int i = 0; i < 3; ++i) cardUse[p[i]] -= t;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildPats();
    int n;
    while (cin >> n && n) {
        memset(cardCnt, 0, sizeof(cardCnt));
        memset(cardUse, 0, sizeof(cardUse));
        for (int i = 0; i < n; ++i) {
            string num, fig;
            cin >> num >> fig;
            ++cardCnt[getVal(num) * 3 + getFig(fig)];
        }
        ans = 0;
        dfs(0, 0);
        cout << ans << '\n';
    }
    return 0;
}
