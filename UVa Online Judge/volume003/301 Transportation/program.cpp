// Transportation
// UVa ID: 301
// Verdict: Accepted
// Submission Date: 2016-06-29
// UVa Run Time: 0.560s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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
vector<order> allOrders;

void dfs(int i, int total, map<int, int> passengers, int money)
{
    if (i == orders)
    {
        maxMoney = max(maxMoney, money);
        return;
    }
    
    // pruning, nor TLE
    if (money + allOrders[i].sumOfRemain <= maxMoney)
        return;
    
    // passengers get down
    for (int j = 0; j <= allOrders[i].start; j++)
    {
        total -= passengers[j];
        passengers[j] = 0;
    }
    
    // take order
    if (total + allOrders[i].passenger <= n)
    {
        map<int, int> nextPassengers(passengers);
        nextPassengers[allOrders[i].end] += allOrders[i].passenger;
        
        int nextTotal = total + allOrders[i].passenger;
        int nextMoney = money + allOrders[i].money;
        
        dfs(i + 1, nextTotal, nextPassengers, nextMoney);
    }
    
    // no take order
    dfs(i + 1, total, passengers, money);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    while (cin >> n >> stations >> orders)
    {
        if (n == 0 && stations == 0 && orders == 0)
            break;
        
        allOrders.clear();
        for (int i = 1; i <= orders; i++)
        {
            order aOrder;
            cin >> aOrder.start >> aOrder.end >> aOrder.passenger;
            aOrder.money = (aOrder.end - aOrder.start) * aOrder.passenger;
            aOrder.sumOfRemain = aOrder.money;
            allOrders.push_back(aOrder);
        }
        
        sort(allOrders.begin(), allOrders.end());
        
        for (int i = allOrders.size() - 2; i >= 0; i--)
            allOrders[i].sumOfRemain += allOrders[i + 1].sumOfRemain;
        
        map<int, int> passengers;
        for (int i = 0; i <= stations; i++)
            passengers[i] = 0;
            
        maxMoney = 0;
        dfs(0, 0, passengers, 0);

        cout << maxMoney << endl;
    }
    
	return 0;
}
