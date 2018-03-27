// Flowers Flourish from France
// UVa ID: 12243
// Verdict: Accepted
// Submission Date: 2018-03-27
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
        if (line == "*") break;

        istringstream iss(line);
        string word;
        char last = 0;
        bool flag = true;
        while (iss >> word)
        {
            if (last == 0) last = tolower(word.front());
            else
            {
                if (last != tolower(word.front()))
                {
                    flag = false;
                    break;
                }
            }
        }
        cout << (flag ? 'Y' : 'N') << '\n';
    }

    return 0;
}
