// Adventures in Moving: Part IV （搬家大冒险：第四部）
// PC/UVa IDs: 111108/10201, Popularity: A, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-19
// UVa Run Time: 0.024s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 2020-04-21 再次提交，发现无法通过当前数据，应该是测试数据发生了变化，故修改了代码。
// 即可能有这样的测试数据：终点位于两个加油站中间而不是位于加油站上。
//
// [解题方法]
// 令到达第 i 个加油站时，剩余油量为 j 升时的最小花费为 cost[i][j]，d[m][i] 为第 m 个加油站
// 和第 i 个加油站之间的距离，p[i] 为第 i 个加油站加 1 升油的费用，则有以下状态转移方程：
//
// cost[i][j] = min{cost[m][n] + ((n - d[m][i] >= j) ? 0 : (d[m][i] + j - n) * 
// p[i] | d[m][i] <= n, 1<= m < i}
//
// 顺便给出一组测试数据和 AC 程序得到的结果：
// 10
//
// 500
// 100 1
// 300 1
// 350 1
// 501 10
//
// 101
// 100 100
// 102 1
//
// 100
//
// 101
//
// 200
// 100 10
//
// 201
// 100 10
//
// 201
// 101 10
//
// 50
// 25 10
//
// 150
// 100 10
// 151 20
//
// 150
// 100 10
// 151 20
// 152 1
//
// AC 程序给出的结果：
// 950
//
// 299
//
// Impossible
//
// Impossible
//
// 2000
//
// Impossible
//
// Impossible
//
// 500
//
// 1500
//
// 618
//
// 注意第一组数据，UVa 中的测试数据应该没有包含这样的数据，在到达 501 公里时，没有再退回到 500
// 公里处。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 110                // 最大加油站数量。
#define MAXL 201                // 最大剩余油量的升数。
#define MAXINT (1 << 30)

int kilometers[MAXN];           // 加油站距离起点的距离（单位：公里）。
int price[MAXN];                // 加油站每加 1 升油的费用（单位：10 美分）。
int cost[MAXN][MAXL];           // 在加油站 i 拥有剩余油量 j 时的最小花费。
int nstations;                  // 加油站总个数。

// 动态规划求花费的最小费用。
int dp(int end)
{
    // 初始时，置全部费用为最大值。
    for (int i = 0; i < nstations; i++)
        for (int j = 0; j < MAXL; j++)
            cost[i][j] = MAXINT;

    // 第 0 个加油站剩余油量为 100 升时，总费用为 0。
    cost[0][100] = 0;
    for (int i = 0; i < nstations - 1; i++)
        for (int j = 0; j < MAXL; j++)
            if (cost[i][j] < MAXINT)
            {
                // 计算从加油站 i，剩余油量为 j 升时到达下一个加油站 next 时剩余油量为 k 升时的最小费用。
                int next = i + 1;
                while ((kilometers[next] - kilometers[i]) <= j && next < nstations)
                {
                    // 计算剩余油量。若剩余油量大于等于 k 升，则不需加油，否则需要加油。
                    int remain = j - (kilometers[next] - kilometers[i]);
                    for (int k = 0; k <= remain; k++)
                        cost[next][k] = min(cost[i][j], cost[next][k]);
                    for (int k = remain + 1; k < MAXL; k++)
                        cost[next][k] = min(cost[i][j] + (k - remain) * price[next], cost[next][k]);
                    next++;
                }
            }

    int minCost = MAXINT;
    for (int i = 0; i < nstations; i++)
        for (int j = 0; j < MAXL; j++)
            if (cost[i][j] < MAXINT)
                if (kilometers[i] <= end && j >= (100 + end - kilometers[i]))
                    minCost = min(minCost, cost[i][j]);
    return minCost;
}

int main(int ac, char *av[])
{
    int cases, end;
    bool printStupidEmptyLine = false;
    string line;

    // 读入测例数。
    cin >> cases;
    cin.ignore();
    getline(cin, line);

    while (cases--)
    {
        // 读入终点和起点间的距离。
        cin >> end;
        cin.ignore(256, '\n');

        // 设置起点为一个虚拟加油站，加油价格为 0，因为不会在此虚拟加油站加油。
        nstations = 0;
        kilometers[nstations] = 0;
        price[nstations] = 0;
        nstations++;

        // 读取实际的加油站距离和价格。
        while (getline(cin, line), line.length())
        {
            istringstream iss(line);
            iss >> kilometers[nstations] >> price[nstations];
            nstations++;
        }

        // 输出空行。
        if (printStupidEmptyLine)
            cout << endl;
        else
            printStupidEmptyLine = true;

        // 判断是否可达，若可达则计算最小花费。
        int r = dp(end);
        if (r == MAXINT)
            cout << "Impossible" << endl;
        else
            cout << r << endl;
    }

    return 0;
}
