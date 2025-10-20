// Chinese Mahjong
// UVa ID: 11210
// Verdict: Accepted
// Submission Date: 2025-10-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 牌型映射表
string tiles[34] = {
    "1T", "2T", "3T", "4T", "5T", "6T", "7T", "8T", "9T",
    "1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S",
    "1W", "2W", "3W", "4W", "5W", "6W", "7W", "8W", "9W",
    "DONG", "NAN", "XI", "BEI", "ZHONG", "FA", "BAI"
};

map<string, int> tileToId;  // 牌名到编号的映射

// 初始化牌名映射表
void initializeMap() { for (int i = 0; i < 34; i++) tileToId[tiles[i]] = i; }

// 递归判断剩下的牌能否组成指定数量的面子
bool canMeld(int hand[], int meldsNeeded) {
    if (meldsNeeded == 0) return true;  // 所有面子都已组成
    
    // 尝试碰（三张相同的牌）
    for (int i = 0; i < 34; i++) {
        if (hand[i] >= 3) {
            hand[i] -= 3;
            if (canMeld(hand, meldsNeeded - 1)) {
                hand[i] += 3;
                return true;
            }
            hand[i] += 3;
        }
    }
    
    // 尝试吃（三张同花色连续数字牌）
    for (int i = 0; i <= 24; i++) {  // 只考虑筒子、条子、万子
        if (i % 9 <= 6 && hand[i] >= 1 && hand[i + 1] >= 1 && hand[i + 2] >= 1) {
            hand[i]--; hand[i + 1]--; hand[i + 2]--;
            if (canMeld(hand, meldsNeeded - 1)) {
                hand[i]++; hand[i + 1]++; hand[i + 2]++;
                return true;
            }
            hand[i]++; hand[i + 1]++; hand[i + 2]++;
        }
    }
    
    return false;
}

// 判断当前 14 张牌是否能胡牌
bool canWin(int hand[]) {
    // 枚举所有可能的眼（一对）
    for (int i = 0; i < 34; i++) {
        if (hand[i] >= 2) {
            hand[i] -= 2;  // 取出眼
            if (canMeld(hand, 4)) {  // 判断剩下的 12 张牌能否组成 4 个面子
                hand[i] += 2;
                return true;
            }
            hand[i] += 2;
        }
    }
    return false;
}

int main() {
    initializeMap();  // 初始化牌名映射
    
    string tile;
    int caseNo = 1;
    
    while (true) {
        vector<string> handStr(13);  // 存储输入的 13 张牌
        for (int i = 0; i < 13; i++) {
            cin >> handStr[i];
            if (handStr[i] == "0") return 0;  // 遇到 0 结束程序
        }
        
        int hand[34] = {0};  // 手牌统计数组
        for (const string& t : handStr) hand[tileToId[t]]++;  // 统计每种牌的数量
        
        vector<int> waiting;  // 存储听牌列表
        for (int i = 0; i < 34; i++) {
            if (hand[i] >= 4) continue;  // 该牌已满 4 张，不能再加
            hand[i]++;  // 尝试加入这张牌
            if (canWin(hand)) waiting.push_back(i);  // 如果能胡牌，加入听牌列表
            hand[i]--;  // 回溯
        }
        
        // 输出结果
        cout << "Case " << caseNo++ << ":";
        if (waiting.empty()) {
            cout << " Not ready" << '\n';
        } else {
            for (int id : waiting) cout << " " << tiles[id];  // 输出听牌名称
            cout << '\n';
        }
    }
    
    return 0;
}
