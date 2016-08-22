// CD
// UVa ID: 624
// Verdict: Accepted
// Submission Date: 2016-08-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int N, tracks, minutes[25], tails[25];
int max_sum, used[25], best[25];

void backtrack(int depth, int sum)
{
    if (sum > max_sum)
    {
        max_sum = sum;
        copy(used, used + 25, best);
    }
    
    if (depth < tracks)
    {
        for (int i = depth; i < tracks; i++)
        {
            if (sum + tails[i] < max_sum)
                return;

            if (used[i] == 0 && sum + minutes[i] <= N)
            {
                used[i] = 1;
                backtrack(depth + 1, sum + minutes[i]);
                used[i] = 0;
            }
        }
    }
}
    
int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> N)
    {
        cin >> tracks;
        int sum = 0;
        for (int i = 0; i < tracks; i++)
        {
            cin >> minutes[i];
            sum += minutes[i];
        }
        
        if (sum <= N)
        {
            for (int i = 0; i < tracks; i++)
                cout << minutes[i] << ' ';
            cout << "sum:" << sum << '\n';
        }
        else
        {
            memset(tails, 0, sizeof(tails));
            tails[tracks - 1] = minutes[tracks - 1];
            for (int i = tracks - 2; i >= 0; i--)
                tails[i] += tails[i + 1] + minutes[i];
                
            max_sum = 0;
            memset(used, 0, sizeof(used));
            backtrack(0, 0);
            
            for (int i = 0; i < tracks; i++)
                if (best[i])
                    cout << minutes[i] << ' ';
                cout << "sum:" << max_sum << '\n';
        }
    }
    
	return 0;
}
