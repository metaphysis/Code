#include <bits/stdc++.h>
using namespace std;

const long long modValue = 1000000007;

struct Edge {
    int to, weight;
};

struct Segment {
    int left, right, mode;
};

int n, q, timer;
vector<vector<Edge>> graph;
vector<int> parentNode, depthNode, sizeNode, heavySon, topNode, positionNode;
vector<long long> parentWeight, linearWeight, lucasValue;
vector<long long> baseValue[4], baseSum[4], treeSum, lazyTag[4];

pair<long long, long long> advancePair(int mode, long long first, long long second, int length) {
    int index = mode * 2;
    long long nextFirst = (first * baseValue[index][length] + second * baseValue[index + 1][length]) % modValue;
    long long nextSecond = (first * baseValue[index][length + 1] + second * baseValue[index + 1][length + 1]) % modValue;
    return {nextFirst, nextSecond};
}

void buildBase(int limit) {
    for (int i = 0; i < 4; i++) {
        baseValue[i].assign(limit + 2, 0);
        baseSum[i].assign(limit + 1, 0);
    }
    baseValue[0][0] = 1;
    baseValue[1][1] = 1;
    baseValue[2][0] = 1;
    baseValue[3][1] = 1;
    for (int i = 2; i <= limit + 1; i++) {
        baseValue[0][i] = (baseValue[0][i - 1] + baseValue[0][i - 2]) % modValue;
        baseValue[1][i] = (baseValue[1][i - 1] + baseValue[1][i - 2]) % modValue;
        baseValue[2][i] = (baseValue[2][i - 2] - baseValue[2][i - 1] + modValue) % modValue;
        baseValue[3][i] = (baseValue[3][i - 2] - baseValue[3][i - 1] + modValue) % modValue;
    }
    for (int i = 1; i <= limit; i++)
        for (int j = 0; j < 4; j++)
            baseSum[j][i] = (baseSum[j][i - 1] + baseValue[j][i - 1]) % modValue;
}

void applyTag(int node, int length, int mode, long long first, long long second) {
    int index = mode * 2;
    long long increase = (first * baseSum[index][length] + second * baseSum[index + 1][length]) % modValue;
    treeSum[node] = (treeSum[node] + increase) % modValue;
    lazyTag[index][node] = (lazyTag[index][node] + first) % modValue;
    lazyTag[index + 1][node] = (lazyTag[index + 1][node] + second) % modValue;
}

void pushDown(int node, int leftLength, int rightLength) {
    for (int mode = 0; mode < 2; mode++) {
        int index = mode * 2;
        long long first = lazyTag[index][node], second = lazyTag[index + 1][node];
        if (first == 0 && second == 0) continue;
        applyTag(node * 2, leftLength, mode, first, second);
        pair<long long, long long> nextPair = advancePair(mode, first, second, leftLength);
        applyTag(node * 2 + 1, rightLength, mode, nextPair.first, nextPair.second);
        lazyTag[index][node] = 0;
        lazyTag[index + 1][node] = 0;
    }
}

void updateSegment(int node, int left, int right, int queryLeft, int queryRight, int mode, long long first, long long second) {
    if (queryLeft <= left && right <= queryRight) {
        pair<long long, long long> currentPair = advancePair(mode, first, second, left - queryLeft);
        applyTag(node, right - left + 1, mode, currentPair.first, currentPair.second);
        return;
    }
    int middle = (left + right) / 2;
    pushDown(node, middle - left + 1, right - middle);
    if (queryLeft <= middle) updateSegment(node * 2, left, middle, queryLeft, queryRight, mode, first, second);
    if (queryRight > middle) updateSegment(node * 2 + 1, middle + 1, right, queryLeft, queryRight, mode, first, second);
    treeSum[node] = (treeSum[node * 2] + treeSum[node * 2 + 1]) % modValue;
}

long long querySegment(int node, int left, int right, int queryLeft, int queryRight) {
    if (queryLeft <= left && right <= queryRight) return treeSum[node];
    int middle = (left + right) / 2;
    long long result = 0;
    pushDown(node, middle - left + 1, right - middle);
    if (queryLeft <= middle) result = querySegment(node * 2, left, middle, queryLeft, queryRight);
    if (queryRight > middle) result = (result + querySegment(node * 2 + 1, middle + 1, right, queryLeft, queryRight)) % modValue;
    return result;
}

void buildTree(int node, int left, int right) {
    if (left == right) {
        treeSum[node] = linearWeight[left] % modValue;
        return;
    }
    int middle = (left + right) / 2;
    buildTree(node * 2, left, middle);
    buildTree(node * 2 + 1, middle + 1, right);
    treeSum[node] = (treeSum[node * 2] + treeSum[node * 2 + 1]) % modValue;
}

void prepareHld() {
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    parentNode[1] = 0;
    depthNode[1] = 0;
    parentWeight[1] = 0;
    for (int i = 0; i < (int)order.size(); i++) {
        int current = order[i];
        for (const Edge &edge : graph[current]) {
            if (edge.to == parentNode[current]) continue;
            parentNode[edge.to] = current;
            depthNode[edge.to] = depthNode[current] + 1;
            parentWeight[edge.to] = edge.weight;
            order.push_back(edge.to);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int current = order[i];
        sizeNode[current] = 1;
        heavySon[current] = 0;
        for (const Edge &edge : graph[current]) {
            if (parentNode[edge.to] != current) continue;
            sizeNode[current] += sizeNode[edge.to];
            if (heavySon[current] == 0 || sizeNode[edge.to] > sizeNode[heavySon[current]]) heavySon[current] = edge.to;
        }
    }
    timer = 0;
    vector<pair<int, int>> stackData;
    stackData.push_back({1, 1});
    while (!stackData.empty()) {
        int startNode = stackData.back().first, chainTop = stackData.back().second;
        stackData.pop_back();
        int current = startNode;
        while (current != 0) {
            topNode[current] = chainTop;
            positionNode[current] = ++timer;
            for (const Edge &edge : graph[current])
                if (parentNode[edge.to] == current && edge.to != heavySon[current])
                    stackData.push_back({edge.to, edge.to});
            current = heavySon[current];
        }
    }
    for (int i = 1; i <= n; i++) linearWeight[positionNode[i]] = parentWeight[i];
}

void updatePath(int startNode, int endNode) {
    vector<Segment> firstPart, secondPart;
    int leftNode = startNode, rightNode = endNode;
    firstPart.reserve(32);
    secondPart.reserve(32);
    while (topNode[leftNode] != topNode[rightNode]) {
        if (depthNode[topNode[leftNode]] >= depthNode[topNode[rightNode]]) {
            firstPart.push_back({positionNode[topNode[leftNode]], positionNode[leftNode], 1});
            leftNode = parentNode[topNode[leftNode]];
        } else {
            secondPart.push_back({positionNode[topNode[rightNode]], positionNode[rightNode], 0});
            rightNode = parentNode[topNode[rightNode]];
        }
    }
    if (depthNode[leftNode] >= depthNode[rightNode]) {
        if (positionNode[rightNode] + 1 <= positionNode[leftNode]) firstPart.push_back({positionNode[rightNode] + 1, positionNode[leftNode], 1});
    } else {
        if (positionNode[leftNode] + 1 <= positionNode[rightNode]) secondPart.push_back({positionNode[leftNode] + 1, positionNode[rightNode], 0});
    }
    int offset = 0;
    for (const Segment &segment : firstPart) {
        int length = segment.right - segment.left + 1;
        long long first = lucasValue[offset + length], second = lucasValue[offset + length - 1];
        updateSegment(1, 1, n, segment.left, segment.right, 1, first, second);
        offset += length;
    }
    for (int i = (int)secondPart.size() - 1; i >= 0; i--) {
        int length = secondPart[i].right - secondPart[i].left + 1;
        long long first = lucasValue[offset + 1], second = lucasValue[offset + 2];
        updateSegment(1, 1, n, secondPart[i].left, secondPart[i].right, 0, first, second);
        offset += length;
    }
}

long long queryPath(int startNode, int endNode) {
    long long result = 0;
    while (topNode[startNode] != topNode[endNode]) {
        if (depthNode[topNode[startNode]] < depthNode[topNode[endNode]]) swap(startNode, endNode);
        result = (result + querySegment(1, 1, n, positionNode[topNode[startNode]], positionNode[startNode])) % modValue;
        startNode = parentNode[topNode[startNode]];
    }
    if (depthNode[startNode] < depthNode[endNode]) swap(startNode, endNode);
    if (positionNode[endNode] + 1 <= positionNode[startNode])
        result = (result + querySegment(1, 1, n, positionNode[endNode] + 1, positionNode[startNode])) % modValue;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        graph.assign(n + 1, {});
        parentNode.assign(n + 1, 0);
        depthNode.assign(n + 1, 0);
        sizeNode.assign(n + 1, 0);
        heavySon.assign(n + 1, 0);
        topNode.assign(n + 1, 0);
        positionNode.assign(n + 1, 0);
        parentWeight.assign(n + 1, 0);
        linearWeight.assign(n + 1, 0);
        for (int i = 1; i < n; i++) {
            int a, b, weight;
            cin >> a >> b >> weight;
            graph[a].push_back({b, weight});
            graph[b].push_back({a, weight});
        }
        lucasValue.assign(n + 3, 0);
        lucasValue[0] = 1;
        lucasValue[1] = 3;
        lucasValue[2] = 4;
        for (int i = 3; i <= n + 2; i++) lucasValue[i] = (lucasValue[i - 1] + lucasValue[i - 2]) % modValue;
        prepareHld();
        buildBase(n);
        treeSum.assign(4 * n + 5, 0);
        for (int i = 0; i < 4; i++) lazyTag[i].assign(4 * n + 5, 0);
        buildTree(1, 1, n);
        cin >> q;
        while (q--) {
            int type, a, b;
            cin >> type >> a >> b;
            if (type == 1) cout << queryPath(a, b) << '\n';
            else updatePath(a, b);
        }
    }
    return 0;
}
