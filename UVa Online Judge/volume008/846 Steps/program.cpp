// Steps （数轴行走）
// PC/UVa IDs: 110608/846, Popularity: A, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-09-25
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>
using namespace std;
int main(int ac, char *av[]) {
	int cases, x, y;
	cin >> cases;
	while (cases--) {
		cin >> x >> y;
		int distance = y - x;
		if (distance <= 3) cout << distance << endl;
		else {
			int n = sqrt(distance);
			if (n * n == distance) cout << (2 * n - 1) << endl;
			else if ((distance - n * n) <= (n + 1)) cout << (2 * n) << endl;
			else cout << (2 * n + 1) << endl;
		}
	}
	return 0;
}
