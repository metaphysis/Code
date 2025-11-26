// Number of Connected Components
// UVa ID: 13153
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.170s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_A = 1000000;
vector<int> primes;
bool isPrime[MAX_A + 1];
int parent[MAX_A + 1];

int findRoot(int x) {
    return parent[x] == x ? x : parent[x] = findRoot(parent[x]);
}

void unionSets(int a, int b) {
    int ra = findRoot(a), rb = findRoot(b);
    if (ra != rb) parent[ra] = rb;
}

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i <= MAX_A; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= MAX_A; j += i)
                isPrime[j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve();
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int n;
        cin >> n;
        vector<int> labels(n);
        int onesCount = 0;
        for (int i = 0; i < n; i++) {
            cin >> labels[i];
            if (labels[i] == 1) onesCount++;
        }
        
        for (int i = 1; i <= MAX_A; i++)
            parent[i] = i;
        
        for (int x : labels) {
            if (x == 1) continue;
            int temp = x;
            for (int p : primes) {
                if (p * p > temp) break;
                if (temp % p == 0) {
                    unionSets(x, p);
                    while (temp % p == 0) temp /= p;
                }
            }
            if (temp > 1) unionSets(x, temp);
        }
        
        unordered_set<int> roots;
        for (int x : labels) {
            if (x != 1) roots.insert(findRoot(x));
        }
        
        int components = roots.size() + onesCount;
        cout << "Case " << caseNum << ": " << components << "\n";
    }
    return 0;
}
