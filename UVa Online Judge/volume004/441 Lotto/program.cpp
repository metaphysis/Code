// Lotto
// UVa IDs: 441
// Verdict: Accepted
// Submission Date: 2016-07-14
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

int k, cases = 0;
vector<int> number(50), selected(6);

void backtrack(int depth, int selected_index)
{
    if (depth == 6)
    {
        for (int i = 0; i < 6; i++)
        {
            if (i > 0) cout << ' ';
            cout << selected[i];
        }
        cout << endl;
        
        return;
    }
    
    for (int i = 1; i <= (k - selected_index) - (5 - depth); i++)
    {
        selected[depth] = number[selected_index + i];
        backtrack(depth + 1, selected_index + i);
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    while (cin >> k, k)
    {
        if (cases++) cout << endl;

        for (int i = 1; i <= k; i++)
            cin >> number[i];

        backtrack(0, 0);
    }
    
	return 0;
}
