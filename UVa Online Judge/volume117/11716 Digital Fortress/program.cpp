// Digital Fortress
// UVa ID: 11716
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(1024, '\n');
    
    for (int c = 1; c <= cases; c++)
    {
        string line;
        getline(cin, line);

        int length = line.length();
        int root = sqrt(length);
        if (root * root != length)
        {
            cout << "INVALID\n";
            continue;
        }
        for (int i = 0; i < root; i++)
            for (int j = 0; j < root; j++)
                cout << line[j * root + i];
        cout << '\n';
    }

    return 0;
}
