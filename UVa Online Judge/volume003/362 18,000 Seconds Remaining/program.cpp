// 18,000 Seconds Remaining
// UVa ID: 362
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int n, transfered, bytes, bytesInFiveSeconds, seconds, cases = 0;
    while (cin >> n, n)
    {
        transfered = 0, bytes = 0, bytesInFiveSeconds = 0, seconds = 0;
        cout << "Output for data set " << ++cases << ", " << n << " bytes:" << "\n";

        while (cin >> bytes)
        {
            seconds++;
            transfered += bytes;
            bytesInFiveSeconds += bytes;

            if (seconds % 5 == 0)
            {
                cout << "   Time remaining: ";
                if (bytesInFiveSeconds == 0)
                    cout << "stalled" << "\n";
                else
                {
                    int remaining = 0;
                    remaining = 5 * (n - transfered) / bytesInFiveSeconds;
                    if (5 * (n - transfered) % bytesInFiveSeconds > 0)
                        remaining++;
                    cout << remaining << " seconds" << "\n";
                }

                bytesInFiveSeconds = 0;
            }

            if (transfered == n)
                break;
        }

        cout << "Total time: " << seconds << " seconds" << "\n";
        cout << endl;
    }

    return 0;
}
