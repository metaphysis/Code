// Constructing BST
// UVa ID: 10921
// Verdict: Accepted
// Submission Date: 2022-11-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void construct(int height, int from, int to)
{
    if (from == to)
    {
        cout << ' ' << from;
        return;
    }
    int length = 0, n = to - from + 1;
    while ((length + 1) <= height && (length + 1) + (1 << (height - length - 1)) - 1 >= n) length++;
    length = min(length, n);
    if (length)
    {
        for (int i = 0; i < length; i++) cout << ' ' << from + i;
        if (length < n) construct(height - length, from + length, to);
    }
    else
    {
        length = 0;
        while ((length + 1) <= n / 2 && length + (1 << (height - 1)) < n) length++;
        cout << ' ' << from + length;
        construct(height - 1, from, from + length - 1);
        construct(height - 1, from + length + 1, to);
    }
}

int main(int argc, char *argv[])
{
    int N, H, cases = 0;
    while (cin >> N >> H, N)
    {
        cout << "Case " << ++cases << ':';
        if ((1 << H) - 1 < N)
        {
            cout << " Impossible.\n";
            continue;
        }
        construct(H, 1, N);
        cout << '\n';
    }
    return 0;
}
