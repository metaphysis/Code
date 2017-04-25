// Morse Mismatches
// UVa ID: 508
// Verdict: Accepted
// Submission Date: 2017-04-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<char, string> table;
    vector<string> word, context;

    char letter;
    string field;
    while (cin >> letter, letter != '*')
    {
        cin >> field;
        table[letter] = field;
    }

    while (cin >> field, field != "*")
    {
        string code;
        for (auto c : field) code += table[c];
        word.push_back(field);
        context.push_back(code);
    }

    while (cin >> field, field != "*")
    {
        vector<string> perfectly;
        string flawed = word.front();
        int minDiff = 102400;
        
        for (int i = 0; i < word.size(); i++)
        {
            size_t matched = 0;
            for (size_t j = 0; j < field.size() && j < context[i].size(); j++)
            {
                if (field[j] != context[i][j]) break;
                matched++;
            }

            if (matched == field.size() && matched == context[i].size())
                perfectly.push_back(word[i]);
            else
            {
                if (matched == min(context[i].size(), field.size()))
                {
                    int diff = abs((int)context[i].size() - (int)field.size());
                    if (diff < minDiff)
                    {
                        minDiff = diff;
                        flawed = word[i];
                    }
                }
            }
        }

        if (perfectly.size() == 1)
            cout << perfectly.front() << '\n';
        else
        {
            if (perfectly.size() > 1)
                cout << perfectly.front() << "!\n";
            else
                cout << flawed << "?\n";
        }
    }

    return 0;
}
