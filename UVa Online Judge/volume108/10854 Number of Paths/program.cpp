// Number of Paths
// UVa ID: 10854
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int i;
string line, expression;

long long match(char token)
{
    if (expression[i] == token)
    {
        i++;
        if (token == '[') return 0LL;
        if (token == '|') return 1LL;
        if (token == ']') return 1LL;
    }
    else
    {
        long long path = 1;
        path *= match('[') + match('|') + match(']');
        path *= match(token);
        return path;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(1024, '\n');

    for (int c = 1; c <= cases; c++)
    {
        expression.clear();
        while (getline(cin, line))
        {
            if (line == "ENDPROGRAM") break;
            if (line == "IF") expression += '[';
            if (line == "ELSE") expression += '|';
            if (line == "END_IF") expression += ']';
        }

        i = 0;
        long long total = 1;
        while (i < expression.length())
            total *= (match('[') + match('|') + match(']'));
        cout << total << '\n';
    }

    return 0;
}
