// Zero or One
// UVa ID: 12646
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char v;
    string line;
    
    while (cin >> v)
    {
        line.clear();
        line += v;

        cin >> v; line += v;
        cin >> v; line += v;
        
        if (line == "100" || line == "011") cout << "A\n";
        else if (line == "010" || line == "101") cout << "B\n";
        else if (line == "001" || line == "110") cout << "C\n";
        else cout << "*\n";
    }

    return 0;
}
