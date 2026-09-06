#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll getMaxCode(ll d, ll e) {
    ll curDay = 0, certCnt = 1, totalCode = 0;
    while (certCnt < e && curDay + 10 <= d) {
        ll trainCnt = min(certCnt, e - certCnt);
        ll workCert = certCnt - trainCnt, workNonCert = e - certCnt - trainCnt;
        totalCode += 4 * (workCert * 200 + workNonCert * 40);
        certCnt += trainCnt;
        curDay += 4;
    }
    totalCode += (d - curDay) * (certCnt * 200 + (e - certCnt) * 40);
    return totalCode;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll d, e, l;
        cin >> d >> e >> l;
        if (getMaxCode(d, e) >= l) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
