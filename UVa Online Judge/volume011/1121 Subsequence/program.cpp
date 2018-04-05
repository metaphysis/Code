// Subsequence
// UVa ID: 1121
// Verdict: Accepted
// Submission Date: 2018-04-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, S;
    while (cin >> N >> S)
    {
        queue<int> q;
        int n, sum = 0, minimum = 0x3f3f3f3f;
        for (int i = 1; i <= N; i++)
        {
            cin >> n;
            sum += n;
            q.push(n);
            while (sum >= S && !q.empty()) 
            {
                minimum = min(minimum, (int)q.size());
                sum -= q.front();
                q.pop();
            }
        }
        if (minimum == 0x3f3f3f3f) minimum = 0;
        cout << minimum << '\n';
    }

    return 0;
}
