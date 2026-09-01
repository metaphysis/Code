#include <bits/stdc++.h>
using namespace std;

struct Block {
    int weight, side[6];
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != -1) {
        vector<Block> blocks(n);
        for (int i = 0; i < n; i++) {
            cin >> blocks[i].weight;
            for (int j = 0; j < 6; j++)
                cin >> blocks[i].side[j];
        }
        sort(blocks.begin(), blocks.end(), [](const Block &a, const Block &b) {
            return a.weight < b.weight;
        });
        int best[1001] = {}, answer = 0;
        for (int i = 0; i < n; i++) {
            int dp[6];
            for (int j = 0; j < 6; j++) {
                int top = j ^ 1;
                dp[j] = best[blocks[i].side[top]] + 1;
                answer = max(answer, dp[j]);
            }
            for (int j = 0; j < 6; j++)
                best[blocks[i].side[j]] = max(best[blocks[i].side[j]], dp[j]);
        }
        cout << answer << '\n';
    }
    return 0;
}
