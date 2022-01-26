// Medals
// UVa ID: 10997
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, score[210];
    while (cin >> n, n)
    {
        int canadaIdx = -1, total = 0;
        vector<int> m;
        string name;
        for (int i = 0, x, y, z; i < n; i++)
        {
            cin >> name;
            cin >> x >> y >> z;
            m.push_back(x * 10000 + y * 100 + z);
            total += x + y + z;
            if (name == "Canada") canadaIdx = i;
        }
        if (canadaIdx == -1)
        {
            cout << "Canada cannot win.\n";
            continue;
        }
        swap(m[0], m[canadaIdx]);
        int weight[3] = {1, total, total * total};
        bool wins = 0;
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int k = 0; k <= 2; k++)
                {
                    for (int u = 0; u < n; u++)
                    {
                        int x = m[u] / 10000, y = m[u] / 100 % 100, z = m[u] % 100;
                        score[u] = x * weight[i] + y * weight[j] + z * weight[k];
                    }
                    if (score[0] == *max_element(score, score + n)) wins = 1;
                }
        if (wins) cout << "Canada wins!\n";
        else cout << "Canada cannot win.\n";   
    }
    return 0;
}
