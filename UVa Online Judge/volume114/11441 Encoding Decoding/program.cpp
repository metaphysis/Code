#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

const int mod = 10007;

struct Node {
    int next[5];
    bool isEnd;
    Node() {
        memset(next, -1, sizeof(next));
        isEnd = false;
    }
};

int leafCnt, branchCnt;
vector<Node> trie;
vector<int> freeDp;

vector<int> mulDp(const vector<int>& a, const vector<int>& b) {
    vector<int> c(leafCnt + 1, 0);
    for (int i = 0; i <= leafCnt; i++)
        if (a[i])
            for (int j = 0; i + j <= leafCnt; j++)
                if (b[j])
                    c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
    return c;
}

vector<int> getDp(int u) {
    vector<int> cur(leafCnt + 1, 0);
    cur[0] = 1;
    if (trie[u].isEnd) return cur;
    for (int i = 0; i < branchCnt; i++) {
        vector<int> sub;
        if (trie[u].next[i] == -1) sub = freeDp;
        else sub = getDp(trie[u].next[i]);
        cur = mulDp(cur, sub);
    }
    return cur;
}

vector<int> buildFreeDp() {
    int maxInner = (leafCnt - 1) / (branchCnt - 1);
    int maxFact = branchCnt * maxInner;
    vector<cpp_int> fac(maxFact + 1);
    vector<int> dp(leafCnt + 1, 0);
    fac[0] = 1;
    for (int i = 1; i <= maxFact; i++)
        fac[i] = fac[i - 1] * i;
    for (int i = 0; i <= maxInner; i++) {
        int leaves = (branchCnt - 1) * i + 1;
        cpp_int ways = fac[branchCnt * i];
        ways /= fac[i];
        ways /= fac[(branchCnt - 1) * i];
        ways /= leaves;
        dp[leaves] = (ways % mod).convert_to<int>();
    }
    return dp;
}

void insertCode(const string& s) {
    int u = 0;
    for (char ch : s) {
        int v = ch - '0';
        if (trie[u].next[v] == -1) {
            trie[u].next[v] = trie.size();
            trie.push_back(Node());
        }
        u = trie[u].next[v];
    }
    trie[u].isEnd = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    while (testCnt--) {
        int knownCnt;
        cin >> knownCnt >> leafCnt >> branchCnt;
        trie.clear();
        trie.push_back(Node());
        for (int i = 0; i < knownCnt; i++) {
            string s;
            cin >> s;
            insertCode(s);
        }
        freeDp = buildFreeDp();
        if (knownCnt == 0) cout << freeDp[leafCnt] << '\n';
        else {
            vector<int> ans = getDp(0);
            cout << ans[leafCnt] << '\n';
        }
    }
    return 0;
}
