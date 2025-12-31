// Spam or Not Spam
// UVa ID: 10476
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void process(unordered_map<string, int>& freq) {
    string line;
    while (getline(cin, line) && line != "ENDMESSAGE") {
        int len = line.length();
        for (int i = 0; i <= len - 3; ++i) {
            string trigram = line.substr(i, 3);
            ++freq[trigram];
        }
    }
}

// 计算两个频率映射之间的余弦相似度
double cosineSimilarity(const unordered_map<string, int>& f1, const unordered_map<string, int>& f2) {
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    // 计算点积
    for (const auto& p : f1) {
        auto it = f2.find(p.first);
        if (it != f2.end()) 
            dotProduct += p.second * it->second;
    }
    // 计算 f1 的范数平方
    for (const auto& p : f1) norm1 += p.second * p.second;
    // 计算 f2 的范数平方
    for (const auto& p : f2) norm2 += p.second * p.second;
    if (norm1 == 0.0 || norm2 == 0.0) return 0.0;
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

int main() {
    int s, n, c;
    int setNumber = 1;
    while (cin >> s >> n >> c && s) {
        // 读取垃圾邮件样本并合并频率
        unordered_map<string, int> spamFreq, nonSpamFreq;
        for (int i = 0; i < s; ++i) process(spamFreq);
        // 读取非垃圾邮件样本并合并频率
        for (int i = 0; i < n; ++i) process(nonSpamFreq);
        // 输出当前组编号
        cout << "Set " << setNumber++ << ":\n";
        // 处理待分类消息
        for (int i = 0; i < c; ++i) {
            unordered_map<string, int> messageFreq;
            process(messageFreq);
            // 计算相似度
            double simSpam = cosineSimilarity(messageFreq, spamFreq);
            double simNonSpam = cosineSimilarity(messageFreq, nonSpamFreq);
            // 输出相似度（保留五位小数）
            cout << fixed << setprecision(5) << simSpam << " " << simNonSpam << "\n";
            // 分类并输出结果
            if (simSpam > simNonSpam) cout << "spam\n";
            else cout << "non-spam\n";
        }
    }
    return 0;
}
