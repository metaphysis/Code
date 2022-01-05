// Inception
// UVa ID: 13055
// Verdict: Accepted
// Submission Date: 2022-01-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    stack<string> names;
    cin >> n;
    string action, name;
    for (int i = 1; i <= n; i++)
    {
        cin >> action;
        if (action == "Sleep")
        {
            cin >> name;
            names.push(name);
        }
        else if (action == "Kick")
        {
            if (names.size()) names.pop();
        }
        else
        {
            if (names.size()) cout << names.top() << '\n';
            else cout << "Not in a dream\n";
        }
    }
    return 0;
}
