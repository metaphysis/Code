#include <bits/stdc++.h>
using namespace std;

struct Node {
    char nodeType;
    int value, childId;
    string propName;
};

string expression;
int currentPos;
vector<Node> nodes;

int parseExpr() {
    char op = expression[currentPos];
    if (op == 'A' || op == 'S') {
        ++currentPos;
        int number = 0;
        while (currentPos < static_cast<int>(expression.size()) && isdigit(expression[currentPos])) {
            number = number * 10 + expression[currentPos] - '0';
            ++currentPos;
        }
        int childId = parseExpr();
        Node node;
        node.nodeType = op;
        node.value = number;
        node.childId = childId;
        node.propName = "";
        nodes.push_back(node);
        return static_cast<int>(nodes.size()) - 1;
    } else if (op == 'N') {
        ++currentPos;
        int childId = parseExpr();
        Node node;
        node.nodeType = op;
        node.value = 0;
        node.childId = childId;
        node.propName = "";
        nodes.push_back(node);
        return static_cast<int>(nodes.size()) - 1;
    } else {
        int startPos = currentPos;
        currentPos = static_cast<int>(expression.size());
        Node node;
        node.nodeType = 'P';
        node.value = 0;
        node.childId = -1;
        node.propName = expression.substr(startPos);
        nodes.push_back(node);
        return static_cast<int>(nodes.size()) - 1;
    }
}

bool evaluateExpr(int rootId, int planetCount, const vector<unordered_set<string>>& planets) {
    vector<vector<char>> dp(nodes.size(), vector<char>(planetCount, 0));
    for (int nodeId = 0; nodeId < static_cast<int>(nodes.size()); ++nodeId) {
        Node& node = nodes[nodeId];
        if (node.nodeType == 'P') {
            for (int i = 0; i < planetCount; ++i)
                dp[nodeId][i] = planets[i].count(node.propName) > 0;
        } else if (node.nodeType == 'N') {
            for (int i = 0; i < planetCount; ++i)
                dp[nodeId][i] = i + 1 >= planetCount || dp[node.childId][i + 1];
        } else {
            vector<char> allTrue(planetCount + 1, 1), anyTrue(planetCount + 1, 0);
            for (int i = planetCount - 1; i >= 0; --i) {
                allTrue[i] = allTrue[i + 1] && dp[node.childId][i];
                anyTrue[i] = anyTrue[i + 1] || dp[node.childId][i];
            }
            for (int i = 0; i < planetCount; ++i) {
                int start = i + node.value;
                if (node.nodeType == 'A')
                    dp[nodeId][i] = start >= planetCount || allTrue[start];
                else
                    dp[nodeId][i] = start >= planetCount || anyTrue[start];
            }
        }
    }
    return dp[rootId][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int planetCount, queryCount;
    bool firstCase = true;
    while (cin >> planetCount) {
        string line;
        getline(cin, line);
        vector<unordered_set<string>> planets(planetCount);
        for (int i = 0; i < planetCount; ++i) {
            getline(cin, line);
            stringstream input(line);
            string propName;
            while (input >> propName)
                planets[i].insert(propName);
        }
        cin >> queryCount;
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        for (int i = 0; i < queryCount; ++i) {
            cin >> expression;
            currentPos = 0;
            nodes.clear();
            int rootId = parseExpr();
            cout << (evaluateExpr(rootId, planetCount, planets) ? "yes" : "no") << '\n';
        }
    }
    return 0;
}
