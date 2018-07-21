#include <cstdio>
#include <cstdlib>
bool flag;
int time, ans, n, a[11][5], dist[41][11][5];
int main()
{
    void search(int, int, int, int, int);
    int s;
    s = 0;
    while (1)
    {
        scanf("%d", &n);
        if (n == 0)
            break;
        n /= 4;
        int x0, y0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= 4; j++)
            {
                scanf("%d", &a[i][j]);
                if (a[i][j] == 1)
                {
                    x0 = i;
                    y0 = j;
                }
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= 4; j++)
                for (int k = 1; k <= n; k++)
                    for (int l = 1; l <= 4; l++)
                    {
                        int x, y;
                        x = abs(i - k);
                        y = abs(j - l);
                        if (y == 3)
                            y = 1;
                        dist[(i - 1) * 4 + j][k][l] = x + y;
                    }
        int sum;
        sum = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= 4; j++)
                if (a[i][j] != 1)
                    sum += dist[a[i][j]][i][j];
        ans = 0;
        flag = false;
        while (1)
        {
            search(x0, y0, sum, 0, -1);
            if (flag)
            {
                s++;
                printf("Set %d:\n", s);
                printf("%d\n", ans);
                break;
            }
            ans++;
        }
    }
    system("pause");
    return (0);
}

void search(int x, int y, int left, int dep, int k)
{
    if (dep + left > ans)
        return;
    if (left == 0)
    {
        flag = true;
        return;
    }
    const int c[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
    int t, q[4][4];
    t = -1;
    for (int i = 0; i < 4; i++)
    {
        if (i == k)
            continue;
        int x0, y0;
        x0 = x + c[i][0];
        y0 = y + c[i][1];
        if (x0 == 0 || x0 == n + 1)
            continue;
        if (y0 == 0)
            y0 = 4;
        if (y0 == 5)
            y0 = 1;
        int p;
        p = a[x0][y0];
        if (dist[p][x][y] <= dist[p][x0][y0])
        {
            a[x][y] = p;
            a[x0][y0] = 1;
            search(x0, y0, left + dist[p][x][y] - dist[p][x0][y0], dep + 1, 3 - i);
            if (flag)
                return;
            a[x][y] = 1;
            a[x0][y0] = p;
        }
        else
        {
            t++;
            q[t][0] = x0;
            q[t][1] = y0;
            q[t][2] = i;
            q[t][3] = dist[p][x][y] - dist[p][x0][y0];
        }
    }
    for (int i = 0; i <= t; i++)
    {
        int x0, y0;
        x0 = q[i][0];
        y0 = q[i][1];
        a[x][y] = a[x0][y0];
        a[x0][y0] = 1;
        search(x0, y0, left + q[i][3], dep + 1, 3 - q[i][2]);
        if (flag)
            return;
        a[x0][y0] = a[x][y];
        a[x][y] = 1;
    }
}
