// Trade on Verweggistan
// UVa ID: 812
// Verdict: Accepted
// Submission Date: 2016-12-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int profit[60][30], w, b[30], cases = 0;
    vector<vector<int>> pruls;

    while (cin >> w, w > 0)
    {
        memset(profit, 0, sizeof(profit));
        pruls.clear();
        
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

                if (profit[i][0] >= 0)
                {
                    vector<int> number;
                    if (profit[i][0] == 0) number.push_back(0);
                    
                    maxProfit += profit[i][0];
                    for (int j = 1; j <= b[i]; j++)
                        if (profit[i][j] == profit[i][0])
                            number.push_back(j);

                    pruls.push_back(number);
                }
            }
        }
        
        if (cases++ > 0) cout << '\n';

        cout << "Workyards " << cases << '\n';
        cout << "Maximum profit is " << maxProfit << ".\n";
        cout << "Number of pruls to buy:";
        
        if (pruls.size() == 0) cout << " 0\n";
        else
        {
            int minimum = 0;
            for (auto group : pruls)
                minimum += group.front();

            if (maxProfit == 0) minimum = 0;

            set<int> boxes = {0};
            for (auto group : pruls)
            {
                set<int> next(boxes);
                boxes.clear();
                for (auto box : next)
                    for (auto single : group)
                        boxes.insert(box + single);
            }

            int outputed = 0;
            for (auto box : boxes)
                if (box >= minimum && outputed++ < 10)
                    cout << ' ' << box;
            cout << '\n';
        }
    }
    
	return 0;
}
