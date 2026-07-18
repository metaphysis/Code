// Symbolic Numerical System
// UVa ID: 826
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 读取非空行（跳过空行）
string readNonEmptyLine() {
    string line;
    while (getline(cin, line)) {
        if (!line.empty()) return line;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    string dummy;
    getline(cin, dummy);  // 消耗第一行剩余换行符

    bool firstOutput = true;

    for (int tc = 0; tc < T; ++tc) {
        string A = readNonEmptyLine();
        string s1 = readNonEmptyLine();
        string s2 = readNonEmptyLine();
        string s3 = readNonEmptyLine();

        unordered_map<char, int> pos;
        for (int i = 0; i < (int)A.size(); ++i) pos[A[i]] = i;

        // 收集候选基（按位置升序）
        vector<pair<int, char>> bases;
        for (char ch : A) {
            int p = pos[ch];
            if (p >= 2) bases.push_back({p, ch});
        }
        sort(bases.begin(), bases.end());

        bool found = false;
        string out1, out2, out3;
        char baseChar = 0;

        for (auto &pr : bases) {
            int base = pr.first;
            char bc = pr.second;

            // 检查所有已知数字的位是否均小于基值
            bool valid = true;
            auto checkDigits = [&](const string& s) {
                for (char c : s) {
                    if (c == '?') continue;
                    if (pos[c] >= base) { valid = false; break; }
                }
            };
            checkDigits(s1);
            if (!valid) continue;
            checkDigits(s2);
            if (!valid) continue;
            checkDigits(s3);
            if (!valid) continue;

            int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
            int maxLen = max(max(len1, len2), len3);

            string tmp1 = s1, tmp2 = s2, tmp3 = s3;
            bool memo[75][2] = {};
            bool ok = false;

            function<bool(int,int)> dfs = [&](int idx, int carry) -> bool {
                if (idx == maxLen) return carry == 0;
                if (memo[idx][carry]) return false;

                // 获取该位字符（不存在则视为 '\0'）
                char c1 = (idx < len1) ? s1[len1 - 1 - idx] : '\0';
                char c2 = (idx < len2) ? s2[len2 - 1 - idx] : '\0';
                char c3 = (idx < len3) ? s3[len3 - 1 - idx] : '\0';

                int v1 = 0, v2 = 0, v3 = 0;
                bool unk1 = false, unk2 = false, unk3 = false;

                if (c1 == '\0') v1 = 0;
                else if (c1 == '?') unk1 = true;
                else v1 = pos[c1];

                if (c2 == '\0') v2 = 0;
                else if (c2 == '?') unk2 = true;
                else v2 = pos[c2];

                if (c3 == '\0') v3 = 0;
                else if (c3 == '?') unk3 = true;
                else v3 = pos[c3];

                // 尝试两种可能的进位
                for (int newCarry = 0; newCarry <= 1; ++newCarry) {
                    int x = -1;

                    if (unk1) {
                        x = v3 + base * newCarry - v2 - carry;
                        if (x >= 0 && x < base) {
                            tmp1[len1 - 1 - idx] = A[x];
                            if (dfs(idx + 1, newCarry)) return true;
                            tmp1[len1 - 1 - idx] = '?';
                        }
                    } else if (unk2) {
                        x = v3 + base * newCarry - v1 - carry;
                        if (x >= 0 && x < base) {
                            tmp2[len2 - 1 - idx] = A[x];
                            if (dfs(idx + 1, newCarry)) return true;
                            tmp2[len2 - 1 - idx] = '?';
                        }
                    } else if (unk3) {
                        x = v1 + v2 + carry - base * newCarry;
                        if (x >= 0 && x < base) {
                            tmp3[len3 - 1 - idx] = A[x];
                            if (dfs(idx + 1, newCarry)) return true;
                            tmp3[len3 - 1 - idx] = '?';
                        }
                    } else {
                        if (v1 + v2 + carry == v3 + base * newCarry) {
                            if (dfs(idx + 1, newCarry)) return true;
                        }
                    }
                }

                memo[idx][carry] = true;
                return false;
            };

            ok = dfs(0, 0);
            if (ok) {
                found = true;
                baseChar = bc;
                out1 = tmp1;
                out2 = tmp2;
                out3 = tmp3;
                break;
            }
        }

        if (found) {
            if (!firstOutput) cout << "\n";
            firstOutput = false;
            cout << baseChar << "\n";
            cout << out1 << "\n";
            cout << out2 << "\n";
            cout << out3 << "\n";
        }
    }

    return 0;
}
