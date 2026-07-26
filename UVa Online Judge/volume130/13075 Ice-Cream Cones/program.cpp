// Ice-Cream Cones
// UVa ID: 13075
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163173291

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int cCount, vCount;
        cin >> cCount >> vCount;
        string s(cCount, 'C');      // cCount 个 'C'
        s.append(vCount, 'V');      // 追加 vCount 个 'V'
        // 此时 s 已按字典序升序排列（'C' < 'V'）
        bool first = true;          // 标记是否为第一个配置，用于控制空格
        do {
            if (!first) cout << ' ';
            cout << s;
            first = false;
        } while (next_permutation(s.begin(), s.end()));
        cout << '\n';
    }
    return 0;
}
