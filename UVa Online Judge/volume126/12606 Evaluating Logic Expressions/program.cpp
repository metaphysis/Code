#include <bits/stdc++.h>
using namespace std;

struct UnaryOp {
    int tab[2];
};

struct BinaryOp {
    int tab[2][2];
};

string expr;
int pos;
int val[26];
map<string, UnaryOp> unaryOp;
map<string, BinaryOp> binaryOp;

void skipSpace() {
    while (pos < (int)expr.size() && expr[pos] == ' ') pos++;
}

string parseName() {
    skipSpace();
    string name;
    while (pos < (int)expr.size() && isalpha((unsigned char)expr[pos])) name += expr[pos++];
    return name;
}

int applyUnary(const string &name, int mask) {
    int res = 0, i;
    for (i = 0; i < 2; i++)
        if (mask & (1 << i))
            res |= unaryOp[name].tab[i];
    return res;
}

int applyBinary(const string &name, int leftMask, int rightMask) {
    int res = 0, i, j;
    for (i = 0; i < 2; i++)
        if (leftMask & (1 << i))
            for (j = 0; j < 2; j++)
                if (rightMask & (1 << j))
                    res |= binaryOp[name].tab[i][j];
    return res;
}

int parseExpr() {
    skipSpace();
    if (expr[pos] != '(') {
        char ch = expr[pos++];
        return val[ch - 'a'];
    }
    pos++;
    skipSpace();
    if (isupper((unsigned char)expr[pos])) {
        string name = parseName();
        int right = parseExpr();
        skipSpace();
        pos++;
        return applyUnary(name, right);
    }
    int left = parseExpr();
    string name = parseName();
    int right = parseExpr();
    skipSpace();
    pos++;
    return applyBinary(name, left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int unaryCount, binaryCount, caseNum = 1;
    while (cin >> unaryCount >> binaryCount) {
        if (unaryCount < 0 && binaryCount < 0) break;
        unaryOp.clear();
        binaryOp.clear();
        int i, j;
        for (i = 0; i < unaryCount; i++) {
            string name, value;
            UnaryOp op;
            cin >> name;
            cin >> value;
            op.tab[0] = value == "true" ? 2 : 1;
            cin >> value;
            op.tab[1] = value == "true" ? 2 : 1;
            unaryOp[name] = op;
        }
        for (i = 0; i < binaryCount; i++) {
            string name, value;
            BinaryOp op;
            cin >> name;
            for (j = 0; j < 2; j++) {
                cin >> value;
                op.tab[0][j] = value == "true" ? 2 : 1;
            }
            for (j = 0; j < 2; j++) {
                cin >> value;
                op.tab[1][j] = value == "true" ? 2 : 1;
            }
            binaryOp[name] = op;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, expr);
        for (i = 0; i < 26; i++) val[i] = 3;
        string line;
        while (getline(cin, line) && line != "*") {
            char variable;
            string state;
            stringstream ss(line);
            ss >> variable >> state;
            val[variable - 'a'] = state == "true" ? 2 : 1;
        }
        pos = 0;
        int result = parseExpr();
        cout << "Case " << caseNum++ << ": ";
        if (result == 1) cout << "false\n";
        else if (result == 2) cout << "true\n";
        else cout << "unknown\n";
    }
    return 0;
}
