#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

int visited[52], edges[52][52];

void dfs(int u)
{
    visited[u] = 1;
    for (int v = 0; v < 52; v++)
        if (edges[u][v] && !visited[v])
            dfs(v);
}

char getChar(int x)
{
    if (x <= 25) return (char)('a' + x);
    else return (char)('A' + x - 26);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int n = 0;
    while (true)
    {
        int u = rand() % 52, v = rand() % 52;
        if (u == v) continue;
        if (edges[u][v]) continue;
        edges[u][v] = 1;
        if (++n == 20) break;
    }

    for (int i = 0; i < 52; i++)
        for (int j = 0; j < 52; j++)
            if (edges[i][j])
            {
                memset(visited, 0, sizeof(visited));
                dfs(i);
                for (int k = 0; k < 52; k++)
                    if (visited[k] && k != i && k != j)
                    {
                        cout << n << '\n';
                        for (int x = 0; x < 52; x++)
                            for (int y = 0; y < 52; y++)
                                if (edges[x][y])
                                    cout << getChar(x) << ' ' << getChar(y) << '\n';
                        cout << (rand() % 1000 + 1) << ' ' << getChar(i) << ' ' << getChar(k) << '\n';
                    }
            }
    cout << "-1\n";

    return 0;
}
