// Transportation
// UVa ID: 301
// Verdict: Accepted
// Submission Date: 2016-06-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct order
{
    int start, end, passenger, money, sumOfRemain;
    
    bool operator<(order x) const
    {
        if (start != x.start)
            return start < x.start;
        else
            return end < x.end;
    }
};

int n, stations, orders, maxMoney = 0;
order allOrders[30];
int passengers[20];

void dfs(int current, int previous, int total, int money)
{
    if (current == orders)
    {
        maxMoney = max(maxMoney, money);
        return;
    }
    
    // pruning, nor TLE
    if (money + allOrders[current].sumOfRemain <= maxMoney)
        return;
    
    // passengers get down
    for (int j = previous + 1; j <= allOrders[current].start; j++)
        total -= passengers[j];
    
    // take order
    if (total + allOrders[current].passenger <= n)
    {
        passengers[allOrders[current].end] += allOrders[current].passenger;
        dfs(current + 1, allOrders[current].start, total + allOrders[current].passenger, money + allOrders[current].money);
        passengers[allOrders[current].end] -= allOrders[current].passenger;
    }
    
    // no take order
    dfs(current + 1, allOrders[current].start, total, money);
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    while (cin >> n >> stations >> orders)
    {
        if (n == 0 && stations == 0 && orders == 0)
            break;
        
        for (int i = 0; i < orders; i++)
        {
            cin >> allOrders[i].start >> allOrders[i].end >> allOrders[i].passenger;
            allOrders[i].money = (allOrders[i].end - allOrders[i].start) * allOrders[i].passenger;
            allOrders[i].sumOfRemain = allOrders[i].money;
        }
        
        sort(allOrders, allOrders + orders);
        
        for (int i = orders - 2; i >= 0; i--)
            allOrders[i].sumOfRemain += allOrders[i + 1].sumOfRemain;

        for (int i = 0; i <= stations; i++)
            passengers[i] = 0;
            
        maxMoney = 0;
        dfs(0, 0, 0, 0);

        cout << maxMoney << endl;
    }
    
	return 0;
}
