// Huffman Codes
// UVa ID: 1072
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int kMaxNodes = 22;
const int kMaxWays = 30000;

int n, i, j, newTot, nodesCount, lastNode, node, caseNo;
int answer[kMaxWays][kMaxNodes];
int newAnswer[kMaxWays][kMaxNodes];
int leftChild[kMaxNodes * 2], rightChild[kMaxNodes * 2];
int stepNode[kMaxNodes * 2];
char lineStr[kMaxNodes];

void splitNode(int curNode) {
    int idx, jdx, kdx, firstPart;
    newTot = 0;
    for (idx = 0; answer[idx][0]; idx++) {
        firstPart = answer[idx][curNode];
        for (jdx = firstPart - 1; jdx > (firstPart - 1) / 2; jdx--) {
            if (jdx <= answer[idx][nodesCount]) {
                for (kdx = 0; kdx < nodesCount; kdx++) {
                    if (kdx >= curNode)
                        newAnswer[newTot][kdx] = answer[idx][kdx + 1];
                    else
                        newAnswer[newTot][kdx] = answer[idx][kdx];
                }
                newAnswer[newTot][kdx] = jdx;
                newAnswer[newTot][kdx + 1] = firstPart - jdx;
                newTot++;
            }
        }
    }
    nodesCount++;
    memcpy(answer, newAnswer, newTot * kMaxNodes * sizeof(int));
    answer[newTot][0] = 0;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        memset(leftChild, 0, sizeof(leftChild));
        memset(rightChild, 0, sizeof(rightChild));
        lastNode = 0;
        for (i = 0; i < n; i++) {
            scanf(" %s", lineStr);
            node = 0;
            for (j = 0; lineStr[j]; j++) {
                if (lineStr[j] == '0') {
                    if (!leftChild[node]) {
                        leftChild[node] = ++lastNode;
                        rightChild[node] = ++lastNode;
                    }
                    node = leftChild[node];
                } else {
                    if (!rightChild[node]) {
                        leftChild[node] = ++lastNode;
                        rightChild[node] = ++lastNode;
                    }
                    node = rightChild[node];
                }
            }
        }
        i = 0;
        j = 0;
        node = 0;
        nodesCount = 0;
        answer[0][0] = 100;
        answer[1][0] = 0;
        while (i <= j) {
            if (leftChild[stepNode[i]]) {
                splitNode(node);
                stepNode[++j] = rightChild[stepNode[i]];
                stepNode[++j] = leftChild[stepNode[i]];
            } else {
                node++;
            }
            i++;
        }
        printf("Case %d: %d\n", ++caseNo, newTot);
    }
    return 0;
}
