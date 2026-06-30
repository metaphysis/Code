// Crazy Calculator
// UVa ID: 354
// Verdict: Accepted
// Submission Date: 2026-06-30
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, char> toStd;
unordered_map<char, int> prec;
unordered_map<char, char> assoc;

int calc(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b ? a / b : 0;
    }
    return 0;
}

void apply(stack<int>& val, stack<string>& exp, stack<char>& op) {
    char o = op.top(); op.pop();
    string r = exp.top(); exp.pop();
    string l = exp.top(); exp.pop();
    int rb = val.top(); val.pop();
    int lb = val.top(); val.pop();
    val.push(calc(lb, rb, toStd[o]));
    exp.push(l + toStd[o] + r);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    getline(cin, line);
    int T = stoi(line);
    getline(cin, line);
    for (int cs = 0; cs < T; ++cs) {
        if (cs) cout << '\n';
        toStd.clear(); prec.clear(); assoc.clear();
        for (int i = 0; i < 4; ++i) {
            getline(cin, line);
            toStd[line[1]] = line[0];
            prec[line[1]] = line[2] - '0';
            assoc[line[1]] = line[3];
        }
        while (getline(cin, line) && !line.empty()) {
            stack<int> val;
            stack<string> exp;
            stack<char> op;
            for (int i = 0; i < (int)line.size(); ) {
                if (isdigit(line[i])) {
                    int num = 0;
                    while (i < (int)line.size() && isdigit(line[i]))
                        num = num * 10 + (line[i++] - '0');
                    val.push(num);
                    exp.push(to_string(num));
                } else {
                    char cur = line[i++];
                    while (!op.empty()) {
                        char top = op.top();
                        bool pop = false;
                        if (prec[cur] < prec[top]) pop = true;
                        else if (prec[cur] == prec[top]) {
                            if (cur == top) pop = (assoc[top] == 'L');
                            else pop = true;
                        }
                        if (!pop) break;
                        apply(val, exp, op);
                    }
                    op.push(cur);
                }
            }
            while (!op.empty()) apply(val, exp, op);
            cout << exp.top() << " = " << val.top() << '\n';
        }
    }
    return 0;
}
