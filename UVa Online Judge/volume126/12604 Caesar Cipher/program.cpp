// Caesar Cipher
// UVa ID: 12604
// Verdict: Accepted
// Submission Date: 2023-05-14
// UVa Run Time: 0.290s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int BASE1 = 16777213, MOD1 = 2147483647;
const int BASE2 = 16777199, MOD2 = 2147483629;

string s1, s2, s3;
int cnt[64], idx[128], n1, n2, n3;
pair<long long, long long> h[64];
long long h1[500010], h2[500010];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> s1 >> s2 >> s3;
        n1 = s1.length(), n2 = s2.length(), n3 = s3.length();
        for (int i = 0; i < n1; i++)
            idx[s1[i]] = i;
        for (int i = 0; i < n1; i++)
            h[i].first = h[i].second = 0;
        for (int i = 0; i < n2; i++)
            for (int j = 0; j < n1; j++) {
                h[j].first = (h[j].first * BASE1 + s1[(idx[s2[i]] + j) % n1]) % MOD1;
                h[j].second = (h[j].second * BASE2 + s1[(idx[s2[i]] + j) % n1]) % MOD2;
            }
        memset(cnt, 0, sizeof cnt);
        h1[0] = h2[0] = 0;
        long long hf, hs, BP1 = 1, BP2 = 1;
        for (int i = 1; i <= n2; i++) {
            BP1 = BP1 * BASE1 % MOD1;
            BP2 = BP2 * BASE2 % MOD2;
        }
        for (int i = 1; i <= n3; i++) {
            h1[i] = (h1[i - 1] * BASE1 + s3[i - 1]) % MOD1;
            h2[i] = (h2[i - 1] * BASE2 + s3[i - 1]) % MOD2;
            if (i >= n2) {
                hf = (h1[i] - h1[i - n2] * BP1 % MOD1 + MOD1) % MOD1;
                hs = (h2[i] - h2[i - n2] * BP2 % MOD2 + MOD2) % MOD2;
                for (int j = 0; j < n1; j++)
                    if (hf == h[j].first && hs == h[j].second)
                        cnt[j]++;
            }
        }
        vector<int> shifts;
        for (int i = 0; i < n1; i++)
            if (cnt[i] == 1)
                shifts.push_back(i);       
        if (shifts.size() == 0) cout << "no solution";
        if (shifts.size() == 1) cout << "unique: " << shifts.front();
        if (shifts.size() > 1) {
            cout << "ambiguous:";
            for (auto sf : shifts) cout << ' ' << sf;
        }
        cout << '\n';
    }
    return 0;
}
