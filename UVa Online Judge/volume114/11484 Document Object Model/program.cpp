// Document Object Model
// UVa ID: 11484
// Verdict: Accepted
// Submission Date: 2026-01-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 定义DOM树节点结构体
struct Node {
    string value; // 节点的值
    Node* parent; // 指向父节点的指针
    vector<Node*> children; // 存储所有子节点指针的向量
    Node(const string& v) : value(v), parent(nullptr) {} // 构造函数
};

int main() {
    int caseNum = 1; // 用例编号
    int n;
    // 循环处理每个测试用例，直到遇到 n=0
    while (cin >> n && n) {
        cin.ignore(); // 忽略n后面的换行符
        vector<string> lines(n);
        for (int i = 0; i < n; ++i) getline(cin, lines[i]); // 读入文档的每一行

        Node* root = nullptr; // 树的根节点
        Node* current = nullptr; // 当前指针，初始为nullptr
        stack<Node*> nodeStack; // 辅助建树的栈

        // 步骤一：构建DOM树
        for (const string& line : lines) {
            // 判断是否为开始标签
            if (line.find("<n value='") != string::npos) {
                // 解析value属性的值
                int start = line.find("'") + 1;
                int end = line.find_last_of("'");
                string value = line.substr(start, end - start);
                // 创建新节点
                Node* newNode = new Node(value);
                if (nodeStack.empty()) {
                    // 栈为空，新节点是根节点
                    root = newNode;
                    current = newNode; // 初始指针指向根节点
                } else {
                    // 栈非空，新节点是栈顶节点的子节点
                    newNode->parent = nodeStack.top();
                    nodeStack.top()->children.push_back(newNode);
                }
                nodeStack.push(newNode); // 新节点入栈
            } else if (line == "</n>") {
                // 遇到结束标签，关闭当前栈顶元素
                nodeStack.pop();
            }
        }

        int i;
        cin >> i; // 读入指令数量
        vector<string> instructions(i);
        for (int j = 0; j < i; ++j) cin >> instructions[j]; // 读入所有指令

        // 输出用例编号
        cout << "Case " << caseNum++ << ":" << endl;
        // 重置当前指针为根节点，开始模拟指令
        current = root;
        for (const string& instr : instructions) {
            if (instr == "first_child") {
                // 移动到第一个子节点
                if (!current->children.empty()) current = current->children[0];
            } else if (instr == "next_sibling") {
                // 移动到下一个兄弟节点
                if (current->parent) {
                    vector<Node*>& siblings = current->parent->children;
                    auto it = find(siblings.begin(), siblings.end(), current);
                    if (it + 1 != siblings.end()) current = *(it + 1);
                }
            } else if (instr == "previous_sibling") {
                // 移动到上一个兄弟节点
                if (current->parent) {
                    vector<Node*>& siblings = current->parent->children;
                    auto it = find(siblings.begin(), siblings.end(), current);
                    if (it != siblings.begin()) current = *(it - 1);
                }
            } else if (instr == "parent") {
                // 移动到父节点
                if (current->parent) current = current->parent;
            }
            // 输出执行指令后当前节点的值
            cout << current->value << endl;
        }
    }
    return 0;
}
