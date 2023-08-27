// Database
// UVa ID: 1592
// Verdict: Accepted
// Submission Date: 2023-08-27
// UVa Run Time: 6.480s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m;
    string line;
    while (cin >> n >> m) {
        cin.ignore(256, '\n');
        int flag = 0;
        map<pair<pair<int, int>, pair<string, string>>, int> cache;
        for (int i = 1; i <= n; i++) {
            getline(cin, line);
            if (flag) continue;
            string block;
            vector<string> clns;
            for (char c : line) {
                if (c == ',') {
                    clns.push_back(block);
                    block.clear();
                } else block.push_back(c);
            }
            clns.push_back(block);
            for (int j = 0; !flag && j < clns.size(); j++)
                for (int k = j + 1; !flag && k < clns.size(); k++) {
                    pair<pair<int, int>, pair<string, string>> pr = make_pair(make_pair(j, k), make_pair(clns[j], clns[k]));
                    if (cache.find(pr) != cache.end()) {
                        flag = 1;
                        cout << "NO\n";
                        cout << cache[pr] << ' ' << i << '\n';
                        cout << j + 1 << ' ' << k + 1 << '\n';
                    } else cache[pr] = i;
                }
        }
        if (!flag) cout << "YES\n";
    }
    return 0;
}
