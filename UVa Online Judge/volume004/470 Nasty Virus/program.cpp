// Nasty Virus
// UVa ID: 470
// Verdict: Accepted
// Submission Date: 2026-10-29
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Statement {
    string raw;           // original line (whitespace preserved, '\r' stripped)
    int lhs;              // 0..25 for a lowercase-letter LHS, -1 for a digit LHS
    unsigned int rhsMask; // bitmask of lowercase letters appearing in the RHS
};

// The reference parser accepts a very loose grammar:
//   [a-z0-9] '=' <sequence over [a-z0-9 + - * /] with no two adjacent operands>
bool parseLine(const string& raw, Statement& st) {
    string c;
    for (char ch : raw) if (!isspace((unsigned char)ch)) c.push_back(ch);
    int len = (int)c.size();
    if (len < 2) return false;
    if (c[1] != '=') return false;
    char lc = c[0];
    bool isLetter = (lc >= 'a' && lc <= 'z');
    bool isDigit = (lc >= '0' && lc <= '9');
    if (!isLetter && !isDigit) return false;
    unsigned int rhsMask = 0;
    bool prevOperand = false;
    for (int i = 2; i < len; ++i) {
        char ch = c[i];
        bool isOperand = (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
        bool isOp = (ch == '+' || ch == '-' || ch == '*' || ch == '/');
        if (!isOperand && !isOp) return false;
        if (isOperand) {
            if (prevOperand) return false;   // two operands in a row (e.g. "10", "ab")
            if (ch >= 'a' && ch <= 'z') rhsMask |= 1u << (ch - 'a');
        }
        prevOperand = isOperand;
    }
    st.raw = raw;
    st.lhs = isLetter ? (lc - 'a') : -1;
    st.rhsMask = rhsMask;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string header, line;
    if (!getline(cin, header)) return 0;
    if (!header.empty() && header.back() == '\r') header.pop_back();

    int C = 0;
    for (char ch : header)
        if (isdigit((unsigned char)ch)) C = C * 10 + (ch - '0');

    vector<Statement> stmts;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        Statement st;
        if (parseLine(line, st)) stmts.push_back(st);
    }

    int m = (int)stmts.size();
    if (m == 0) { cout << header << '\n'; return 0; }

    vector<int> asgn[26], allUses[26];
    for (int i = 0; i < m; ++i) {
        if (stmts[i].lhs >= 0) asgn[stmts[i].lhs].push_back(i);
        for (int v = 0; v < 26; ++v)
            if (stmts[i].rhsMask & (1u << v)) allUses[v].push_back(i);
    }

    // A[v] = number of non-empty "runs" of uses of v (forward liveness with the
    // self-reference special case).  The first A[v] assignments of v are original.
    int A[26] = {0};
    for (int v = 0; v < 26; ++v) {
        if (asgn[v].empty()) continue;
        int k = (int)asgn[v].size();
        int Av = 0;
        bool nextRun = false;
        for (int j = k - 1; j >= 0; --j) {
            int p = asgn[v][j];
            bool normal = false;
            if (j == k - 1) {
                normal = upper_bound(allUses[v].begin(), allUses[v].end(), p) != allUses[v].end();
            } else {
                int np = asgn[v][j + 1];
                auto it = upper_bound(allUses[v].begin(), allUses[v].end(), p);
                normal = (it != allUses[v].end() && *it < np);
            }
            bool selfRef = (j < k - 1) && ((stmts[asgn[v][j + 1]].rhsMask & (1u << v)) != 0);
            bool run = normal || (selfRef && !nextRun);
            if (run) ++Av;
            nextRun = run;
        }
        A[v] = Av;
    }

    vector<char> marked(m, 0);
    marked[m - 1] = 1;                       // last statement is always original
    for (int i = 0; i < m; ++i)
        if (stmts[i].lhs < 0) marked[i] = 1;  // digit-LHS statements are always original
    marked[0] = 1;                            // reference bug: first statement is always kept
    for (int v = 0; v < 26; ++v)
        if (A[v] >= 1) marked[asgn[v][0]] = 1; // first assignment of each used variable

    // Fill up to C statements with the earliest not-yet-included statements.
    int cnt = 0;
    for (int i = 0; i < m; ++i) if (marked[i]) ++cnt;
    for (int i = 0; i < m && cnt < C; ++i)
        if (!marked[i]) { marked[i] = 1; ++cnt; }

    cout << header << '\n';
    for (int i = 0; i < m; ++i)
        if (marked[i]) cout << stmts[i].raw << '\n';
    return 0;
}
