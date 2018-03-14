// Boxes
// UVa ID: 11003
// Verdict: Accepted
// Submission Date: 2017-11-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct box
{
    int weight, load;
} boxes[1100];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    
    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
            cin >> boxes[i].weight >> boxes[i].load;
            
        vector<int> m;            
        m.push_back(0);
        for (int i = n; i >= 1; i--)
        {
            if (boxes[i].load >= m.back()) m.push_back(m.back() + boxes[i].weight);
            for (int j = m.size() - 2; j >= 0; j--)
                if (boxes[i].load >= m[j] && m[j] + boxes[i].weight < m[j + 1])
                    m[j + 1] = m[j] + boxes[i].weight;
        }
        cout << m.size() - 1 << '\n';
    }

    return 0;
}
