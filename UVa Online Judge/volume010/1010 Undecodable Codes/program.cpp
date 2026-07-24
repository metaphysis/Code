// Undecodable Codes
// UVa ID: 1010
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 1.140s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<string> code;
int m;

int lcp(const string& a, const string& b) {
    int n = min(a.size(), b.size());
    int i = 0;
    while (i < n && a[i] == b[i]) ++i;
    return i;
}

struct StateKey {
    string s1, s2;
    bool e1, e2;
    bool operator==(const StateKey& o) const {
        return s1 == o.s1 && s2 == o.s2 && e1 == o.e1 && e2 == o.e2;
    }
};

struct KeyHash {
    size_t operator()(const StateKey& k) const {
        size_t h1 = hash<string>()(k.s1);
        size_t h2 = hash<string>()(k.s2);
        return h1 ^ (h2 << 1) ^ (k.e1 ? 0x9e3779b9 : 0) ^ (k.e2 ? 0x85ebca6b : 0);
    }
};

struct Node {
    int len;
    string path;
    string s1, s2;
    bool e1, e2;
};

struct Cmp {
    bool operator()(const Node& a, const Node& b) const {
        if (a.len != b.len) return a.len > b.len;
        return a.path > b.path;
    }
};

pair<int, string> solveCase() {
    unordered_map<StateKey, pair<int, string>, KeyHash> best;
    priority_queue<Node, vector<Node>, Cmp> pq;
    best.reserve(100000);

    auto addState = [&](Node nd) {
        StateKey key{nd.s1, nd.s2, nd.e1, nd.e2};
        auto it = best.find(key);
        if (it == best.end() || nd.len < it->second.first ||
            (nd.len == it->second.first && nd.path < it->second.second)) {
            best[key] = {nd.len, nd.path};
            pq.push(std::move(nd));
        }
    };

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == j) continue;
            Node nd;
            nd.len = 0;
            nd.path = "";
            nd.s1 = code[i];
            nd.s2 = code[j];
            nd.e1 = nd.e2 = false;
            addState(std::move(nd));
        }
    }

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        StateKey key{cur.s1, cur.s2, cur.e1, cur.e2};
        auto it = best.find(key);
        if (it == best.end() || cur.len != it->second.first || cur.path != it->second.second)
            continue;

        if (cur.s1.empty() && cur.s2.empty()) {
            if (cur.e1 && cur.e2) return {cur.len, cur.path};
            if (!cur.e1) {
                Node nxt = cur;
                nxt.e1 = true;
                addState(std::move(nxt));
                for (int k = 0; k < m; ++k) {
                    Node nxt2 = cur;
                    nxt2.s1 = code[k];
                    nxt2.e1 = false;
                    addState(std::move(nxt2));
                }
            }
            if (!cur.e2) {
                Node nxt = cur;
                nxt.e2 = true;
                addState(std::move(nxt));
                for (int k = 0; k < m; ++k) {
                    Node nxt2 = cur;
                    nxt2.s2 = code[k];
                    nxt2.e2 = false;
                    addState(std::move(nxt2));
                }
            }
            continue;
        }

        if (!cur.s1.empty() && !cur.s2.empty()) {
            int L = lcp(cur.s1, cur.s2);
            if (L == 0) continue;
            Node nxt = cur;
            nxt.len += L;
            nxt.path += cur.s1.substr(0, L);
            nxt.s1 = cur.s1.substr(L);
            nxt.s2 = cur.s2.substr(L);
            addState(std::move(nxt));
            continue;
        }

        if (cur.s1.empty() && !cur.s2.empty()) {
            if (cur.e1) continue;
            for (int k = 0; k < m; ++k) {
                Node nxt = cur;
                nxt.s1 = code[k];
                addState(std::move(nxt));
            }
            continue;
        }

        if (!cur.s1.empty() && cur.s2.empty()) {
            if (cur.e2) continue;
            for (int k = 0; k < m; ++k) {
                Node nxt = cur;
                nxt.s2 = code[k];
                addState(std::move(nxt));
            }
            continue;
        }
    }
    return {0, ""};
}

void printCode(int caseNo, int len, const string& s) {
    cout << "Code " << caseNo << ": " << len << " bits" << endl;
    for (size_t i = 0; i < s.size(); i += 20)
        cout << s.substr(i, 20) << endl;
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 1;
    while (cin >> m && m != 0) {
        code.resize(m);
        for (int i = 0; i < m; ++i) cin >> code[i];
        pair<int, string> ans = solveCase();
        printCode(caseNo++, ans.first, ans.second);
    }
    return 0;
}
