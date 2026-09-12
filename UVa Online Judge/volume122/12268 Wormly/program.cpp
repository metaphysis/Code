#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    while (testCases--) {
        int l, b, n;
        string bridge;
        cin >> l >> b >> n;
        cin >> bridge;
        bridge = " " + bridge;
        vector<int> sum(n + 1, 0);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + (bridge[i] == '1');
        int left = 1, right = b;
        long long answer = 0;
        bool possible = true;
        while (left < n - l + 1 || right < n) {
            bool moved = false;
            if (left < n - l + 1 && sum[right] - sum[left - 1] > l) {
                int nextLeft = left;
                while (nextLeft < n - l + 1 && sum[right] - sum[nextLeft - 1] > l)
                    nextLeft++;
                while (bridge[nextLeft] == '0')
                    nextLeft++;
                left = nextLeft;
                answer += l;
                moved = true;
            }
            if (right < n && left > right - b + 1) {
                int move = left - (right - b + 1);
                move = min(move, n - right);
                right += move;
                answer += move;
                moved = true;
            }
            if (!moved) {
                possible = false;
                break;
            }
        }
        if (possible) cout << answer << '\n';
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
