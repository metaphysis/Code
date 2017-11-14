// The Problem of the Crazy Linguist
// UVa ID: 11201
// Verdict: Accepted
// Submission Date: 2017-11-14
// UVa Run Time: 0.350s
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

int counter[10][26] = {0}, used[26] = {0};
int flag[26] = {0};
int sequence[10], cnt = 0, top;
string even = "aeiou";

double probability[26] = {
    12.53, 1.42, 4.68, 5.86, 13.68,
    0.69, 1.01, 0.70, 6.25, 0.44,
    0.00, 4.97, 3.15, 6.71, 8.68,
    2.51, 0.88, 6.87, 7.98, 4.63,
    3.93, 0.90, 0.02, 0.22, 0.90, 0.52
};

void dfs(int depth, int tag)
{
    if (depth > top)
    {
        cnt++;
        for (int i = 1; i <= top; i++)
            counter[i][sequence[i]]++;
        return;
    }
    
    for (int i = 0; i < 26; i++)
        if (tag == flag[i] && used[i] < 2)
        {
            used[i] += 1;
            sequence[depth] = i;
            dfs(depth + 1, (tag + 1) % 2);
            used[i] -= 1;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string word;

    for (int i = 0; i < 26; i++) flag[i] = 1;
    for (int i = 0; i < even.length(); i++) flag[even[i] - 'a'] = 0;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> word;
        
        top = word.length();
        memset(used, 0, sizeof(used));
        memset(counter, 0, sizeof(counter));
        used[word.front() - 'a'] = 1;
        sequence[1] = word.front() - 'a';
        cnt = 0;

        dfs(2,  0);
        
        double total = 0.0;
        for (int i = 1; i <= top; i++)
            for (int j = 0; j < 26; j++)
                if (counter[i][j])
                    total += probability[j] * i * counter[i][j];
        double average = total / cnt;

        double single = 0.0;
        for (int i = 0; i < word.length(); i++)
            single += (i + 1) * probability[word[i] - 'a'];
            
        if (single + 1e-7 < average) cout << "below\n";
        else cout << "above or equal\n";
    }

    return 0;
}
