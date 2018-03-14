// Sort! Sort!! And Sort!!!
// UVa ID: 11321
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, M, numbers[10010];

bool cmp(const int &a, const int &b)
{
    int m1 = a % M, m2 = b % M;
    if (m1 != m2) return m1 < m2;
    int aa = abs(a), bb = abs(b);
    if ((aa & 1) && (bb & 1)) return a > b;
    if (!(aa & 1) && !(bb & 1)) return a < b;
    return aa & 1 ? true : false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> N >> M, N > 0)
    {
        for (int i = 0; i < N; i++) cin >> numbers[i];
        sort(numbers, numbers + N, cmp);
        cout << N << ' ' << M << '\n';
        for (int i = 0; i < N; i++)
            cout << numbers[i] << '\n';
    }

    cout << "0 0\n";

    return 0;
}
