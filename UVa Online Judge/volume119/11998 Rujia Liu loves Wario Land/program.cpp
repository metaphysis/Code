#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000 + 10;
static const int MAXE = MAXN << 1;
static const int BLOCK_SIZE = 200;

int n, m, mod;
int value[MAXN];
int blockId[MAXN];
int head[MAXN];
int to[MAXE];
int nextEdge[MAXE];
int edgeCount;

namespace FastIO {
    static const int INPUT_SIZE = 1 << 20;
    static const int OUTPUT_SIZE = 1 << 20;
    char inputBuffer[INPUT_SIZE];
    char outputBuffer[OUTPUT_SIZE];
    int inputPos = 0;
    int inputLength = 0;
    int outputLength = 0;
    inline char getChar() {
        if (inputPos == inputLength) {
            inputLength = (int)fread(inputBuffer, 1, INPUT_SIZE, stdin);
            inputPos = 0;
            if (inputLength == 0) return 0;
        }
        return inputBuffer[inputPos++];
    }
    inline bool readInt(int &x) {
        char c = getChar();
        int sign = 1;
        x = 0;
        while (c && c != '-' && (c < '0' || c > '9')) c = getChar();
        if (!c) return false;
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getChar();
        }
        x *= sign;
        return true;
    }
    inline void flush() {
        fwrite(outputBuffer, 1, outputLength, stdout);
        outputLength = 0;
    }
    inline void putChar(char c) {
        if (outputLength == OUTPUT_SIZE) flush();
        outputBuffer[outputLength++] = c;
    }
    inline void printInt(int x) {
        if (x == 0) {
            putChar('0');
            return;
        }
        if (x < 0) {
            putChar('-');
            x = -x;
        }
        char buffer[12];
        int length = 0;
        while (x > 0) {
            buffer[length++] = char('0' + x % 10);
            x /= 10;
        }
        while (length > 0) putChar(buffer[--length]);
    }
}

using namespace FastIO;

struct ValueBlock {
    struct Node {
        int value;
        int prefixProduct;
        Node() {}
        Node(int v) : value(v), prefixProduct(0) {}
        bool operator<(const Node &other) const {
            return value < other.value;
        }
    };
    int lazySize;
    vector<Node> nodes;
    inline void clear() {
        nodes.clear();
        lazySize = 0;
    }
    inline void rebuild() {
        if (nodes.empty()) return;
        sort(nodes.begin(), nodes.end());
        nodes[0].prefixProduct = nodes[0].value % mod;
        for (int i = 1, size = (int)nodes.size(); i < size; ++i) {
            nodes[i].prefixProduct = (int)(1LL * nodes[i - 1].prefixProduct * nodes[i].value % mod);
        }
    }
    inline int query(int limit) const {
        int left = 0;
        int right = (int)nodes.size() - 1;
        int result = -1;
        while (left <= right) {
            int middle = (left + right) >> 1;
            if (nodes[middle].value <= limit) {
                result = middle;
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        return result;
    }
};

ValueBlock blocks[MAXN];

namespace DynamicHLD {
    int parentNode[MAXN];
    int subtreeSize[MAXN];
    int heavySon[MAXN];
    int depthNode[MAXN];
    int chainTop[MAXN];
    inline void addEdge(int u, int v) {
        to[++edgeCount] = v;
        nextEdge[edgeCount] = head[u];
        head[u] = edgeCount;
        to[++edgeCount] = u;
        nextEdge[edgeCount] = head[v];
        head[v] = edgeCount;
    }
    inline int findRoot(int x) {
        while (parentNode[x]) x = chainTop[parentNode[x]];
        return x;
    }
    void dfs1(int u, int father) {
        parentNode[u] = father;
        depthNode[u] = depthNode[father] + 1;
        subtreeSize[u] = 1;
        heavySon[u] = 0;
        blocks[u].clear();
        for (int i = head[u]; i; i = nextEdge[i]) {
            int v = to[i];
            if (v == father) continue;
            dfs1(v, u);
            subtreeSize[u] += subtreeSize[v];
            if (subtreeSize[v] > subtreeSize[heavySon[u]]) heavySon[u] = v;
        }
    }
    void dfs2(int u, int top) {
        chainTop[u] = top;
        if (u == top) {
            blockId[u] = u;
            blocks[u].nodes.emplace_back(value[u]);
        } else if ((int)blocks[blockId[parentNode[u]]].nodes.size() < BLOCK_SIZE) {
            blockId[u] = blockId[parentNode[u]];
            blocks[blockId[u]].nodes.emplace_back(value[u]);
        } else {
            blockId[u] = u;
            blocks[u].nodes.emplace_back(value[u]);
        }
        if (heavySon[u]) dfs2(heavySon[u], top);
        for (int i = head[u]; i; i = nextEdge[i]) {
            int v = to[i];
            if (v == parentNode[u] || v == heavySon[u]) continue;
            dfs2(v, v);
        }
        if (u == blockId[u]) blocks[u].rebuild();
    }
}

using namespace DynamicHLD;

int answerCount;
int answerProduct;

inline void linkTree(int x, int y) {
    int rootX = findRoot(x);
    int rootY = findRoot(y);
    if (rootX == rootY) return;
    if (subtreeSize[rootX] + blocks[rootX].lazySize < subtreeSize[rootY] + blocks[rootY].lazySize) {
        swap(rootX, rootY);
        swap(x, y);
    }
    if (subtreeSize[heavySon[x]] < subtreeSize[rootY] + blocks[rootY].lazySize) {
        int oldHeavySon = heavySon[x];
        heavySon[x] = y;
        if (oldHeavySon) {
            blocks[blockId[x]].nodes.clear();
            dfs1(oldHeavySon, x);
            dfs2(oldHeavySon, oldHeavySon);
            int u = x;
            while (u != blockId[u]) {
                blocks[blockId[u]].nodes.emplace_back(value[u]);
                u = parentNode[u];
            }
            blocks[u].nodes.emplace_back(value[u]);
        }
    }
    addEdge(x, y);
    parentNode[y] = x;
    dfs1(y, x);
    dfs2(y, heavySon[x] == y ? chainTop[x] : y);
    int u = x;
    while (u != blockId[x]) {
        subtreeSize[u] += subtreeSize[y];
        u = parentNode[u];
    }
    subtreeSize[u] += subtreeSize[y];
    u = parentNode[u];
    while (u && blockId[u] != rootX) {
        blocks[blockId[u]].lazySize += subtreeSize[y];
        u = parentNode[blockId[u]];
    }
    if (u) blocks[rootX].lazySize += subtreeSize[y];
    blocks[blockId[x]].rebuild();
}

inline void modifyValue(int x, int newValue) {
    ValueBlock &currentBlock = blocks[blockId[x]];
    for (ValueBlock::Node &node : currentBlock.nodes) {
        if (node.value == value[x]) {
            node.value = newValue;
            break;
        }
    }
    value[x] = newValue;
    currentBlock.rebuild();
}

inline void addSingle(int x) {
    ++answerCount;
    answerProduct = (int)(1LL * answerProduct * value[x] % mod);
}

inline void addWholeBlock(int id, int index) {
    answerCount += index + 1;
    answerProduct = (int)(1LL * answerProduct * blocks[id].nodes[index].prefixProduct % mod);
}

inline void checkSingle(int x, int limit) {
    if (value[x] <= limit) addSingle(x);
}

inline void queryUpToChainTop(int x, int limit) {
    int u = x;
    while (u != blockId[x]) {
        checkSingle(u, limit);
        u = parentNode[u];
    }
    checkSingle(u, limit);
    if (chainTop[x] == u) return;
    u = parentNode[u];
    while (blockId[u] != chainTop[x]) {
        int index = blocks[blockId[u]].query(limit);
        if (index != -1) addWholeBlock(blockId[u], index);
        u = parentNode[blockId[u]];
    }
    int index = blocks[blockId[u]].query(limit);
    if (index != -1) addWholeBlock(blockId[u], index);
}

inline void queryPath(int x, int y, int limit) {
    if (findRoot(x) != findRoot(y)) return;
    while (chainTop[x] != chainTop[y]) {
        if (depthNode[chainTop[x]] < depthNode[chainTop[y]]) swap(x, y);
        queryUpToChainTop(x, limit);
        x = parentNode[chainTop[x]];
    }
    if (depthNode[x] < depthNode[y]) swap(x, y);
    while (blockId[x] != blockId[y]) {
        if (blockId[heavySon[x]] == blockId[x]) {
            checkSingle(x, limit);
            x = parentNode[x];
            continue;
        }
        x = blockId[x];
        int index = blocks[x].query(limit);
        if (index != -1) addWholeBlock(x, index);
        x = parentNode[x];
    }
    while (x != y) {
        checkSingle(x, limit);
        x = parentNode[x];
    }
    checkSingle(x, limit);
}

int main() {
    while (readInt(n)) {
        readInt(m);
        readInt(mod);
        edgeCount = 0;
        for (int i = 1; i <= n; ++i) {
            readInt(value[i]);
            head[i] = 0;
            parentNode[i] = 0;
            subtreeSize[i] = 0;
            heavySon[i] = 0;
            depthNode[i] = 0;
            chainTop[i] = 0;
            blockId[i] = 0;
            blocks[i].clear();
        }
        for (int i = 1; i <= n; ++i) {
            dfs1(i, 0);
            dfs2(i, i);
        }
        int lastAnswer = 0;
        for (int i = 1; i <= m; ++i) {
            int operation;
            int x;
            int y;
            readInt(operation);
            readInt(x);
            readInt(y);
            x -= lastAnswer;
            y -= lastAnswer;
            if (operation == 1) {
                linkTree(x, y);
            } else if (operation == 2) {
                modifyValue(x, y);
            } else {
                int limit;
                readInt(limit);
                limit -= lastAnswer;
                answerCount = 0;
                answerProduct = 1 % mod;
                queryPath(x, y, limit);
                printInt(answerCount);
                if (answerCount) {
                    putChar(' ');
                    printInt(answerProduct);
                    lastAnswer = answerProduct;
                } else {
                    lastAnswer = 0;
                }
                putChar('\n');
            }
        }
    }
    flush();
    return 0;
}
