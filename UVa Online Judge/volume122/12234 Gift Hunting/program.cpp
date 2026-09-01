#include <bits/stdc++.h>
using namespace std;

const int NegInf = -1000000000;

struct Gift {
    int price, happy, special;
};

int solve() {
    int v1, v2, n, caseNum = 1;
    while (cin >> v1 >> v2 >> n) {
        if (v1 == 0 && v2 == 0 && n == 0)
            break;
        vector<Gift> gifts(n);
        for (int i = 0; i < n; i++)
            cin >> gifts[i].price >> gifts[i].happy >> gifts[i].special;
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(v1 + 1, vector<int>(v2 + 1, NegInf)));
        dp[0][0][0] = 0;
        for (const Gift &gift : gifts) {
            vector<vector<vector<int>>> nextDp(2, vector<vector<int>>(v1 + 1, vector<int>(v2 + 1, NegInf)));
            for (int usedFree = 0; usedFree <= 1; usedFree++) {
                for (int usedV1 = 0; usedV1 <= v1; usedV1++) {
                    for (int usedV2 = 0; usedV2 <= v2; usedV2++) {
                        if (dp[usedFree][usedV1][usedV2] == NegInf)
                            continue;
                        if (gift.special == 0)
                            nextDp[usedFree][usedV1][usedV2] = max(nextDp[usedFree][usedV1][usedV2], dp[usedFree][usedV1][usedV2]);
                        if (usedV1 + gift.price <= v1)
                            nextDp[usedFree][usedV1 + gift.price][usedV2] = max(nextDp[usedFree][usedV1 + gift.price][usedV2], dp[usedFree][usedV1][usedV2] + gift.happy);
                        if (usedV2 + gift.price <= v2)
                            nextDp[usedFree][usedV1][usedV2 + gift.price] = max(nextDp[usedFree][usedV1][usedV2 + gift.price], dp[usedFree][usedV1][usedV2] + gift.happy);
                        if (usedFree == 0)
                            nextDp[1][usedV1][usedV2] = max(nextDp[1][usedV1][usedV2], dp[usedFree][usedV1][usedV2] + gift.happy);
                    }
                }
            }
            dp.swap(nextDp);
        }
        int answer = -1;
        for (int usedFree = 0; usedFree <= 1; usedFree++)
            for (int usedV1 = 0; usedV1 <= v1; usedV1++)
                for (int usedV2 = 0; usedV2 <= v2; usedV2++)
                    answer = max(answer, dp[usedFree][usedV1][usedV2]);
        cout << "Case " << caseNum++ << ": " << answer << "\n\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
