// Stamping Out Stamps
// UVa ID: 266
// Verdict: Accepted
// Submission Date: 2016-06-09
// UVa Run Time: 0.140s
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
#include <vector>

using namespace std;

vector <int> values;
int n;

void convert(int amount)
{
    int coverage[3100], parent[3100][2];
    for (int i = 0; i < 3100; i++)
    {
        coverage[i] = 10000;
        parent[i][0] = -1;
        parent[i][1] = -1;
    }
    
    coverage[0] = 0;
    for (int i = 1; i < 3100; i++)
        for (int j = 0; j < n; j++)
        {
            if (i >= values[j] && (coverage[i - values[j]] + 1) < coverage[i])
            {
                coverage[i] = coverage[i - values[j]] + 1;
                parent[i][0] = i - values[j];
                parent[i][1] = values[j];
            }
        }
    
    if (coverage[amount] > 10)
    {
        for (int i = amount + 1; i < 3100; i++)
            if (coverage[i] <= 10)
            {
                amount = i;
                break;
            }
    }
    
    vector <int> stamps;
    int end = parent[amount][0];
    stamps.push_back(parent[amount][1]);
    while (parent[end][0] != -1)
    {
        stamps.push_back(parent[end][1]);
        end = parent[end][0];
    }
    sort(stamps.begin(), stamps.end(), greater<int>());
    cout << "STAMPS USED";
    for (int i = 0; i < stamps.size(); i++)
        cout << " " << stamps[i];
    cout << endl;
}

int main(int argc, char *argv[])
{
    while (cin >> n, n > 0)
    {
        values.resize(n);
        for (int i = 1; i <= n; i++)
            cin >> values[i - 1];
            
        sort(values.begin(), values.end());
        cout << "STAMP VALUES";
        for (int i = 0; i < values.size(); i++)
            cout << " " << values[i];
        cout << endl << endl;
        reverse(values.begin(), values.end());
        
        int amount;
        while (cin >> amount, amount > 0)
        {
            cout << "AMOUNT " << amount << endl;
            if (amount > values.front() * 10)
                cout << "NO SOLUTION EXISTS" << endl;
            else
                convert(amount);
            cout << endl;
        }
    }
    
	return 0;
}
