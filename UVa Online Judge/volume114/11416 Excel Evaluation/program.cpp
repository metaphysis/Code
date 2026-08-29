#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<vector<string>> cells;
vector<vector<int>> vals;
vector<vector<bool>> computed;

int getVal(int r, int c);
int parseExpr(const string& expr, int& pos);
int parseTerm(const string& expr, int& pos);
int parseFactor(const string& expr, int& pos);

int parseFactor(const string& expr, int& pos) {
    if (pos >= (int)expr.size()) return 0;
    char ch = expr[pos];
    if (ch == '(') {
        pos++;
        int res = parseExpr(expr, pos);
        if (pos < (int)expr.size() && expr[pos] == ')') pos++;
        return res;
    } else if (isdigit(ch)) {
        int num = 0;
        while (pos < (int)expr.size() && isdigit(expr[pos])) {
            num = num * 10 + (expr[pos] - '0');
            pos++;
        }
        return num;
    } else if (isalpha(ch)) {
        string colStr;
        while (pos < (int)expr.size() && isalpha(expr[pos])) {
            colStr.push_back(expr[pos]);
            pos++;
        }
        int rowNum = 0;
        while (pos < (int)expr.size() && isdigit(expr[pos])) {
            rowNum = rowNum * 10 + (expr[pos] - '0');
            pos++;
        }
        int colIdx = 0;
        for (char cc : colStr)
            colIdx = colIdx * 26 + (cc - 'A' + 1);
        colIdx--;
        int rowIdx = rowNum - 1;
        return getVal(rowIdx, colIdx);
    } else {
        pos++;
        return 0;
    }
}

int parseTerm(const string& expr, int& pos) {
    int res = parseFactor(expr, pos);
    while (pos < (int)expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
        char op = expr[pos];
        pos++;
        int rhs = parseFactor(expr, pos);
        if (op == '*') res = res * rhs;
        else res = res / rhs;
    }
    return res;
}

int parseExpr(const string& expr, int& pos) {
    int res = parseTerm(expr, pos);
    while (pos < (int)expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos];
        pos++;
        int rhs = parseTerm(expr, pos);
        if (op == '+') res = res + rhs;
        else res = res - rhs;
    }
    return res;
}

int getVal(int r, int c) {
    if (computed[r][c]) return vals[r][c];
    string s = cells[r][c];
    if (s[0] != 'e') {
        vals[r][c] = stoi(s);
    } else {
        string expr = s.substr(2, s.size() - 3);
        int pos = 0;
        vals[r][c] = parseExpr(expr, pos);
    }
    computed[r][c] = true;
    return vals[r][c];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    bool firstCase = true;
    while (T--) {
        cin >> ::m >> ::n;
        cells.assign(::m, vector<string>(::n));
        for (int i = 0; i < ::m; ++i)
            for (int j = 0; j < ::n; ++j)
                cin >> cells[i][j];
        vals.assign(::m, vector<int>(::n, 0));
        computed.assign(::m, vector<bool>(::n, false));
        if (!firstCase) cout << '\n';
        firstCase = false;
        for (int i = 0; i < ::m; ++i) {
            for (int j = 0; j < ::n; ++j) {
                if (j) cout << ' ';
                cout << getVal(i, j);
            }
            cout << '\n';
        }
    }
    return 0;
}
