// Triangles
// UVa ID: 12651
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<int> X(N);
        long long total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> X[i];
            total += X[i];
        }

        // 如果总周长不能被3整除，无法构造等边三角形
        if (total % 3 != 0) {
            cout << "0\n";
            continue;
        }

        // 计算前缀和
        vector<long long> prefix(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            prefix[i + 1] = prefix[i] + X[i];
        }

        // 将前缀和存入哈希集合，方便快速查找
        unordered_set<long long> prefixSet(prefix.begin(), prefix.end());

        long long third = total / 3;
        int count = 0;

        // 遍历每个起点
        for (int i = 0; i < N; ++i) {
            long long target1 = prefix[i] + third;
            long long target2 = prefix[i] + 2 * third;

            // 处理循环，取模 total
            if (target1 > total) target1 -= total;
            if (target2 > total) target2 -= total;

            // 如果两个目标位置都存在，则构成三角形
            if (prefixSet.count(target1) && prefixSet.count(target2)) {
                count++;
            }
        }

        // 每个三角形被三个起点各统计一次
        cout << count / 3 << "\n";
    }

    return 0;
}
