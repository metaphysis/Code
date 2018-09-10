// The Bridges of Kölsberg
// UVa ID: 1172
// Verdict: Accepted
// Submission Date: 2018-09-10
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool useBottomUp = false;

const int INF = 0x3f3f3f3f;

struct city
{
    string cityName, osType;
    int tradeValue;
} north[1001], south[1001];

int maxValue[1001][1001], minBridge[1001][1001];

void update(int i, int j, int ii, int jj)
{
    if (maxValue[i][j] < maxValue[ii][jj])
    {
        maxValue[i][j] = maxValue[ii][jj];
        minBridge[i][j] = minBridge[ii][jj];
    }
    else if (maxValue[i][j] == maxValue[ii][jj])
    {
        if (minBridge[i][j] > minBridge[ii][jj])
            minBridge[i][j] = minBridge[ii][jj];
    }
}

void dp(int i, int j)
{
    if (i == 0 || j == 0)
    {
        maxValue[i][j] = minBridge[i][j] = 0;
        return;
    }

    if (maxValue[i - 1][j] == -1) dp(i - 1, j);
    if (maxValue[i][j - 1] == -1) dp(i, j - 1);
    if (maxValue[i - 1][j - 1] == -1) dp(i - 1, j - 1);
    
    update(i, j, i - 1, j);
    update(i, j, i, j - 1);
    update(i, j, i - 1, j - 1);
    
    if (north[i].osType == south[j].osType)
    {
        int new_value = maxValue[i - 1][j - 1] + north[i].tradeValue + south[j].tradeValue;
        int new_bridge = minBridge[i - 1][j - 1] + 1;
        if (maxValue[i][j] < new_value)
        {
            maxValue[i][j] = new_value;
            minBridge[i][j] = new_bridge;
        }
        else if (maxValue[i][j] == new_value)
        {
            if (minBridge[i][j] > new_bridge)
                minBridge[i][j] = new_bridge;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n1, n2;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n1;
        for (int i = 1; i <= n1; i++)
            cin >> north[i].cityName >> north[i].osType >> north[i].tradeValue;
        cin >> n2;
        for (int i = 1; i <= n2; i++)
            cin >> south[i].cityName >> south[i].osType >> south[i].tradeValue;
            
        // initialize
        for (int i = 0; i <= n1; i++)
            for (int j = 0; j <= n2; j++)
            {
                maxValue[i][j] = -1;
                minBridge[i][j] = INF;
            }

        // bottom-up
        if (useBottomUp)
        {
            for (int i = 0; i <= n1; i++)
            {
                maxValue[i][0] = 0;
                minBridge[i][0] = 0;
            }
            for (int i = 0; i <= n2; i++)
            {
                maxValue[0][i] = 0;
                minBridge[0][i] = 0;
            }

            for (int i = 1; i <= n1; i++)
                for (int j = 1; j <= n2; j++)
                {
                    update(i, j, i - 1, j - 1);
                    update(i, j, i - 1, j);
                    update(i, j, i, j - 1);
                    if (north[i].osType == south[j].osType)
                    {
                        int new_value = maxValue[i - 1][j - 1] + north[i].tradeValue + south[j].tradeValue;
                        int new_bridge = minBridge[i - 1][j - 1] + 1;
                        if (maxValue[i][j] < new_value)
                        {
                            maxValue[i][j] = new_value;
                            minBridge[i][j] = new_bridge;
                        }
                        else if (maxValue[i][j] == new_value)
                        {
                            if (minBridge[i][j] > new_bridge)
                                minBridge[i][j] = new_bridge;
                        }
                    }
                }
        }
        // top-down
        else
            dp(n1, n2);

        cout << maxValue[n1][n2] << ' ' << minBridge[n1][n2] << '\n';
    }

    return 0;
}
