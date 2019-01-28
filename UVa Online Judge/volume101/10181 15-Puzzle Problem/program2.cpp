// 15-Puzzle Problem
// UVa ID: 10181
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 0.150s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct config
{
    int hn, dir, r, c;
    bool operator<(const config &cfg) const { return hn < cfg.hn; }
};

string directions = "URLD";
int offset[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
int puzzle[5][5], Hn[16][5][5] = {}, dHn[16][5][5][5][5] = {};
int done, depthLimit, path[64];

void dfs(int hn, int gn, int dir, int missingr, int missingc)
{
    if (hn + gn > depthLimit) return;
    // 当布局的熵降低为零时，表明布局已经为目标状态。
    if (hn == 0) {
        done = 1;
        for (int i = 0; i < gn; i++) cout << directions[path[i]];
        cout << '\n';
        return;
    }

    // 确定从当前布局能够得到的后续布局。
    int cnt = 0;
    config next[4];
    for (int k = 0; k < 4; k++) {
        if (k == dir) continue;
        int rr = missingr + offset[k][0], cc = missingc + offset[k][1];
        if (rr < 1 || rr > 4 || cc < 1 || cc > 4) continue;
        // 更新布局的熵。
        next[cnt].hn = hn +
            dHn[puzzle[rr][cc]][rr][cc][missingr][missingc];
        next[cnt].dir = k, next[cnt].r = rr, next[cnt].c = cc;
        cnt++;
    }

    // 对具有较低熵的布局优先搜索。
    sort(next, next + cnt);
    for (int k = 0; k < cnt; k++) {
        swap(puzzle[missingr][missingc], puzzle[next[k].r][next[k].c]);
        // 记录移动。
        path[gn] = next[k].dir;
        dfs(next[k].hn, gn + 1, 3 - next[k].dir, next[k].r, next[k].c);
        if (done) return;
        swap(puzzle[missingr][missingc], puzzle[next[k].r][next[k].c]);
    }
}

void IDAStar(int missingr, int missingc)
{
    // 通过累加每个非空滑块的熵来确定给定布局的熵。
    int hn = 0;
    for (int r = 1; r <= 4; r++)
        for (int c = 1; c <= 4; c++)
            if (puzzle[r][c])
                hn += Hn[puzzle[r][c]][r][c];

    // 每当搜索不成功时，搜索的限制深度递增1。
    depthLimit = 0;
    while (true) {
        done = 0;
        dfs(hn, 0, -1, missingr, missingc);
        if (done) break;
        depthLimit++;
    }
}

// 判断给定的布局是否可解。
bool solvable(vector<int> tiles)
{
    int sum = 0;
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i] == 0) sum += (i / 4 + 1);
        else {
            for (int j = i + 1; j < tiles.size(); j++)
                if (tiles[j] && tiles[j] < tiles[i])
                    sum++;
        }
    }
    return (sum % 2 == 0);
}

int main(int argc, char *argv[])
{
    // 预先计算正确位置为[r1, c1]的滑块移动到位置[r2, c2]时熵的改变。
    for (int r1 = 1; r1 <= 4; r1++)
        for (int c1 = 1; c1 <= 4; c1++)
            for (int r2 = 1; r2 <= 4; r2++)
                for (int c2 = 1; c2 <= 4; c2++)
                    Hn[(r1 - 1) * 4 + c1][r2][c2] = abs(r1 - r2) + abs(c1 - c2);

    // 预先计算编号为i的滑块从位置[r1, c1]移动到位置[r2, c2]时熵的变化。
    for (int i = 1; i <= 15; i++)
        for (int r1 = 1; r1 <= 4; r1++)
            for (int c1 = 1; c1 <= 4; c1++)
                for (int r2 = 1; r2 <= 4; r2++)
                    for (int c2 = 1; c2 <= 4; c2++)
                        dHn[i][r1][c1][r2][c2] = Hn[i][r2][c2] - Hn[i][r1][c1];

    int cases = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        vector<int> tiles;
        // missingr和missingc表示空滑块所在的行和列。
        int missingr, missingc;
        for (int r = 1; r <= 4; r++)
            for (int c = 1; c <= 4; c++)
            {
                cin >> puzzle[r][c];
                tiles.push_back(puzzle[r][c]);
                if (puzzle[r][c] == 0) missingr = r, missingc = c;
            }
        // 若布局可解，则进行IDA*搜索。
        if (solvable(tiles)) IDAStar(missingr, missingc);
        else cout << "This puzzle is not solvable.\n";
    }

    return 0;
}
