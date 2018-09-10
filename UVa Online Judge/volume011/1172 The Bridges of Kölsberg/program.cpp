// The Bridges of Kölsberg
// UVa ID: 1172
// Verdict: Accepted
// Submission Date: 2018-09-10
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool use_bottom_to_up = false;

const int INF = 0x3f3f3f3f;

struct city
{
    string city_name, os_type;
    int trade_value;
} north[1001], south[1001];

int max_value[1001][1001], min_bridge[1001][1001];

void update(int i, int j, int ii, int jj)
{
    if (max_value[ii][jj] > max_value[i][j])
    {
        max_value[i][j] = max_value[ii][jj];
        min_bridge[i][j] = min_bridge[ii][jj];
    }
    else if (max_value[ii][jj] == max_value[i][j])
    {
        if (min_bridge[ii][jj] < min_bridge[i][j])
            min_bridge[i][j] = min_bridge[ii][jj];
    }
}

void dp(int i, int j)
{
    if (max_value[i - 1][j] == -1) dp(i - 1, j);
    if (max_value[i][j - 1] == -1) dp(i, j - 1);
    if (max_value[i - 1][j - 1] == -1) dp(i - 1, j - 1);
    
    update(i, j, i - 1, j - 1);
    update(i, j, i - 1, j);
    update(i, j, i, j - 1);
    
    if (north[i].os_type == south[j].os_type)
    {
        int new_value = max_value[i - 1][j - 1] + north[i].trade_value + south[j].trade_value;
        int new_bridge = min_bridge[i - 1][j - 1] + 1;
        if (new_value > max_value[i][j])
        {
            max_value[i][j] = new_value;
            min_bridge[i][j] = new_bridge;
        }
        else if (new_value == max_value[i][j])
        {
            if (min_bridge[i][j] > new_bridge)
                min_bridge[i][j] = new_bridge;
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
            cin >> north[i].city_name >> north[i].os_type >> north[i].trade_value;
        cin >> n2;
        for (int i = 1; i <= n2; i++)
            cin >> south[i].city_name >> south[i].os_type >> south[i].trade_value;
            
        // initialize
        for (int i = 0; i <= n1; i++)
            for (int j = 0; j <= n2; j++)
            {
                max_value[i][j] = -1;
                min_bridge[i][j] = INF;
            }
        for (int i = 0; i <= n1; i++)
        {
            max_value[i][0] = 0;
            min_bridge[i][0] = 0;
        }
        for (int i = 0; i <= n2; i++)
        {
            max_value[0][i] = 0;
            min_bridge[0][i] = 0;
        }

        // bottom to up
        if (use_bottom_to_up)
        {
            for (int i = 1; i <= n1; i++)
                for (int j = 1; j <= n2; j++)
                {
                    update(i, j, i - 1, j - 1);
                    update(i, j, i - 1, j);
                    update(i, j, i, j - 1);
                    if (north[i].os_type == south[j].os_type)
                    {
                        int new_value = max_value[i - 1][j - 1] + north[i].trade_value + south[j].trade_value;
                        int new_bridge = min_bridge[i - 1][j - 1] + 1;
                        if (new_value > max_value[i][j])
                        {
                            max_value[i][j] = new_value;
                            min_bridge[i][j] = new_bridge;
                        }
                        else if (new_value == max_value[i][j])
                        {
                            if (min_bridge[i][j] > new_bridge)
                                min_bridge[i][j] = new_bridge;
                        }
                    }
                }
        }
        // top to bottom
        else
            dp(n1, n2);

        cout << max_value[n1][n2] << ' ' << min_bridge[n1][n2] << '\n';
    }

    return 0;
}
