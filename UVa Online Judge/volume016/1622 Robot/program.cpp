// Robot
// UVa ID: 1622
// Verdict: Accepted
// Submission Date: 2026-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    LL nRows, nCols;                 // 行数、列数
    int caseNo = 1;
    while (cin >> nRows >> nCols, nRows || nCols) {
        LL cntNorth, cntSouth, cntWest, cntEast;
        cin >> cntNorth >> cntSouth >> cntWest >> cntEast;
        LL answer = 0;

        // 保证 cntNorth >= cntSouth, cntWest >= cntEast
        if (cntNorth < cntSouth) swap(cntSouth, cntNorth);
        if (cntWest < cntEast) swap(cntEast, cntWest);

        // 计算两种优先顺序的预估收益，决定先东西还是先南北
        LL gainFirstEW = nRows + (nCols - 1) * nRows * cntEast * 2
                       + (nCols - 1) + (nCols - 1) * (nRows - 1) * cntSouth * 2;
        LL gainFirstNS = nCols + nCols * (nRows - 1) * cntSouth * 2
                       + (nRows - 1) + (nCols - 1) * (nRows - 1) * cntEast * 2;

        if (cntWest - cntEast) {
            gainFirstEW += (nCols - 1) * nRows;
            gainFirstNS += (nCols - 1) * (nRows - 1);
        }
        if (cntNorth - cntSouth) {
            gainFirstEW += (nCols - 1) * (nRows - 1);
            gainFirstNS += nCols * (nRows - 1);
        }

        // 若先南北更优，则交换行列及对应的方向计数
        if (gainFirstEW < gainFirstNS) {
            swap(nRows, nCols);
            swap(cntNorth, cntWest);
            swap(cntSouth, cntEast);
        }

        bool hasExecutedEWPair = true;   // 是否已执行过东西配对

        // 执行东西配对（cntEast 对）
        if (cntEast) {
            answer += nRows + (nCols - 1) * nRows * cntEast * 2;
            cntWest -= cntEast;
            cntEast = 0;
            --nCols;
            hasExecutedEWPair = false;
        }

        // 处理多余的向西指令
        if (cntWest) {
            answer += nCols * nRows;
            --cntWest;
            if (hasExecutedEWPair) --nCols;
        }

        // 超过列数的向西指令无法执行，截断
        cntWest = min(nCols, cntWest);

        // 处理剩余的西向和北向指令（可能还有南向）
        while (cntWest || cntNorth) {
            if (cntSouth) {
                // 比较“先南北配对”与“继续向西”的收益
                LL t1 = nCols * nRows + (nRows - 1) * nCols * 2 * cntSouth;
                LL t2 = nCols * nRows + (nCols - 1) * nRows
                      + (nCols - 1) * (nRows - 1) * (2 * cntSouth - 1);
                if (cntNorth - cntSouth) {
                    t1 = nCols * nRows + (nRows - 1) * nCols * (2 * cntSouth + 1);
                    t2 = nCols * nRows + (nCols - 1) * nRows
                       + (nCols - 1) * (nRows - 1) * 2 * cntSouth;
                }
                if (t1 > t2 || !cntWest) {
                    // 执行南北配对
                    answer += nCols + nCols * (nRows - 1) * cntSouth * 2;
                    cntNorth -= cntSouth;
                    cntSouth = 0;
                    --nRows;
                    if (cntNorth) {
                        answer += nCols * nRows;
                        --cntNorth;
                    }
                    cntNorth = min(nRows, cntNorth);
                } else {
                    // 继续向西
                    answer += nCols * nRows;
                    --nCols;
                    --cntWest;
                }
            } else if (!cntWest) {
                // 仅剩北向，等差数列
                answer += nCols * cntNorth * (2 * nRows - cntNorth + 1) / 2;
                cntNorth = 0;
            } else if (!cntNorth) {
                // 仅剩西向，等差数列
                answer += nRows * cntWest * (2 * nCols - cntWest + 1) / 2;
                cntWest = 0;
            } else {
                // 两者都有，选择剩余空间较大的方向
                answer += nCols * nRows;
                if (nCols > nRows) {
                    --nCols;
                    --cntWest;
                } else {
                    --nRows;
                    --cntNorth;
                }
            }
        }

        cout << "Case " << caseNo++ << ": " << answer << endl;
    }
    return 0;
}
