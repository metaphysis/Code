// Life on Mars
// UVa ID: 11508
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    string inputLine;
    while (getline(cin, inputLine)) {
        // 检查结束条件
        if (inputLine == "0") break;
        
        istringstream inputStream(inputLine);
        vector<int> message;
        int number;
        
        // 读取消息序列
        while (inputStream >> number) {
            message.push_back(number);
        }
        
        int messageLength = message.size();
        bool isValid = true;
        
        // 检查是否存在大于等于数组长度的值
        for (int num : message) {
            if (num >= messageLength) {
                isValid = false;
                break;
            }
        }
        
        if (!isValid) {
            cout << "Message hacked by the Martians!!!" << endl;
            continue;
        }
        
        // 统计每个数字的出现频率
        vector<int> frequency(messageLength, 0);
        for (int num : message) {
            frequency[num]++;
        }
        
        // 初始化结果数组
        vector<int> resultArray(messageLength, -1);
        
        // 第一步：固定必要的位置
        for (int value = 0; value < messageLength; value++) {
            if (frequency[value] > 0) {
                resultArray[value] = value;
                frequency[value]--;
            }
        }
        
        // 第二步：填充剩余的数字
        for (int value = 0; value < messageLength; value++) {
            while (frequency[value] > 0) {
                // 找到空位置
                for (int position = 0; position < messageLength; position++) {
                    if (resultArray[position] == -1) {
                        resultArray[position] = value;
                        frequency[value]--;
                        break;
                    }
                }
            }
        }
        
        // 输出结果
        for (int i = 0; i < messageLength; i++) {
            if (i > 0) cout << " ";
            cout << resultArray[i];
        }
        cout << endl;
    }
    return 0;
}
