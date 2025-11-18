// Help
// UVa ID: 10728
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool isPlaceholder(const string& s) {
    return s.length() > 2 && s[0] == '<' && s.back() == '>';
}

vector<string> split(const string& s) {
    vector<string> res;
    stringstream ss(s);
    string token;
    while (ss >> token) {
        res.push_back(token);
    }
    return res;
}

string solve(const string& p1, const string& p2) {
    vector<string> a = split(p1);
    vector<string> b = split(p2);
    if (a.size() != b.size()) return "-";

    int n = a.size();
    
    // 为每个模式分别建立映射
    map<string, string> bindA, bindB;
    
    // 第一遍：处理单词约束
    for (int i = 0; i < n; i++) {
        string s1 = a[i];
        string s2 = b[i];
        bool ph1 = isPlaceholder(s1);
        bool ph2 = isPlaceholder(s2);
        
        if (!ph1 && !ph2) {
            // 两个都是单词，必须相同
            if (s1 != s2) return "-";
        } else if (ph1 && !ph2) {
            // s1是占位符，s2是单词
            if (bindA.count(s1) && bindA[s1] != s2) return "-";
            bindA[s1] = s2;
        } else if (!ph1 && ph2) {
            // s1是单词，s2是占位符
            if (bindB.count(s2) && bindB[s2] != s1) return "-";
            bindB[s2] = s1;
        }
        // 两个都是占位符：暂时没有约束
    }
    
    // 第二遍：传播约束
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < n; i++) {
            string s1 = a[i];
            string s2 = b[i];
            bool ph1 = isPlaceholder(s1);
            bool ph2 = isPlaceholder(s2);
            
            if (ph1 && ph2) {
                // 如果s1已经映射到某个单词
                if (bindA.count(s1) && !bindB.count(s2)) {
                    bindB[s2] = bindA[s1];
                    changed = true;
                }
                // 如果s2已经映射到某个单词
                if (bindB.count(s2) && !bindA.count(s1)) {
                    bindA[s1] = bindB[s2];
                    changed = true;
                }
                // 如果两个都映射了但不同
                if (bindA.count(s1) && bindB.count(s2) && bindA[s1] != bindB[s2]) {
                    return "-";
                }
            }
        }
    } while (changed);
    
    // 生成最终短语（使用第一个模式）
    vector<string> result;
    for (int i = 0; i < n; i++) {
        if (isPlaceholder(a[i])) {
            if (bindA.count(a[i])) {
                result.push_back(bindA[a[i]]);
            } else {
                // 未约束的占位符可以任意赋值，这里用"x"
                result.push_back("x");
            }
        } else {
            result.push_back(a[i]);
        }
    }
    
    // 验证生成的短语是否匹配第二个模式
    for (int i = 0; i < n; i++) {
        if (isPlaceholder(b[i])) {
            if (bindB.count(b[i]) && bindB[b[i]] != result[i]) {
                return "-";
            }
        } else {
            if (b[i] != result[i]) {
                return "-";
            }
        }
    }
    
    // 输出结果
    string output;
    for (int i = 0; i < n; i++) {
        if (i > 0) output += " ";
        output += result[i];
    }
    return output;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string p1, p2;
        getline(cin, p1);
        getline(cin, p2);
        cout << solve(p1, p2) << endl;
    }
    return 0;
}
