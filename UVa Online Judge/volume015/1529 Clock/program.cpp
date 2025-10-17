// Clock
// UVa ID: 1529
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int h1, m1, h2, m2;
    // 注意，题目描述中并未提到需要输出此行信息，若不输出，无法获得 Accepted
    cout << "Program 3 by team X\n";
    // 输出表头
    cout << "Initial time  Final time  Passes" << endl;
    while (cin >> h1 >> m1 >> h2 >> m2) {
        // 转换为从12:00开始的分钟数
        int start = (h1 % 12) * 60 + m1;
        int end = (h2 % 12) * 60 + m2;
        bool crossed_12 = false;
        // 如果结束时间小于起始时间，表示跨过12点
        if (end <= start) {
            end += 720; // 12小时
            crossed_12 = true;
        }
        int count = 0;
        // 检查所有可能的k值，直到覆盖整个区间
        for (int k = 0; k <= 20; k++) {
            double meet = 720.0 * k / 11;
            // 严格在开区间 (start, end) 内
            if (meet > start && meet < end) {
                count++;
            }
            // 如果已经超出区间范围，提前退出
            if (meet > end + 1) break;
        }
        // 输出，严格按照题目格式
        // 注意：小时部分用空格填充，分钟部分用0填充
        cout << "       " 
             << setw(2) << setfill('0') << h1 << ":" 
             << setw(2) << setfill('0') << m1
             << "       "
             << setw(2) << setfill('0') << h2 << ":" 
             << setw(2) << setfill('0') << m2
             << setw(8) << setfill(' ') << count << endl;
    }
    // 注意，题目描述中并未提到需要输出此行信息，若不输出，无法获得 Accepted
    cout << "End of program 3 by team X\n";
    return 0;
}
