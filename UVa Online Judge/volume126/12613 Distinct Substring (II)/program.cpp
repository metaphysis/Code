// Distinct Substring (II)
// UVa ID: 12613
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.240s

#include <bits/stdc++.h>
using namespace std;

struct SuffixAutomaton {
    struct State {
        int len, link, next[26];
        State() : len(0), link(-1) {
            memset(next, -1, sizeof(next));
        }
    };
    vector<State> st;
    int last;
    SuffixAutomaton(int maxLen = 0) {
        st.reserve(maxLen * 2);
        st.push_back(State());
        last = 0;
    }
    void extend(int c) {
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};

vector<int> prefixFunction(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int main() {
    int tc;
    scanf("%d", &tc);
    for (int caseNo = 1; caseNo <= tc; ++caseNo) {
        string S;
        long long K;
        cin >> S >> K;
        int n = (int)S.size();
        vector<int> pi = prefixFunction(S);
        int cand = n - pi[n - 1];
        int p = (n % cand == 0) ? cand : n;
        string U = S + S;
        SuffixAutomaton sam(2 * n);
        for (char ch : U) sam.extend(ch - 'a');
        long long A = 0;
        for (int v = 1; v < (int)sam.st.size(); ++v) {
            int maxLen = sam.st[v].len;
            int minLen = sam.st[sam.st[v].link].len + 1;
            int limit = min(maxLen, n);
            if (limit >= minLen) A += (limit - minLen + 1);
        }
        long long sumG;
        if (p >= n) {
            sumG = 1LL * n * (n - 1) / 2;
        } else {
            sumG = 1LL * p * (p - 1) / 2 + 1LL * (n - p) * p;
        }
        long long count1 = 1LL * n * (K - 2) + 1;
        long long ans = A + 1LL * p * count1 + sumG;
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
