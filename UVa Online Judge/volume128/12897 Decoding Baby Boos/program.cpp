// Decoding Baby Boos
// UVa ID: 12897
// Verdict: Accepted
// Submission Date: 2023-07-07
// UVa Run Time: 0.130s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h> 
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
	while (T--) {
        string s;
        int n, mp[128];
        for (int i = 0; i < 128; i++) mp[i] = i;
        cin >> s >> n;
        for (int i = 0; i < n; i++) {
            char a, b;
            cin >> a >> b;
            for (int i = 65; i <= 90; i++)
                if (mp[i] == b)
                    mp[i] = a;
        }
        for (auto c : s) cout << (char)mp[c];
        cout << '\n';
    }
    return 0;
}
