// Jury Compromise
// UVa ID: 323
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct preference
{
    int prosecution, defence;
};

struct optimal
{
    int sum_of_prosecution, sum_of_defence;
};

preference candidates[210];
int n, m, cases = 0;

void knapsack()
{
    optimal memo[210][30];
    memset(memo, 0, sizeof(memo));
    for (int i = 0; i < 210; i++)
        for (int j = 0; j < 30; j++)
            memo[i][j].sum_of_prosecution = -10000;
    memo[0][0].sum_of_prosecution = 0;
    
    int choosed[210][30];
    memset(choosed, 0, sizeof(choosed));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int diff_now = memo[i - 1][j - 1].sum_of_prosecution - memo[i - 1][j - 1].sum_of_defence;
            diff_now += candidates[i].prosecution - candidates[i].defence;
            int diff_best = memo[i - 1][j].sum_of_prosecution - memo[i - 1][j].sum_of_defence;
            
            if (abs(diff_now) <= abs(diff_best))
            {
                choosed[i][j] = 1;
                memo[i][j].sum_of_prosecution = memo[i - 1][j - 1].sum_of_prosecution + candidates[i].prosecution;
                memo[i][j].sum_of_defence = memo[i - 1][j - 1].sum_of_defence + candidates[i].defence;
            }
            else
            {
                memo[i][j].sum_of_prosecution = memo[i - 1][j].sum_of_prosecution;
                memo[i][j].sum_of_defence = memo[i - 1][j].sum_of_defence;
            }
        }

    cout << "Jury #" << ++cases << '\n';
    cout << "Best jury has value " << memo[n][m].sum_of_prosecution;
    cout << " for prosecution and value " << memo[n][m].sum_of_defence;
    cout << " for defence:\n";

    int indexer = n, capacity = m;
    vector<int> jurors;
    while (indexer > 0)
    {
        if (choosed[indexer][capacity] == 1)
        {
            jurors.insert(jurors.begin(), indexer);
            capacity--;
        }
        indexer--;
    }
    for (int i = 0; i < jurors.size(); i++)
        cout << ' ' << jurors[i];
    cout << "\n\n";
}

int main(int argc, char *argv[])
{
    while (cin >> n >> m, n > 0)
    {
        for (int i = 1; i <= n; i++)
            cin >> candidates[i].prosecution >> candidates[i].defence;
        knapsack();
    }
    
	return 0;
}
