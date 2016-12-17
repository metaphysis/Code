// The Mailbox Manufacturers Problem
// UVa ID: 882
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int maximal = 0;

void dfs(int used, int k, int low, int high)
{
    cout << "used = " << used << " k = " << k << " low = " << low << " high = " << high << '\n';
    if (k > 1 && low < high)
    {
        int middle = (low + high) / 2;
        dfs(used + middle, k - 1, low, middle - 1);
        dfs(used + middle, k, middle + 1, high);
    }
    else
    {
        for (int i = low; i <= high; i++) used += i;
        maximal = max(maximal, used);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int N, k, m;
    cin >> N;
    
    for (int i = 1; i <= N; i++)
    {
        cin >> k >> m;
        maximal = 0;
        dfs(0, k, 1, m);
        cout << maximal << '\n';
    }
    
	return 0;
}
