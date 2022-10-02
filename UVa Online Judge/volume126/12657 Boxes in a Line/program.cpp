// Boxes in a Line
// UVa ID: 12657
// Verdict: Accepted
// Submission Date: 2022-10-01
// UVa Run Time: 0.060s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100100;

int pre[MAXN], nxt[MAXN];

void moveLeft(int x, int y)
{
    if (pre[y] == x) return;
    nxt[pre[x]] = nxt[x];
    pre[nxt[x]] = pre[x];
    nxt[pre[y]] = x;
    pre[x] = pre[y];
    pre[y] = x;
    nxt[x] = y;
}

void moveRight(int x, int y)
{
    if (nxt[y] == x) return;
    nxt[pre[x]] = nxt[x];
    pre[nxt[x]] = pre[x];
    pre[nxt[y]] = x;
    nxt[x] = nxt[y];
    pre[x] = y;
    nxt[y] = x;
}

void swapIt(int x, int y)
{
    if (pre[x] == y)
    {
        swap(x, y);
        swapIt(x, y);
        return;
    }
    
    if (pre[y] == x)
    {
        nxt[pre[x]] = y;
        pre[nxt[y]] = x;
        pre[y] = pre[x];
        pre[x] = y;
        nxt[x] = nxt[y];
        nxt[y] = x;
    }
    else
    {
        nxt[pre[x]] = y;
        pre[nxt[x]] = y;
        nxt[pre[y]] = x;
        pre[nxt[y]] = x;
        swap(pre[x], pre[y]);
        swap(nxt[x], nxt[y]);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int n, m, cases = 0;
    
    while (cin >> n >> m)
    {
        for (int i = 0; i <= n + 1; i++)
        {
            pre[i] = i - 1;
            nxt[i] = i + 1;
        }

        int command, x, y, reversed = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> command;
            if (command == 4) { reversed = !reversed; continue; }
            cin >> x >> y;
            if (command == 1) reversed ? moveRight(x, y) : moveLeft(x, y);
            if (command == 2) reversed ? moveLeft(x, y) : moveRight(x, y);
            if (command == 3) swapIt(x, y);
        }
        
        long long sum = 0;
        int head = 0;
        if (n % 2 == 0 && reversed) head = nxt[0];
        for (int i = 0; i <= n; i++)
        {
            if (i % 2) sum += head;
            head = nxt[head];
        }
        cout << "Case " << ++cases << ": ";
        cout << sum << '\n';
    }

    return 0;
}
