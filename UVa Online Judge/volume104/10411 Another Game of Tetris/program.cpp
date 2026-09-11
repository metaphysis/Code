// Another Game of Tetris
// UVa ID: 10411
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int heights[100], nCols;
int candidates[19], candPtr;
int deltaCol[19] = {0, 0, 0, -1, 0, -1, 0, 0, -1, -1, 0, 0, -2, 0, 0, 0, -1, 0, 0};
int length[19] = {1, 4, 2, 3, 3, 2, 2, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 2, 2};
int offset[19][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, -1, -1, 0}, {0, 0, 1, 0}, {0, -1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, -1, 0, 0}, {0, -1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, -1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 2, 0, 0}, {0, -2, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int addVal[19][4] = {{4, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 0, 0}, {1, 2, 1, 0}, {1, 2, 1, 0}, {2, 2, 0, 0}, {2, 2, 0, 0}, {1, 2, 1, 0}, {1, 2, 1, 0}, {1, 3, 0, 0}, {3, 1, 0, 0}, {2, 1, 1, 0}, {1, 1, 2, 0}, {2, 1, 1, 0}, {1, 1, 2, 0}, {3, 1, 0, 0}, {1, 3, 0, 0}, {3, 1, 0, 0}, {1, 3, 0, 0}};

bool isGameOver() {
    for (int i = 0; i < nCols; i++) if (heights[i]) return false;
    return true;
}

int canPlace(int col, int type) {
    int temp[100], maxHeight = 0;
    if (col + deltaCol[type] < 0 || col + deltaCol[type] + length[type] >= nCols + 1) return -1;
    int baseCol = col + deltaCol[type];
    for (int i = 1; i < length[type]; i++) if (heights[baseCol + i] != heights[baseCol] + offset[type][i]) return -1;
    for (int i = 0; i < nCols; i++) temp[i] = heights[i];
    for (int i = 0; i < length[type]; i++) {
        temp[baseCol + i] += addVal[type][i];
        if (temp[baseCol + i] > maxHeight) maxHeight = temp[baseCol + i];
    }
    return maxHeight;
}

void placeBlock(int col, int type) {
    int minVal = 9999999;
    int baseCol = col + deltaCol[type];
    for (int i = 0; i < length[type]; i++) heights[baseCol + i] += addVal[type][i];
    for (int i = 0; i < nCols; i++) if (heights[i] < minVal) minVal = heights[i];
    for (int i = 0; i < nCols; i++) heights[i] -= minVal;
}

int main() {
    int t;
    scanf("%d", &t);
    srand(time(NULL));
    while (t--) {
        scanf("%d", &nCols);
        for (int i = 0; i < nCols; i++) scanf("%d", heights + i);
        while (true) {
            if (isGameOver()) break;
            int minCol = 0, minHeight = 999, p;
            candPtr = 0;
            for (int i = 0; i < nCols; i++) if (heights[i] < heights[minCol]) minCol = i;
            for (int k = 0; k < 19; k++) {
                int res = canPlace(minCol, k);
                if (res == -1) continue;
                if (res < minHeight) {
                    minHeight = res;
                    candPtr = 0;
                    candidates[candPtr++] = k;
                } else if (res == minHeight) {
                    candidates[candPtr++] = k;
                }
            }
            p = candidates[rand() % candPtr];
            placeBlock(minCol, p);
            printf("%d %d\n", p + 1, minCol + deltaCol[p] + 1);
        }
        puts("-1 -1");
    }
    return 0;
}
