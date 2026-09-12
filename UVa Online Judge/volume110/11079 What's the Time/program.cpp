#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

double getTime(int leftTime, int rightTime, ll leftVal, ll rightVal, ll target) {
    return leftTime + (rightTime - leftTime) * (target - leftVal) * 1.0 / (rightVal - leftVal);
}

int main() {
    int n, k, caseId = 1;
    while (scanf("%d%d", &n, &k) != EOF) {
        if (n == 0 && k == 0) break;
        map<int, int> openMap;
        int lcmVal = 1;
        while (n--) {
            int period, cap;
            scanf("%d%d", &period, &cap);
            lcmVal = lcmVal / __gcd(lcmVal, period) * period;
            openMap[period] += cap;
        }
        ll target, need;
        scanf("%lld", &target);
        need = target - k;
        printf("Case %d: ", caseId++);
        if (need == 0) {
            printf("0.00000000\n");
            continue;
        }
        bool reverseFlag = need < 0;
        if (reverseFlag) need = -need;
        for (map<int, int>::iterator it = openMap.begin(); it != openMap.end(); ++it) if (reverseFlag) it->second = -it->second;
        lcmVal *= 2;
        vector<ll> sum(lcmVal + 1, 0);
        for (map<int, int>::iterator it = openMap.begin(); it != openMap.end(); ++it) {
            int period, cap;
            period = it->first;
            cap = it->second;
            for (int i = 1; i < lcmVal; i += 2 * period) {
                sum[i] += cap;
                sum[i + period] -= cap;
            }
        }
        for (int i = 1; i <= lcmVal; i++) sum[i] += sum[i - 1];
        for (int i = 1; i <= lcmVal; i++) sum[i] += sum[i - 1];
        ll step = sum[lcmVal], left = 0, right = 0;
        if (step > 0) right = need / step;
        int flag = 0;
        double answer = 1e100;
        while (left <= right) {
            ll mid, cur;
            mid = (left + right) / 2;
            cur = step * mid;
            int ok = 0;
            for (int i = 1; i <= lcmVal; i++) {
                ll leftVal, rightVal;
                leftVal = sum[i - 1] + cur;
                rightVal = sum[i] + cur;
                if (leftVal <= need && need <= rightVal) {
                    ok = 1;
                    if (leftVal == rightVal) answer = min(answer, i - 1.0 + lcmVal * 1.0 * mid);
                    else answer = min(answer, getTime(i - 1, i, leftVal, rightVal, need) + lcmVal * 1.0 * mid);
                }
            }
            if (ok) {
                right = mid - 1;
                flag = 1;
            } else left = mid + 1;
        }
        if (!flag) printf("Impossible.\n");
        else printf("%.8f\n", answer);
    }
    return 0;
}
