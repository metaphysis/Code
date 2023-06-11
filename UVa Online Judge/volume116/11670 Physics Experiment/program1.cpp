// Physics Experiment
// UVa ID: 11670
// Verdict: Accepted
// Submission Date: 2023-06-11
// UVa Run Time: 0.300s
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
		double low = 0, high = d[n - 1], mid;
		while (fabs(low - high) >= 1e-6) {
		    mid = (low + high) / 2;
		    int ok = 1;
		    double last = d[0] + mid;
		    for (int i = 1; i < n; i++) {
			    if (last + D < d[i] - mid) { ok = 0; break; }
			    last = min(last + D, d[i] + mid);
		    }
		    if (ok) high = mid;
		    else low = mid;
		}
        cout << "Case " << cases++ << ": " << mid << '\n';
	}	 
	return 0;
}
