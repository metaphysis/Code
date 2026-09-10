#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1000000 + 5;

struct Node {
    int pre, nxt;
};

int T, L, P;
int pairNode[MAXL];   // 配对点，-1表示无配对
int coverState[MAXL]; // 1:在上方, -1:在下方, 0:无覆盖
int visTag[MAXL];     // 访问标记，用于一轮扫描中去重
Node listNode[MAXL];

// 从双向链表中删除节点pos
void deleteNode(int pos) {
    coverState[pos] = 0;
    listNode[listNode[pos].pre].nxt = listNode[pos].nxt;
    listNode[listNode[pos].nxt].pre = listNode[pos].pre;
}

int main() {
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        scanf("%d%d", &L, &P);
        // 初始化链表
        for (int i = 0; i < L; i++) {
            listNode[i].pre = i - 1;
            listNode[i].nxt = i + 1;
            pairNode[i] = -1;
            coverState[i] = 0;
            visTag[i] = 0;
        }
        listNode[0].pre = L - 1;
        listNode[L - 1].nxt = 0;

        // 读入配对
        for (int i = 0; i < P; i++) {
            int A, B;
            scanf("%d%d", &A, &B);
            pairNode[A] = B;
            pairNode[B] = A;
            coverState[A] = 1;   // A在B上方
            coverState[B] = -1;  // B在A下方
        }

        // 删除所有未参与覆盖的点（它们不阻碍消除过程）
        for (int i = 0; i < L; i++) {
            if (coverState[i] == 0) {
                deleteNode(i);
            }
        }

        int head = 0;
        while (coverState[head] == 0) head++;
        int roundTag = 0;

        // 反复扫描并消除
        while (P > 0) {
            bool eliminated = false;
            roundTag++;
            // 从head开始遍历当前环
            for (int i = head; visTag[i] != roundTag && !eliminated; i = listNode[i].nxt) {
                visTag[i] = roundTag;
                int x = listNode[i].nxt;

                // 规则一：旋转消除（i与x相邻且互为配对）
                if (x == pairNode[i] || listNode[x].nxt == i) {
                    deleteNode(i);
                    deleteNode(x);
                    P--;
                    eliminated = true;
                    break;
                }

                // 规则二：平移消除
                if (coverState[i] == coverState[x]) {
                    int pi = pairNode[i];
                    int px = pairNode[x];
                    if (listNode[pi].nxt == px || listNode[px].nxt == pi) {
                        deleteNode(i);
                        deleteNode(x);
                        deleteNode(pi);
                        deleteNode(px);
                        P -= 2;
                        eliminated = true;
                        break;
                    }
                }
            }

            // 若无任何消除，说明无法继续化简
            if (!eliminated) break;

            // 更新head为下一个未被删除的点
            while (coverState[head] == 0) head++;
        }

        printf("Case #%d: %s\n", caseNo, P == 0 ? "YES" : "NO");
    }
    return 0;
}
