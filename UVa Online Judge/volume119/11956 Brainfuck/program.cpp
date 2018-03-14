// Brainfuck
// UVa ID: 11956
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.070s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, memory[100];
    string line;

    cin >> T;
    cin.ignore(1024, '\n');

    for (int i = 1; i <= T; i++)
    {
        getline(cin, line);

        memset(memory, 0, sizeof(memory));
        
        int k = 0;
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '>') k = (k + 1) % 100;
            else if (line[j] == '<') k = (k + 99) % 100;
            else if (line[j] == '+') memory[k] = (memory[k] + 1) % 256;
            else if (line[j] == '-') memory[k] = (memory[k] + 255) % 256;
        }
        
        cout << "Case " << dec << i << ":";
        for (int j = 0; j < 100; j++)
        {
            cout << ' ';
            cout << hex << uppercase << setw(2) << setfill('0') << memory[j];
        }
        cout << '\n';
    }

    return 0;
}
