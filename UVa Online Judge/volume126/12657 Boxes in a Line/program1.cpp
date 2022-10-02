// Boxes in a Line
// UVa ID: 12657
// Verdict: Accepted
// Submission Date: 2022-10-02
// UVa Run Time: 0.060s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100100;

int Left[MAXN], Right[MAXN];

void link(int x, int y)
{
    Right[x] = y, Left[y] = x;
}

void moveLeft(int x, int y)
{
    link(Left[x], Right[x]);
    link(Left[y], x);
    link(x, y);
}

void moveRight(int x, int y)
{
    link(Left[x], Right[x]);
    link(x, Right[y]);
    link(y, x);
}

void swapIt(int x, int y)
{
    if (y == Left[x])
    {
        swap(x, y);
        swapIt(x, y);
        return;
    }

    if (x == Left[y])
    {
        link(Left[x], y);
        link(x, Right[y]);
        link(y, x);
    }
    else
    {
        int Ly = Left[y], Ry = Right[y];
        link(Left[x], y), link(y, Right[x]);
        link(Ly, x), link(x, Ry);
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
            Left[i] = i - 1;
            Right[i] = i + 1;
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
        if (n % 2 == 0 && reversed) head = Right[0];
        for (int i = 0; i <= n; i++)
        {
            if (i % 2) sum += head;
            head = Right[head];
        }
        cout << "Case " << ++cases << ": ";
        cout << sum << '\n';
    }

    return 0;
}
