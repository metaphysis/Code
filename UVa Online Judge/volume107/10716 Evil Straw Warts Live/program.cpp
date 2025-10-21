// Evil Straw Warts Live
// UVa ID: 10716
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int minSwapsToPalindrome(string s) {
    int n = s.length();
    vector<int> count(26, 0);
    for (char c : s) {
        count[c - 'a']++;
    }
    // 检查是否可以构成回文
    int oddCount = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 != 0) {
            oddCount++;
        }
    }
    if ((n % 2 == 0 && oddCount > 0) || (n % 2 == 1 && oddCount != 1)) {
        return -1;
    }
    int swaps = 0;
    int l = 0, r = n - 1;
    while (l < r) {
        // 在 [l, r] 中寻找与 s[l] 匹配的字符
        int k = r;
        while (k > l && s[k] != s[l]) {
            k--;
        }
        if (k == l) {
            // 没有找到匹配，这个字符应该是中心字符
            // 交换一次，把它向右移动一位
            swap(s[l], s[l + 1]);
            swaps++;
            continue;
        } else {
            // 把 s[k] 移动到 s[r] 的位置
            for (int i = k; i < r; i++) {
                swap(s[i], s[i + 1]);
                swaps++;
            }
            l++;
            r--;
        }
    }
    return swaps;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int result = minSwapsToPalindrome(s);
        if (result == -1) {
            cout << "Impossible" << endl;
        } else {
            cout << result << endl;
        }
    }
    return 0;
}
