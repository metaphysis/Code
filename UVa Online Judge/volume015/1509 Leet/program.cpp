// Leet
// UVa ID: 1509
// Verdict: Accepted
// Submission Date: 2026-05-23
// UVa Run Time: 0.590s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int T, k;
string eng, leet;
unordered_map<char, string> mp; // 英文字符 -> Leet映射
bool ok;

void dfs(int posEng, int posLeet) {
    if (ok) return; // 已经找到答案，提前返回
    if (posEng == eng.length() && posLeet == leet.length()) {
        ok = true; // 完全匹配成功
        return;
    }
    if (posEng >= eng.length() || posLeet >= leet.length()) return; // 边界越界

    char curChar = eng[posEng];
    if (mp.count(curChar)) { // 当前字符已有映射
        string& mapped = mp[curChar];
        if (leet.substr(posLeet, mapped.length()) == mapped)
            dfs(posEng + 1, posLeet + mapped.length());
    } else { // 当前字符无映射，尝试所有可能的映射长度
        for (int len = 1; len <= k; ++len) {
            if (posLeet + len > leet.length()) break; // 长度不够
            string candidate = leet.substr(posLeet, len);
            mp[curChar] = candidate; // 建立映射
            dfs(posEng + 1, posLeet + len);
            mp.erase(curChar); // 回溯，撤销映射
        }
    }
}

int main() {
    cin >> T;
    while (T--) {
        cin >> k >> eng >> leet;
        mp.clear();
        ok = false;
        dfs(0, 0);
        cout << (ok ? 1 : 0) << endl;
    }
    return 0;
}
