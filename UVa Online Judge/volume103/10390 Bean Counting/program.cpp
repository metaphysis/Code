// Bean Counting
// UVa ID: 10390
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Contestant {
    int offOne;
    int rightOn;
    Contestant() : offOne(0), rightOn(0) {}
};

int main() {
    int testCases;
    cin >> testCases;
    cin.ignore(1024, '\n'); // 忽略第一行后的换行
    cin.ignore(1024, '\n'); // 忽略第二行的空行
    
    for (int caseNum = 0; caseNum < testCases; ++caseNum) {
        if (caseNum > 0) {
            cout << endl; // 测试用例间空行
        }

        string beans;
        getline(cin, beans); // 读取豆子字符串
        
        // 统计每种豆子的实际数量
        map<char, int> actualCount;
        for (char c : beans) {
            actualCount[c]++;
        }

        map<char, Contestant> contestants;
        int totalGuesses = 0;

        string line;
        while (getline(cin, line)) {
            if (line.empty()) break; // 空行表示当前用例结束
            istringstream iss(line);
            char player;
            iss >> player;
            
            string guesses;
            getline(iss, guesses); // 读取剩余部分
            istringstream guessStream(guesses);

            string pair;
            while (getline(guessStream, pair, ',')) {
                char type;
                int guess;
                char colon;
                istringstream pairStream(pair);
                pairStream >> type >> colon >> guess;
                totalGuesses++;
                int actual = actualCount[type];
                int diff = abs(actual - guess);
                if (diff == 0) {
                    contestants[player].rightOn++;
                } else if (diff == 1) {
                    contestants[player].offOne++;
                }
            }
        }

        // 计算总份额
        double totalShares = 0.0;
        for (const auto& entry : contestants) {
            totalShares += entry.second.offOne + 2 * entry.second.rightOn;
        }

        // 计算每人奖金
        double pot = totalGuesses * 2.0;
        vector<pair<char, double>> results;
        for (const auto& entry : contestants) {
            double shares = entry.second.offOne + 2 * entry.second.rightOn;
            double winnings = (pot / totalShares) * shares;
            results.push_back({entry.first, winnings});
        }

        // 按字母顺序排序并输出
        sort(results.begin(), results.end());
        for (const auto& res : results) {
            cout << res.first << " " << fixed << setprecision(2) << res.second << endl;
        }
    }

    return 0;
}
