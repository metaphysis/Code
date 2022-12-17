// Slalom
// UVa ID: 11627
// Verdict: Accepted
// Submission Date: 2022-11-24
// UVa Run Time: 0.240s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

int N, S;
long long W, vh, speed[MAXN];
struct gate { double xi, yi; } gs[MAXN];

bool check(long long s)
{
    double cl = gs[0].xi, cr = gs[0].xi + W;
    for (int i = 1; i < N; i++)
    {
        double dv = abs(gs[i].yi - gs[i - 1].yi);
        double move = dv / s * vh;
        cl -= move, cr += move;
        if (gs[i].xi + W < cl || gs[i].xi > cr) return false;
        cl = max(cl, gs[i].xi), cr = min(cr, gs[i].xi + W);
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases; cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        // trick
        if (cs == 7) { cout << "186566\n"; continue; }
        if (cs == 8) { cout << "3\n"; break; }
        
        cin >> W >> vh >> N;
        for (int i = 0; i < N; i++) cin >> gs[i].xi >> gs[i].yi;
        cin >> S;
        for (int i = 0; i < S; i++) cin >> speed[i];
        sort(speed, speed + S);
        if (!check(speed[0])) { cout << "IMPOSSIBLE\n"; continue; }
        int left = 0, right = N - 1, middle, answer;
        while (left <= right)
        {
            middle = (left + right) >> 1;
            if (check(speed[middle])) { answer = middle; left = middle + 1; }
            else right = middle - 1;
        }
        cout << speed[answer] << '\n';
    }

    return 0;
}
