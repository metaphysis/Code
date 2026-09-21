#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool isLeaf;
    int left, right;
};

int addLeaf(vector<Node>& nodes) {
    int id = nodes.size();
    nodes.push_back({true, -1, -1});
    return id;
}

int buildMinTree(int leafCount, vector<Node>& nodes) {
    if (leafCount == 1) return addLeaf(nodes);
    int id = nodes.size();
    nodes.push_back({false, -1, -1});
    int leftId = buildMinTree(1, nodes);
    int rightId = buildMinTree(leafCount - 1, nodes);
    nodes[id].left = leftId;
    nodes[id].right = rightId;
    return id;
}

int getLeafCount(int id, const vector<Node>& nodes) {
    if (nodes[id].isLeaf) return 1;
    return getLeafCount(nodes[id].left, nodes) + getLeafCount(nodes[id].right, nodes);
}

int parseTree(int& pos, const vector<int>& bits, vector<Node>& nodes, bool& valid) {
    if (pos >= bits.size()) {
        valid = false;
        return -1;
    }
    int bit = bits[pos++];
    int id = nodes.size();
    nodes.push_back({bit == 0, -1, -1});
    if (bit == 1) {
        int leftId = parseTree(pos, bits, nodes, valid);
        int rightId = parseTree(pos, bits, nodes, valid);
        nodes[id].left = leftId;
        nodes[id].right = rightId;
    }
    return id;
}

bool getNextLimited(int id, int maxLeaves, vector<Node>& nodes) {
    if (nodes[id].isLeaf) {
        if (maxLeaves < 2) return false;
        int leftId = addLeaf(nodes);
        int rightId = addLeaf(nodes);
        nodes[id].isLeaf = false;
        nodes[id].left = leftId;
        nodes[id].right = rightId;
        return true;
    }
    int leftLeaves, rightLeaves;
    leftLeaves = getLeafCount(nodes[id].left, nodes);
    rightLeaves = getLeafCount(nodes[id].right, nodes);
    if (getNextLimited(nodes[id].right, maxLeaves - leftLeaves, nodes)) return true;
    if (getNextLimited(nodes[id].left, maxLeaves - 1, nodes)) {
        int rightId = addLeaf(nodes);
        nodes[id].right = rightId;
        return true;
    }
    return false;
}

bool getNextFixed(int id, vector<Node>& nodes) {
    if (nodes[id].isLeaf) return false;
    int leftLeaves, rightLeaves, totalLeaves;
    leftLeaves = getLeafCount(nodes[id].left, nodes);
    rightLeaves = getLeafCount(nodes[id].right, nodes);
    totalLeaves = leftLeaves + rightLeaves;
    if (getNextFixed(nodes[id].right, nodes)) return true;
    if (getNextLimited(nodes[id].left, totalLeaves - 1, nodes)) {
        leftLeaves = getLeafCount(nodes[id].left, nodes);
        int rightId = buildMinTree(totalLeaves - leftLeaves, nodes);
        nodes[id].right = rightId;
        return true;
    }
    return false;
}

void encodeTree(int id, const vector<Node>& nodes, unsigned long long& value) {
    value = (value << 1) | (nodes[id].isLeaf ? 0 : 1);
    if (!nodes[id].isLeaf) {
        encodeTree(nodes[id].left, nodes, value);
        encodeTree(nodes[id].right, nodes, value);
    }
}

int solve() {
    int testCount;
    cin >> testCount;
    while (testCount--) {
        unsigned int inputValue;
        cin >> inputValue;
        vector<int> bits;
        if (inputValue == 0) {
            bits.push_back(0);
        } else {
            while (inputValue > 0) {
                bits.push_back(inputValue & 1);
                inputValue >>= 1;
            }
            reverse(bits.begin(), bits.end());
        }
        vector<Node> nodes;
        bool valid = true;
        int pos = 0;
        int root = parseTree(pos, bits, nodes, valid);
        if (!valid || pos != bits.size()) {
            cout << "NO\n";
            continue;
        }
        if (!getNextFixed(root, nodes)) {
            root = buildMinTree(getLeafCount(root, nodes), nodes);
        }
        unsigned long long answer = 0;
        encodeTree(root, nodes, answer);
        cout << answer << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
