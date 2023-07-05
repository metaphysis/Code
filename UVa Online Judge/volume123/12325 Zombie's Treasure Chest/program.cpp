// Zombie's Treasure Chest
// UVa ID: 12325
// Verdict: Accepted
// Submission Date: 2023-07-04
// UVa Run Time: 0.130s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h> 
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	int T; cin >> T;
	for (int cs = 1; cs <= T; cs++) {
        cout << "Case #" << cs << ": ";
        long long N, S1, V1, S2, V2;
        cin >> N >> S1 >> V1 >> S2 >> V2;
        if (V1 * S2 < V2 * S1) {
            swap(S1, S2);
            swap(V1, V2);
        }
        long long r = 0;
        for (int i = 0; i <= min(S1 - 1, N / S2); i++)
            r = max(r, i * V2 + (N - i * S2) / S1 * V1);
        cout << r << '\n';
	}
	return 0;
}
