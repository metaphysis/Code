// Railroads （铁路）
// PC/UVa IDs: 111004/10039, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-05
// UVa Run Time: 0.392s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [Problem Description]
// Tomorrow morning Jill must travel from Hamburg to Darmstadt to compete in the
// regional programming contest. Since she is afraid of arriving late and being
// excluded from the contest, she is looking for the train which gets her to
// Darmstadt as early as possible. However, she dislikes getting to the station
// too early, so if there are several schedules with the same arrival time then
// she will choose the one with the latest departure time.
//
// Jill asks you to help her with her problem. You are given a set of railroad
// schedules from which you must compute the train with the earliest arrival time
// and the fastest connection from one location to another. Fortunately, Jill is
// very experienced in changing trains and can do this instantaneously, i.e., in
// zero time!
// 
// [Input]
// The very first line of the input gives the number of scenarios. Each scenario
// consists of three parts. The first part lists the names of all cities connected
// by the railroads. It starts with a number 1 < C <= 100, followed by C lines
// containing city names. All names consist only of letters.
//
// The second part describes all the trains running during a day. It starts with
// a number T <= 1,000 followed by T train descriptions. Each of them consists
// of one line with a number ti <= 100 and then ti more lines, each with a time
// and a city name, meaning that passengers can get on or off the train at that
// time at that city.
//
// The final part consists of three lines: the first containing the earliest
// possible starting time, the second the name of the city where she starts, and
// the third with the destination city. The start and destination cities are always
// different.
//
// [Output]
// For each scenario print a line containing ``Scenario i'', where i is the
// scenario number starting from 1.
//
// If a connection exists, print the two lines containing zero padded timestamps
// and locations as shown in the example. Use blanks to achieve the indentation.
// If no connection exists on the same day (i.e., arrival before midnight), print
// a line containing ``No connection''.
//
// Print a blank line after each scenario.
//
// [Sample Input]
// 2
// 3
// Hamburg
// Frankfurt
// Darmstadt
// 3
// 2
// 0949 Hamburg
// 1006 Frankfurt
// 2
// 1325 Hamburg
// 1550 Darmstadt
// 2
// 1205 Frankfurt
// 1411 Darmstadt
// 0800
// Hamburg
// Darmstadt
// 2
// Paris
// Tokyo
// 1
// 2
// 0100 Paris
// 2300 Tokyo
// 0800
// Paris
// Tokyo
//
// [Sample Output]
// Scenario 1
// Departure 0949 Hamburg
// Arrival   1411 Darmstadt
//
// Scenario 2
// No connection
//
// [解题方法]
// 题意需要求最早到达的最晚出发路线，从题目所给条件可以建模成有向图，然后从给定城市
// 寻找到目标城市的所有通路，这个可以通过宽度优先遍历来获得，与 UVa 10187 From Dusk
// till Dawn 类似，然后再比较出发时间和到达时间，得到正确答案，当数据量较少时，可以
// 很快得到正确结果，但是当火车列数和城市数较多时，则因大量计算无法 AC，故用动态规划
// 来加速。设立一个二维数组，表示到达时间为 T ，到达城市为C 时的最早出发时间，根据每
// 个城市的路线情况来更新这个二维数组的值，最后从中间寻找是否有通路，若有通路，则找出
// 其最晚出发时间。

#include <bits/stdc++.h>

using namespace std;

#define MAXV 100
#define MAXTIME 2400
#define NO_CONNECTION (-1)

struct edge
{
	int departure;
	int arrival;
	int to;

	bool operator<(const edge &e) const
	{
		return departure < e.departure;
	}
};

vector < edge > edges[MAXV];

// 缓存：到达时间为 T，到达城市为 C 的最晚出发时间。
int cache[MAXTIME][MAXV];

// DP 搜索。
void search(int tdeparture, int from, int to, string cstart, string cdestination)
{
	edge e;

	// 初始化缓存。
	for (int i = 0; i < MAXTIME; i++)
		for (int j = 0; j < MAXV; j++)
			cache[i][j] = NO_CONNECTION;

	// 排序，将出发时间早的排在前面，可以减少一些后续比较时的运行时间，可根据情况选用。
	for (int i = 0; i < MAXV; i++)
		sort(edges[i].begin(), edges[i].end());

	// 设定初始条件。
	for (int i = 0; i < edges[from].size(); i++)
	{
		e = edges[from][i];
		if (e.departure < tdeparture)
			continue;

		// 更新缓存信息。
		cache[e.arrival][e.to] = max(cache[e.arrival][e.to], e.departure);
	}

	// 动态规划。
	for (int i = 0; i < MAXTIME; i++)
		for (int j = 0; j < MAXV; j++)
		{
			// 若为 NO_CONNECTION，不需处理。
			if (cache[i][j] == NO_CONNECTION)
				continue;
			
			for (int k = edges[j].size() - 1; k >= 0; k--)
			{
				// 如果当前时间晚于此城市所有路线的最晚出发时间，则不可能在
				// 当天再乘坐火车前往其他城市。
				if (i > edges[j][k].departure)
					break;

				// 路线到达下一城市的时间。
				int arrival = edges[j][k].arrival;
				// 路线到达的下一城市。
				int next = edges[j][k].to;

				// 更新到达时间为 arrival，到达城市为 next 时的最晚出发时间。
				cache[arrival][next] =
					max(cache[arrival][next], cache[i][j]);
			}
		}

	// 查找是否存在路线。
	for (int i = 0; i < MAXTIME; i++)
		if (cache[i][to] != NO_CONNECTION)
		{
			cout << "Departure " << setw(4) << setfill('0');
			cout << cache[i][to] << " " << cstart << endl;
			cout << "Arrival   " << setw(4) << setfill('0');
			cout << i << " " << cdestination << endl;

			return;
		}

	cout << "No connection" << endl;
}

int main(int ac, char *av[])
{
	int output = 1, cases, ncities, routes, nstations;
	string city;
	int tprevious, tcurrent, tdeparture;
	string cprevious, ccurrent, cstart, cdestination;

	cin >> cases;
	while (cases--)
	{
		// 读入城市名。
		map < string, int > cities;

		cin >> ncities;
		for (int c = 0; c < ncities; c++)
		{
			cin >> city;
			cities[city] = c;
			edges[c].clear();
		}

		// 建有向图。
		cin >> routes;
		for (int c = 1; c <= routes; c++)
		{
			cin >> nstations;
			for (int m = 1; m <= nstations; m++)
			{
				cin >> tcurrent >> ccurrent;

				if (m > 1)
					edges[cities[cprevious]].push_back(
					(edge){tprevious, tcurrent, cities[ccurrent]});

				tprevious = tcurrent;
				cprevious = ccurrent;
			}
		}

		cout << "Scenario " << output++ << endl;

		// 读入出发时间，出发城市和终点城市。
		cin >> tdeparture >> cstart >> cdestination;
		// 使用动态规划找到从出发城市到终点城市最晚出发最早到达时间。
		search(tdeparture, cities[cstart], cities[cdestination],
							cstart, cdestination);
		cout << endl;
	}

	return 0;
}
