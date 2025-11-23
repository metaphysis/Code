// A Duckpin Tournament
// UVa ID: 600
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Player {
    string name;
    int totalScore = 0;
    int maxGameScore = 0;
};

vector<int> calculateGame(const string& line1, const string& line2, const string& line3) {
    stringstream combined(line1 + " Q " + line2 + " Q " + line3);
    vector<int> frameScores(10, 0), framePins(12, 0);
    vector<tuple<int, int, int, int>> throws; // (frame, attempt, score, totalPins)
    int currentFrame = 0, attemptType = 1;
    string token;
    while (combined >> token) {
        if (token == "Q") {
            attemptType++;
            currentFrame = 0;
            continue;
        }
        int score = stoi(token);
        // 跳过已经完成（全中/补中）的frame
        while (framePins[currentFrame] == 10) currentFrame++;
        // 更新frame的累计击倒数
        if (score < 0) framePins[currentFrame] = 10; // 犯规视为完成该frame
        else framePins[currentFrame] += score;
        throws.emplace_back(currentFrame, attemptType, score, framePins[currentFrame]);
        currentFrame++;
    }
    // 按frame排序投掷记录
    sort(throws.begin(), throws.end());
    // 计算每个frame的得分
    for (int i = 0; i < throws.size(); i++) {
        auto [frame, attempt, scoreVal, totalPins] = throws[i];
        if (frame >= 10) break; // 只处理前10个frame
        // 基础分（只计算正分）
        if (scoreVal >= 0) frameScores[frame] += scoreVal;
        // 计算奖励分
        int bonusAttempts = 0;
        if (scoreVal >= 0 && totalPins == 10) {
            if (attempt == 1) bonusAttempts = 2; // 第一次尝试全中
            else if (attempt == 2) bonusAttempts = 1; // 第二次尝试补中
        }
        // 添加奖励分
        for (int j = 1; j <= bonusAttempts; j++) {
            auto [nextFrame, nextAttempt, nextScore, nextTotal] = throws[i + j];
            if (nextScore >= 0) frameScores[frame] += nextScore;
            else break; // 遇到犯规停止奖励
        }
    }
    // 计算累计得分
    for (int i = 1; i < 10; i++) frameScores[i] += frameScores[i - 1];
    return frameScores;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n != 0) {
        vector<Player> players(n);
        for (int i = 0; i < n; i++) cin >> players[i].name;
        cin.ignore(128, '\n');
        vector<string> data;
        string line;
        // 读取所有比赛数据
        while (getline(cin, line)) {
            if (line.find('#') != string::npos) break;
            data.push_back(line);
        }
        // 处理每个选手的每局比赛
        for (int i = 0; i < data.size(); i += 3) {
            int playerIndex = (i / 3) % n;
            vector<int> scores = calculateGame(data[i], data[i + 1], data[i + 2]);
            // 格式化输出
            cout << left << setw(10) << players[playerIndex].name;
            for (int score : scores) cout << right << setw(4) << score;
            cout << endl;
            // 更新选手统计
            int gameScore = scores.back();
            players[playerIndex].totalScore += gameScore;
            players[playerIndex].maxGameScore = max(players[playerIndex].maxGameScore, gameScore);
        }
        // 确定获胜者
        int bestSeries = 0, bestGame = 0;
        string seriesWinner, gameWinner;
        for (const auto& player : players) {
            if (player.totalScore > bestSeries) {
                bestSeries = player.totalScore;
                seriesWinner = player.name;
            }
            if (player.maxGameScore > bestGame) {
                bestGame = player.maxGameScore;
                gameWinner = player.name;
            }
        }
        cout << seriesWinner << " has the high series score of " << bestSeries << "." << '\n';
        cout << gameWinner << " has the high game score of " << bestGame << "." << '\n';
        cout << '\n';
    }
    return 0;
}
