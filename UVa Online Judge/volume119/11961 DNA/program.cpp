// DNA
// UVa ID: 11961
// Verdict: Accepted
// Submission Date: 2017-11-14
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

int n, k, used[20];
string dna;
set<string> all;
string letters = "ACGT";

void dfs(int depth, int idx)
{
    if (depth == k)
    {
        if (all.find(dna) == all.end())
            all.insert(dna);
        return;
    }
    
    for (int i = idx; i < n; i++)
        if (!used[i])
        {
            used[i] = 1;
            char c = dna[i];
            for (int j = 0; j < 4; j++)
            {
                dna[i] = letters[j];
                dfs(depth + 1, i + 1);
                dna[i] = c;
            }
            used[i] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k >> dna;
        
        all.clear();
        memset(used, 0, sizeof(used));
        dfs(0, 0);
        
        cout << all.size() << '\n';
        for (auto a : all) cout << a << '\n';
    }

    return 0;
}
