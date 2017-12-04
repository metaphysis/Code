// Editor Nottoobad
// UVa ID: 10602
// Verdict: Accepted
// Submission Date: 2017-12-04
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

    int cases, n;
    vector<string> words, sequence;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        words.clear();
        sequence.clear();

        string word;
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            words.push_back(word);
        }

        int pressed = words.front().length();
        string last = words.front();
        sequence.push_back(words.front());
        words.erase(words.begin());

        while (words.size())
        {
            int picked = -1, longest = 0;
            
            for (int i = 0; i < words.size(); i++)
            {
                int same = 0;
                for (int j = 0; j < words[i].length() && j < last.length(); j++)
                    if (last[j] == words[i][j])
                        same++;
                    else
                        break;
                if (picked == -1 || same > longest) picked = i, longest = same;
            }

            pressed += words[picked].length() - longest;
            last = words[picked];
            sequence.push_back(words[picked]);
            words.erase(words.begin() + picked);
        }

        cout << pressed << '\n';
        for (auto w : sequence) cout << w << '\n';
    }

    return 0;
}
