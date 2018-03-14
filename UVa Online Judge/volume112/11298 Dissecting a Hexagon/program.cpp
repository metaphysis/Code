// Dissecting a Hexagon
// UVa ID: 11298
// Verdict: Accepted
// Submission Date: 2018-03-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line.front() == '-') cout << "0\n";
        else
        {
            int n = stoi(line);
            if (n && (n % 3 == 0)) cout << "1\n";
            else cout << "0\n";
        }
    }

    return 0;
}
