// Bulk Mailing
// UVa ID: 643
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算最多能组成的捆内信件数和捆数，返回 {letters_in_bundles, bundle_count}
pair<int, int> computeBundle(int n) {
    if (n < 10) return {0, 0};
    int k = n / 15;
    int r = n % 15;
    if (r == 0) return {n, k};
    if (n >= 10 * (k + 1)) return {n, k + 1};
    return {15 * k, k};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, int> countMap;                // 有效邮编 -> 总出现次数
    vector<string> invalidList;               // 按出现顺序去重存储无效邮编
    unordered_set<string> invalidSet;

    string token;
    while (cin >> token) {
        bool valid = true;
        if (token.length() != 5) valid = false;
        else {
            bool allZero = true;
            for (char c : token) {
                if (c < '0' || c > '9') { valid = false; break; }
                if (c != '0') allZero = false;
            }
            if (valid && allZero) valid = false;    // 全 0 无效
        }
        if (valid) {
            countMap[token]++;
        } else {
            if (invalidSet.find(token) == invalidSet.end()) {
                invalidSet.insert(token);
                invalidList.push_back(token);
            }
        }
    }

    // 有效邮编升序排列
    vector<string> validZips;
    for (auto &p : countMap) validZips.push_back(p.first);
    sort(validZips.begin(), validZips.end());

    // 存储 5 位捆结果：zip, letters, bundles
    vector<tuple<string, int, int>> fiveBundles;
    // 按前缀分组：prefix -> vector of (zip, remaining)
    map<string, vector<pair<string, int>>> prefixRemMap;
    int totalLetters = 0;
    int totalBundles = 0;

    for (const string &zip : validZips) {
        int cnt = countMap[zip];
        totalLetters += cnt;
        auto [t5, b5] = computeBundle(cnt);
        if (b5 > 0) {
            fiveBundles.emplace_back(zip, t5, b5);
            totalBundles += b5;
        }
        int rem = cnt - t5;
        if (rem > 0) {
            string prefix = zip.substr(0, 3);
            prefixRemMap[prefix].push_back({zip, rem});
        }
    }

    // 存储 3 位捆结果：prefix, letters, bundles
    vector<tuple<string, int, int>> threeBundles;
    map<string, int> firstClassMap;   // 最终 first class 信件：zip -> count

    for (auto &entry : prefixRemMap) {
        string prefix = entry.first;
        auto &vec = entry.second;
        // 按邮编升序排序
        sort(vec.begin(), vec.end(), [](const pair<string,int> &a, const pair<string,int> &b){
            return a.first < b.first;
        });

        int totalRem = 0;
        for (auto &p : vec) totalRem += p.second;

        auto [t3, b3] = computeBundle(totalRem);
        if (b3 > 0) {
            threeBundles.emplace_back(prefix, t3, b3);
            totalBundles += b3;
        }

        // 从低邮编依次取 t3 封信组成 3 位捆，剩下的归入 firstClass
        int need = t3;
        for (auto &p : vec) {
            int &rem = p.second;
            if (rem == 0) continue;
            if (need > 0) {
                int take = min(rem, need);
                rem -= take;
                need -= take;
            }
            if (rem > 0) {
                firstClassMap[p.first] += rem;
            }
        }
    }

    // ---------- 输出报告（严格按给定格式） ----------
    // 表头，列宽：ZIP 左对齐 8，LETTERS 右对齐 10，BUNDLES 右对齐 8
    cout << left << setw(8) << "ZIP"
         << right << setw(11) << "LETTERS"
         << setw(12) << "BUNDLES" << "\n";
    cout << "\n";   // 标题后空行

    // 5 位捆
    if (!fiveBundles.empty()) {
        for (auto &t : fiveBundles) {
            string zip; int letters, bundles;
            tie(zip, letters, bundles) = t;
            cout << left << setw(8) << zip
                 << right << setw(8) << letters
                 << setw(12) << bundles << "\n";
        }
        cout << "\n";   // 组间空行
    }

    // 3 位捆
    if (!threeBundles.empty()) {
        for (auto &t : threeBundles) {
            string prefix; int letters, bundles;
            tie(prefix, letters, bundles) = t;
            cout << left << setw(8) << (prefix + "xx")
                 << right << setw(8) << letters
                 << setw(12) << bundles << "\n";
        }
        cout << "\n";   // 组间空行
    }

    // first class
    if (!firstClassMap.empty()) {
        for (auto &p : firstClassMap) {
            cout << left << setw(8) << p.first
                 << right << setw(8) << p.second
                 << setw(12) << 0 << "\n";
        }
        cout << "\n";   // 总计前空行
    }

    // 总计
    cout << left << setw(8) << "TOTALS"
         << right << setw(8) << totalLetters
         << setw(12) << totalBundles << "\n";
    cout << '\n';

    // 无效邮编，每个占一行
    cout << "INVALID ZIP CODES\n";
    for (const string &inv : invalidList) cout << inv << "\n";

    return 0;
}
