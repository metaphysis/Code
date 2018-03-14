// Laser Sculpture
// UVa ID: 11683
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int A, C;
    
    while (cin >> A, A > 0)
    {
        cin >> C;
        int times = 0;
        int H1, H2;
        cin >> H1;
        times += (A - H1);
        for (int i = 2; i <= C; i++)
        {
            cin >> H2;
            if (H2 < H1) times += (H1 - H2);
            H1 = H2;
        }
        cout << times << '\n';
    }

    return 0;
}
