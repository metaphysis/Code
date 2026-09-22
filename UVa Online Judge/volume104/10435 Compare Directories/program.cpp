#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    long long size;
    bool isDir;
    vector<int> children;
};

vector<Node> nodes;

string trim(const string &text) {
    size_t left = text.find_first_not_of(" \t\r\n"), right = text.find_last_not_of(" \t\r\n");
    if (left == string::npos) return "";
    return text.substr(left, right - left + 1);
}

bool readLine(string &line) {
    while (getline(cin, line)) {
        line = trim(line);
        if (!line.empty()) return true;
    }
    return false;
}

string takeLast(string &text) {
    size_t pos = text.find_last_of(" \t");
    string token;
    if (pos == string::npos) {
        token = text;
        text.clear();
    } else {
        token = text.substr(pos + 1);
        text = trim(text.substr(0, pos));
    }
    return token;
}

int readNode() {
    string line, token;
    readLine(line);
    token = takeLast(line);
    Node node;
    node.size = stoll(token);
    node.isDir = line.size() >= 5 && line.compare(line.size() - 5, 5, "<DIR>") == 0;
    if (node.isDir) line = trim(line.substr(0, line.size() - 5));
    node.name = line;
    int nodeId = (int)nodes.size(), childCount = node.isDir ? (int)node.size : 0;
    nodes.push_back(node);
    for (int i = 0; i < childCount; ++i) {
        int childId = readNode();
        nodes[nodeId].children.push_back(childId);
    }
    return nodeId;
}

string joinPath(const string &base, const string &name) {
    if (base.empty()) return name;
    if (base.back() == '/') return base + name;
    return base + "/" + name;
}

string indent(int depth) {
    return string(depth * 4, ' ');
}

void printNode(int nodeId, int depth) {
    const Node &node = nodes[nodeId];
    cout << indent(depth) << node.name;
    if (node.isDir) cout << " <DIR> " << node.children.size() << " object(s)\n";
    else cout << " " << node.size << " byte(s)\n";
}

bool printMissing(const string &path, const vector<int> &children, const vector<char> &matched, int depth) {
    bool hasMissing = false;
    int childCount = (int)children.size();
    for (int i = 0; i < childCount; ++i) {
        if (matched[i]) continue;
        if (!hasMissing) {
            cout << indent(depth + 1) << "\"" << path << "\" lacks of following file(s)\n";
            hasMissing = true;
        }
        printNode(children[i], depth + 2);
    }
    return hasMissing;
}

bool compareDirs(int leftId, int rightId, const string &leftPath, const string &rightPath, int depth) {
    const vector<int> &left = nodes[leftId].children, &right = nodes[rightId].children;
    map<string, int> rightPos;
    vector<pair<int, int>> common;
    vector<char> leftMatched(left.size(), 0), rightMatched(right.size(), 0);
    bool same = true;
    int leftCount = (int)left.size(), rightCount = (int)right.size();
    cout << indent(depth) << "Comparing \"" << leftPath << "\" with \"" << rightPath << "\".\n";
    for (int i = 0; i < rightCount; ++i) rightPos[nodes[right[i]].name] = i;
    for (int i = 0; i < leftCount; ++i) {
        auto it = rightPos.find(nodes[left[i]].name);
        if (it == rightPos.end()) continue;
        common.push_back(make_pair(i, it->second));
        leftMatched[i] = 1;
        rightMatched[it->second] = 1;
    }
    if (common.empty()) {
        cout << indent(depth) << "Totally different.\n";
        return false;
    }
    for (const auto &item : common) {
        int leftIdx = item.first, rightIdx = item.second;
        int leftChild = left[leftIdx], rightChild = right[rightIdx];
        const Node &leftNode = nodes[leftChild], &rightNode = nodes[rightChild];
        string leftFile = joinPath(leftPath, leftNode.name), rightFile = joinPath(rightPath, rightNode.name);
        if (!leftNode.isDir && !rightNode.isDir) {
            if (leftNode.size != rightNode.size) {
                cout << indent(depth + 1) << "File size mismatch : \"" << leftFile << " (" << leftNode.size
                     << ")\" and \"" << rightFile << " (" << rightNode.size << ")\".\n";
                same = false;
            }
        } else {
            bool childSame = compareDirs(leftChild, rightChild, leftFile, rightFile, depth + 1);
            if (!childSame) same = false;
        }
    }
    if (printMissing(leftPath, right, rightMatched, depth)) same = false;
    if (printMissing(rightPath, left, leftMatched, depth)) same = false;
    cout << indent(depth);
    if (same) cout << "No difference.\n";
    else cout << "Difference(s) encountered.\n";
    return same;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string date, leftRoot, rightRoot;
    int transactionId = 0;
    cout << "==== Begin of Comparison ====\n";
    while (readLine(date)) {
        nodes.clear();
        readLine(leftRoot);
        int leftId = readNode(), rightId;
        readLine(rightRoot);
        rightId = readNode();
        if (transactionId > 0) cout << '\n';
        ++transactionId;
        cout << "Transaction #" << transactionId << " : Date " << date << '\n';
        string leftPath = joinPath(leftRoot, nodes[leftId].name), rightPath = joinPath(rightRoot, nodes[rightId].name);
        compareDirs(leftId, rightId, leftPath, rightPath, 0);
    }
    cout << "==== End of Comparison ====\n";
    return 0;
}
