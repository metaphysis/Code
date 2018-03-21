// Decode the Tape
// UVa ID: 10878
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

    string line;
    while (getline(cin, line))
    {
        if (line.front() == '_') continue;
        line.erase(line.begin());
        line.pop_back();
        for (int i = line.length(); i >= 0; i--)
            if (line[i] == 'o') line[i] = '1';
            else if (line[i] == '.') line.erase(line.begin() + i);
            else line[i] = '0';
        bitset<8> letter(line);
        cout << (char)letter.to_ulong();
    }

    return 0;
}
