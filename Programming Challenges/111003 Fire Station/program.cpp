// Fire Station （消防站）
// PC/UVa IDs: 111003/10278, Popularity: B, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-10-05
// UVa Run Time: 0.888s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 某城市中有一些消防队，居民抱怨说一些房子离最近的消防站都很远，所以必须建一个新的消防站。你要选择
// 这个新消防站的位置，让它离最缺少服务的居民区最近。
//
// 这个城市最多有 500 个路口，被长度不同的道路连接。汇集在同一路口的道路数不会超过 20。房子和消防
// 站的位置都在路口上。假定在每个路口至少有一栋房子，且在同一路口可以有多个消防站。
//
// [输入]
// 输入第一行只有一个整数，代表测试数据的数量，接下来有一个空行。相邻两组数据之间也有一个空行。每组
// 数据的第一行有两个整数：现有的消防站数量 f（f <= 100） 和路口的数量 i（i <= 500）。路口用
// 1 ～ i 的连续整数来表示。接下来的 f 行，每一行有一个数，表示该消防站所在路口的编号。后面的若干
// 行，每行有 3 个正整数：一个路口的编号，另一个路口的编号，和连接这两个路口道路的长度。所有的道路
// 都是双向的（至少消防车可以从两边通过），并且任何两个路口之间的都是可达的。
//
// [输出]
// 对于每一组数据，输出新消防站所在的路口编号（使得任意路口到最近消防站的最大距离最小）。如果有多个
// 路口满足条件，输出编号最小的一个。相邻两组数据的输出被一个空行隔开。
//
// [样例输入]
// 1
//
// 1 6
// 2
// 1 2 10
// 2 3 10
// 3 4 10
// 4 5 10
// 5 6 10
// 6 1 10
//
// [样例输出]
// 5
//
// [解题方法]
// 如何求出路口到最近消防站的距离？回忆学习过的图算法，可以通过求每对结点之间的最短路长度来得到，即
// Floyd 算法。通过 Floyd 算法，可以方便的从图的边权矩阵直接算出距离矩阵，然后通过比较路口到各个
// 消防站的距离得到至最近消防站的距离，然后再比较各个路口至最近消防站的距离得到路口离消防站的最大距
// 离，由于新消防站只能位于所有路口中的一个，那么可以从编号大的路口开始枚举新消防站所处的路口，重新计
// 算路口离消防站的最大距离，在此过程中，取能得到最小最大距离且编号最小的路口编号即为新消防站的位置。

#include <iostream>
#include <sstream>

using namespace std;

#define MAXI 500
#define MAXF 100
#define MAXINT (1 << 20)

int main(int ac, char *av[])
{
	string line;
	int output = 0, cases;
	int nstations, nintersections;
	int stations[MAXF + 1];
	int weight[MAXI + 1][MAXI + 1];
	int shortest[MAXI + 1];
	int fi, si, wi;
	istringstream iss;

	cin >> cases;
	while (cases--)
	{
		// 读入现有消防站总数和路口总数。
		cin >> nstations >> nintersections;
		
		// 读入消防站位置。
		for (int c = 1; c <= nstations; c++)
			cin >> stations[c];
		
		// 初始化边权矩阵。
		for (int i = 1; i <= nintersections; i++)
			for (int j = 1; j <= nintersections; j++)
				weight[i][j] = MAXINT;
		
		// 读入边权数据。
		cin.ignore();
		while (getline(cin, line), line.length())
		{
			iss.clear();
			iss.str(line);
			iss >> fi >> si >> wi;
			weight[fi][si] = weight[si][fi] = wi;
		}

		// 使用 Floyd 算法计算点对间最短距离。
        for (int k = 1; k <= nintersections; k++)
	        for (int i = 1; i <= nintersections; i++)
		        for (int j = 1; j <= nintersections; j++)
		        {
			        int through = weight[i][k] + weight[k][j];
			        if (through < weight[i][j])
				        weight[i][j] = through;
		        }

		// 当路口与消防站位于同一路口时，距离为 0。
		for (int i = 1; i <= nintersections; i++)
			weight[i][i] = 0;
	
		// 得到各个路口到最近消防站的距离及最大的最近距离。
		int maxshortest = 0;
		for (int i = 1; i <= nintersections; i++)
		{
			int distance = MAXINT;
			for (int j = 1; j <= nstations; j++)
				if (weight[i][stations[j]] < distance)
					distance = weight[i][stations[j]];

			shortest[i] = distance;
			if (distance > maxshortest)
				maxshortest = distance;
		}

		// 从编号最大的路口开始枚举新消防站的位置。
		int intersection = 1;
		for (int i = nintersections; i >= 1; i--)
		{
			// 比较之前路口到最近消防站距离和路口到新消防站的距离，若之前的最近
			// 距离小于路口到新消防站的距离，则路口到消防站的距离即为到新消防站
			// 的距离，否则最近距离不变，与此同时找最大的最近距离。
			int tmaxshortest = 0;
			for (int j = 1; j <= nintersections; j++)
				if (weight[j][i] < shortest[j])
				{
					if (tmaxshortest < weight[j][i])
						tmaxshortest = weight[j][i];
				}
				else
				{
					if (tmaxshortest < shortest[j])
						tmaxshortest = shortest[j];
				}
					
			// 更新当前的最大最近距离。
			if (tmaxshortest <= maxshortest)
			{
				intersection = i;
				maxshortest = tmaxshortest;
			}
		}
		
		// 相邻两组数据间输出空行。
		if (output++)
			cout << endl;

		// 输出新消防站的位置。
		cout << intersection << endl;
	}
	
	return 0;
}
