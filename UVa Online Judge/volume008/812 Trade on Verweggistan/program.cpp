// Trade on Verweggistan
// UVa ID: 812
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

set<int> boxes;

void backtrack(int total, int i, int j)
{

}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int profit[60][30], w, b[30], cases = 0;
    vector<vector<int>> prul;

    while (cin >> w, w > 0)
    {
        memset(profit, 0, sizeof(profit));
        prul.clear();
        
        int maxProfit = 0;
        for (int i = 0; i < w; i++)
        {
            cin >> b[i];

            if (b[i] > 0)
            {
                for (int j = 1; j <= b[i]; j++)
                {
                    cin >> profit[i][j];
                    profit[i][j] = 10 - profit[i][j] + profit[i][j - 1];
                }
            
                profit[i][0] = profit[i][1];
                for (int j = 1; j <= b[i]; j++)
                    profit[i][0] = max(profit[i][0], profit[i][j]);
                    
                if (profit[i][0] > 0)
                {
                    maxProfit += profit[i][0];
                    vector<int> number;
                    for (int j = 1; j <= b[i]; j++)
                        if (profit[i][j] == profit[i][0])
                            number.push_back(j);
                    prul.push_back(number);
                }
            }
        }
        
        if (cases++ > 0) cout << '\n';

        cout << "Workyards " << cases << '\n';
        cout << "Maximum profit is " << maxProfit << ".\n";
        cout << "Number of pruls to buy:";
        
        if (prul.size() == 0) cout << " 0\n";
        else
        {
            boxes.clear();
            total = 0;
            backtrack(0, 0);
            for (auto box : boxes) cout << ' ' << box;
            cout << '\n';
        }
    }
    
	return 0;
}
