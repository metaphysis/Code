// Molar Mass
// UVa ID: 1586
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

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        string line;
        cin >> line;
        
        string block;
        for (auto letter : line)
        {
            if (isalpha(letter))
                block += ' ';
            block += letter;
        }
        
        int mass = 0, quantity;
        string group;
        istringstream iss(block);
        while (iss >> group)
        {
            if (group.length() > 1)
                quantity = stoi(group.substr(1));
            else
                quantity = 1;
            char atom = group.front();
            if (atom == 'C') mass += quantity * 12010;
            if (atom == 'H') mass += quantity * 1008;
            if (atom == 'O') mass += quantity * 16000;
            if (atom == 'N') mass += quantity * 14010;
        }

        cout << (mass / 1000) << '.';
        cout << setw(3) << setfill('0') << (mass % 1000) << '\n';
    }

    return 0;
}
