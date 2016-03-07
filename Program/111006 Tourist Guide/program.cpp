// Tourist Guide （导游）
// PC/UVa IDs: 111006/10199, Popularity: B, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-07
// UVa Run Time: 0.040s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [Problem Description]
// Rio de Janeiro is a very beautiful city, but there are so many places to visit
// that you feel overwhelmed, Fortunately, your friend Bruno has promised to be
// your tour guide.
//
// Unfortunately, Bruno is terrible driver. He has a lot of traffic fines to pay
// and is eager to avoid paying more. Therefore he wants to know where all the
// police cameras are located so he can drive more carefully when passing by them.
// These cameras are strategically distributed over the city, in locations that
// a driver must pass through in order to travel from one zone of the city to
// another. A location C will have a camera if and only if there are two city
// locations A and B such that all paths from A to B pass through a location C.
//
// For instance, suppose that we have six locations (A, B, C, D, E, and F ) with
// seven bidirectional routes B − C, A − B, C − A, D − C, D − E, E − F , and F − C.
// There must be a camera on C because to go from A to E you must pass through C.
// In this configuration, C is the only camera location.
//
// Given a map of the city, help Bruno avoid further fines during your tour by
// writing a program to identify where all the cameras are.
//
// [Input]
// The input will consist of an arbitrary number of city maps, where each map
// begins with an integer N (2 < N ≤ 100) denoting the total number of locations
// in the city. Then follow N different place names at one per line, where each
// place name will consist of least one and at most 30 lowercase letters. A
// non-negative integer R then follows, denoting the total routes of the city.
// The next R lines each describe a bidirectional route represented by the two
// places that the route connects.
//
// Location names in route descriptions will always be valid, and there will be
// no route from one place to itself. You must read until N = 0, which should not
// be processed.
//
// [Output]
// For each city map you must print the following line:
//
// City map #d: c camera(s) found
//
// where d stands for the city map number (starting from 1) and c stands for the
// total number of cameras. Then should follow c lines with the location names
// of each camera in alphabetical order. Print a blank line between output sets.
//
// [Sample Input]
// 6
// sugarloaf
// maracana
// copacabana
// ipanema
// corcovado
// lapa
// 7
// ipanema copacabana
// copacabana sugarloaf
// ipanema sugarloaf
// maracana lapa
// sugarloaf maracana
// corcovado sugarloaf
// lapa corcovado
// 5
// guanabarabay
// downtown
// botanicgarden
// colombo
// sambodromo
// 4
// guanabarabay sambodromo
// downtown sambodromo
// sambodromo botanicgarden
// colombo sambodromo
// 0
//
// [Sample Output]
// City map #1: 1 camera(s) found
// sugarloaf
//
// City map #2: 1 camera(s) found
// sambodromo
//
// [解题方法]
// 摄像头的位置对应图论的割顶（articulation vertex）概念，求图的割顶即可，需要注意的是，测试数
// 据所给的可能不是连通图，故需要找到其中的所有连通子图的割顶。

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

#define MAXV 100

string locations[MAXV + 1];
int edges[MAXV + 1][MAXV + 1];
int degree[MAXV + 1];
int nvertices;
bool discovered[MAXV + 1];

// 深度优先遍历。
void dfs(int start)
{
	discovered[start] = true;
	nvertices++;
	
	for (int i = 0; i < degree[start]; i++)
		if (discovered[edges[start][i]] == false)
			dfs(edges[start][i]);
}

// 求连通图的割顶。
void articulation_vertex(vector < int > &component, vector < string > &cameras)
{
	int ncomponent = component.size();

	for (int i = 0; i < ncomponent; i++)
	{
		nvertices = 0;
		memset(discovered, 0, sizeof(discovered));
		discovered[component[i]] = true;

		dfs(i < (ncomponent - 1) ? component[i + 1] : component[i - 1]);

		if (nvertices < (ncomponent - 1))
			cameras.push_back(locations[component[i]]);	
	}
}

int main(int ac, char *av[])
{
	int cases = 1, ncities, routes;
	string location, start, end;
	
	while (cin >> ncities, ncities)
	{
		map < string, int > cityMap;
		for (int i = 1; i <= ncities; i++)
		{
			cin >> location;
			cityMap[location] = i;
			degree[i] = 0;
			locations[i] = location;
		}
		
		cin >> routes;
		for (int i = 1; i <= routes; i++)
		{
			cin >> start >> end;
			edges[cityMap[start]][degree[cityMap[start]]++] = cityMap[end];
			edges[cityMap[end]][degree[cityMap[end]]++] = cityMap[start];
		}
		
		// 找出所有连通子图，并求其割顶。
		bool visited[MAXV + 1];
		memset(visited, 0, sizeof(visited));
		vector < string > cameras;

		for (int i = 1; i <= ncities; i++)
			if (visited[i] == false)
			{
				queue < int > vertices;
				vector < int > component;

				vertices.push(i);
				visited[i] = true;
				component.push_back(i);
				
				while (!vertices.empty())
				{
					int v = vertices.front();
					vertices.pop();
					
					for (int i = 0; i < degree[v]; i++)
						if (visited[edges[v][i]] == false)
						{
							vertices.push(edges[v][i]);
							visited[edges[v][i]] = true;
							component.push_back(edges[v][i]);
						}
				}
				
				// 求连通子图的割顶。
				articulation_vertex(component, cameras);
			}

		// 输出。
		if (cases > 1)
			cout << endl;
		sort(cameras.begin(), cameras.end());	
		cout << "City map #" << cases++ << ": ";
		cout << cameras.size() << " camera(s) found" << endl;
		for (int i = 0; i < cameras.size(); i++)
			cout << cameras[i] << endl;
	}

	return 0;
}
