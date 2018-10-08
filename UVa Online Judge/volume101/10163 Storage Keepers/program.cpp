// Storage Keepers
// UVa ID: 10163
// Verdict: Accepted
// Submission Date: 2018-10-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

int N, M, Pi[32];

bool doable(int L)
{
    if (L == 0) return true;
    int cnt = 0;
    for (int i = 0; i < M; i++)
        cnt += Pi[i] / L;
    return cnt >= N;
}

int binarySearch()
{
    sort(Pi, Pi + M, greater<int>());
    int low = 0, high = Pi[0], middle;
    while (low <= high)
    {
        middle = (low + high) >> 1;
        if (doable(middle)) low = middle + 1;
        else high = middle - 1;
    }
    if (!doable(low)) low--;
    return low;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> N >> M)
    {
        if (N == 0) break;
        for (int i = 0; i < M; i++)
            cin >> Pi[i];
        
        int L = binarySearch();
        if (L == 0)
        {
            cout << "0 0\n";
            continue;
        }
        
        int T = 0;
        for (int i = 0; i < M; i++) T += Pi[i] / L;
        int money[T + 1] = {};
        memset(money, INF, (T + 1) * sizeof(int));
        money[0] = 0;
        for (int i = 1; i <= M; i++)
        {
            if (Pi[i - 1] < L) continue;
            for (int j = T; j >= Pi[i - 1] / L; j--)
            {
                if (money[j - Pi[i - 1] / L] != INF)
                    money[j] = min(money[j], money[j - Pi[i - 1] / L] + Pi[i - 1]);
            }
        }
        cout << L << ' ';
        for (int i = N; i <= T; i++)
            if (money[i] != INF)
            {
                cout << money[i];
                break;
            }
        cout << '\n';
    }

    return 0;
}
