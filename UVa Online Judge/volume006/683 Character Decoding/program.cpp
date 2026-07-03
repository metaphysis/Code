// Character Decoding
// UVa ID: 683
// Verdict: Accepted
// Submission Date: 2026-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 解析一个项，返回系数映射和常数，同时收集字母到 letters 集合
pair<unordered_map<char, ll>, ll> parseTerm(const string& s, set<char>& letters) {
    unordered_map<char, ll> mp;
    ll constVal = 0;
    ll weight = 1;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            mp[c] += weight;
            letters.insert(c);
        } else {
            constVal += (c - '0') * weight;
        }
        weight *= 10;
    }
    return {mp, constVal};
}

// 求解单个表达式，返回最小左边项值，无解返回 -1
ll solveExpression(const string& expr) {
    // 去掉所有空白字符
    string s;
    for (char c : expr) if (c != ' ' && c != '\t') s.push_back(c);
    if (s.empty()) return -1;

    size_t eqPos = s.find('=');
    string left = s.substr(0, eqPos);
    string right = s.substr(eqPos + 1);

    set<char> allLettersSet;
    set<char> firstLetters;   // 所有项的首字母（不能为0）

    // 解析左边项
    auto leftRes = parseTerm(left, allLettersSet);
    unordered_map<char, ll> leftCoeff = leftRes.first;
    ll leftConst = leftRes.second;
    if (left[0] >= 'A' && left[0] <= 'Z') firstLetters.insert(left[0]);

    // 解析右边，按 '+' 和 '-' 分割
    vector<string> rightTerms;
    vector<char> rightSigns;
    int i = 0;
    while (i < (int)right.size()) {
        char sign = '+';
        if (right[i] == '+' || right[i] == '-') {
            sign = right[i];
            ++i;
        }
        int start = i;
        while (i < (int)right.size() && right[i] != '+' && right[i] != '-') ++i;
        string term = right.substr(start, i - start);
        rightTerms.push_back(term);
        rightSigns.push_back(sign);
    }

    // 总系数 = 左边系数 - 右边 '+' 项系数 + 右边 '-' 项系数
    // 总常数 = 左边常数 - 右边 '+' 项常数 + 右边 '-' 项常数
    unordered_map<char, ll> totalCoeff = leftCoeff;
    ll totalConst = leftConst;

    for (size_t j = 0; j < rightTerms.size(); ++j) {
        auto termRes = parseTerm(rightTerms[j], allLettersSet);
        unordered_map<char, ll> termCoeff = termRes.first;
        ll termConst = termRes.second;
        if (rightSigns[j] == '+') {
            for (auto& p : termCoeff) totalCoeff[p.first] -= p.second;
            totalConst -= termConst;
        } else { // '-'
            for (auto& p : termCoeff) totalCoeff[p.first] += p.second;
            totalConst += termConst;
        }
        // 记录该项的首字母
        if (rightTerms[j][0] >= 'A' && rightTerms[j][0] <= 'Z')
            firstLetters.insert(rightTerms[j][0]);
    }

    // 所有字母列表
    vector<char> letters(allLettersSet.begin(), allLettersSet.end());
    int n = (int)letters.size();

    // 检查是否所有字母系数均为0
    bool allZero = true;
    for (auto& p : totalCoeff) if (p.second != 0) { allZero = false; break; }
    if (allZero) {
        if (totalConst != 0) return -1;          // 矛盾，无解
        // 恒等，每个字母取允许的最小值（首位为1，否则0）使左边项最小
        ll leftVal = leftConst;
        for (auto& p : leftCoeff) {
            char ch = p.first;
            ll coeff = p.second;
            int minVal = (firstLetters.count(ch) ? 1 : 0);
            leftVal += coeff * minVal;
        }
        return leftVal;
    }

    // 选择系数绝对值最大的字母作为被解变量
    char idxLetter = letters[0];
    ll idxCoeff = totalCoeff[idxLetter];
    for (char ch : letters) {
        if (llabs(totalCoeff[ch]) > llabs(idxCoeff)) {
            idxCoeff = totalCoeff[ch];
            idxLetter = ch;
        }
    }

    // 构建其他变量列表，按系数绝对值降序排序（增强剪枝）
    vector<char> otherLetters;
    vector<ll> otherCoeffs;
    for (char ch : letters) {
        if (ch != idxLetter) {
            otherLetters.push_back(ch);
            otherCoeffs.push_back(totalCoeff[ch]);
        }
    }
    // 按系数绝对值降序
    vector<int> order(otherLetters.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return llabs(otherCoeffs[a]) > llabs(otherCoeffs[b]);
    });
    vector<char> sortedOther;
    vector<ll> sortedCoeff;
    for (int idx : order) {
        sortedOther.push_back(otherLetters[idx]);
        sortedCoeff.push_back(otherCoeffs[idx]);
    }
    otherLetters = sortedOther;
    otherCoeffs = sortedCoeff;

    int m = (int)otherLetters.size();

    // 后缀最大最小贡献（不含被解变量）
    vector<ll> maxSuffix(m + 1, 0), minSuffix(m + 1, 0);
    for (int i = m - 1; i >= 0; --i) {
        ll c = otherCoeffs[i];
        ll maxAdd = (c > 0 ? c * 9 : 0);
        ll minAdd = (c < 0 ? c * 9 : 0);   // 负数乘9最小
        maxSuffix[i] = maxSuffix[i + 1] + maxAdd;
        minSuffix[i] = minSuffix[i + 1] + minAdd;
    }

    // 字母到索引的映射
    unordered_map<char, int> letterIndex;
    for (int i = 0; i < n; ++i) letterIndex[letters[i]] = i;

    ll ans = LLONG_MAX;

    // 深度优先搜索，pos 表示已枚举的 otherLetters 个数，cur 为已赋值部分加权和
    function<void(int, ll, vector<int>&)> dfs = [&](int pos, ll cur, vector<int>& val) {
        if (pos == m) {
            // 所有其他变量已赋值，计算被解变量的值
            ll total = totalConst + cur;   // const + sum(otherCoeff * val)
            if (total % idxCoeff != 0) return;
            ll vIdx = -total / idxCoeff;
            if (vIdx < 0 || vIdx > 9) return;
            if (firstLetters.count(idxLetter) && vIdx == 0) return;
            int idxPos = letterIndex[idxLetter];
            val[idxPos] = (int)vIdx;

            // 计算左边项的值
            ll leftVal = leftConst;
            for (auto& p : leftCoeff) {
                char ch = p.first;
                ll coeff = p.second;
                leftVal += coeff * val[letterIndex[ch]];
            }
            ans = min(ans, leftVal);
            return;
        }

        char ch = otherLetters[pos];
        ll c = otherCoeffs[pos];
        for (int v = 0; v <= 9; ++v) {
            if (firstLetters.count(ch) && v == 0) continue;   // 首位字母不可为0
            ll newCur = cur + c * v;

            // 剪枝：判断剩余变量能否使被解变量落在 [0,9]
            ll low = totalConst + newCur + minSuffix[pos + 1];
            ll high = totalConst + newCur + maxSuffix[pos + 1];
            bool ok = false;
            int startV = (firstLetters.count(idxLetter) ? 1 : 0);
            for (int vv = startV; vv <= 9; ++vv) {
                ll target = -idxCoeff * vv;
                if (target >= low && target <= high) { ok = true; break; }
            }
            if (!ok) continue;

            val[letterIndex[ch]] = v;
            dfs(pos + 1, newCur, val);
            // 无需恢复 val，后续会覆盖
        }
    };

    vector<int> val(n, 0);   // 每个字母的取值
    dfs(0, 0, val);

    return (ans == LLONG_MAX ? -1 : ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        // 去除空白
        string s;
        for (char c : line) if (c != ' ' && c != '\t') s.push_back(c);
        if (s == "*") break;
        if (s.empty()) continue;

        ll res = solveExpression(s);
        if (res == -1) cout << "?\n";
        else cout << res << '\n';
    }
    return 0;
}
