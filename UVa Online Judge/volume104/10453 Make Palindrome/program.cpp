// Make Palindrome
// UVa ID: 10453
// Verdict: Accepted
// Submission Date: 2017-04-04
// UVa Run Time: 0.350s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct optimal
{
    int minimalCost, operation;
};

optimal dp[1010][1010];
string line;

int find(int i, int j)
{
    if (i >= j) return 0;
    if (dp[i][j].minimalCost >= 0) return dp[i][j].minimalCost;

    if (line[i] == line[j])
    {
        dp[i][j].minimalCost = find(i + 1, j - 1);
        dp[i][j].operation = 0;
    }
    else
    {
        int cost = 2 + find(i + 1, j - 1);
        if (dp[i][j].minimalCost == -1 || cost < dp[i][j].minimalCost)
        {
            dp[i][j].minimalCost = cost;
            dp[i][j].operation = 1;
        }
        
        cost = 1 + find(i + 1, j);
        if (cost < dp[i][j].minimalCost)
        {
            dp[i][j].minimalCost = cost;
            dp[i][j].operation = 2;
        }
        
        cost = 1 + find(i, j - 1);
        if (cost < dp[i][j].minimalCost)
        {
            dp[i][j].minimalCost = cost;
            dp[i][j].operation = 3;
        }
    }

    return dp[i][j].minimalCost;
}

void rebuild(int i, int j)
{
    string front, back;
    
    while (i <= j)
    {
        if (i == j)
        {
            front.push_back(line[i]);
            break;
        }
        
        if (dp[i][j].operation == 0)
        {
            front.push_back(line[i]);
            back.insert(back.begin(), line[j]);
            i += 1, j -= 1;
        }
        else if (dp[i][j].operation == 1)
        {
            front.push_back(line[i]);
            front.push_back(line[j]);
            back.insert(back.begin(), line[i]);
            back.insert(back.begin(), line[j]);
            i += 1, j -= 1;
        }
        else if (dp[i][j].operation == 2)
        {
            front.push_back(line[i]);
            back.insert(back.begin(), line[i]);
            i += 1;
        }
        else
        {
            front.push_back(line[j]);
            back.insert(back.begin(), line[j]);
            j -= 1;
        }
    }
    
    cout << front << back << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (getline(cin, line))
    {
        memset(dp, -1, sizeof(dp));
        
        int cost = find(0, line.length() - 1);
        cout << cost << ' ';
        
        rebuild(0, line.length() - 1);
    }
    
    return 0;
}
