#include <bits/stdc++.h>
using namespace std;

struct Order {
    int start, end;
    long long price;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool firstCase = true;
    int n;
    while (cin >> n) {
        vector<Order> orders(n);
        string name;
        for (int i = 0; i < n; ++i) {
            int start, duration;
            long long price;
            cin >> name >> start >> duration >> price;
            orders[i] = {start, start + duration, price};
        }

        sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
            return a.end < b.end;
        });

        vector<long long> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int lo = 0, hi = n;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (orders[mid].end <= orders[i - 1].start)
                    lo = mid + 1;
                else
                    hi = mid;
            }
            int p = lo;
            dp[i] = max(dp[i - 1], orders[i - 1].price + dp[p]);
        }

        if (!firstCase) cout << '\n';
        cout << dp[n] << '\n';
        firstCase = false;
    }
    return 0;
}
