// A Word Puzzle in the Sunny Mountains
// UVa ID: 921
// Verdict: Accepted
// Submission Date: 2017-03-14
// UVa Run Time: 2.080s
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

vector<vector<int>> encrypted;
unordered_set<string> dictionary;
char table[30];
string key, word;
int letters, n, used[30];
bool finished = false;

void backtrack(int i, int j)
{
    if (i == (n + 1))
    {
        finished = true;
        return;
    }
    
    int next = j;
    for (; next < encrypted[i].size(); next++)
        if (!table[encrypted[i][next]]) break;
        
    if (next == encrypted[i].size())
    {
        string word;
        for (int k = 0; k < encrypted[i].size(); k++)
            word += table[encrypted[i][k]];
        
        if (dictionary.find(word) != dictionary.end())
            backtrack(i + 1, 0);
    }
    else
    {
        for (int k = 1; k <= 26; k++)
        {
            if (!used[k])
            {
                used[k] = 1;
                table[encrypted[i][next]] = (char)('A' + k - 1);
                backtrack(i, next + 1);
                
                if (finished) return;
                
                used[k] = 0;
                table[encrypted[i][next]] = 0;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, number;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> letters;
        cin >> n;
        
        encrypted.assign(30, vector<int>());
        for (int i = 1; i <= n; i++)
        {
            while (cin >> number)
            {
                if (number == 0) break;
                encrypted[i].push_back(number);
            }
        }
        
        cin >> key;
        
        dictionary.clear();
        while (cin >> word)
        {
            if (word == "*") break;
            dictionary.insert(word);
        }
        
        memset(table, 0, sizeof(table));
        memset(used, 0, sizeof(used));
        
        for (int i = 0; i < encrypted[1].size(); i++)
        {
            table[encrypted[1][i]] = key[i];
            used[key[i] - 'A' + 1] = 1;
        }

        finished = false;

        backtrack(1, 0);
        
        for (int i = 1; i <= letters; i++)
            cout << table[i];
            
        cout << '\n';
    }
    
    return 0;
}
