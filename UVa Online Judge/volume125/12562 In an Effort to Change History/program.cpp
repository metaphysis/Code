#include <bits/stdc++.h>
using namespace std;

struct AstNode {
    int type, value, left, right;
};

vector<AstNode> nodes;
string expr;
int exprPos;
int bRoot[20], cRoot[20], senseMask;
int x, y, z;
int baseAMask, baseBMask, baseFuture;
int bestFuture, bestChangeCount, bestList[20];

int parseOr();
int parseAnd();
int parseUnary();
int parsePrimary();

int addNode(int type, int value, int left, int right) {
    AstNode node;
    node.type = type;
    node.value = value;
    node.left = left;
    node.right = right;
    nodes.push_back(node);
    return (int)nodes.size() - 1;
}

int parsePrimary() {
    if (expr[exprPos] == '(') {
        ++exprPos;
        int nodeId = parseOr();
        ++exprPos;
        return nodeId;
    }
    int type = expr[exprPos] == 'a' ? 0 : 1;
    ++exprPos;
    int index = 0;
    while (exprPos < (int)expr.size() && isdigit(expr[exprPos])) {
        index = index * 10 + expr[exprPos] - '0';
        ++exprPos;
    }
    return addNode(0, type * 100 + index, -1, -1);
}

int parseUnary() {
    if (expr[exprPos] == '!') {
        ++exprPos;
        int child = parseUnary();
        return addNode(1, 0, child, -1);
    }
    return parsePrimary();
}

int parseAnd() {
    int left = parseUnary();
    while (expr.compare(exprPos, 2, "&&") == 0) {
        exprPos += 2;
        int right = parseUnary();
        left = addNode(2, 0, left, right);
    }
    return left;
}

int parseOr() {
    int left = parseAnd();
    while (expr.compare(exprPos, 2, "||") == 0) {
        exprPos += 2;
        int right = parseAnd();
        left = addNode(3, 0, left, right);
    }
    return left;
}

int buildExpr(const string &line) {
    int equalPos = line.find('=');
    expr = line.substr(equalPos + 1);
    exprPos = 0;
    return parseOr();
}

int evalNode(int nodeId, int aMask, int bMask) {
    AstNode &node = nodes[nodeId];
    if (node.type == 0) {
        int eventType = node.value / 100;
        int index = node.value % 100;
        if (eventType == 0)
            return (aMask >> (index - 1)) & 1;
        return (bMask >> (index - 1)) & 1;
    }
    if (node.type == 1)
        return !evalNode(node.left, aMask, bMask);
    if (node.type == 2)
        return evalNode(node.left, aMask, bMask) && evalNode(node.right, aMask, bMask);
    return evalNode(node.left, aMask, bMask) || evalNode(node.right, aMask, bMask);
}

int getBMask(int aMask) {
    int bMask = 0;
    for (int i = 1; i <= y; ++i)
        if (evalNode(bRoot[i], aMask, 0))
            bMask |= 1 << (i - 1);
    return bMask;
}

int getFutureCount(int bMask) {
    int result = 0;
    for (int i = 1; i <= z; ++i)
        result += evalNode(cRoot[i], 0, bMask);
    return result;
}

bool isLexSmaller(int curList[], int curCount) {
    for (int i = 0; i < curCount; ++i) {
        if (curList[i] != bestList[i])
            return curList[i] < bestList[i];
    }
    return false;
}

void solveCase(int caseId) {
    cin >> x >> y >> z;
    baseAMask = 0;
    for (int i = 1; i <= x; ++i) {
        int value;
        cin >> value;
        if (value)
            baseAMask |= 1 << (i - 1);
    }
    nodes.clear();
    senseMask = 0;
    for (int i = 1; i <= y; ++i) {
        string line;
        cin >> line;
        if (line[0] == '*') {
            senseMask |= 1 << (i - 1);
            line = line.substr(1);
        }
        bRoot[i] = buildExpr(line);
    }
    for (int i = 1; i <= z; ++i) {
        string line;
        cin >> line;
        cRoot[i] = buildExpr(line);
    }
    baseBMask = getBMask(baseAMask);
    baseFuture = getFutureCount(baseBMask);
    bestFuture = -1;
    bestChangeCount = INT_MAX;
    int totalMask = 1 << x;
    for (int aMask = 0; aMask < totalMask; ++aMask) {
        int bMask = getBMask(aMask);
        if ((bMask & senseMask) != (baseBMask & senseMask))
            continue;
        int futureCount = getFutureCount(bMask);
        int changeCount = __builtin_popcount((unsigned)(aMask ^ baseAMask));
        int curList[20], curCount = 0;
        for (int i = 1; i <= x; ++i)
            if (((aMask ^ baseAMask) >> (i - 1)) & 1)
                curList[curCount++] = i;
        bool update = false;
        if (futureCount > bestFuture)
            update = true;
        else if (futureCount == bestFuture && changeCount < bestChangeCount)
            update = true;
        else if (futureCount == bestFuture && changeCount == bestChangeCount && isLexSmaller(curList, curCount))
            update = true;
        if (update) {
            bestFuture = futureCount;
            bestChangeCount = changeCount;
            for (int i = 0; i < curCount; ++i)
                bestList[i] = curList[i];
        }
    }
    cout << "Case " << caseId << ": ";
    if (bestFuture <= baseFuture) {
        cout << "Unable to improve future." << '\n' << '\n';
        return;
    }
    cout << "Increased from " << baseFuture << " to " << bestFuture << "." << '\n';
    for (int i = 0; i < bestChangeCount; ++i) {
        if (i)
            cout << ' ';
        cout << 'a' << bestList[i];
    }
    cout << '\n' << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId)
        solveCase(caseId);
    return 0;
}
