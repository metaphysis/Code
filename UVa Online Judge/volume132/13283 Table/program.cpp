#include <bits/stdc++.h>
using namespace std;

const int maxSize = 2005;

int cover[maxSize][maxSize], heightArr[maxSize], leftChild[maxSize], rightChild[maxSize], parentNode[maxSize], subSize[maxSize], stackArr[maxSize], orderArr[maxSize];
long long diffA[maxSize][maxSize], diffB[maxSize][maxSize];

void addUpdate(int left, int right, int height, long long a, long long b) {
    if (left > right || height <= 0) return;
    diffA[1][left] += a;
    diffA[1][right + 1] -= a;
    diffA[height + 1][left] -= a;
    diffA[height + 1][right + 1] += a;
    diffB[1][left] += b;
    diffB[1][right + 1] -= b;
    diffB[height + 1][left] -= b;
    diffB[height + 1][right + 1] += b;
}

void processRow(int row, int width, int tableHeight) {
    int i, top, last, root, orderSize, leftSize, rightSize, p, q, small, large, node;
    top = 0;
    for (i = 0; i < width; i++) {
        if (cover[row][i] == 0) heightArr[i]++;
        else heightArr[i] = 0;
        leftChild[i] = -1;
        rightChild[i] = -1;
        parentNode[i] = -1;
    }
    for (i = 0; i < width; i++) {
        last = -1;
        while (top > 0 && heightArr[stackArr[top - 1]] >= heightArr[i]) last = stackArr[--top];
        if (top > 0) {
            rightChild[stackArr[top - 1]] = i;
            parentNode[i] = stackArr[top - 1];
        }
        if (last != -1) {
            leftChild[i] = last;
            parentNode[last] = i;
        }
        stackArr[top++] = i;
    }
    root = 0;
    while (parentNode[root] != -1) root = parentNode[root];
    orderSize = 0;
    stackArr[orderSize++] = root;
    for (i = 0; i < orderSize; i++) {
        node = stackArr[i];
        if (leftChild[node] != -1) stackArr[orderSize++] = leftChild[node];
        if (rightChild[node] != -1) stackArr[orderSize++] = rightChild[node];
    }
    for (i = orderSize - 1; i >= 0; i--) {
        node = stackArr[i];
        subSize[node] = 1;
        if (leftChild[node] != -1) subSize[node] += subSize[leftChild[node]];
        if (rightChild[node] != -1) subSize[node] += subSize[rightChild[node]];
        if (heightArr[node] == 0) continue;
        leftSize = leftChild[node] == -1 ? 0 : subSize[leftChild[node]];
        rightSize = rightChild[node] == -1 ? 0 : subSize[rightChild[node]];
        p = leftSize + 1;
        q = rightSize + 1;
        small = min(p, q);
        large = max(p, q);
        addUpdate(1, small, heightArr[node], 1, 0);
        addUpdate(small + 1, large, heightArr[node], 0, small);
        addUpdate(large + 1, p + q - 1, heightArr[node], -1, p + q);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y, n, d, x1, x2, y1, y2, i, j, width, height;
    while (cin >> x >> y >> n >> d) {
        memset(cover, 0, sizeof(cover));
        memset(diffA, 0, sizeof(diffA));
        memset(diffB, 0, sizeof(diffB));
        for (i = 0; i < n; i++) {
            cin >> x1 >> x2 >> y1 >> y2;
            cover[y1][x1]++;
            cover[y1][x2]--;
            cover[y2][x1]--;
            cover[y2][x2]++;
        }
        for (i = 0; i < y; i++)
            for (j = 0; j < x; j++) {
                if (i > 0) cover[i][j] += cover[i - 1][j];
                if (j > 0) cover[i][j] += cover[i][j - 1];
                if (i > 0 && j > 0) cover[i][j] -= cover[i - 1][j - 1];
            }
        memset(heightArr, 0, sizeof(heightArr));
        for (i = 0; i < y; i++) processRow(i, x, y);
        for (i = 1; i <= y; i++)
            for (j = 1; j <= x; j++) {
                diffA[i][j] += diffA[i - 1][j] + diffA[i][j - 1] - diffA[i - 1][j - 1];
                diffB[i][j] += diffB[i - 1][j] + diffB[i][j - 1] - diffB[i - 1][j - 1];
            }
        for (i = 0; i < d; i++) {
            cin >> width >> height;
            if (width > x || height > y) cout << 0 << '\n';
            else cout << diffA[height][width] * width + diffB[height][width] << '\n';
        }
    }
    return 0;
}
