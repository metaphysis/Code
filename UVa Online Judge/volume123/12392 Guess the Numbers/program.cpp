// Guess the Numbers
// UVa ID: 12392
// Verdict: Accepted
// Submission Date: 2023-04-22
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int OPERATOR = 0, OPERAND = 1;

struct block {
    int type, value;
} blk[310];

int cnt;

int calculate() {
    stack<int> result;
    for (int i = 0; i < cnt; i++) {
        block c = blk[i];
        if (c.type == OPERAND) result.push(c.value);
        else {
            int second = result.top(); result.pop();
            int first = result.top(); result.pop();
            if (c.value == '+') result.push(first + second);
            if (c.value == '-') result.push(first - second);
            if (c.value == '*') result.push(first * second);
            if (c.value == '/') result.push(first / second);
        }
    }
    return result.top();
}

map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}
};

bool lessPriority(char previous, char next) {
    return priority[previous] <= priority[next];
}

string toPostfix(string infix) {
    stack<char> operands, operators;
    for (auto c : infix) {
        if (isalpha(c)) {
            operands.push(c);
            continue;
        }
        if (c == '(') {
            operators.push(c);
            continue;
        }
        if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                operands.push(operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
            continue;
        }
        if (operators.empty() || operators.top() == '(' ||
            !lessPriority(c, operators.top())) {
            operators.push(c);
        } else {
            while (!operators.empty() && lessPriority(c, operators.top())) {
                operands.push(operators.top());
                operators.pop();
            }
            operators.push(c);
        }
    }
    while (!operators.empty()) {
        operands.push(operators.top());
        operators.pop();
    }
    string postfix;
    while (!operands.empty()) {
        postfix = operands.top() + postfix;
        operands.pop();
    }
    return postfix;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, v[6], r;
    string s;
    while (cin >> n, n) {
        for (int i = 0; i < n; i++) cin >> v[i];
        cin >> r >> s;
        cnt = 0;
        for (auto c : toPostfix(s)) {
            if (isalpha(c)) blk[cnt++] = block{OPERAND, 0};
            else blk[cnt++] = block{OPERATOR, c};
        }
        sort(v, v + n);
        int flag = 0;
        do {
            for (int i = 0, j = 0; i < cnt; i++)
                if (blk[i].type == OPERAND)
                    blk[i].value = v[j++];
            if (calculate() == r) { flag = 1; break;}
        } while (next_permutation(v, v + n));
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}
