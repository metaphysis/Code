// Inverting Huffman
// UVa ID: 12676
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> L(n);
        for (int i = 0; i < n; i++) cin >> L[i];
        sort(L.begin(), L.end(), greater<int>());
        long long weight = 1;
        vector<long long> merged;
        int depth = L.front();
        while (L.size()) {
            priority_queue<long long, vector<long long>, greater<long long>> pq;
            for (auto m : merged) pq.push(m);
            while (L.size() && L.front() == depth) {
                pq.push(weight);
                L.erase(L.begin());
            }
            merged.clear();
            while (pq.size()) {
                long long w1 = pq.top(); pq.pop();
                long long w2 = pq.top(); pq.pop();
                weight = max(weight, max(w1, w2));
                merged.push_back(w1 + w2);
            }
            depth--;
        }
        cout << accumulate(merged.begin(), merged.end(), 0LL) << '\n';
    }
    return 0;
}
