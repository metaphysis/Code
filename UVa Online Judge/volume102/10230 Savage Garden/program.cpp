// Savage Garden
// UVa ID: 10230
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

enum {UP_LEFT, UP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

vector<string> garden;
int houseX, houseY;

// 在 L 形状所在的三乘以三大小的邻域内寻找可用颜色
char findAvailableColor(int r, int c, int size) {
    int br = max(0, r - 1), er = min(size - 1, r + 2);
    int bc = max(0, c - 1), ec = min(size - 1, c + 2);
    for (char color = 'a'; color <= 'z'; color++) {
        bool available = true;
        for (int i = br; i <= er && available; i++)
            for (int j = bc; j <= ec && available; j++)
                if (garden[i][j] == color) 
                    available = false;
        if (available) return color;
    }
    return 'a';
}

void fillGarden(int size, int row, int col, int missR, int missC) {
    int half = size / 2;
    // 确定当前的空缺在哪个象限 (0:左上, 1:右上, 2:左下, 3:右下)
    int quadrant = ((missR - row) / half) * 2 + ((missC - col) / half);
    // 正方形的中心位置坐标
    int centerR = row + half - 1, centerC = col + half - 1;
    // 先确定在中心放置 L 形砖的颜色，
    // 然后根据象限放置 L 形砖（避开当前空缺位置所在的象限）
    char color = findAvailableColor(centerR, centerC, garden.size());
    if (quadrant != UP_LEFT) garden[centerR][centerC] = color;
    if (quadrant != UP_RIGHT) garden[centerR][centerC + 1] = color;
    if (quadrant != BOTTOM_LEFT) garden[centerR + 1][centerC] = color;
    if (quadrant != BOTTOM_RIGHT) garden[centerR + 1][centerC + 1] = color;
    // 当正方形的大小为 2 时，已经填满，不需要继续递归填充
    if (size == 2) return;
    // 递归处理四个象限
    for (int i = 0; i < 4; i++) {
        // 确定象限的左上角坐标
        int newRow = row + half * (i / 2), newCol = col + half * (i % 2);
        if (i == quadrant)
            // 房子所在象限：保持原始房子所在的空缺
            fillGarden(half, newRow, newCol, missR, missC);
        else {
            // 非房子所在象限：在交界处创建新的空缺
            int newMissR = centerR + (i / 2), newMissC = centerC + (i % 2);
            fillGarden(half, newRow, newCol, newMissR, newMissC);
        }
    }
}

int main() {
    int N, X, Y;
    while (cin >> N >> X >> Y) {
        int size = 1 << N;
        garden.assign(size, string(size, ' '));
        houseX = Y - 1, houseY = X - 1;
        garden[houseX][houseY] = '*';
        fillGarden(size, 0, 0, houseX, houseY);
        for (int i = 0; i < size; i++) cout << garden[i] << '\n';
        cout << "\n";
    }
    return 0;
}
