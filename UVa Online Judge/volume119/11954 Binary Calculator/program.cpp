// Binary Calculator
// UVa ID: 11954
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

string stripLeadingZeros(string s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

string applyUnary(string s, const string& op) {
    s = stripLeadingZeros(s);
    if (op == "not") {
        string res;
        for (char c : s) res += (c == '0' ? '1' : '0');
        return stripLeadingZeros(res);
    }
    if (op == "shr") {
        if (s == "0") return "0";
        return stripLeadingZeros(s.substr(0, s.size() - 1));
    }
    if (op == "shl") {
        return stripLeadingZeros(s + "0");
    }
    return s;
}

string applyBinary(const string& a, const string& b, const string& op) {
    int maxLen = max(a.size(), b.size());
    string A = string(maxLen - a.size(), '0') + a;
    string B = string(maxLen - b.size(), '0') + b;
    string res;
    if (op == "xor") {
        for (int i = 0; i < maxLen; ++i) res += (A[i] == B[i] ? '0' : '1');
    } else if (op == "and") {
        for (int i = 0; i < maxLen; ++i) res += (A[i] == '1' && B[i] == '1') ? '1' : '0';
    } else if (op == "or") {
        for (int i = 0; i < maxLen; ++i) res += (A[i] == '1' || B[i] == '1') ? '1' : '0';
    }
    return stripLeadingZeros(res);
}

string parseTerm(const vector<string>& tokens, int& idx) {
    string tok = tokens[idx];
    if (tok.find_first_not_of("01") == string::npos) {
        ++idx;
        return stripLeadingZeros(tok);
    }
    ++idx; // consume unary operator
    string inner = parseTerm(tokens, idx);
    return applyUnary(inner, tok);
}

string parseExpression(const vector<string>& tokens) {
    int idx = 0;
    string left = parseTerm(tokens, idx);
    while (idx < (int)tokens.size()) {
        string op = tokens[idx];
        if (op != "xor" && op != "and" && op != "or") break;
        ++idx;
        string right = parseTerm(tokens, idx);
        left = applyBinary(left, right, op);
    }
    return left;
}

int main() {
    int T;
    cin >> T;
    cin.ignore();
    for (int i = 1; i <= T; ++i) {
        string line;
        getline(cin, line);
        vector<string> tokens;
        istringstream iss(line);
        string token;
        while (iss >> token) tokens.push_back(token);
        string result = parseExpression(tokens);
        cout << "Case " << i << ": " << result << "\n";
    }
    return 0;
}
