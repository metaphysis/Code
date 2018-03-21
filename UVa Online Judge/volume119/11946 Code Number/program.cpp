// Code Number
// UVa ID: 11946
// Verdict: Accepted
// Submission Date: 2018-03-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<int, char> book = {
        {3, 'E'}, {0, 'O'}, {1, 'I'}, {4, 'A'}, {9, 'P'}, {8, 'B'}, {5, 'S'}, {7, 'T'}, {4, 'A'}, {2, 'Z'}, {6, 'G'}
    };

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        while (getline(cin, line), line.length() > 0)
        {
            for (auto letter : line)
                if (isdigit(letter))
                    cout << book[letter - '0'];
                else
                    cout << letter;
            cout << '\n';
        }
    }

    return 0;
}
