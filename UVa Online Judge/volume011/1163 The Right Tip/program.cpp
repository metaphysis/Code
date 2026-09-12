#include <bits/stdc++.h>
using namespace std;

int n;
int cnt[8];
int val[8] = {1, 2, 5, 10, 20, 50, 100, 200};
int need[5], have[8];

bool judge() {
    int i, j;
    for (i = 0; i < n; i++) if (need[i] < 0) return false;
    for (i = 0; i < 8; i++) if (have[i] < 0) return false;
    if (have[2] % 2 == 1 || have[5] % 2 == 1) return false;
    have[3] += have[2] / 2;
    have[2] = 0;
    have[6] += have[5] / 2;
    have[5] = 0;
    for (i = 0; i < n; i++) {
        int tv = need[i];
        for (j = 7; j >= 0; j--) {
            if (tv >= have[j] * val[j]) {
                tv -= have[j] * val[j];
                have[j] = 0;
            } else {
                have[j] -= tv / val[j];
                tv %= val[j];
            }
        }
        if (tv != 0) return false;
    }
    return true;
}

int main() {
    while (1) {
        int i, j, k;
        scanf("%d", &n);
        if (n == -1) break;
        for (i = 0; i < 8; i++) scanf("%d", &cnt[i]);
        int sum = 0;
        for (i = 0; i < 8; i++) sum += val[i] * cnt[i];
        if (sum % n != 0) {
            printf("no\n");
            continue;
        }
        int target = sum / n;
        bool flag = false;
        for (int mask1 = 0; mask1 < (1 << n) && !flag; mask1++) {
            for (int mask2 = 0; mask2 < (1 << n) && !flag; mask2++) {
                for (i = 0; i < n; i++) need[i] = target;
                for (i = 0; i < 8; i++) have[i] = cnt[i];
                for (k = 0; k < n; k++) {
                    if ((mask1 >> k) & 1) {
                        have[2]--;
                        need[k] -= 5;
                    }
                    if ((mask2 >> k) & 1) {
                        have[5]--;
                        need[k] -= 50;
                    }
                }
                if (judge()) flag = true;
            }
        }
        printf(flag ? "yes\n" : "no\n");
    }
    return 0;
}
