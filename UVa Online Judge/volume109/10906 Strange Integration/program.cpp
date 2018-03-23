// Strange Integration
// UVa ID: 10906
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct expression
{
    string variable1, variable2, operators, variable3;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    string line, equal;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cin.ignore(1024, '\n');

        map<string, expression> all;
        vector<string> sequence;
        for (int i = 0; i < n; i++)
        {
            expression expr;
            cin >> expr.variable1 >> equal;
            cin >> expr.variable2 >> expr.operators >> expr.variable3;
            all[expr.variable1] = expr;
            sequence.push_back(expr.variable1);
        }
        
        // Replace.
        map<string, string> restored;
        for (auto s : sequence)
        {
            expression expr = all[s];
            string finals;
            if (isalpha(expr.variable2.front()))
            {
                string r = restored[expr.variable2];
                string op1 = expr.operators, op2 = all[expr.variable2].operators;
                if (op1 == "*" && op2 == "+")
                    finals += "(" + r + ")";
                else
                    finals += r;
            }
            else
                finals += expr.variable2;
            finals += expr.operators;
            if (isalpha(expr.variable3.front()))
            {
                string r = restored[expr.variable3];
                string op1 = expr.operators, op2 = all[expr.variable3].operators;
                if ((op1 == "*" && op2 == "*") || op2 == "+")
                    finals += "(" + r + ")";
                else
                    finals += r;
            }
            else
                finals += expr.variable3;
            restored[s] = finals;
        }

        // Print.
        cout << "Expression #" << c << ": ";
        cout << restored[sequence.back()] << '\n';
    }

    return 0;
}
