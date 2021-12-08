// Temperature Monitoring
// UVa ID: 11638
// Verdict: Accepted
// Submission Date: 2021-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int M, S, C, threshold[4], K, alarmed[4];

void record(int temp)
{
    for (int i = 0; i < 4; i++)
        if (C & (1 << i))
        {
            if (alarmed[i]) continue;
            if (C & (1 << (i + 4))) alarmed[i] = temp > threshold[i];
            else alarmed[i] = temp < threshold[i];
        }
}

bool between(int start, int end, bool startIncluded)
{
    //int left = (start - S) / M, right = (end - S) / M;
    //if ((start - S) > 0 && (start - S) % M != 0) left++;
    //if ((end - S) < 0 && (end - S) % M != 0) right--;
    int left = ceil(1.0 * (start - S) / M), right = floor(1.0 * (end - S) / M);
    if (!startIncluded && (start - S) % M == 0) left++;
    return 0 <= right && left <= right;
}

void process()
{
    cin >> M >> S;
    for (int i = 0; i < 4; i++) cin >> threshold[i];
    cin >> C >> K;
    memset(alarmed, 0, sizeof alarmed);
    int time, temp;
    int start = 0, end = 0;
    for (int i = 0; i < K; i++)
    {
        cin >> time >> temp;
        start = end, end += time;
        if (between(start, end, !i)) record(temp);
    }
}

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ":";
        process();
        for (int i = 0; i < 4; i++) cout << ' ' << (alarmed[i] ? "yes" : "no");
        cout << '\n';
    }

    return 0;
}
