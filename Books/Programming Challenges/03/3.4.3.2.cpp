#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

int fail[MAXN] = {0};

void getFail1(string p) {
    p = '#' + p;
    fail[1] = 0;
    int i = 1, j = 0, m = p.length();
    while (i < m) {
        if (j == 0 || p[i] == p[j]) {
            i++, j++;
            fail[i] = j;
        } else j = fail[j];
    }
}

// 寻找第一次匹配
bool kmp1(string s, string p) {
    s = '#' + s, p = '#' + p;
    int i = 1, j = 1, n = s.length(), m = p.length();
    while (i < n) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j == m) {
            cout << "找到匹配，主串序号为：" << (i - j + 1) << '\n';
            return true;
        }
    }
    cout << "未找到匹配。\n";
    return false;
}

// 寻找所有匹配
void kmpAllMatch(string s, string p) {
    s = '#' + s, p = '#' + p;
    int i = 1, j = 1, n = s.length(), m = p.length();
    bool found = false;
    while (i < n) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j == m) {
            cout << "找到匹配，主串序号为：" << (i - j + 1) << '\n';
            j = fail[j];
            found = true;
        }
    }
    if (!found) cout << "未找到匹配。\n";
}

// 对失配函数进行优化
void getFail2(string p) {
    p = '#' + p;
    fail[1] = 0;
    int i = 1, j = 0, m = p.length();
    while (i < m) {
        if (j == 0 || p[i] == p[j]) {
            i++, j++;
            int k = j;
            while (k && p[i] == p[k]) k = fail[k];
            fail[i] = k;
        } else j = fail[j];
    }
}

bool kmp2(string s, string p) {
    int i = 0, j = 1, n = s.length(), m = p.length();
    while (i < n) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j == m) return true;
    }
    return false;
}

void getFail3(string &p) {
    fail[0] = -1;
    int i = 0, j = -1, m = p.length();
    while (i < m - 1) {
        if (j == -1 || p[i] == p[j]) {
            i++, j++;
            int k = j;
            while (k != -1 && p[i] == p[k]) k = fail[k];
            fail[i] = k;
        } else j = fail[j];
    }
}

bool kmp3(string &s, string &p) {
    int i = 0, j = 0, n = s.length(), m = p.length();
    while (i < n) {
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j == m) return true;
    }
    return false;
}

int main() {
    string t = "abcdefghijklmnAopqrstuvwxyzAabcdefghijklmnopqrstuvwxyzA", p = "A";
    cout << "主串：" << t << '\n';
    cout << "模式串：" << p << '\n';
    cout << "====================\n";
    cout << "从 1 开始计数字符，寻找第一次匹配。\n";
    {
        getFail1(p);
        cout << "失配函数：\n";
        for (int i = 1; i <= p.length(); i++)
            cout << "fail[" << i << "] = " << fail[i] << '\n';
        kmp1(t, p);
    }
    cout << "====================\n";
    cout << "从 1 开始计数字符，寻找所有匹配。\n";
    {
        getFail1(p);
        cout << "失配函数：\n";
        for (int i = 1; i <= p.length(); i++)
            cout << "fail[" << i << "] = " << fail[i] << '\n';
        kmpAllMatch(t, p);
    }
    return 0;
}
