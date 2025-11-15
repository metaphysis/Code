// Triples
// UVa ID: 11386
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 2.170s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int numCount;
    // 循环读取输入直到 EOF
    while (cin >> numCount) {
        vector<int> numbers(numCount);
        unordered_map<int, long long> frequency;
        
        // 读取数字并统计频率
        for (int i = 0; i < numCount; i++) {
            cin >> numbers[i];
            frequency[numbers[i]]++;
        }
        
        // 获取唯一数字并排序
        vector<int> uniqueNumbers;
        for (auto& pair : frequency) {
            uniqueNumbers.push_back(pair.first);
        }
        sort(uniqueNumbers.begin(), uniqueNumbers.end());
        
        long long totalTriples = 0;
        int uniqueCount = uniqueNumbers.size();
        
        // 枚举所有可能的数值对 (x, y)
        for (int i = 0; i < uniqueCount; i++) {
            int x = uniqueNumbers[i];
            for (int j = i; j < uniqueCount; j++) {
                int y = uniqueNumbers[j];
                int z = x + y;
                
                // 检查 z 是否存在于序列中
                if (frequency.count(z)) {
                    if (x == y) {
                        // x 和 y 相同的情况：组合数 C(freq[x], 2)
                        long long combination = frequency[x] * (frequency[x] - 1) / 2;
                        totalTriples += combination * frequency[z];
                    } else {
                        // x 和 y 不同的情况：直接相乘
                        totalTriples += frequency[x] * frequency[y] * frequency[z];
                    }
                }
            }
        }
        
        cout << totalTriples << "\n";
    }
    
    return 0;
}
