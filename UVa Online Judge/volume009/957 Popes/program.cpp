// Popes
// UVa ID: 957
// Verdict: Accepted
// Submission Date: 2017-03-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int period, popes, year;

    while (cin >> period)
    {
        cin >> popes;

        deque < int >years;
        int maxCount = 0, maxStart = 0, maxEnd = 0;

        cin >> year;
        years.push_back(year);
        maxCount = 1, maxStart = year, maxEnd = year;

        for (int i = 2; i <= popes; i++)
        {
            cin >> year;
            if (year - years.front() < period)
            {
                years.push_back(year);
            }
            else
            {
                if (years.size() > maxCount)
                {
                    maxCount = years.size();
                    maxStart = years.front();
                    maxEnd = years.back();
                }

                while (!years.empty())
                {
                    if (year - years.front() < period)
                    {
                        years.push_back(year);
                        break;
                    }
                    years.pop_front();
                }
            }
        }

        if (years.size() > maxCount)
        {
            maxCount = years.size();
            maxStart = years.front();
            maxEnd = years.back();
        }

        cout << maxCount << ' ' << maxStart << ' ' << maxEnd << '\n';
    }

    return 0;
}
