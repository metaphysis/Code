#include <bits/stdc++.h>
using namespace std;

class Solver {
private:
    string expr;
    int pos;
    long long baseVal;
    vector<long long> coef;

    void skip() {
        while (pos < (int)expr.size() && expr[pos] == ' ') pos++;
    }

    void parseFact(long long sign) {
        skip();
        if (expr[pos] == '(') {
            pos++;
            parseExpr(sign);
            skip();
            pos++;
            return;
        }
        int st = pos;
        while (pos < (int)expr.size() && (expr[pos] == '#' || isdigit(expr[pos]))) pos++;
        long long pw = 1;
        vector<long long> cur;
        for (int i = pos - 1; i >= st; i--) {
            if (expr[i] == '#') cur.push_back(sign * pw);
            else baseVal += sign * (expr[i] - '0') * pw;
            pw *= 10;
        }
        reverse(cur.begin(), cur.end());
        for (long long val : cur) coef.push_back(val);
    }

    void parseExpr(long long sign) {
        parseFact(sign);
        skip();
        while (pos < (int)expr.size() && expr[pos] != ')') {
            char op = expr[pos++];
            parseFact(sign * (op == '+' ? 1 : -1));
            skip();
        }
    }

public:
    void solveCase(int id, string curExpr, string digits) {
        expr = curExpr;
        pos = 0;
        baseVal = 0;
        coef.clear();
        parseExpr(1);
        int n = coef.size();
        vector<int> ord(n);
        for (int i = 0; i < n; i++) ord[i] = i;
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            if (coef[a] != coef[b]) return coef[a] > coef[b];
            return a < b;
        });
        vector<char> dig;
        for (char c : digits)
            if (isdigit(c)) dig.push_back(c);
        sort(dig.begin(), dig.end());
        vector<char> ansDig(n);
        int l = 0;
        while (l < n) {
            int r = l + 1;
            while (r < n && coef[ord[r]] == coef[ord[l]]) r++;
            int st = n - r;
            for (int i = l; i < r; i++) ansDig[ord[i]] = dig[st + i - l];
            l = r;
        }
        long long ansVal = baseVal;
        for (int i = 0; i < n; i++) ansVal += (ansDig[i] - '0') * coef[i];
        string result = expr;
        int p = 0;
        for (char &c : result)
            if (c == '#') c = ansDig[p++];
        cout << "Case " << id << ":\n";
        cout << result << "\n";
        cout << ansVal << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string expr, digits;
    cin >> n;
    getline(cin, expr);
    Solver solver;
    for (int i = 1; i <= n; i++) {
        getline(cin, expr);
        getline(cin, digits);
        if (!expr.empty() && expr.back() == '\r') expr.pop_back();
        if (!digits.empty() && digits.back() == '\r') digits.pop_back();
        solver.solveCase(i, expr, digits);
    }
    return 0;
}
