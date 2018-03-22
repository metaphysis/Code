// Ensuring Truth
// UVa ID: 11357
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, positive[26], negative[26];
    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        string line;
        getline(cin, line);

        string block;
        bool printed = false;
        istringstream iss1(line);
        while (getline(iss1, block, '|'))
        {
            if (block.front() == '(') block.erase(block.begin());
            if (block.back() == ')') block.pop_back();

            memset(positive, 0, sizeof(positive));
            memset(negative, 0, sizeof(negative));

            string literal;
            istringstream iss2(block);
            while (getline(iss2, literal, '&'))
            {
                if (literal.length() == 2)
                {
                    negative[literal.back() - 'a'] = 1;
                }
                else
                {
                    positive[literal.back() - 'a'] = 1;
                }
            }
            
            bool no = false;
            for (int i = 0; i < 26; i++)
                if (positive[i] && negative[i])
                {
                    no = true;
                    break;
                }
            if (!no)
            {
                cout << "YES\n";
                printed = true;
                break;
            }
        }
        
        if (!printed) cout << "NO\n";
    }

    return 0;
}
