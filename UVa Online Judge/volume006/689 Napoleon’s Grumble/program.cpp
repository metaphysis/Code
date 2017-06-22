// Napoleon’s Grumble
// UVa ID: 689
// Verdict: Accepted
// Submission Date: 2017-06-22
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

struct palindrome
{
    int idx, length;
    
    bool operator<(const palindrome &p) const
    {
        return length > p.length;
    }
};

bool contains(set<string> &palindromes, string &block)
{
    if (palindromes.find(block) != palindromes.end()) return true;
    
    for (auto p : palindromes)
    {
        if (p.length() == block.length()) continue;
        if ((p.length() + block.length()) % 2 == 1) continue;
        
        bool included = true;
        int start = (p.length() - block.length()) / 2;
        for (int i = 0; i < block.length(); i++)
            if (p[start + i] != block[i])
            {
                included = false;
                break;
            }
        if (included) return true;
    }
    
    return false;
}

void manacher(string &line)
{
    string word;
    word.push_back('#');
    for (int i = 0; i < line.length(); i++)
    {
        word.push_back(line[i]);
        word.push_back('#');
    }
    
    vector<palindrome> P(word.size());
    for (int i = 0; i < P.size(); i++)
        P[i].idx = i;

    int center = 0, rightmost = 0, low = 0, high = 0;
    for (int i = 1; i < word.length(); i++)
    {
        if (rightmost > i)
        {
            int j = center * 2 - i;
            if (P[j].length < (rightmost - i))
            {
                P[i].length = P[j].length;
                low = -1;
            }
            else
            {
                P[i].length = rightmost - i;
                high = rightmost + 1;
                low = i * 2 - high;
            }
        }
        else
        {
            P[i].length = 0;
            low = i - 1;
            high = i + 1;
        }

        while (low >= 0 && high < word.length() && word[low] == word[high])
        {
            P[i].length++;
            low--;
            high++;
        }

        if ((i + P[i].length) > rightmost)
        {
            center = i;
            rightmost = i + P[i].length;
        }
    }
    
    sort(P.begin(), P.end());
    
    set<string> palindromes;
    for (int i = 0; i < P.size(); i++)
    {
        if (P[i].length <= 2) continue;

        string block;
        if (isalpha(word[P[i].idx])) block += word[P[i].idx];
        for (int j = 1; j <= P[i].length; j++)
            if (isalpha(word[P[i].idx + j]))
            {
                block.insert(block.begin(), word[P[i].idx + j]);
                block.push_back(word[P[i].idx + j]);
            }
        if (contains(palindromes, block)) continue;

        palindromes.insert(block);
    }
    
    bool first = true;
    for (auto p : palindromes)
    {
        if (first) first = false;
        else cout << ' ';

        cout << p;
    }
    
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0) cout << '\n';
        else
        {
            string cleared;
            for (int i = 0; i < line.length(); i++)
                if (isalpha(line[i]))
                    cleared += toupper(line[i]);
            manacher(cleared);
        }
    }
    
    return 0;
}
