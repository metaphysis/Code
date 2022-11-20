// Keep the Customer Satisfied
// UVa ID: 1153
// Verdict: Accepted
// Submission Date: 2022-10-20
// UVa Run Time: 0.170s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 800010;

struct order { int q, d; } o[MAXN];

bool cmp(order a, order b)
{
    if (a.d != b.d) return a.d < b.d;
    return a.q < b.q;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases; cin >> cases;
    while (cases--)
    {
        int n; cin >> n;
        for (int i = 0; i < n; i++) cin >> o[i].q >> o[i].d;
        sort(o, o + n, cmp);
        int tons = 0;
        priority_queue<int> pq;
        for (int i = 0; i < n; i++)
        {
            if (tons + o[i].q <= o[i].d)
            {
                tons += o[i].q;
                pq.push(o[i].q);
            }
            else
            {
                if (!pq.empty())
                {
                    if (o[i].q < pq.top() && tons - pq.top() + o[i].q <= o[i].d)
                    {
                        tons = tons - pq.top() + o[i].q;
                        pq.pop(); pq.push(o[i].q);
                    }
                }
            }
        }
        cout << pq.size() << '\n';
        if (cases) cout << '\n';
    }
    return 0;
}
