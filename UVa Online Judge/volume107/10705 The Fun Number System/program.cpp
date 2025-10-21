// The Fun Number System
// UVa ID: 10705
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;  // 读取测试用例数量
    while (t--) {
        int k;
        string type;
        long long N;
        cin >> k >> type >> N;  // 读取位数、权重类型和目标值
        
        vector<int> bits(k, 0);  // 存储结果的二进制位
        bool possible = true;    // 标记是否可表示
        
        // 从最低位(i=0)到最高位(i=k-1)处理
        for (int i = 0; i < k; i++) {
            if (N % 2 != 0) {    // 当前N为奇数，必须在该位放1
                bits[i] = 1;
                if (type[k - 1 - i] == 'p') {  // 正权重位
                    N = (N - 1) / 2;
                } else {  // 负权重位
                    N = (N + 1) / 2;
                }
            } else {             // 当前N为偶数，该位放0
                bits[i] = 0;
                N = N / 2;
            }
        }
        
        // 检查是否完全表示
        if (N != 0) {
            cout << "Impossible" << endl;
        } else {
            // 从高位到低位输出结果
            for (int i = k - 1; i >= 0; i--) {
                cout << bits[i];
            }
            cout << endl;
        }
    }
    return 0;
}
