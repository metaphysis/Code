// Assemble
// UVa ID: 12124
// Verdict: Accepted
// Submission Date: 2022-01-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        int n, b;
        cin >> n >> b;
        map<string, vector<pair<int, int>>> component;
        string type, name;
        int price, quality;
        int low = 0, high = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> type >> name >> price >> quality;
            component[type].push_back(make_pair(quality, price));
            high = max(high, quality);
        }
        int middle, r;
        while (low <= high)
        {
            int middle = (low + high) >> 1;
            int s = 0;
            for (auto item : component)
            {
                int lowest = 0x3f3f3f3f;
                for (auto p : item.second)
                    if (p.first >= middle)
                        lowest = min(lowest, p.second);
                if (lowest == 0x3f3f3f3f) s = b + 1;
                else s += lowest;
                if (s > b) break;
            }
            if (s <= b)
            {
                r = middle;
                low = middle + 1;
            }
            else high = middle - 1;
        }
        cout << r << '\n';
    }
    return 0;
}
