// Hippo Circus
// UVa ID: 13054
// Verdict: Accepted
// Submission Date: 2022-01-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    int N, H, Ta, Td;
    int h[100010];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> N >> H >> Ta >> Td;
        for (int i = 0; i < N; i++) cin >> h[i];
        sort(h, h + N);
        if (Td >= 2 * Ta) cout << N * Ta << '\n';
        else
        {
            int time = 0;
            int left = 0, right = N - 1;
            while (true)
            {
                if (left > right) break;
                if (left == right) { time += Ta; break; }
                if (h[left] + h[right] < H)
                {
                    time += Td;
                    left++;
                    right--;
                }
                else
                {
                    time += Ta;
                    right--;
                }
            }
            cout << time << '\n';
        }
    }
    return 0;
}
