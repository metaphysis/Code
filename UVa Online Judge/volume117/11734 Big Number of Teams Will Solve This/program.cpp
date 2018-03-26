// Big Number of Teams Will Solve This
// UVa ID: 11734
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases; cin.ignore(1024, '\n');

    string line1, line2;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        getline(cin, line1);
        getline(cin, line2);
        
        if (line1 == line2) cout << "Yes\n";
        else
        {
            string next;
            for (int i = 0; i < line1.length(); i++)
                if (line1[i] != ' ' && line1[i] != '\t')
                    next += line1[i];
            if (next == line2) cout << "Output Format Error\n";
            else cout << "Wrong Answer\n";
        }
    }

    return 0;
}
