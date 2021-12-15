// Rational Grading
// UVa ID: 13151
// Verdict: Accepted
// Submission Date: 2021-12-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int t;
    string ivalue, expression;
    while (cin >> ivalue >> t, t)
    {
        int variable, expected, printed;
        if (ivalue.front() != '0') variable = stoi(ivalue);
        else
        {
            if (ivalue[1] == 'x') variable = stoi(ivalue, 0, 16);
            else variable = stoi(ivalue, 0, 8);
        }
        int marks = 0;
        cin >> expression >> printed;
        if (expression == "++i") expected = variable + 1;
        else if (expression == "--i") expected = variable - 1;
        else expected = variable;
        if (printed == expected) marks++;
        if (expression == "i++") variable = printed + 1;
        else if (expression == "i--") variable = printed - 1;
        else variable = printed;
        for (int i = 2; i <= t; i++)
        {
            cin >> expression >> printed;
            if (expression == "++i") expected = variable + 1;
            else if (expression == "--i") expected = variable - 1;
            else expected = variable;
            if (printed == expected) marks++;
            if (expression == "i++") variable = printed + 1;
            else if (expression == "i--") variable = printed - 1;
            else variable = printed;
        }
        cout << marks << '\n';
    }

    return 0;
}
