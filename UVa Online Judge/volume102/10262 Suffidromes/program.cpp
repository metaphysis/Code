// Suffidromes
// UVa ID: 10262
// Verdict: Accepted
// Submission Date: 2025-12-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool cmp(string a, string b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

// 判断回文
bool isPalindrome(const string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right)
        if (s[left++] != s[right--]) return false;
    return true;
}

// 获取所有可能的 x，使得 s+x 是回文
vector<string> getCandidates(const string& s) {
    vector<string> result;
    string ss = s;
    reverse(ss.begin(), ss.end());
    int n = ss.size();
    // 枚举分割点 i，如果 reversed[0..i] 是回文，那么可以取 reversed[i+1,n-1] 作为 x
    for (int i = -1; i < n; ++i) {
        string x = ss.substr(0, i + 1);
        if (isPalindrome(x)) result.push_back(ss.substr(i + 1));
    }
    // 增加一个字符，构成长度为奇数的回文
    for (char i = 'a'; i <= 'z'; i++) result.push_back(i + ss);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    while (getline(cin, a)) {
        getline(cin, b);
        // 两个字符串相等则不存在解
        if (a == b) {
            cout << "No solution.\n";
            continue;
        }
        if (a.size() > b.size()) swap(a, b);
        vector<string> A = getCandidates(a), B = getCandidates(b);
        for (auto s : B) A.push_back(s);
        sort(A.begin(), A.end(), cmp);
        A.erase(unique(A.begin(), A.end()));
        for (auto s : A)
            if (isPalindrome(a + s) && !isPalindrome(b + s) ||
                !isPalindrome(a + s) && isPalindrome(b + s)) {
                    cout << s << '\n';
                    break;
                }
    }
    return 0;
}
