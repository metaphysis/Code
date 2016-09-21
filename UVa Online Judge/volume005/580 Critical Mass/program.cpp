// Critical Mass
// UVa ID: 580
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

const int MAX_N = 31;

int dp[MAX_N][8][2] = {0}, number[MAX_N] = {0};

void initialize()
{
    for (int i = 0; i < 8; i++)
        dp[3][i][0] = 0, dp[3][i][1] = 1;
    dp[3][7][0] = 1, dp[3][7][1] = 0;

    for (int i = 4; i <= 30; i++)
    {
        dp[i][0][0] = dp[i - 1][0][0] + dp[i - 1][4][0];
        dp[i][0][1] = dp[i - 1][0][1] + dp[i - 1][4][1];
        
        dp[i][1][0] = dp[i - 1][0][0] + dp[i - 1][4][0];
        dp[i][1][1] = dp[i - 1][0][1] + dp[i - 1][4][1];
        
        dp[i][2][0] = dp[i - 1][1][0] + dp[i - 1][5][0];
        dp[i][2][1] = dp[i - 1][1][1] + dp[i - 1][5][1];
        
        dp[i][3][0] = dp[i - 1][1][0] + dp[i - 1][5][0];
        dp[i][3][1] = dp[i - 1][1][1] + dp[i - 1][5][1];
        
        dp[i][4][0] = dp[i - 1][2][0] + dp[i - 1][6][0];
        dp[i][4][1] = dp[i - 1][2][1] + dp[i - 1][6][1];
        
        dp[i][5][0] = dp[i - 1][2][0] + dp[i - 1][6][0];
        dp[i][5][1] = dp[i - 1][2][1] + dp[i - 1][6][1];
        
        dp[i][6][0] = dp[i - 1][3][0] + dp[i - 1][7][0];
        dp[i][6][1] = dp[i - 1][3][1] + dp[i - 1][7][1];
        
        dp[i][7][0] = dp[i - 1][3][0] + dp[i - 1][7][0];
        dp[i][7][1] = dp[i - 1][3][1] + dp[i - 1][7][1];
    }
    
    
    for (int i = 3; i <= 30; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << dp[i][j][0] << ' ' << dp[i][j][1] << ' ';
            number[i] += dp[i][j][0];
        }
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    initialize();
    
    int n;
    while (cin >> n, n)
        cout << number[n] << '\n';
        
	return 0;
}
