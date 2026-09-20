#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount;
    cin >> caseCount;
    cout << fixed << setprecision(2);
    while (caseCount--) {
        long long stageCount, stageIdx;
        long double startP, endP, rate, ans;
        cin >> stageCount >> startP >> endP >> stageIdx;
        if (stageIdx == 1 || startP == endP) ans = 1.0L;
        else if (stageIdx == stageCount + 1) ans = endP / startP;
        else {
            rate = static_cast<long double>(stageIdx - 1) / stageCount;
            ans = expl(rate * (logl(endP) - logl(startP)));
        }
        cout << ans << '\n';
    }
    return 0;
}
