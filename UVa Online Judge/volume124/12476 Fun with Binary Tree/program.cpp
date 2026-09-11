#include <bits/stdc++.h>
using namespace std;

const int maxNode = 20005, maxLen = 41000, maxEdge = 210005;

int n, leftChild[maxNode], rightChild[maxNode];
int head[maxLen], edgeTo[maxEdge], nextEdge[maxEdge], cnt;
string str;

void addEdge(int from, int to) {
    if (to == -1) return;
    edgeTo[cnt] = to;
    nextEdge[cnt] = head[from];
    head[from] = cnt++;
}

bool checkWin() {
    int strLen = (int)str.size();
    cnt = 1;
    memset(head, 0, sizeof(head));
    addEdge(0, 1);
    for (int i = 0; i < strLen; i++) {
        if (!head[i]) continue;
        int pos = i;
        while (pos < strLen && str[pos] == str[i]) pos++;
        int runLen = pos - i;
        if (runLen == 1) {
            if (pos == strLen) return true;
            for (int j = head[i]; j; j = nextEdge[j]) {
                int v = edgeTo[j];
                if (str[i] == 'L') {
                    addEdge(i + 1, leftChild[v]);
                    addEdge(i + 2, rightChild[v]);
                } else {
                    addEdge(i + 1, rightChild[v]);
                    addEdge(i + 2, leftChild[v]);
                }
            }
        } else {
            if (runLen & 1) {
                runLen--;
                pos--;
            }
            for (int j = head[i]; j; j = nextEdge[j]) {
                int v = edgeTo[j];
                int p = v;
                for (int k = 0; k < runLen; k++) {
                    if (str[i] == 'L') p = leftChild[p];
                    else p = rightChild[p];
                    if (p == -1) break;
                    if (k + 1 >= runLen / 2) addEdge(pos, p);
                }
            }
        }
    }
    return head[strLen - 1] || head[strLen];
}

int main() {
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> n;
        // 尚未找到原因，使用以下语句读入数据，会出现运行时错误：
        // for (int i = 1; i <= n; i++) cin >> leftChild[i] >> rightChild[i];
        // 使用 scanf 读入数据可以通过
        for (int i = 1; i <= n; i++) scanf("%d %d", &leftChild[i], &rightChild[i]);
        cin >> str;
        cout << "Case " << cs << ": " << (checkWin() ? "Yes" : "No") << '\n';
    }
    return 0;
}
