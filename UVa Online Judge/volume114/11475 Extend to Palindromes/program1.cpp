// Extend to Palindromes
// UVa ID: 11475
// Verdict: Accepted
// Submission Date: 2017-03-29
// UVa Run Time: 0.020s
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

void manacher(string &line)
{
    string word;
    word.push_back('#');
    for (int i = 0; i < line.length(); i++)
    {
        word.push_back(line[i]);
        word.push_back('#');
    }
    
    vector<int> P(word.size());
    
    int center = 0, rightmost = 0, low = 0, high = 0;
    int maxP = 0;
    for (int i = 1; i < word.length(); i++)
    {
        if (rightmost > i)
        {
            int j = center * 2 - i;
            if (P[j] < (rightmost - i))
            {
                P[i] = P[j];
                low = -1;
            }
            else
            {
                P[i] = rightmost - i;
                high = rightmost + 1;
                low = i * 2 - high;
            }
        }
        else
        {
            P[i] = 0;
            low = i - 1;
            high = i + 1;
        }

        while (low >= 0 && high < word.length() && word[low] == word[high])
        {
            P[i]++;
            low--;
            high++;
        }

        if ((i + P[i]) > rightmost)
        {
            center = i;
            rightmost = i + P[i];
        }
        
        maxP = max(maxP, P[i]);
    }
    
    if (maxP == line.length())
        cout << line << '\n';
    else
    {
        cout << line;
        for (int i = 0; i < P.size(); i++)
            if ((i + P[i]) == (P.size() - 1) )
            {
                for (int j = i - P[i] - 1; j >= 0; j--)
                    if (word[j] != '#')
                        cout << word[j];
                break;
            }
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line)) manacher(line);
    
    return 0;
}
