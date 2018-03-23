// Smeech
// UVa ID: 11291
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int i;
string line;

double dfs()
{
    while (isblank(line[i]) && i < line.length()) i++;
    if (line[i] == '(')
    {
        i++;
        double p, e1, e2;
        while (isblank(line[i])) i++;
        string block;
        while (!isblank(line[i])) block += line[i++];
        p = stod(block);
        e1 = dfs();
        e2 = dfs();
        while (line[i] != ')') i++;
        if (i < line.length()) i++;
        return p * (e1 + e2) + (1.0 - p) * (e1 - e2);
    }
    else
    {
        double e;
        while (isblank(line[i])) i++;
        string block;
        while (!isblank(line[i]) && line[i] != ')' && i < line.length()) block += line[i++];
        e = stod(block);
        return e;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (getline(cin, line))
    {
        if (line == "()") break;
        i = 0;
        double r = dfs();
        cout << fixed << setprecision(2) << r << '\n';
    }

    return 0;
}
