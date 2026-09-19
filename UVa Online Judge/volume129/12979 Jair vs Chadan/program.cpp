#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long mod = 1000000007;
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int n, k, card;
        cin >> n >> k;
        vector<int> minPrime(n + 1, 0);
        vector<bool> used(n + 1, false);
        set<int> remain, faceUp;
        for (int i = 1; i <= n; ++i) remain.insert(i);
        for (int i = 0; i < k; ++i) {
            cin >> card;
            faceUp.insert(card);
        }
        for (int i = 2; i <= n; ++i) {
            if (minPrime[i] != 0) continue;
            for (int j = i; j <= n; j += i) if (minPrime[j] == 0) minPrime[j] = i;
        }
        long long ans = 0;
        for (int turn = 0; turn < n; ++turn) {
            const set<int>& choices = faceUp.empty() ? remain : faceUp;
            if (turn % 2 == 0) card = *choices.rbegin();
            else card = *choices.begin();
            ans = (ans * (n + 1) + card) % mod;
            remain.erase(card);
            faceUp.erase(card);
            used[card] = true;
            int value = card;
            while (value > 1) {
                int prime = minPrime[value];
                if (!used[prime]) {
                    auto it = faceUp.find(prime);
                    if (it == faceUp.end()) faceUp.insert(prime);
                    else faceUp.erase(it);
                }
                while (value % prime == 0) value /= prime;
            }
        }
        cout << "Case #" << caseId << ": " << ans << '\n';
    }
    return 0;
}
