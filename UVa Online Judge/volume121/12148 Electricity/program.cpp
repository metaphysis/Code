// Electricity
// UVa ID: 12148
// Verdict: Accepted
// Submission Date: 2017-12-28
// UVa Run Time: 0.000s
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

void getNextDay(int &D, int &M, int &Y)
{
    if (D == 31 && M == 12)
    {
        D = 1;
        M = 1;
        Y++;
        return;
    }
    
    if ((Y % 400 == 0) || (Y % 4 == 0 && Y % 100 != 0))
    {
        if (M == 2)
        {
            if (D <= 28)
            {
                D++;
                return;
            }
            else
            {
                D = 1;
                M = 3;
                return;
            }
        }
    }
    else
    {
        if (M == 2)
        {
            if (D <= 27)
            {
                D++;
                return;
            }
            else
            {
                D = 1;
                M = 3;
                return;
            }
        }
    }
    
    if (M == 1 || M == 3 || M == 5 || M == 7 || M == 8 || M == 10 || M == 12)
    {
        if (D == 31)
        {
            D = 1;
            M++;
            return;
        }
    }
    else
    {
        if (D == 30)
        {
            D = 1;
            M++;
            return;
        }
    }
    
    D++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    
    while (cin >> n, n > 0)
    {
        int days = 0, consumption = 0;

        int D1, M1, Y1, C1;
        int D2, M2, Y2, C2;
        
        cin >> D1 >> M1 >> Y1 >> C1;
    
        for (int i = 1; i < n; i++)
        {
            cin >> D2 >> M2 >> Y2 >> C2;
            getNextDay(D1, M1, Y1);
            if (D1 == D2 && M1 == M2 && Y1 == Y2)
            {
                days++;
                consumption += C2 - C1;
            }
            D1 = D2, M1 = M2, Y1 = Y2, C1 = C2;
        }
        
        cout << days << ' ' << consumption << '\n';
    }

    return 0;
}
