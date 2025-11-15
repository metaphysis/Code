// Generating Permutations
// UVa ID: 11925
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
    int n;
    // 处理多个测试用例，直到输入 0
    while (cin >> n && n != 0) {
        vector<int> targetArr(n);
        // 读入目标排列
        for (int i = 0; i < n; i++) {
            cin >> targetArr[i];
        }
        
        // 使用双端队列存储当前排列，便于两端操作
        deque<int> currentDeque(targetArr.begin(), targetArr.end());
        string reverseOperations;
        
        // 逆向操作直到排列变为 [1, 2, ..., n]
        while (true) {
            // 检查当前排列是否已经有序
            bool isSorted = true;
            for (int i = 0; i < n; i++) {
                if (currentDeque[i] != i + 1) {
                    isSorted = false;
                    break;
                }
            }
            if (isSorted) break;
            
            // 逆向操作规则：
            // 如果第一个元素大于第二个元素，且不是特殊情况 (n, 1)，则交换
            if (currentDeque[0] > currentDeque[1] && !(currentDeque[0] == n && currentDeque[1] == 1)) {
                swap(currentDeque[0], currentDeque[1]);
                reverseOperations += '1';
            } else {
                // 否则将最后一个元素移到前面
                int lastElement = currentDeque.back();
                currentDeque.pop_back();
                currentDeque.push_front(lastElement);
                reverseOperations += '2';
            }
        }
        
        // 反转操作序列得到正向操作序列
        reverse(reverseOperations.begin(), reverseOperations.end());
        cout << reverseOperations << "\n";
    }
    return 0;
}
