#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 1010;
int stk[MAXV], top, connected[MAXV][MAXV];
int numberOfVertices, numberOfEdges;

void dfs(int x)
{
    stk[top++] = x;
    for (int i = 1; i <= numberOfVertices; i++) {
        if (connected[x][i]) {
            connected[x][i] = connected[i][x] = 0;
            dfs(i);
            break;
        }
    }
}

void fleury(int start)
{
    top = 0, stk[top++] = start;

    while (top > 0) {
        int brige = 1;
        for (int i = 1; i <= numberOfVertices; ++i)
            if (connected[stk[top - 1]][i]) {
                brige = 0;
                break;
            }

        if (brige) cout << stk[--top] << ' ';
        else dfs(stk[--top]);
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    while (cin >> numberOfVertices >> numberOfEdges) {
        memset(connected, 0, sizeof (connected));

        int x, y;
        for (int i = 0; i < numberOfEdges; i++) {
            cin >> x >> y;
            connected[x][y] = connected[y][x] = 1;
        }

        int start = 1, numberOfOddDegree = 0;
        for (int i = 1; i <= numberOfVertices; i++) {
            int degree = 0;
            for (int j = 1; j <= numberOfVertices; j++)
                degree += connected[i][j];
            if (degree % 2 == 1) start = i, numberOfOddDegree++;
        }

        if (numberOfOddDegree == 0 || numberOfOddDegree == 2) fleury(start);
        else cout << "No Euler path.\n";
    }

    return 0;
}
