#include <bits/stdc++.h>
using namespace std;

int getMax(vector<int>& height, int left, int right) {
    vector<int> st;
    int ans = 0, i = left;
    for (i = left; i <= right; i++) {
        int cur = i == right ? 0 : height[i];
        while (!st.empty() && height[st.back()] >= cur) {
            int pos = st.back();
            st.pop_back();
            int width = st.empty() ? i - left : i - st.back() - 1;
            ans = max(ans, height[pos] * width);
        }
        st.push_back(i);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<int> last(m), cur(m), height(m);
        int ans = 0, i, j;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                int x;
                cin >> x;
                cur[j] = x - i - j;
                if (i > 0 && cur[j] == last[j]) height[j]++;
                else height[j] = 1;
            }
            for (j = 0; j < m; ) {
                int right = j + 1;
                while (right < m && cur[right] == cur[j]) right++;
                ans = max(ans, getMax(height, j, right));
                j = right;
            }
            last.swap(cur);
        }
        cout << ans << '\n';
    }
    return 0;
}
