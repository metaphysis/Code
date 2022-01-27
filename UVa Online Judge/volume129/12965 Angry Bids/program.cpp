// Angry Bids
// UVa ID: 12965
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.040s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    int P, C, PC, p[10010], c[10010], pc[20010];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> P >> C;
        PC = 0;
        for (int i = 0; i < P; i++) { cin >> p[i]; pc[PC++] = p[i]; }
        for (int i = 0; i < C; i++) { cin >> c[i]; pc[PC++] = c[i]; }
        sort(p, p + P);
        sort(c, c + C);
        pc[PC++] = 0;
        pc[PC++] = max(p[P - 1], c[C - 1]) + 1;
        sort(pc, pc + PC);
        int angryPeople = 0x3f3f3f3f, bestPrice = 0x3f3f3f3f;
        int cnt, k;
        for (int i = 0; i < PC; i++)
        {
            cnt = 0;
            k = upper_bound(p, p + P, pc[i]) - p;
            cnt += P - k;
            k = upper_bound(c, c + C, pc[i] - 1) - c;
            cnt += k;
            if (cnt < angryPeople) bestPrice = pc[i], angryPeople = cnt;
        }
        cout << bestPrice << ' ' << angryPeople << '\n';
    }
    return 0;
}
