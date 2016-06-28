// Transportation
// UVa IDs: 301
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct order
{
    int start, end, passengers;
    
    bool operator<(order x) const
    {
        if (start != x.start)
            return start < x.start;
        else if (end != x.end)
            return end < x.end;
        else
            return passengers < x.passengers;
    }
};

int maxMoney = 0;
void backtrack(int n, int depth, int total, map<int, int> passengers, int money)
{
    if (depth == n + 1)
    {
        maxMoney = max(maxMoney, money);
        return;
    }
    
    
}

int main(int argc, char *argv[])
{
    int n, stations, orders;
    while (cin >> n >> stations >> orders)
    {
        vector<order> allOrders;
        for (int i = 1; i <= orders; i++)
        {
            order aOrder;
            cin >> aOrder.start >> aOrder.end >> aOrder.passengers;
            allOrders.push_back(aOrder);
        }
        
        sort(allOrders.begin(), allOrders.end());
        
        maxMoney = 0;
        
        cout << maxMoney << endl;
    }
	return 0;
}
