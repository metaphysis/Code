#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        int M = N * N;
        vector<int> board(M);
        for (int i = 0; i < M; ++i) cin >> board[i];

        int D = 0;
        for (int i = 0; i < M; ++i) if (board[i] != i) ++D;

        vector<bool> visited(M, false);
        int k = 0;
        for (int i = 0; i < M; ++i) {
            if (!visited[i] && board[i] != i) {
                ++k;
                int cur = i;
                while (!visited[cur]) {
                    visited[cur] = true;
                    cur = board[cur];
                }
            }
        }

        int ans;
        if (board[0] == 0) ans = D + k;
        else ans = D + k - 2;

        cout << "Case " << caseNo << ": " << ans << "\n";
    }
    return 0;
}
