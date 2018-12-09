// Enemy at the Gates
// UVa ID: 12428
// Verdict: Accepted
// Submission Date: 2018-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    long long N, M;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N >> M;
        long long low = 0, high = N - 1, mid, answer;
        while (low <= high)
        {
            mid = (low + high) >> 1;
            long long r = N - mid;
            if (r * (r - 1) / 2LL >= (M - mid))
            {
                answer = mid;
                low = mid + 1;
            }
            else high = mid - 1;
        }
        cout << answer << '\n';
    }

    return 0;
}
