// Tobby and the LED Display
// UVa ID: 13097
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long displaySize, timeMinutes;
    char direction;
    
    while (cin >> displaySize >> timeMinutes >> direction) {
        cin.ignore(); // 忽略换行符
        
        string topBorder, middleLine, bottomBorder;
        getline(cin, topBorder);
        getline(cin, middleLine);
        getline(cin, bottomBorder);
        
        // 提取初始字符（位于奇数索引位置）
        vector<char> initialChars(displaySize);
        for (int i = 0; i < displaySize; i++) {
            initialChars[i] = middleLine[2 * i + 1];
        }
        
        // 计算有效移位次数
        long long shiftAmount = timeMinutes % displaySize;
        vector<char> newChars(displaySize);
        
        if (direction == 'R') {
            // 向右移动：字符来自初始位置的 (j - shiftAmount + N) % N
            for (int j = 0; j < displaySize; j++) {
                int sourceIndex = (j - shiftAmount + displaySize) % displaySize;
                newChars[j] = initialChars[sourceIndex];
            }
        } else { // direction == 'L'
            // 向左移动：字符来自初始位置的 (j + shiftAmount) % N
            for (int j = 0; j < displaySize; j++) {
                int sourceIndex = (j + shiftAmount) % displaySize;
                newChars[j] = initialChars[sourceIndex];
            }
        }
        
        // 构建新的中间行
        string newMiddleLine = middleLine;
        for (int i = 0; i < displaySize; i++) {
            newMiddleLine[2 * i + 1] = newChars[i];
        }
        
        // 输出结果
        cout << topBorder << "\n";
        cout << newMiddleLine << "\n";
        cout << bottomBorder << "\n";
    }
    
    return 0;
}
