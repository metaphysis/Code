// Find the Telephone
// UVa ID: 10921
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

    // ABC 2
    // DEF 3
    // GHI 4
    // JKL 5
    // MNO 6
    // PQRS 7
    // TUV 8
    // WXYZ 9

    map<char, int> book = {
        {'A', 2}, {'B', 2}, {'C', 2},
        {'D', 3}, {'E', 3}, {'F', 3},
        {'G', 4}, {'H', 4}, {'I', 4},
        {'J', 5}, {'K', 5}, {'L', 5},
        {'M', 6}, {'N', 6}, {'O', 6},
        {'P', 7}, {'Q', 7}, {'R', 7}, {'S', 7},
        {'T', 8}, {'U', 8}, {'V', 8},
        {'W', 9}, {'X', 9}, {'Y', 9}, {'Z', 9}
    };

    string line;
    while (getline(cin, line))
    {
        for (auto c : line)
            if (isupper(c)) cout << book[c];
            else cout << c;
        cout << '\n';
    }

    return 0;
}
