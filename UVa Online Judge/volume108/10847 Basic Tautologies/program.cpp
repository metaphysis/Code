// Basic Tautologies
// UVa ID: 10847
// Verdict: Accepted
// Submission Date: 2026-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    unsigned long long mask;
    bool cons;
};

int getIndex(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return 26 + (c - 'A');
    return -1;
}

string judge(const string& s) {
    stack<Node> st;
    bool valid = true;
    for (char ch : s) {
        if (ch == '-') {
            if (st.empty()) { valid = false; break; }
            Node cur = st.top(); st.pop();
            cur.cons = cur.cons ^ 1;
            st.push(cur);
        } else if (ch == '=') {
            if (st.size() < 2) { valid = false; break; }
            Node r = st.top(); st.pop();
            Node l = st.top(); st.pop();
            Node cur;
            cur.mask = l.mask ^ r.mask;
            cur.cons = l.cons ^ r.cons ^ 1;
            st.push(cur);
        } else {
            int idx = getIndex(ch);
            if (idx == -1) { valid = false; break; }
            Node cur;
            cur.mask = 1ULL << idx;
            cur.cons = 0;
            st.push(cur);
        }
    }
    if (!valid || st.size() != 1) return "incorrect";
    Node ans = st.top();
    if (ans.cons == 1 && ans.mask == 0) return "tautology";
    return "formula";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cin.ignore();
    for (int i = 0; i < N; ++i) {
        string s;
        getline(cin, s);
        cout << judge(s) << '\n';
    }
    return 0;
}
