// From Dusk till Dawn （从黄昏到拂晓）
// PC/UVa IDs: 110907/10187, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-02
// UVa Run Time: 0.048s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// Vladimir has white skin, very long teeth and is 600 years old, but this is no
// problem because Vladimir is a vampire.
// Vladimir has never had any problems with being a vampire. In fact, he is a very
// successful doctor who always takes the night shift and so has made many friends
// among his colleagues. He has a very impressive trick which he shows at dinner
// partys: He can tell tell blood group by taste.
// Vladimir loves to travel, but being a vampire he has to overcome three problems.
//
// First, he can only travel by train because he has to take his coffin with him.
// (On the up side he can always travel first class because he has invested a lot
// of money in long term stocks.)
// Second, he can only travel from dusk till dawn, namely from 6 pm to 6 am. During
// the day he has to stay inside a train station.
// Third, he has to take something to eat with him. He needs one litre of blood
// per day, which he drinks at noon (12:00) inside his coffin. 
//
// You should help Vladimir to find the shortest route between two given cities,
// so that he can travel with the minimum amount of blood. (If he takes too much
// with him, people will ask funny questions like "What do you do with all that
// blood?")
//
// [输入]
// The first line of the input will contain a single number telling you the number
// of test cases.
// Each test case specification begins with a single number telling you how many
// route specifications follow.
// Each route specification consists of the names of two cities, the departure
// time from city one and the total travelling time. The times are in hours. Note
// that Vladimir can't use routes departing earlier than 18:00 or arriving later
// than 6:00.
// There will be at most 100 cities and less than 1000 connections. No route takes
// less than one hour and more than 24 hours. (Note that Vladimir can use only
// routes with a maximum of 12 hours travel time (from dusk till dawn).) All city
// names are shorter than 32 characters.
// The last line contains two city names. The first is Vladimir's start city, the
// second is Vladimir's destination. 
//
// [输出]
// For each test case you should output the number of the test case followed by
// "Vladimir needs # litre(s) of blood." or "There is no route Vladimir can take." 
//
// [样例输入]
// 2
// 3
// Ulm Muenchen 17 2
// Ulm Muenchen 19 12
// Ulm Muenchen 5 2
// Ulm Muenchen
// 10
// Lugoj Sibiu 12 6
// Lugoj Sibiu 18 6
// Lugoj Sibiu 24 5
// Lugoj Medias 22 8
// Lugoj Medias 18 8
// Lugoj Reghin 17 4
// Sibiu Reghin 19 9
// Sibiu Medias 20 3
// Reghin Medias 20 4
// Reghin Bacau 24 6
// Lugoj Bacau
//
// [样例输出]
// Test Case 1.
// There is no route Vladimir can take.
// Test Case 2.
// Vladimir needs 2 litre(s) of blood.
//
// [解题方法]
// 由题意可知，Vladimir 在乘坐火车从一个城市到另一个城市时可以有多种路线，其中出发时
// 间不在 18：00之后且到达时间不在 06：00 之前的都可以不予考虑，然后对这些满足要求的
// 路线用 DAG 建模，问题即求图中两点的最短路线。其中需要注意的是，由于需要将携带血量
// 最小化，故需要考虑从起始城市到终点城市的所有路线，因为有可能从 A 到 B 的车是 18:00
// 出发，20:00 到达 B，然后再从 B 到 C，有出发时间为 21:00，24:00 到达 C 的火车路线，
// 这样若从 A 到 C 就不需在车站停留，从而不需喝 1 升的血，所以虽然总路线不是最短的，
// 但是携带血量可以是最少的，故需要遍历可能的通路来获取最少使用血量，这个可以通过使用
// 宽度优先遍历的思想来解决。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 100
#define EARLIER 18
#define LATER 6
#define HOURS 24
#define NO_ROUTE (-1)

// 当前路线的状态，其中 city 标志当前到达的城市，time 表示到达的时间，litres 表示已
// 经使用的血量。
class state
{
public:
	int city, time, litres;

	// 使用血量少的路线先处理。
	bool operator<(const state &current) const
	{
		return litres > current.litres;
	}
};

// 火车路线。
class route
{
public:
	int departure;		// 出发时间。
	int arrival;		// 到达时间。
	int to;			    // 到达城市。
};

// 城市之间的火车路线。
vector<route> edges[MAXN + 1];

// 使用优先队列的方法来遍历所有从起始城市 from 到 终点城市 to 的路线。在此过程中，
// 先处理使用血量少的路线，当发现当前路线的状态 state 所标志的城市 city 已经为目标
// 城市 to 时，表明当前需要血量最少的路线即为该 state 所走的路线。
int travel(int from, int to)
{
	// 建立优先队列，需要血量少的路线先处理。
	priority_queue<state> states;

	// 将当前城市为 from，到达时间为 18:00 的状态添加到优先队列中，表示已经从一个虚拟
	// 的地方到达了起始城市 from，到达时间小于起始城市 from 的所有可用火车路线的出发
	// 时间，当前已经使用血量为 0 升。
	states.push((state){from, EARLIER, 0});

	// 处理队列中的路线状态。
	while (!states.empty())
	{
		// 取出队首的路线状态处理。
		state current = states.top();
		cout << current.city << " " << current.time << " " << current.litres << endl;
		states.pop();

		// 若当前城市已经为目标城市，则直接返回当前路线所使用的血量。
		if (current.city == to)
			return current.litres;

		// 遍历当前到达城市至其他城市的火车路线，根据情况决定是否需要取用 1 升的血。
		for (int r = 0; r < edges[current.city].size(); r++)
		{
			int used = current.litres;
			// 若到达时间晚于该火车路线出发时间，则需在此车站停留一个中午，取血 1 升。
			if (current.time > edges[current.city][r].departure)
				used++;

			states.push((state){edges[current.city][r].to,
					edges[current.city][r].arrival, used});
		}
	}

	// 起始城市与目标城市无连通路线。
	return NO_ROUTE;
}

int main(int ac, char *av[])
{
	int test, routes, cases = 1;
	int from, to;
	string start, destination;
	int departure, traveling;

	cin >> test;
	while (test--)
	{
		map<string, int> cities;

		for (int i = 0; i < MAXN + 1; i++)
			edges[i].clear();

		cin >> routes;
		for (int i = 1; i <= routes; i++)
		{
			// 读入起始和终点城市、出发时间、旅行时间，并将其插入到 map 中。
			cin >> start >> destination >> departure >> traveling;
			if (cities.find(start) == cities.end())
			{
				from = cities.size();
				cities[start] = from;
			}
			else
				from = cities[start];

			if (cities.find(destination) == cities.end())
			{
				to = cities.size();
				cities[destination] = to;
			}
			else
				to = cities[destination];

			// 满足条件的路线则添加到有向图中。若出发时间为凌晨，则加上 24 小时
			// 以统一时间起点。
			departure += (departure <= LATER ? HOURS : 0);
			if (departure >= EARLIER
				&& (departure + traveling) <= (HOURS + LATER))
				edges[from].push_back((route){departure,
						(departure + traveling), to});
		}

		// 出发和到达城市。
		cin >> start >> destination;

		cout << "Test Case " << cases++ << "." << endl;

		// 处理特殊情况：起始和目标城市相同。
		if (start == destination)
		{
			cout << "Vladimir needs 0 litre(s) of blood." << endl;
			continue;
		}

		// 处理特殊情况：起始或目标城市不在输入数据中。
		if (cities.find(start) == cities.end()
			|| cities.find(destination) == cities.end())
		{
			cout << "There is no route Vladimir can take." << endl;
			continue;
		}

		// 取出起始和目标城市的序号。
		from = cities[start];
		to = cities[destination];

		// 遍历所有路线以找到从城市 from 到城市 to 所需的最少血量。
		int litres = travel(from, to);

		if (litres == NO_ROUTE)
			cout << "There is no route Vladimir can take." << endl;
		else
			cout << "Vladimir needs " << litres << " litre(s) of blood." << endl;
	}

	return 0;
}
