// Master Mind Helper
// UVa ID: 947
// Verdict: Accepted
// Submission Date: 2017-03-13
// UVa Run Time: 0.070s
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

vector<vector<string>> secret(6);

void dfs(string code, int length)
{
    if (length > 5) return;
    for (int i = 1; i <= 9; i++)
    {
        string next = code + (char)('0' + i);
        secret[length].push_back(next);
        dfs(next, length + 1);
    }
}

bool match(string answer, string guess, int right, int wrong)
{
    int r = 0, w = 0;
    for (int i = 0; i < answer.length(); i++)
        if (answer[i] == guess[i])
        {
            r++;
            guess[i] = '0';
            answer[i] = '0';
        }

    for (int i = 0; i < guess.length(); i++)
        for (int j = 0; j < answer.length(); j++)
            if (guess[i] != '0' && guess[i] == answer[j])
            {
                w++;
                answer[j] = '0';
                break;
            }
 
    return right == r && wrong == w;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    dfs("", 1);
    
    string guess;
    int right, wrong;
    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> guess >> right >> wrong;
        
        int count = 0;
        for (auto answer : secret[guess.length()])
            if (match(answer, guess, right, wrong))
                count++;
        cout << count << '\n';
    }
    
    return 0;
}
