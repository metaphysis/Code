#include <bits/stdc++.h>
using namespace std;

const long long modVal = 2147483647LL;
const int testCnt = 4;

struct Parser {
    const string &expr;
    const array<long long, 26> &varVal;
    int pos;
    Parser(const string &s, const array<long long, 26> &vals) : expr(s), varVal(vals), pos(0) {}

    void skipSpace() {
        while (pos < (int)expr.size() && expr[pos] == ' ') ++pos;
    }

    long long parseFactor() {
        skipSpace();
        long long result = 0, base = 0;
        if (expr[pos] == '(') {
            ++pos;
            result = parseExpr();
            skipSpace();
            ++pos;
        } else if (expr[pos] >= '0' && expr[pos] <= '9') {
            while (pos < (int)expr.size() && expr[pos] >= '0' && expr[pos] <= '9') {
                result = (result * 10 + expr[pos] - '0') % modVal;
                ++pos;
            }
        } else {
            base = varVal[expr[pos] - 'a'];
            ++pos;
            skipSpace();
            int power = 1;
            if (pos < (int)expr.size() && expr[pos] == '^') {
                ++pos;
                skipSpace();
                power = expr[pos] - '0';
                ++pos;
            }
            result = 1;
            for (int i = 0; i < power; ++i) result = result * base % modVal;
        }
        return result;
    }

    long long parseTerm() {
        long long result = parseFactor();
        skipSpace();
        while (pos < (int)expr.size() && expr[pos] != '+' && expr[pos] != '-' && expr[pos] != ')') {
            result = result * parseFactor() % modVal;
            skipSpace();
        }
        return result;
    }

    long long parseExpr() {
        long long result = parseTerm(), value = 0;
        skipSpace();
        while (pos < (int)expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
            char op = expr[pos++];
            value = parseTerm();
            if (op == '+') result = (result + value) % modVal;
            else result = (result - value + modVal) % modVal;
            skipSpace();
        }
        return result;
    }
};

array<long long, testCnt> getValues(const string &expr, const array<array<long long, 26>, testCnt> &varVals) {
    array<long long, testCnt> result;
    for (int i = 0; i < testCnt; ++i) {
        Parser parser(expr, varVals[i]);
        result[i] = parser.parseExpr();
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937 rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()));
    uniform_int_distribution<long long> dist(0, modVal - 1);
    array<array<long long, 26>, testCnt> varVals;
    array<long long, testCnt> target;
    string line;
    bool hasTarget = false;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line == ".") {
            if (!hasTarget) break;
            cout << ".\n";
            hasTarget = false;
        } else if (!hasTarget) {
            for (auto &vals : varVals) for (auto &value : vals) value = dist(rng);
            target = getValues(line, varVals);
            hasTarget = true;
        } else cout << (getValues(line, varVals) == target ? "yes" : "no") << '\n';
    }
    return 0;
}
