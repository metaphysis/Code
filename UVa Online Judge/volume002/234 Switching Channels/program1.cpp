// Switching Channels
// UVa ID: 234
// Verdict: Accepted
// Submission Date: 2016-06-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    vector <int> programme;
    int alignment[10][2], minutes[10] = {0}, bestTime[10], bestMiss[10] = {0};
    int p, a, cases = 0;

    while (cin >> p, p)
    {
        int times;
        programme.clear();
        for (int i = 1; i <= p; i++)
        {
            cin >> times;
            programme.push_back(times);
        }

        cin >> a;
        for (int i = 1; i <= a; i++)
            cin >> alignment[i][0] >> alignment[i][1];

        bool initialized = false;
        sort(programme.begin(), programme.end());

        do
        {
            for (int i = 0; i < programme.size(); i++)
                minutes[i + 1] = minutes[i] + programme[i];

            int miss[10] = { 0 };
            for (int i = 1; i <= a; i++)
            {
                bool flag = false;
                for (int j = 0; j < p; j++)
                    if (minutes[j] >= alignment[i][1])
                    {
                        miss[alignment[i][0]] += min(abs(alignment[i][1] - minutes[j - 1]),
                                                     abs(alignment[i][1] - minutes[j]));
                        flag = true;
                        break;
                    }
                if (!flag)
                    miss[alignment[i][0]] += alignment[i][1] - minutes[p];
            }

            if (!initialized)
            {
                copy(miss, miss + 10, bestMiss);
                for (int i = 1; i <= p; i++)
                    bestTime[i] = programme[i - 1];
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
                            for (int i = 1; i <= p; i++)
                                bestTime[i] = programme[i - 1];
                        }
                        break;
                    }
            }
        }
        while (next_permutation(programme.begin(), programme.end()));

        cout << "Data set " << ++cases << endl;
        cout << "  Order:";

        for (int i = 1; i <= p; i++)
            cout << " " << bestTime[i];
        cout << endl;

        int bestTotalMiss = 0;
        for (int i = 1; i <= a; i++)
            bestTotalMiss += bestMiss[i];

        cout << "  Error: " << bestTotalMiss << endl;
    }

    return 0;
}
