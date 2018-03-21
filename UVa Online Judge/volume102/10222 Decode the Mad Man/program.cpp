// Decode the Mad Man
// UVa ID: 10222
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

    string keyboard = "qwertyuiop[]\\{}|asdfghjkl;'zxcvbnm,./<>?";
    string line;
    while (getline(cin, line))
    {
        for (auto letter : line)
        {
            int idx = keyboard.find(letter);
            if (idx != keyboard.npos)
                cout << keyboard[idx - 2];
            else
                cout << letter;
        }
        cout << '\n';
    }

    return 0;
}
