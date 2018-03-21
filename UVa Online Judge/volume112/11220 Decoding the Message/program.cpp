// Decoding the Message
// UVa ID: 11220
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
    getline(cin, line);
    int cases = stoi(line);
    getline(cin, line);

    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cout << "Case #" << c << ":\n";
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);

            int idx = 1;
            string word;
            while (iss >> word)
            {
                if (word.length() >= idx)
                {
                    cout << word[idx - 1];
                    idx++;
                }
            }
            cout << '\n';
        }
    }

    return 0;
}
