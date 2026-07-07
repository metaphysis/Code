// Follow the Folding Dot
// UVa ID: 733
// Verdict: Accepted
// Submission Date: 2026-07-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 翻转纸面：T<->B
char flipSide(char c) { return c == 'T' ? 'B' : 'T'; }

int main() {
    int paperNo = 0;
    double W, H, x, y;
    char side;
    string token;

    while (cin >> W >> H) {                     // 类型1：宽 高
        ++paperNo;
        cin >> x >> y >> side;                  // 类型2：坐标 面

        double initW = W, initH = H, initX = x, initY = y;
        char initSide = side;
        int page = 1;                           // 当前点所在页（层）号
        int totalLayers = 1;                    // 当前纸张总层数

        // 输出开始信息
        cout << "Paper number " << paperNo << "\n";
        cout << "Beginning paper dimensions " << fixed << setprecision(6)
             << initW << " X " << initH << "\n";
        cout << "Dot is on " << (initSide == 'T' ? "TOP" : "BOTTOM")
             << " of page 1. Position: " << initX << " X " << initY << "\n";

        // 循环执行折叠指令，直到 'S'
        while (cin >> token) {
            if (token == "S") break;

            char edge = token[0];               // 折叠边：T/B/L/R
            char dir = token[1];                // 方向：O（over）或 U（under）

            double oldW = W, oldH = H;
            int oldL = totalLayers;
            bool folded = false;                // 点是否位于被折叠的那一半

            if (edge == 'T') {                  // 折叠上边
                if (y < oldH / 2.0) {           // 点在上半部分（被折叠）
                    folded = true;
                    y = oldH / 2.0 - y;         // 关于中线镜像
                    side = flipSide(side);
                } else {                        // 点在下半部分（未折叠）
                    y = y - oldH / 2.0;         // 新原点下移
                }
                H = oldH / 2.0;
            } else if (edge == 'B') {           // 折叠下边
                if (y > oldH / 2.0) {           // 点在下半部分（被折叠）
                    folded = true;
                    y = oldH - y;               // 镜像
                    side = flipSide(side);
                }                               // 上半部分未折叠，y 不变
                H = oldH / 2.0;
            } else if (edge == 'L') {           // 折叠左边
                if (x < oldW / 2.0) {           // 点在左半（被折叠）
                    folded = true;
                    x = oldW / 2.0 - x;
                    side = flipSide(side);
                } else {                        // 点在右半（未折叠）
                    x = x - oldW / 2.0;         // 新原点右移
                }
                W = oldW / 2.0;
            } else if (edge == 'R') {           // 折叠右边
                if (x > oldW / 2.0) {           // 点在右半（被折叠）
                    folded = true;
                    x = oldW - x;
                    side = flipSide(side);
                }                               // 左半未折叠，x 不变
                W = oldW / 2.0;
            }

            // 更新点所在的页号（层号）
            if (folded) {                       // 被折叠的那一半翻转后重新堆叠
                if (dir == 'O')                 // over：被折叠部分置于顶部
                    page = oldL - page + 1;     // 内部顺序反转，再放在最上面
                else if (dir == 'U')            // under：被折叠部分置于底部
                    page = oldL + (oldL - page + 1);
            } else {                            // 未被折叠的一半
                if (dir == 'O')                 // over：上面增加了 oldL 层
                    page = page + oldL;
                // dir == 'U' 时，下面增加层，页号不变
            }

            totalLayers = oldL * 2;             // 层数加倍
        }

        // 输出最终结果
        cout << '\n';
        cout << "After folding paper. Paper dimensions: " << fixed << setprecision(6)
             << W << " X " << H << "\n";
        cout << "Dot is on " << (side == 'T' ? "TOP" : "BOTTOM")
             << " of page " << page << ". Position " << x << " X " << y << "\n";
        cout << "\n";                           // 每组数据后空一行
    }

    return 0;
}
