// Grandpa Pepe's Pizza
// UVa ID: 12801
// Verdict: Accepted
// Submission Date: 2022-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int C, N;
int Xi[10010];
int oliveStart, oliveEnd, oliveIdx;

bool check()
{
    int lengthOfSector = C / N;
    for (int i = oliveStart + 1; i < oliveEnd; i += 2)
    {
        bool valid = true;
        for (int j = 0; j < N && valid; j++)
        {
            int sectorStart = i + j * lengthOfSector;
            int sectorEnd = i + (j + 1) * lengthOfSector;
            int positionOfOlive = Xi[(oliveIdx + j) % N];
            if (sectorStart < positionOfOlive && positionOfOlive < sectorEnd) continue;
            positionOfOlive += C;
            if (sectorStart < positionOfOlive && positionOfOlive < sectorEnd) continue;
            valid = false;
        }
        if (valid) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> C >> N)
    {
        int lastXi = -1, gap = 0x3f3f3f3f;
        for (int i = 0; i < N; i++)
        {
            cin >> Xi[i];
            Xi[i] *= 2;
            if (lastXi != -1)
            {
                if (gap > Xi[i] - lastXi)
                {
                    oliveStart = lastXi;
                    oliveEnd = Xi[i];
                    oliveIdx = i;
                    gap = Xi[i] - lastXi;
                }
            }
            lastXi = Xi[i];
        }
        C *= 2;
        cout << (check() ? 'S' : 'N') << '\n';
    }
    return 0;
}
