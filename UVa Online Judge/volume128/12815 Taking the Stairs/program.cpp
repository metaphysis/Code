#include <bits/stdc++.h>
using namespace std;

struct Stair {
    int x, y;
};

int solve() {
    int t;
    cin >> t;
    while (t--) {
        int h, w, n;
        cin >> h >> w >> n;
        vector<Stair> stairs(n);
        for (int i = 0; i < n; i++)
            cin >> stairs[i].x >> stairs[i].y;
        sort(stairs.begin(), stairs.end(), [](const Stair &a, const Stair &b) {
            return a.x < b.x;
        });
        vector<int> floor(h);
        for (int i = 0; i < h; i++)
            floor[i] = i;
        for (const Stair &stair : stairs)
            swap(floor[stair.y - 1], floor[stair.y]);
        for (int i = 0; i < h; i++) {
            if (i > 0)
                cout << ' ';
            cout << char('A' + floor[i]);
        }
        cout << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
