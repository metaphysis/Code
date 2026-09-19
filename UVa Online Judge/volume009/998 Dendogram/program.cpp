#include <bits/stdc++.h>
using namespace std;

struct Node {
    float value;
    string label;
    int leftChild, rightChild;
};

bool nodeLess(const vector<Node> &nodes, int first, int second) {
    if (nodes[first].value != nodes[second].value)
        return nodes[first].value < nodes[second].value;
    return nodes[first].label < nodes[second].label;
}

bool pairLess(const vector<Node> &nodes, int first, int second, int bestFirst, int bestSecond) {
    if (nodeLess(nodes, first, bestFirst))
        return true;
    if (nodeLess(nodes, bestFirst, first))
        return false;
    return nodeLess(nodes, second, bestSecond);
}

bool isBetterPair(const vector<Node> &nodes, int first, int second, int bestFirst, int bestSecond, float difference, float bestDifference) {
    if (bestFirst == -1)
        return true;
    if (difference != bestDifference)
        return difference < bestDifference;
    return pairLess(nodes, first, second, bestFirst, bestSecond);
}

int buildTree(const vector<float> &values, vector<Node> &nodes) {
    vector<int> activeNodes;
    for (int i = 0; i < static_cast<int>(values.size()); i++) {
        Node node;
        node.value = values[i];
        node.label = string(1, static_cast<char>('a' + i));
        node.leftChild = -1;
        node.rightChild = -1;
        nodes.push_back(node);
        activeNodes.push_back(i);
    }
    while (activeNodes.size() > 1) {
        int bestFirst = -1, bestSecond = -1;
        float bestDifference = 0.0f;
        for (int i = 0; i < static_cast<int>(activeNodes.size()); i++) {
            for (int j = i + 1; j < static_cast<int>(activeNodes.size()); j++) {
                int first = activeNodes[i], second = activeNodes[j];
                if (nodeLess(nodes, second, first))
                    swap(first, second);
                float difference = fabs(nodes[first].value - nodes[second].value);
                if (isBetterPair(nodes, first, second, bestFirst, bestSecond, difference, bestDifference)) {
                    bestFirst = first;
                    bestSecond = second;
                    bestDifference = difference;
                }
            }
        }
        Node cluster;
        cluster.value = (nodes[bestFirst].value + nodes[bestSecond].value) / 2.0f;
        cluster.label = nodes[bestFirst].label + nodes[bestSecond].label;
        cluster.leftChild = bestFirst;
        cluster.rightChild = bestSecond;
        int clusterIndex = static_cast<int>(nodes.size());
        nodes.push_back(cluster);
        vector<int> nextNodes;
        for (int nodeIndex : activeNodes)
            if (nodeIndex != bestFirst && nodeIndex != bestSecond)
                nextNodes.push_back(nodeIndex);
        nextNodes.push_back(clusterIndex);
        activeNodes = nextNodes;
    }
    return activeNodes[0];
}

void printInfix(const vector<Node> &nodes, int root) {
    if (nodes[root].leftChild != -1)
        printInfix(nodes, nodes[root].leftChild);
    cout << static_cast<int>(nodes[root].value + 0.5f) << "," << nodes[root].label << '\n';
    if (nodes[root].rightChild != -1)
        printInfix(nodes, nodes[root].rightChild);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<float> values;
    float value;
    bool firstCase = true;
    while (cin >> value) {
        if (value != 0.0f) {
            values.push_back(value);
            continue;
        }
        if (values.empty())
            continue;
        if (!firstCase)
            cout << '\n';
        vector<Node> nodes;
        int root = buildTree(values, nodes);
        printInfix(nodes, root);
        values.clear();
        firstCase = false;
    }
    return 0;
}
