// Working With Specific Gravity
// UVa ID: 10434
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    const double pi = acos(-1.0);
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        double W = 0, D = 0, h = -1, SG = -1;
        bool hasH = false, hasSG = false;
        
        // 读取三行输入，每行包含一个参数
        std::vector<string> lines;
        lines.push_back(line);
        for (int i = 2; i <= 3; i++) {
            getline(cin, line);
            lines.push_back(line);
        }
        
        // 解析三行参数
        for (int i = 0; i < 3; i++) {
            string token = lines[i];
            if (token.find("W=") == 0) {
                W = stod(token.substr(2));
            } else if (token.find("D=") == 0) {
                D = stod(token.substr(2));
            } else if (token.find("h=") == 0) {
                h = stod(token.substr(2));
                hasH = true;
            } else if (token.find("SG=") == 0) {
                SG = stod(token.substr(3));
                hasSG = true;
            }
        }
        
        // 单位转换：D从mm转换为cm
        double D_cm = D / 10.0;
        double A = pi * D_cm * D_cm / 4.0;  // 横截面积，单位：cm²
        
        if (hasH) {
            // 已知h，计算SG
            SG = W / (W - A * h);
            cout << fixed << setprecision(2) << "SG=" << SG << endl;
        } else if (hasSG) {
            // 已知SG，计算h
            h = W * (SG - 1) / (SG * A);
            cout << fixed << setprecision(2) << "h=" << h << endl;
        }
    }
    
    return 0;
}
