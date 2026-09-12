// Tobby and the quaseEquals Strings
// UVa ID: 13186
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

const long long mod1 = 1000000007;
const long long mod2 = 1000000009;
const long long base = 911382323;

struct HashVal {
    long long x, y;
    bool operator == (const HashVal &other) const {
        return x == other.x && y == other.y;
    }
};

struct HashFunc {
    size_t operator () (const HashVal &value) const {
        return value.x ^ (value.y + 0x9e3779b97f4a7c15ULL + (value.x << 6) + (value.x >> 2));
    }
};

HashVal getHash(const string &str, int pos, const vector<long long> &pow1, const vector<long long> &pow2) {
    int len = str.size();
    vector<long long> pre1(len + 1), pre2(len + 1);
    for (int i = 0; i < len; i++) {
        int value = str[i] - 'a' + 1;
        pre1[i + 1] = (pre1[i] * base + value) % mod1;
        pre2[i + 1] = (pre2[i] * base + value) % mod2;
    }
    int rightLen = len - pos - 1;
    long long left1 = pre1[pos];
    long long left2 = pre2[pos];
    long long right1 = (pre1[len] - pre1[pos + 1] * pow1[rightLen] % mod1 + mod1) % mod1;
    long long right2 = (pre2[len] - pre2[pos + 1] * pow2[rightLen] % mod2 + mod2) % mod2;
    long long hash1 = (left1 * pow1[rightLen] + right1) % mod1;
    long long hash2 = (left2 * pow2[rightLen] + right2) % mod2;
    return {hash1, hash2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, l;
    while (cin >> n >> q >> l) {
        vector<long long> pow1(l + 1), pow2(l + 1);
        pow1[0] = 1;
        pow2[0] = 1;
        for (int i = 1; i <= l; i++) {
            pow1[i] = pow1[i - 1] * base % mod1;
            pow2[i] = pow2[i - 1] * base % mod2;
        }
        vector<unordered_map<HashVal, int, HashFunc>> hashTable(l);
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            vector<long long> pre1(l + 1), pre2(l + 1);
            for (int j = 0; j < l; j++) {
                int value = str[j] - 'a' + 1;
                pre1[j + 1] = (pre1[j] * base + value) % mod1;
                pre2[j + 1] = (pre2[j] * base + value) % mod2;
            }
            for (int j = 0; j < l; j++) {
                int rightLen = l - j - 1;
                long long left1 = pre1[j];
                long long left2 = pre2[j];
                long long right1 = (pre1[l] - pre1[j + 1] * pow1[rightLen] % mod1 + mod1) % mod1;
                long long right2 = (pre2[l] - pre2[j + 1] * pow2[rightLen] % mod2 + mod2) % mod2;
                HashVal key;
                key.x = (left1 * pow1[rightLen] + right1) % mod1;
                key.y = (left2 * pow2[rightLen] + right2) % mod2;
                hashTable[j][key]++;
            }
        }
        for (int i = 0; i < q; i++) {
            string str;
            cin >> str;
            vector<long long> pre1(l + 1), pre2(l + 1);
            for (int j = 0; j < l; j++) {
                int value = str[j] - 'a' + 1;
                pre1[j + 1] = (pre1[j] * base + value) % mod1;
                pre2[j + 1] = (pre2[j] * base + value) % mod2;
            }
            long long answer = 0;
            for (int j = 0; j < l; j++) {
                int rightLen = l - j - 1;
                long long left1 = pre1[j];
                long long left2 = pre2[j];
                long long right1 = (pre1[l] - pre1[j + 1] * pow1[rightLen] % mod1 + mod1) % mod1;
                long long right2 = (pre2[l] - pre2[j + 1] * pow2[rightLen] % mod2 + mod2) % mod2;
                HashVal key;
                key.x = (left1 * pow1[rightLen] + right1) % mod1;
                key.y = (left2 * pow2[rightLen] + right2) % mod2;
                auto it = hashTable[j].find(key);
                if (it != hashTable[j].end())
                    answer += it->second;
            }
            cout << answer << '\n';
        }
    }
    return 0;
}
