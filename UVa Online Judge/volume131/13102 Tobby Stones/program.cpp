#include <bits/stdc++.h>
using namespace std;

const int maxN = 1000005;
const int bufSize = 1 << 20;

int childNode[maxN][2], parentNode[maxN], subSize[maxN], blackCnt[maxN];
int pushStack[maxN];
unsigned char colorVal[maxN], revTag[maxN], flipTag[maxN];
signed char setTag[maxN];
char inBuf[bufSize], outBuf[bufSize];
int inPos, inLen, outPos, rootNode;

inline char getChar() {
    if (inPos >= inLen) {
        inLen = fread(inBuf, 1, bufSize, stdin);
        inPos = 0;
        if (inLen == 0) return 0;
    }
    return inBuf[inPos++];
}

inline bool readInt(int &num) {
    char ch;
    do {
        ch = getChar();
        if (ch == 0) return false;
    } while (ch <= ' ');
    num = 0;
    while (ch > ' ') {
        num = num * 10 + ch - '0';
        ch = getChar();
    }
    return true;
}

inline void flushOut() {
    if (outPos > 0) fwrite(outBuf, 1, outPos, stdout);
    outPos = 0;
}

inline void writeChar(char ch) {
    if (outPos == bufSize) flushOut();
    outBuf[outPos++] = ch;
}

inline void writeInt(int num) {
    char str[12];
    int len = 0;
    if (num == 0) str[len++] = '0';
    while (num > 0) {
        str[len++] = char(num % 10 + '0');
        num /= 10;
    }
    while (len > 0) writeChar(str[--len]);
}

inline void pull(int node) {
    subSize[node] = subSize[childNode[node][0]] + subSize[childNode[node][1]] + 1;
    blackCnt[node] = blackCnt[childNode[node][0]] + blackCnt[childNode[node][1]] + colorVal[node];
}

inline void applySet(int node, int color) {
    if (node == 0) return;
    colorVal[node] = color;
    blackCnt[node] = subSize[node] * color;
    setTag[node] = color;
    flipTag[node] = 0;
}

inline void applyFlip(int node) {
    if (node == 0) return;
    colorVal[node] ^= 1;
    blackCnt[node] = subSize[node] - blackCnt[node];
    if (setTag[node] != -1) setTag[node] ^= 1;
    else flipTag[node] ^= 1;
}

inline void applyReverse(int node) {
    if (node == 0) return;
    swap(childNode[node][0], childNode[node][1]);
    revTag[node] ^= 1;
}

inline void push(int node) {
    if (revTag[node]) {
        applyReverse(childNode[node][0]);
        applyReverse(childNode[node][1]);
        revTag[node] = 0;
    }
    if (setTag[node] != -1) {
        applySet(childNode[node][0], setTag[node]);
        applySet(childNode[node][1], setTag[node]);
        setTag[node] = -1;
    }
    if (flipTag[node]) {
        applyFlip(childNode[node][0]);
        applyFlip(childNode[node][1]);
        flipTag[node] = 0;
    }
}

inline void rotate(int node) {
    int father = parentNode[node], grand = parentNode[father];
    int dir = childNode[father][1] == node;
    int middle = childNode[node][dir ^ 1];
    childNode[father][dir] = middle;
    if (middle) parentNode[middle] = father;
    parentNode[node] = grand;
    if (grand) childNode[grand][childNode[grand][1] == father] = node;
    childNode[node][dir ^ 1] = father;
    parentNode[father] = node;
    pull(father);
    pull(node);
}

inline void splay(int node, int goal) {
    int top = 0, cur = node;
    pushStack[++top] = cur;
    while (parentNode[cur] != goal) {
        cur = parentNode[cur];
        pushStack[++top] = cur;
    }
    while (top > 0) push(pushStack[top--]);
    while (parentNode[node] != goal) {
        int father = parentNode[node], grand = parentNode[father];
        if (grand != goal) {
            if ((childNode[father][0] == node) == (childNode[grand][0] == father)) rotate(father);
            else rotate(node);
        }
        rotate(node);
    }
    if (goal == 0) rootNode = node;
}

int buildTree(int leftPos, int rightPos, int father) {
    if (leftPos > rightPos) return 0;
    int midPos = (leftPos + rightPos) >> 1;
    int leftRoot = buildTree(leftPos, midPos - 1, midPos);
    int rightRoot = buildTree(midPos + 1, rightPos, midPos);
    parentNode[midPos] = father;
    childNode[midPos][0] = leftRoot;
    childNode[midPos][1] = rightRoot;
    pull(midPos);
    return midPos;
}

inline int getKth(int rank) {
    int node = rootNode;
    while (true) {
        push(node);
        int leftSize = subSize[childNode[node][0]];
        if (rank == leftSize + 1) return node;
        if (rank <= leftSize) node = childNode[node][0];
        else {
            rank -= leftSize + 1;
            node = childNode[node][1];
        }
    }
}

inline int getRange(int leftPos, int rightPos) {
    int leftNode = getKth(leftPos + 1);
    splay(leftNode, 0);
    int rightNode = getKth(rightPos + 3);
    splay(rightNode, leftNode);
    return childNode[rightNode][0];
}

inline void updateRange() {
    int rightNode = childNode[rootNode][1];
    pull(rightNode);
    pull(rootNode);
}

int main() {
    int n, m;
    while (readInt(n) && readInt(m)) {
        int total = n + 2;
        for (int i = 0; i <= total; i++) {
            childNode[i][0] = 0;
            childNode[i][1] = 0;
            parentNode[i] = 0;
            subSize[i] = 0;
            blackCnt[i] = 0;
            colorVal[i] = 0;
            revTag[i] = 0;
            flipTag[i] = 0;
            setTag[i] = -1;
        }
        rootNode = buildTree(1, total, 0);
        for (int i = 0; i < m; i++) {
            int type, leftPos, rightPos, color;
            readInt(type);
            readInt(leftPos);
            readInt(rightPos);
            if (type == 3) readInt(color);
            int midNode = getRange(leftPos, rightPos);
            if (type == 0) {
                writeInt(blackCnt[midNode]);
                writeChar(' ');
                writeInt(subSize[midNode] - blackCnt[midNode]);
                writeChar('\n');
            } else if (type == 1) {
                applyReverse(midNode);
                updateRange();
            } else if (type == 2) {
                applyFlip(midNode);
                updateRange();
            } else {
                applySet(midNode, color == 0);
                updateRange();
            }
        }
    }
    flushOut();
    return 0;
}
