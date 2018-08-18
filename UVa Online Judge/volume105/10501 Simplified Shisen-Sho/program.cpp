// Simplified Shisen-Sho
// UVa ID: 10501
// Verdict: Accepted
// Submission Date: 2018-08-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, N;
char board[24][24];
int moves[200][2][2];
int offset[4][3] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct package
{
    int i, j, k;
    package (int i = 0, int j = 0, int k = 0): i(i), j(j), k(k) {}
};

bool dfs(int depth)
{
    if (depth == N) return true;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            if (board[i][j] != ' ')
            {
                int arrived[400][2], cntOfArrived = 0;
                int dists[24][24], visited[24][24] = {};
                int nexti, nextj, nextd;

                memset(dists, 0x3f, sizeof(dists));
                dists[i][j] = 0;
                visited[i][j] = 1;

                queue<package> q;
                for (int k = 0; k < 4; k++)
                {
                    nexti = i + offset[k][0], nextj = j + offset[k][1];
                    if (board[nexti][nextj] == ' ')
                    {
                        q.push(package(nexti, nextj, k));
                        dists[nexti][nextj] = 1;
                    }
                }
                
                package p;
                while (!q.empty())
                {
                    p = q.front(); q.pop();
                    for (int k = 0; k < 4; k++)
                    {
                        nexti = p.i + offset[k][0];
                        nextj = p.j + offset[k][1];
                        if (!(nexti >= 0 && nexti <= (m + 1) && nextj >= 0 && nextj <= (n + 1))) continue;
                        
                        nextd = dists[p.i][p.j] + (k != p.k);
                        if (nextd >= 4) continue;

                        if (board[nexti][nextj] != ' ')
                        {
                            if (!visited[nexti][nextj] && board[nexti][nextj] == board[i][j])
                            {
                                arrived[cntOfArrived][0] = nexti;
                                arrived[cntOfArrived][1] = nextj;
                                visited[nexti][nextj] = 1;
                                cntOfArrived++;
                            }
                            continue;
                        }
                        if (dists[nexti][nextj] <= nextd) continue;

                        q.push(package(nexti, nextj, k));
                        dists[nexti][nextj] = nextd;
                    }
                }
                
                if (cntOfArrived)
                {
                    for (int k = 0; k < cntOfArrived; k++)
                    {
                        char backup = board[i][j];
                        board[i][j] = board[arrived[k][0]][arrived[k][1]] = ' ';
                        moves[depth][0][0] = j;
                        moves[depth][0][1] = i;
                        moves[depth][1][0] = arrived[k][1];
                        moves[depth][1][1] = arrived[k][0];
                        if (dfs(depth + 1)) return true;
                        board[i][j] = board[arrived[k][0]][arrived[k][1]] = backup;
                    }
                }
            }
        }
        return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        memset(board, ' ', sizeof(board));

        map<char, int> counter;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> board[i][j];
                counter[board[i][j]]++;
            }

        N = n * m;
        if (N % 2 == 1)
        {
            cout << "No solution\n";
            continue;
        }
        N /= 2;
        
        bool flag = true;
        for (auto p : counter)
            if (p.second % 2 == 1)
            {
                flag = false;
                break;
            }
        if (!flag)
        {
            cout << "No solution\n";
            continue;
        }

        if (dfs(0))
        {
            for (int i = 0; i < N; i++)
            {
                cout << '(';
                cout << moves[i][0][0] << ',' << moves[i][0][1];
                cout << "),(";
                cout << moves[i][1][0] << ',' << moves[i][1][1];
                cout << ")\n";
            }
        }
        else cout << "No Solution.\n";
    }

    return 0;
}
