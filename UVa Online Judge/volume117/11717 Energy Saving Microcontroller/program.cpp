// Energy Saving Microcontroller
// UVa ID: 11717
// Verdict: Accepted
// Submission Date: 2018-01-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int ACTIVING = 0, RUNNING = 1, SLEEPING = 2;
const int MAX_MS = 0x7fffffff;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int n, live, recovery, ms;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> live >> recovery;

        int idles = 0, ignores = 0;
        int begin = 0, end = live, status = RUNNING;

        for (int i = 1; i <= n; i++)
        {
            cin >> ms;

            while (true)
            {
                if (ms >= begin && ms < end)
                {
                    if (status == ACTIVING) ignores++;
                    else if (status == SLEEPING)
                    {
                        idles++;
                        begin = ms, end = ms + recovery, status = ACTIVING;
                    }
                    else
                    {
                        begin = ms, end = ms + live, status = RUNNING;
                    }
                    break;
                }
                else
                {
                    if (status == RUNNING) begin = end, end = MAX_MS, status = SLEEPING;
                    else if (status == SLEEPING) begin = ms, end = ms + recovery, status = ACTIVING;
                    else if (status == ACTIVING) begin = end, end += live, status = RUNNING;  
                }
            }
        }
    
        cout << "Case " << c << ": " << idles << ' ' << ignores << '\n';
    }

    return 0;
}
