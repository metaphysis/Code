// Tele-loto
// UVa ID: 11975
// Verdict: Accepted
// Submission Date: 2017-11-08
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int N, L, ball;
    int money[10], rank[100], ticket[10][10];
    int combin1[4][2] = {{1, 1}, {1, 5}, {5, 1}, {5, 5}};
    int combin2[5][2] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}};
    int combin3[9][2] = {{1, 1}, {1, 5}, {5, 1}, {5, 5}, {2, 2}, {2, 4}, {4, 2}, {4, 4}, {3, 3}};
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cout << "Case " << c << ":\n";

        cin >> N >> L;
        
        fill(rank, rank + 100, 10000);
        for (int i = 1; i <= N; i++)
        {
            cin >> ball;
            rank[ball] = i;
        }
        
        for (int i = 1; i <= 4; i++)
            cin >> money[i];
            
        for (int k = 1; k <= L; k++)
        {
            for (int i = 1; i <= 5; i++)
                for (int j = 1; j <= 5; j++)
                    cin >> ticket[i][j];
                    
            int total = 0;
            
            bool flag = true;
            for (int i = 0; i < 4; i++)
                if (rank[ticket[combin1[i][0]][combin1[i][1]]] > 35)
                {
                    flag = false;
                    break;
                }
            if (flag) total += money[1];
            
            flag = true;
            for (int i = 0; i < 5; i++)
                if (rank[ticket[combin2[i][0]][combin2[i][1]]] > 40)
                {
                    flag = false;
                    break;
                }
            if (flag) total += money[2];
            
            flag = true;
            for (int i = 0; i < 9; i++)
                if (rank[ticket[combin3[i][0]][combin3[i][1]]] > 45)
                {
                    flag = false;
                    break;
                }
            if (flag) total += money[3];
            
            flag = true;
            for (int i = 1; i <= 5; i++)
                for (int j = 1; j <= 5; j++)
                    if (rank[ticket[i][j]] > 75)
                    {
                        flag = false;
                        break;
                    }
            if (flag) total += money[4];
            
            cout << total << '\n';
        }
            
    }
    
    return 0;
}
