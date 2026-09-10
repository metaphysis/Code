// Minimum Sum
// UVa ID: 12778
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        cin >> n;
        vector<long long> a(n + 2);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        long long part1 = 0;
        for (int i = 1; i <= n; ++i) part1 += a[i] * 1LL * i * (n - i + 1);
        vector<int> leftArr(n + 2), rightArr(n + 2);
        vector<int> st;
        st.reserve(n);
        for (int i = 1; i <= n; ++i) {
            while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
            leftArr[i] = st.empty() ? 0 : st.back();
            st.push_back(i);
        }
        st.clear();
        for (int i = n; i >= 1; --i) {
            while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
            rightArr[i] = st.empty() ? n + 1 : st.back();
            st.push_back(i);
        }
        long long part2 = 0;
        for (int i = 1; i <= n; ++i) {
            int A = i - leftArr[i];
            int B = rightArr[i] - i;
            long long lenSum = 1LL * A * B * (A + B + 2) / 2;
            part2 += a[i] * lenSum;
        }
        long long ans = part1 - part2;
        cout << "Case " << caseNo << ": " << ans << "\n";
    }
    return 0;
}
