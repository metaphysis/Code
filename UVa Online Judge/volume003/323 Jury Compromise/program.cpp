// Jury Compromise
// UVa ID: 323
// Verdict: Accepted
// Submission Date: 2018-09-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct person
{
    int prosecution, defence, sum, diff;
};

struct data
{
    int sum, pre_diff;
    vector<int> selected;
};

int n, m, cases = 0, offset;
person jury[210];
data cache[21][810];

void knapsack()
{
    int top = 2 * offset * m;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= top; j++)
        {
            cache[i][j].sum = -1;
            cache[i][j].selected.clear();
        }
    cache[0][0].sum = 0;

    for (int i = 1; i <= n; i++)
        for (int j = min(i, m); j >= 1; j--)
            for (int k = (jury[i].diff + offset); k <= top; k++)
            {
                int pre_diff = k - (jury[i].diff + offset);
                if (cache[j - 1][pre_diff].sum != -1)
                {
                    int next = cache[j - 1][pre_diff].sum + jury[i].sum;
                    if (next > cache[j][k].sum)
                    {
                        cache[j][k].sum = next;
                        cache[j][k].selected = cache[j - 1][pre_diff].selected;
                        cache[j][k].selected.push_back(i);
                        cache[j][k].pre_diff = pre_diff;
                    }
                }
            }

    cout << "Jury #" << ++cases << '\n';
    int last_diff = offset * m;
    for (int i = 0; ; i++)
    {
        int j = last_diff - i, k = last_diff + i;
        if (cache[m][j].sum == -1 && cache[m][k].sum == -1) continue;
        if (cache[m][j].sum != -1 && cache[m][k].sum != -1)
        {
            if (cache[m][j].sum > cache[m][k].sum)
                last_diff -= i;
            else
                last_diff += i;
        }
        else if (cache[m][j].sum != -1 && cache[m][k].sum == -1)
        {
            last_diff -= i;
        }
        else
        {
            last_diff += i;
        }
        break;
    }

    int sum_of_prosecution = 0, sum_of_defence = 0;
    sort(cache[m][last_diff].selected.begin(), cache[m][last_diff].selected.end());
    for (auto k : cache[m][last_diff].selected)
    {
        sum_of_prosecution += jury[k].prosecution;
        sum_of_defence += jury[k].defence;
    }
    cout << "Best jury has value " << sum_of_prosecution;
    cout << " for prosecution and value " << sum_of_defence;
    cout << " for defence:\n";
    for (auto k : cache[m][last_diff].selected)
        cout << ' ' << k;
    cout << "\n\n";
}

int main(int argc, char *argv[])
{
    while (cin >> n >> m, n > 0)
    {
        offset = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> jury[i].prosecution >> jury[i].defence;
            jury[i].sum = jury[i].prosecution + jury[i].defence;
            jury[i].diff = jury[i].prosecution - jury[i].defence;
            offset = max(offset, max(jury[i].prosecution, jury[i].defence));
        }
        knapsack();
    }
    
	return 0;
}
