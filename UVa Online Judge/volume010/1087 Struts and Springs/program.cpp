// Struts and Springs
// UVa ID: 1087
// Verdict: Accepted
// Submission Date: 2026-08-04
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Window {
    long long x, y, width, height;
    array<long long, 3> hLen, vLen;
    array<int, 3> hMark, vMark;
};

vector<Window> winList;
vector<vector<int>> childList;

array<long long, 3> calcPart(const array<long long, 3> &base, const array<int, 3> &mark, long long total, int fallback) {
    array<int, 3> isSpring = mark;
    bool hasSpring = false;
    for (int i = 0; i < 3; i++) {
        if (isSpring[i]) hasSpring = true;
    }
    if (!hasSpring) isSpring[fallback] = 1;
    long long fixedLen = 0, springLen = 0;
    for (int i = 0; i < 3; i++) {
        if (isSpring[i]) springLen += base[i];
        else fixedLen += base[i];
    }
    long long newSpringLen = total - fixedLen;
    array<long long, 3> result;
    for (int i = 0; i < 3; i++) {
        if (isSpring[i]) result[i] = base[i] * newSpringLen / springLen;
        else result[i] = base[i];
    }
    return result;
}

void updateWindow(int id, long long px, long long py, long long pWidth, long long pHeight) {
    array<long long, 3> hPart = calcPart(winList[id].hLen, winList[id].hMark, pWidth, 2);
    array<long long, 3> vPart = calcPart(winList[id].vLen, winList[id].vMark, pHeight, 0);
    winList[id].x = px + hPart[0];
    winList[id].y = py + vPart[0];
    winList[id].width = hPart[1];
    winList[id].height = vPart[1];
    for (int next : childList[id]) updateWindow(next, winList[id].x, winList[id].y, winList[id].width, winList[id].height);
}

int solve() {
    int caseId = 1;
    while (true) {
        int nWin, nResize;
        long long oWidth, oHeight;
        cin >> nWin >> nResize >> oWidth >> oHeight;
        if (nWin == 0 && nResize == 0 && oWidth == 0 && oHeight == 0) break;
        winList.assign(nWin + 1, Window());
        childList.assign(nWin + 1, vector<int>());
        winList[0].x = 0;
        winList[0].y = 0;
        winList[0].width = oWidth;
        winList[0].height = oHeight;
        for (int i = 1; i <= nWin; i++) {
            int widthMark, heightMark, topMark, bottomMark, leftMark, rightMark;
            cin >> winList[i].x >> winList[i].y >> winList[i].width >> winList[i].height;
            cin >> widthMark >> heightMark >> topMark >> bottomMark >> leftMark >> rightMark;
            winList[i].hMark = array<int, 3>{leftMark, widthMark, rightMark};
            winList[i].vMark = array<int, 3>{topMark, heightMark, bottomMark};
        }
        for (int i = 1; i <= nWin; i++) {
            int parent = 0;
            long long bestArea = oWidth * oHeight;
            for (int j = 1; j <= nWin; j++) {
                if (i == j) continue;
                if (winList[j].x < winList[i].x && winList[j].y < winList[i].y && winList[j].x + winList[j].width > winList[i].x + winList[i].width && winList[j].y + winList[j].height > winList[i].y + winList[i].height) {
                    long long area = winList[j].width * winList[j].height;
                    if (area < bestArea) {
                        bestArea = area;
                        parent = j;
                    }
                }
            }
            long long parentX = parent == 0 ? 0 : winList[parent].x;
            long long parentY = parent == 0 ? 0 : winList[parent].y;
            long long parentWidth = parent == 0 ? oWidth : winList[parent].width;
            long long parentHeight = parent == 0 ? oHeight : winList[parent].height;
            winList[i].hLen = array<long long, 3>{
                winList[i].x - parentX,
                winList[i].width,
                parentWidth - (winList[i].x - parentX) - winList[i].width
            };
            winList[i].vLen = array<long long, 3>{
                winList[i].y - parentY,
                winList[i].height,
                parentHeight - (winList[i].y - parentY) - winList[i].height
            };
            childList[parent].push_back(i);
        }
        for (int op = 1; op <= nResize; op++) {
            long long newWidth, newHeight;
            cin >> newWidth >> newHeight;
            cout << "Case " << caseId << ", resize operation " << op << ":\n";
            for (int id : childList[0]) updateWindow(id, 0, 0, newWidth, newHeight);
            for (int i = 1; i <= nWin; i++) {
                cout << "    Window " << i << ", x = " << winList[i].x << ", y = " << winList[i].y << ", width = " << winList[i].width << ", height = " << winList[i].height << "\n";
            }
        }
        caseId++;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
