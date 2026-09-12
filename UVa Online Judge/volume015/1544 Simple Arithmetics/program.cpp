#include <bits/stdc++.h>
using namespace std;

vector<int> toVec(const string &str) {
    vector<int> v;
    int i;
    for (i = 0; i < (int)str.size(); i++) v.push_back(str[i] - '0');
    reverse(v.begin(), v.end());
    return v;
}

string toStr(const vector<int> &v) {
    string str;
    int i;
    for (i = 0; i < (int)v.size(); i++) str += char(v[i] + '0');
    reverse(str.begin(), str.end());
    return str;
}

void refine(vector<int> &v) {
    while (v.size() > 1 && v.back() == 0) v.pop_back();
}

vector<int> addNum(const vector<int> &v1, const vector<int> &v2) {
    vector<int> v(max(v1.size(), v2.size()) + 5, 0);
    int i;
    for (i = 0; i < (int)v1.size(); i++) v[i] += v1[i];
    for (i = 0; i < (int)v2.size(); i++) v[i] += v2[i];
    for (i = 0; i < (int)v.size() - 1; i++) {
        if (v[i] >= 10) {
            v[i + 1] += v[i] / 10;
            v[i] %= 10;
        }
    }
    refine(v);
    return v;
}

vector<int> subNum(const vector<int> &v1, const vector<int> &v2) {
    vector<int> v(max(v1.size(), v2.size()) + 5, 0);
    int i;
    for (i = 0; i < (int)v1.size(); i++) v[i] += v1[i];
    for (i = 0; i < (int)v2.size(); i++) v[i] -= v2[i];
    for (i = 0; i < (int)v.size() - 1; i++) {
        if (v[i] < 0) {
            v[i + 1]--;
            v[i] += 10;
        }
    }
    refine(v);
    return v;
}

vector<int> mulNum(const vector<int> &v1, int num) {
    vector<int> v = v1;
    v.push_back(0);
    for (int &x : v) x *= num;
    for (int i = 0; i < (int)v.size() - 1; i++) {
        if (v[i] >= 10) {
            v[i + 1] += v[i] / 10;
            v[i] %= 10;
        }
    }
    refine(v);
    return v;
}

vector<int> mulNum(const vector<int> &v1, const vector<int> &v2) {
    vector<int> v(v1.size() + v2.size() + 100, 0);
    int i, j;
    for (i = 0; i < (int)v1.size(); i++)
        for (j = 0; j < (int)v2.size(); j++) v[i + j] += v1[i] * v2[j];
    for (i = 0; i < (int)v.size() - 1; i++) {
        if (v[i] >= 10) {
            v[i + 1] += v[i] / 10;
            v[i] %= 10;
        }
    }
    refine(v);
    return v;
}

void printLine(const string &str, int maxV) {
    string s = str;
    int len = s.size();
    while (!s.empty() && s.back() == ' ') s.pop_back();
    cout << string(maxV - len, ' ') << s << '\n';
}

void solveAdd(const string &str) {
    int pos = str.find('+');
    if (pos == (int)string::npos) return;
    string s1 = str.substr(0, pos), s2 = str.substr(pos + 1);
    vector<int> v1 = toVec(s1), v2 = toVec(s2), v3 = addNum(v1, v2);
    string s3 = toStr(v3);
    s2 = "+" + s2;
    int maxLen = max(s2.size(), s3.size()), maxV = max({s1.size(), s2.size(), s3.size()});
    printLine(s1, maxV);
    printLine(s2, maxV);
    printLine(string(maxLen, '-'), maxV);
    printLine(s3, maxV);
}

void solveSub(const string &str) {
    int pos = str.find('-');
    if (pos == (int)string::npos) return;
    string s1 = str.substr(0, pos), s2 = str.substr(pos + 1);
    vector<int> v1 = toVec(s1), v2 = toVec(s2), v3 = subNum(v1, v2);
    string s3 = toStr(v3);
    s2 = "-" + s2;
    int maxLen = max(s2.size(), s3.size()), maxV = max({s1.size(), s2.size(), s3.size()});
    printLine(s1, maxV);
    printLine(s2, maxV);
    printLine(string(maxLen, '-'), maxV);
    printLine(s3, maxV);
}

void solveMul(const string &str) {
    int pos = str.find('*');
    if (pos == (int)string::npos) return;
    string s1 = str.substr(0, pos), s2 = str.substr(pos + 1);
    vector<int> v1 = toVec(s1), v2 = toVec(s2), ans = mulNum(v1, v2);
    string s3 = toStr(ans);
    vector<string> part;
    int i;
    for (i = 0; i < (int)v2.size(); i++) {
        string cur = toStr(mulNum(v1, v2[i])) + string(i, ' ');
        part.push_back(cur);
    }
    s2 = "*" + s2;
    int maxLen = max(s2.size(), part[0].size()), maxV = max({s1.size(), s2.size(), s3.size()});
    for (const string &s : part) maxV = max(maxV, (int)s.size());
    printLine(s1, maxV);
    printLine(s2, maxV);
    printLine(string(maxLen, '-'), maxV);
    for (const string &s : part) printLine(s, maxV);
    if (part.size() == 1) return;
    string line = string(max(part.back().size(), s3.size()), '-');
    printLine(line, maxV);
    printLine(s3, maxV);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int nCase;
    string str;
    cin >> nCase;
    while (nCase--) {
        cin >> str;
        solveAdd(str);
        solveSub(str);
        solveMul(str);
        cout << '\n';
    }
    return 0;
}
