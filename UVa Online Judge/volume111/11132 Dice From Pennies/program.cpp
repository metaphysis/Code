// Dice From Pennies
// UVa ID: 11132
// Verdict: Accepted
// Submission Date: 2025-11-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// 计算模拟一个 s 面骰子需要的最少硬币数
int coinsNeeded(int sides) {
    int k = 0;
    while ((1 << k) < sides) {
        k++;
    }
    return k;
}

// 将硬币序列（H/T）转换为二进制数值（H=0, T=1）
int coinToValue(const string& coins, int start, int length) {
    int val = 0;
    for (int i = 0; i < length; i++) {
        val = (val << 1) | (coins[start + i] == 'T' ? 1 : 0);
    }
    return val;
}

// 模拟一次掷骰子
int simulateDie(const string& coins, int sides, int& index) {
    int k = coinsNeeded(sides);
    int n = coins.length();
    
    while (index + k <= n) {
        int val = coinToValue(coins, index, k);
        if (val < sides) {
            index += k;
            return val + 1;
        }
        // 跳过整个k个硬币，而不是只跳1个
        index += k;
    }
    return -1; // 硬币不够
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line == "0D0") break;
        
        // 解析骰子数量和面数
        int dPos = line.find('D');
        int numDice = stoi(line.substr(0, dPos));
        int sides = stoi(line.substr(dPos + 1));
        
        // 读取硬币序列
        getline(cin, line);
        
        int index = 0;
        int total = 0;
        bool valid = true;
        
        for (int i = 0; i < numDice; i++) {
            int result = simulateDie(line, sides, index);
            if (result == -1) {
                valid = false;
                break;
            }
            total += result;
        }
        
        if (valid) {
            cout << total << endl;
        } else {
            cout << -1 << endl;
        }
    }
    
    return 0;
}
