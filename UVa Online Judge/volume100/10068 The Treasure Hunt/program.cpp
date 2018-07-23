// The Treasure Hunt
// UVa ID: 10068
// Verdict: Accepted
// Submission Date: 2018-07-23
// UVa Run Time: 0.120s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char maze[32][32];
int R, C;
int bestEnergy, bestPath[512], path[512], used[16];
int moveEnergy, lootEnergy[16], carryEnergy[16];
int treasureR[16], treasureC[16];
int treasureIdx[512], treasureCnt = 0;
string bestMove[16][16];

void dfs(int depth, int energySpend, int carryEnergySum)
{
    if (energySpend >= bestEnergy) return;
    if (depth == treasureCnt - 1)
    {
        if (bestMove[path[depth - 1]][treasureCnt - 1].length() > 0)
        {
            int steps = bestMove[path[depth - 1]][treasureCnt - 1].length();
            energySpend += steps * (moveEnergy + carryEnergySum);
            if (energySpend < bestEnergy)
            {
                bestEnergy = energySpend;
                path[depth] = treasureCnt - 1;
                copy(path, path + 512, bestPath);
            }
        }
        return;
    }
    for (int i = 1; i <= treasureCnt - 2; i++)
    {
        if (used[i]) continue;
        if (bestMove[path[depth - 1]][i].length() == 0) continue;
        used[i] = 1, path[depth] = i;
        int steps = bestMove[path[depth - 1]][i].length();
        int nextEnergySpend = energySpend + steps * (moveEnergy + carryEnergySum) + lootEnergy[i];
        int nextCarryEnergySum = carryEnergySum + carryEnergy[i];
        dfs(depth + 1, nextEnergySpend, nextCarryEnergySum);
        used[i] = 0;
    }
}

string dir = "NESW";
int visited[32][32];
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct package
{
    int r, c;
    string move;
    package (int r = 0, int c = 0, string move = ""): r(r), c(c), move(move) {}
} pack;

void bfs()
{
    for (int i = 0; i < treasureCnt; i++)
        for (int j = 0; j < treasureCnt; j++)
            bestMove[i][j].clear();
            
    for (int t = 0; t < treasureCnt; t++)
    {
        int sr = treasureR[t], sc = treasureC[t];
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                visited[i][j] = 0;

        queue<package> q;
        q.push(package(sr, sc, ""));
        visited[sr][sc] = 1;
        while (!q.empty())
        {
            pack = q.front(); q.pop();
            for (int k = 0; k < 4; k++)
            {
                int nextr = pack.r + offset[k][0], nextc = pack.c + offset[k][1];
                if (nextr < 0 || nextr >= R || nextc < 0 || nextc >= C) continue;
                if (visited[nextr][nextc]) continue;
                if (maze[nextr][nextc] == '#') continue;
                if (maze[nextr][nextc] == '*' || maze[nextr][nextc] == 'T')
                {
                    bestMove[t][treasureIdx[nextr * C + nextc]] = pack.move + dir[k];
                }
                visited[nextr][nextc] = 1;
                q.push(package(nextr, nextc, pack.move + dir[k]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int startr, startc, endr, endc;

    while (cin >> R >> C)
    {
        if (R == 0) break;

        treasureCnt = 1;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
            {
                cin >> maze[i][j];
                if (maze[i][j] == '*')
                {
                    treasureIdx[i * C + j] = treasureCnt;
                    treasureR[treasureCnt] = i;
                    treasureC[treasureCnt] = j;
                    treasureCnt++;
                }
                else if (maze[i][j] == 'S')
                {
                    startr = i;
                    startc = j;              
                }
                else if (maze[i][j] == 'T')
                {
                    endr = i;
                    endc = j;
                }
            }

        // S
        treasureR[0] = startr, treasureC[0] = startc;
        treasureIdx[startr * C + startc] = 0;

        // T
        treasureR[treasureCnt] = endr, treasureC[treasureCnt] = endc;
        treasureIdx[endr * C + endc] = treasureCnt;
        treasureCnt++;

        cin >> moveEnergy;
        lootEnergy[0] = carryEnergy[0] = 0;
        for (int t = 1; t <= treasureCnt - 2; t++)
            cin >> lootEnergy[t] >> carryEnergy[t];

        bfs();

        bestEnergy = 0x3f3f3f3f;
        memset(used, 0, sizeof(used));
        path[0] = 0;
        dfs(1, 0, 0);

        cout << "Hunt #" << ++cases << '\n';
        if (bestEnergy == 0x3f3f3f3f)
            cout << "The hunt is impossible.\n";
        else
        {
            cout << "Minimum energy required = " << bestEnergy << " cal\n";
            for (int i = 0; i <= treasureCnt - 2; i++)
            {
                cout << bestMove[bestPath[i]][bestPath[i + 1]];
                if (i <= treasureCnt - 3)
                    cout << 'P';
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
