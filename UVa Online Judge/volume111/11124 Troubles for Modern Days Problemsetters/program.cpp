// Troubles for Modern Days Problemsetters
// UVa ID: 11124
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 解析一行命令，生成所有数字并追加到 nums 中
void parseAndGenerate(const string& line, vector<int>& nums) {
    size_t pos = 0;
    while (pos < line.size()) {
        size_t plus = line.find('+', pos);                 // 查找命令分隔符
        string cmd = line.substr(pos, plus - pos);         // 提取单个命令
        size_t lp = cmd.find('('), rp = cmd.find(')', lp);
        string args = cmd.substr(lp + 1, rp - lp - 1);     // 括号内的参数列表
        for (char& c : args) if (c == ',') c = ' ';        // 逗号转空格便于流读取
        stringstream ss(args);

        if (cmd.find("NList") == 0) {
            int n; ss >> n;
            for (int k = 0; k < n; ++k) { int val; ss >> val; nums.push_back(val); }
        } else if (cmd.find("IList") == 0) {
            int n; long long s, inc; ss >> n >> s >> inc;
            for (int k = 0; k < n; ++k) nums.push_back((int)(s + inc * k));
        } else if (cmd.find("RList") == 0) {
            int n; long long l, h; unsigned long long seed;
            ss >> n >> l >> h >> seed;
            unsigned int seed32 = (unsigned int)(seed & 0xFFFFFFFFULL);
            long long range = h - l + 1;                   // 可能大于 2^31，用 long long
            for (int k = 0; k < n; ++k) {
                seed32 = (unsigned int)((seed32 * 17ULL + 11ULL) & 0xFFFFFFFFULL);
                nums.push_back((int)(l + (seed32 % range)));
            }
        }
        pos = (plus == string::npos) ? line.size() : plus + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int i, caseNo = 1;
    string line;
    while (cin >> i) {
        if (i == 0) break;
        getline(cin, line);   // 消耗第一行末尾的换行符
        getline(cin, line);   // 读取实际的命令行
        vector<int> nums;
        nums.reserve(1000000);
        parseAndGenerate(line, nums);
        nth_element(nums.begin(), nums.begin() + i - 1, nums.end());
        cout << "Case " << caseNo++ << ": " << nums[i - 1] << "\n";
    }
    return 0;
}
