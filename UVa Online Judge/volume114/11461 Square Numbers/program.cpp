// Square Numbers
// UVa ID: 11461
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> square;
    for (int i = 1; i < 340; i++) square.push_back(i * i);
    int a, b;
    while (cin >> a >> b, a > 0)
    {
        int cnt = 0;
        for (auto s : square)
            if (a <= s && s <= b)
                cnt++;
        cout << cnt << '\n';
    }
    return 0;
}
