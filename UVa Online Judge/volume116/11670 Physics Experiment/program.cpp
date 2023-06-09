// Physics Experiment
// UVa ID: 11670
// Verdict: Accepted
// Submission Date: 2023-06-07
// UVa Run Time: 0.090s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
double d[10010], D;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	int n, cases = 1;
    cout << fixed << setprecision(3);
	while (cin >> n, n) {
		for (int i = 0; i < n; i++) cin >> d[i];
        cin >> D;
		sort(d, d + n);
		double t = 0;
		for (int i = 1; i < n; i++) {
			if (d[i] - d[i - 1] > D) {
				if (d[i] - t - d[i - 1] > D) {
					double needed = (d[i] - t - d[i - 1] - D) / 2;
					d[i] = d[i] - needed - t;
					t += needed;
				} else d[i] = d[i - 1] + D;
			} else {
				if (d[i] + t < d[i - 1] + D) d[i] += t;
				else d[i] = d[i - 1] + D;
			}
		}
        cout << "Case " << cases++ << ": " << t << '\n';
	}	 
	return 0;
}
