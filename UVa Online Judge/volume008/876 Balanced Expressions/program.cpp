// Balanced Expressions
// UVa ID: 876
// Verdict: Accepted
// Submission Date: 2026-10-21
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Result {
    int id;
    bool balanced;
};

class Parser {
    string s;
    size_t pos;
    int nextId;
    map<tuple<int, int, int>, int> ids;

    char peek() {
        return pos < s.size() ? s[pos] : '\0';
    }

    int getId(int type, int left = 0, int right = 0) {
        tuple<int, int, int> key = make_tuple(type, left, right);
        auto it = ids.find(key);
        if (it != ids.end()) return it->second;
        int id = nextId++;
        ids.emplace(key, id);
        return id;
    }

    Result combine(char op, const Result& left, const Result& right) {
        return {getId(op, left.id, right.id), left.balanced && right.balanced && left.id == right.id};
    }

    Result parseExpression() {
        Result result = parseTerm();
        while (peek() == '+' || peek() == '-') {
            char op = s[pos++];
            Result right = parseTerm();
            result = combine(op, result, right);
        }
        return result;
    }

    Result parseTerm() {
        Result result = parseUnary();
        while (peek() == '*' || peek() == '/') {
            char op = s[pos++];
            Result right = parseUnary();
            result = combine(op, result, right);
        }
        return result;
    }

    Result parseUnary() {
        if (peek() == '-') {
            ++pos;
            Result inner = parseUnary();
            return {getId(256, inner.id), inner.balanced};
        }
        return parsePrimary();
    }

    Result parsePrimary() {
        if (peek() == '(') {
            ++pos;
            Result inner = parseExpression();
            ++pos;
            return {getId(257, inner.id), inner.balanced};
        }
        while (pos < s.size() && isdigit(s[pos])) ++pos;
        return {getId(258), true};
    }

public:
    explicit Parser(const string& expression) : s(expression), pos(0), nextId(1) {}

    bool solve() {
        return parseExpression().balanced;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        string clean;
        for (auto c : line) {
            if (c == '=') break;
            if (!isspace(c)) clean += c;
        }
        Parser parser(clean);
        cout << (parser.solve() ? "YES" : "NO") << '\n';
    }
    return 0;
}
