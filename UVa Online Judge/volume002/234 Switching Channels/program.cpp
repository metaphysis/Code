// Switching Channels
// UVa ID: 234
// Verdict: Accepted
// Submission Date: 2016-06-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int programme[10], alignment[10][2], used[8], minutes[10], p, a;
int indexer[10], bestIndex[10], bestMiss[10], initialized = false;

void backtrack(int index)
{
    if (index == (p + 1))
    {
        int miss[10] = { 0 };
        for (int i = 1; i <= a; i++)
        {
            int j = lower_bound(minutes, minutes + p, alignment[i][1]) - minutes;
            if (j > p)
                miss[alignment[i][0]] += alignment[i][1] - minutes[p];
            else
                miss[alignment[i][0]] += min(abs(alignment[i][1] - minutes[j - 1]),
                    abs(alignment[i][1] - minutes[j]));
        }

        if (!initialized)
        {
            copy(miss, miss + 10, bestMiss);
            copy(indexer, indexer + 10, bestIndex);
            initialized = true;
        }
        else
        {
            for (int i = 0; i < 10; i++)
                if (miss[i] == bestMiss[i])
                    continue;
                else
                {
                    if (miss[i] < bestMiss[i])
                    {
                        copy(miss, miss + 10, bestMiss);
                        copy(indexer, indexer + 10, bestIndex);
                    }
                    break;
                }
        }

        return;
    }

    for (int i = 1; i <= p; i++)
        if (used[i] == false)
        {
            used[i] = true;
            indexer[index] = i;
            minutes[index] = minutes[index - 1] + programme[i];
            backtrack(index + 1);
            used[i] = false;
        }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> p, p)
    {
        for (int i = 1; i <= p; i++)
            cin >> programme[i];

        cin >> a;
        for (int i = 1; i <= a; i++)
            cin >> alignment[i][0] >> alignment[i][1];

        memset(used, 0, sizeof(used));
        memset(minutes, 0, sizeof(minutes));
        initialized = false;

        backtrack(1);

        cout << "Data set " << ++cases << endl;
        cout << "  Order:";

        for (int i = 1; i <= p; i++)
            cout << " " << programme[bestIndex[i]];
        cout << endl;

        int bestTotalMiss = 0;
        for (int i = 1; i <= a; i++)
            bestTotalMiss += bestMiss[i];

        cout << "  Error: " << bestTotalMiss << endl;
    }

    return 0;
}
