// Educational Journey
// UVa ID: 10995
// Verdict: Accepted
// Submission Date: 2026-01-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 将时间字符串转换为秒数
int timeToSeconds(const string& t) {
    int h, m, s;
    sscanf(t.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

// 将秒数转换为时间字符串，四舍五入到整数秒
string secondsToTime(double sec) {
    sec = round(sec);
    int total = (int)sec;
    int h = total / 3600;
    int m = (total % 3600) / 60;
    int s = total % 60;
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", h, m, s);
    return string(buf);
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line == "-1") break;
        
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (ss >> token) tokens.push_back(token);
        
        if (tokens.size() != 5) continue;
        
        // 转换为秒
        double t1 = timeToSeconds(tokens[0]);  // A passed C
        double t2 = timeToSeconds(tokens[1]);  // A passed M
        double t3 = timeToSeconds(tokens[2]);  // A met D
        double t4 = timeToSeconds(tokens[3]);  // D met C
        double t5 = timeToSeconds(tokens[4]);  // D met M
        
        // 计算相对速度
        double vc = (t3 - t1) / (t4 - t1);
        double vm = (t3 - t2) / (t5 - t2);
        
        // 计算C追上M的时间
        double t_cm = t1 + (1.0 - vm) * (t2 - t1) / (vc - vm);
        
        // 输出结果
        cout << secondsToTime(t_cm) << endl;
    }
    return 0;
}
