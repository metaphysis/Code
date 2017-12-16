// Fermat vs. Pythagoras
// UVa ID: 106
// Verdict: Accepted
// Submission Date: 2011-11-21
// UVa Run Time: 0.236s
//
// 版权所有（C）2011,邱秋。metaphysis # yeah dot net

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

#define MAXN 1000001

bool used[MAXN];

int gcd(int a, int b)
{
	return a < b ? gcd(b, a) : (b ? gcd(b, a % b) : a);
}

int main(int argc, char const *argv[])
{
	int n, limit, x, y, z;

	while (cin >> n)
	{
		for (int i = 1; i <= n; i++) used[i] = false;

		limit = floor(sqrt(n));
		
		int total = 0;
		for (int i = 1; i < limit; i++)
			for (int j = i + 1; j <= limit; j += 2)
				if ((z = (i * i + j * j)) <= n && gcd(i, j) == 1)
				{
					x = j * j - i * i;
					y = 2 * i * j;

					total++;
					for (int start = 1; z * start <= n; start++)
						used[x * start] = used[y * start] = used[z * start] = true;
				}

		int unused = 0;
		for (int i = 1; i <= n; i++)
			if (!used[i])
				unused++;

		cout << total << " " << unused << endl;
	}

	return 0;
}
