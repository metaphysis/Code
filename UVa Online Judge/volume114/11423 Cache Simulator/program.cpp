// Cache Simulator
// UVa ID: 11423
// Verdict: Accepted
// Submission Date: 2022-01-08
// UVa Run Time: 0.560s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 24;

int cache[32], missed[32];
int pos[MAXN], fenwick[MAXN];

struct data
{
    int value, last;
};

inline int lowbit(int x) { return x & (-x); }

void add(int x, int delta)
{
    for (int i = x; i < MAXN; i += lowbit(i))
        fenwick[i] += delta;
}

int get(int x)
{
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))
        sum += fenwick[i];
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> cache[i];
    
    queue<data> q;

    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "END") break;
        if (cmd == "STAT")
        {
            q.push(data{-1, 0});
        }
        if (cmd == "RANGE")
        {
            int b, y, n;
            cin >> b >> y >> n;
            for (int k = 0; k < n; k++)
            {
                int access = b + y * k;
                q.push(data{access, pos[access]});
                pos[access] = q.size();
            }
        }
        if (cmd == "ADDR")
        {
            int x;
            cin >> x;
            q.push(data{x, pos[x]});
            pos[x] = q.size();
        }
    }
    
    int cnt = 1;
    while (!q.empty())
    {
        data dt = q.front(); q.pop();
        if (dt.value >= 0)
        {
            add(cnt, 1);
            if (dt.last)
            {
                int needed = get(cnt) - get(dt.last);
                for (int i = 0; i < N; i++)
                    if (needed > cache[i])
                        missed[i]++;
                    else break;
                add(dt.last,  -1);
            }
            else
            {
                for (int i = 0; i < N; i++)
                    missed[i]++;
            }
        }
        else
        {
            for (int i = 0; i < N; i++)
                cout << missed[i] << (i == N - 1 ? '\n' : ' ');
            memset(missed, 0, sizeof missed);
        }
        cnt++;
    }
    return 0;
}
