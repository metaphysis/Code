#include <bits/stdc++.h>
using namespace std;

const int maxN = 205;
bool linkGraph[maxN][maxN];
int best;

void colorSort(int candidate[], int candidateCount, int order[], int bound[], int &orderCount) {
    int remain[maxN], nextRemain[maxN], colorVertex[maxN];
    int remainCount, nextCount, colorCount, colorVertexCount;
    int i, j, vertex;
    bool canUse;
    remainCount = candidateCount;
    for (i = 0; i < candidateCount; i++)
        remain[i] = candidate[i];
    orderCount = 0;
    colorCount = 0;
    while (remainCount > 0) {
        colorCount++;
        nextCount = 0;
        colorVertexCount = 0;
        for (i = 0; i < remainCount; i++) {
            vertex = remain[i];
            canUse = true;
            for (j = 0; j < colorVertexCount; j++)
                if (linkGraph[vertex][colorVertex[j]]) {
                    canUse = false;
                    break;
                }
            if (canUse) {
                order[orderCount] = vertex;
                bound[orderCount] = colorCount;
                orderCount++;
                colorVertex[colorVertexCount++] = vertex;
            } else {
                nextRemain[nextCount++] = vertex;
            }
        }
        remainCount = nextCount;
        for (i = 0; i < remainCount; i++)
            remain[i] = nextRemain[i];
    }
}

void expand(int candidate[], int candidateCount, int depth) {
    int order[maxN], bound[maxN], nextCandidate[maxN];
    int orderCount, nextCount, i, j, vertex;
    if (depth > best) best = depth;
    colorSort(candidate, candidateCount, order, bound, orderCount);
    for (i = orderCount - 1; i >= 0; i--) {
        if (depth + bound[i] <= best) return;
        vertex = order[i];
        nextCount = 0;
        for (j = 0; j < i; j++)
            if (linkGraph[vertex][order[j]])
                nextCandidate[nextCount++] = order[j];
        expand(nextCandidate, nextCount, depth + 1);
    }
}

int solve() {
    int friendCount, enemyCount, enemy, testCaseCount, testCase, i, j;
    int candidate[maxN];
    cin >> testCaseCount;
    for (testCase = 0; testCase < testCaseCount; testCase++) {
        cin >> friendCount;
        for (i = 0; i < friendCount; i++)
            for (j = 0; j < friendCount; j++)
                linkGraph[i][j] = i != j;
        for (i = 0; i < friendCount; i++) {
            cin >> enemyCount;
            for (j = 0; j < enemyCount; j++) {
                cin >> enemy;
                if (enemy >= 0 && enemy < friendCount && enemy != i) {
                    linkGraph[i][enemy] = false;
                    linkGraph[enemy][i] = false;
                }
            }
        }
        for (i = 0; i < friendCount; i++)
            candidate[i] = i;
        best = 0;
        expand(candidate, friendCount, 0);
        cout << best << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
