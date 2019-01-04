#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int stk[MAXV], top, connected[MAXV][MAXV];
int cntOfVertices, cntOfEdges;

void dfs(int x)
{
    stk[top++] = x;
    for (int i = 0; i < cntOfVertices; i++) {
        if (connected[x][i]) {
            connected[x][i] = connected[i][x] = 0;
            dfs(i);
            break;
        }
    }
}

void hierholzer(int u)
{
    top = 0, stk[top++] = u;

    while (top > 0) {
        int going = 1;
        for (int i = 0; i < cntOfVertices; ++i)
            if (connected[stk[top - 1]][i]) {
                going = 0;
                break;
            }

        if (going) cout << stk[--top] << ' ';
        else dfs(stk[--top]);
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    while (cin >> cntOfVertices >> cntOfEdges) {
        memset(connected, 0, sizeof (connected));

        int x, y;
        for (int i = 0; i < cntOfEdges; i++) {
            cin >> x >> y;
            x--, y--;
            connected[x][y] = connected[y][x] = 1;
        }

        int u = 0, cntOfOddDegree = 0;
        for (int i = 0; i < cntOfVertices; i++) {
            int degree = 0;
            for (int j = 0; j < cntOfVertices; j++) degree += connected[i][j];
            if (degree % 2 == 1) u = i, cntOfOddDegree++;
        }

        if (cntOfOddDegree == 0 || cntOfOddDegree == 2) hierholzer(u);
        else cout << "No Euler path.\n";
    }

    return 0;
}
