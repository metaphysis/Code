[UVa 174 Strategy](https://blog.csdn.net/metaphysis/article/details/160705690)

## 题目分析

本题是一个博弈策略模拟问题。两个玩家同时选择 $\texttt{TRADE}$ 或 $\texttt{CHEAT}$，根据组合结果获得不同分数：

- 双方都 $\texttt{TRADE}$：各得 $1$ 分
- 一方 $\texttt{TRADE}$，另一方 $\texttt{CHEAT}$：$\texttt{TRADE}$ 方得 $-2$ 分，$\texttt{CHEAT}$ 方得 $2$ 分
- 双方都 $\texttt{CHEAT}$：各得 $-1$ 分

每个策略由一个简单的程序描述，程序支持条件判断和基本命令。条件可以访问最近两次交锋的历史记录（自己的或对方的）。

题目要求读入最多 $10$ 个策略程序，让每个策略与其它每个策略对战 $10$ 次（不与自己对战），输出每个策略的最终总分。

## 解题思路

### 1. 解析策略程序

程序遵循给定的文法规则：
- 基本命令：$\texttt{TRADE}$ 或 $\texttt{CHEAT}$
- 条件语句：$\texttt{IF condition THEN statement ELSE statement}$
- 条件：可以组合 $\texttt{AND}$ / $\texttt{OR}$，比较 $\texttt{MY LAST1}$、$\texttt{YOUR LAST2}$ 等与 $\texttt{TRADE}$、$\texttt{CHEAT}$ 或 $\texttt{NULL}$ 是否相等或不等于

解析采用递归下降方法。每个节点可能是命令节点（叶子）或条件节点（内部节点）。对于条件节点，提取条件字符串，并递归解析 $\texttt{THEN}$ 和 $\texttt{ELSE}$ 分支。

### 2. 条件求值

条件表达式支持：
- 原子条件：如 $\texttt{MY LAST1 = CHEAT}$
- 复合条件：使用 $\texttt{AND}$ 和 $\texttt{OR}$ 连接

求值时，根据当前记忆的历史记录（最多最近两次交锋）判断条件真伪。注意处理 $\texttt{NULL}$ 表示“未发生交锋”的情况。

### 3. 对战模拟

对于每对不同的策略 $i$ 和 $j$：
- 初始化双方的历史记录为空
- 重复 $10$ 次：
  - 根据各自的历史记录（注意角色互换：对 $i$ 来说是 “$\texttt{MY}$” 的历史是它之前对 $j$ 的动作，“$\texttt{YOUR}$” 是 $j$ 的动作；对 $j$ 则相反）
  - 解析得到本轮动作
  - 更新历史记录
  - 根据规则计算分数累加到双方总分

### 4. 输出

每个策略的总分右对齐，宽度为 $3$。

## 代码实现

```cpp
// Strategy
// UVa ID: 174
// Verdict: Accepted
// Submission Date: 2016-03-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 定义动作类型常量
const int TRADE = 0;      // 合作
const int CHEAT = 1;      // 欺骗
const int CONDITION = 2;  // 条件节点
const int NONE = 3;       // 表示NULL，即未发生交锋

// 语法树节点结构
struct node {
    int category;                   // 节点类型：TRADE / CHEAT / CONDITION
    string conditions;              // 条件字符串（仅当 category == CONDITION 时有效）
    node *leftChild, *rightChild;   // 条件节点的 THEN 和 ELSE 分支
};

vector<string> programs;   // 存储所有程序字符串
vector<node*> nodes;       // 存储所有解析后的语法树根节点

// 去除程序字符串末尾空格和制表符，并移除末尾的句点
string spaceOut(string line) {
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    line.erase(line.end() - 1);  // 移除句点
    return line;
}

// 全局解析状态
string strategy;  // 当前正在解析的程序
int idx = 0;      // 当前解析位置

// 递归解析策略程序，构建语法树
void parseStrategy(node *parent) {
    if (idx >= strategy.length()) return;
    if (strategy[idx] == 'T')  { // TRADE 命令
        parent->category = TRADE;
        parent->leftChild = NULL;
        parent->rightChild = NULL;
        idx += 5;  // 跳过 "TRADE"
    } else if (strategy[idx] == 'C')  { // CHEAT 命令
        parent->category = CHEAT;
        parent->leftChild = NULL;
        parent->rightChild = NULL;
        idx += 5;  // 跳过 "CHEAT"
    } else if (strategy[idx] == 'I')  {// IF 条件语句
        parent->category = CONDITION;
        idx += 2;  // 跳过 "IF"
        // 找到 THEN 的位置，提取条件字符串
        int thenIndex = strategy.find("THEN", idx);
        parent->conditions = strategy.substr(idx, thenIndex - idx);
        idx = thenIndex + 4;  // 跳过 "THEN"
        // 解析 THEN 分支
        node *leftNode = new node;
        parseStrategy(leftNode);
        parent->leftChild = leftNode;
        idx += 4;  // 跳过 "ELSE"
        // 解析 ELSE 分支
        node *rightNode = new node;
        parseStrategy(rightNode);
        parent->rightChild = rightNode;
    }
}

// 求值一个原子条件，如 "MY LAST1 = CHEAT"
// part: 条件字符串，如 "MY LAST1 = CHEAT"
// my: 自己的历史动作序列（最近的在末尾）
// your: 对方的历史动作序列
bool evaluatePart(string part, vector<int>& my, vector<int>& your)
{
    bool isEqual = true;   // 默认是比较相等
    int op = part.find("=");
    if (op == part.npos)   { // 找不到等号，则尝试不等号
        op = part.find("#");
        isEqual = false;   // 不等比较
    }
    // 获取比较的右操作数
    int right = NONE;
    if (part[op + 1] == 'T') right = TRADE;
    if (part[op + 1] == 'C') right = CHEAT;
    // 获取 LAST1 或 LAST2 中的数字
    int idx = part[op - 1] - '0';
    if (part[0] == 'M')  { // MY LAST...
        if (idx > my.size())  // 历史记录不足，视为 NULL
            return isEqual ? NONE == right : NONE != right;
        else
            return isEqual ? my[my.size() - idx] == right : my[my.size() - idx] != right;
    } else  { // YOUR LAST...
        if (idx > your.size())
            return isEqual ? NONE == right : NONE != right;
        else
            return isEqual ? your[your.size() - idx] == right : your[your.size() - idx] != right;
    }
}

// 递归求值复合条件（支持 AND / OR）
bool evaluate(string conditions, vector<int>& my, vector<int>& your) {
    int orIndex = conditions.find("OR", 0);
    int andIndex = conditions.find("AND", 0);
    // 原子条件，直接求值
    if (orIndex == conditions.npos && andIndex == conditions.npos)
        return evaluatePart(conditions, my, your);
    int opIndex, nextIndex;
    bool isAnd = false;
    // 确定优先级：先找位置靠前的操作符
    if (orIndex == conditions.npos) {
        opIndex = andIndex;
        nextIndex = andIndex + 3;
        isAnd = true;
    } else if (andIndex == conditions.npos) {
        opIndex = orIndex;
        nextIndex = orIndex + 2;
    } else if (orIndex < andIndex) {
        opIndex = orIndex;
        nextIndex = orIndex + 2;
    } else {
        opIndex = andIndex;
        nextIndex = andIndex + 3;
        isAnd = true;
    }
    // 递归求值左右部分
    bool leftPart = evaluatePart(conditions.substr(0, opIndex), my, your);
    bool rightPart = evaluate(conditions.substr(nextIndex), my, your);
    return isAnd ? (leftPart && rightPart) : (leftPart || rightPart);
}

// 根据当前历史记录，执行策略树得到本轮动作
int getStrategy(node *parent, vector<int>& my, vector<int>& your) {
    if (parent->category == TRADE || parent->category == CHEAT)
        return parent->category;
    // 条件节点：根据条件真假选择分支
    return evaluate(parent->conditions, my, your) ?
        getStrategy(parent->leftChild, my, your) :
        getStrategy(parent->rightChild, my, your);
}

// 模拟一局对战，更新双方历史记录和分数
vector<int> myMemory, yourMemory;  // 临时存储当前对战的历史
int scores = 0;                    // 当前策略的总分

void execute(int i, int j) {
    // 获取双方本轮动作
    int my = getStrategy(nodes[i], myMemory, yourMemory);
    int your = getStrategy(nodes[j], yourMemory, myMemory);
    // 更新历史记录
    myMemory.push_back(my);
    yourMemory.push_back(your);
    // 根据规则计算分数
    if (my == TRADE && your == TRADE) scores++;
    if (my == CHEAT && your == CHEAT) scores--;
    if (my == TRADE && your == CHEAT) scores -= 2;
    if (my == CHEAT && your == TRADE) scores += 2;
}

// 主对战逻辑
void play() {
    // 解析所有程序
    for (int i = 0; i < programs.size(); i++) {
        idx = 0;
        strategy = programs[i];
        node *root = new node;
        parseStrategy(root);
        nodes.push_back(root);
    }
    // 对每个策略 i
    for (int i = 0; i < nodes.size(); i++) {
        scores = 0;
        // 与除自己外的每个策略 j 对战
        for (int j = 0; j < nodes.size(); j++) {
            if (i == j) continue;
            myMemory.clear();
            yourMemory.clear();
            // 对战 10 次
            for (int k = 1; k <= 10; k++) execute(i, j);
        }
        // 输出最终分数，右对齐宽度 3
        cout << right << setw(3) << scores << "\n";
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0); cout.sync_with_stdio(false);
    string line, program;
    while (getline(cin, line), line != "#") {
        program += line;
        // 遇到句点表示一个程序结束
        if (line.find('.') != line.npos) {
            programs.push_back(spaceOut(program));
            program.clear();
        }
    }
    play();
    return 0;
}
```

## 要点总结

1. **语法解析**：采用递归下降法，每个 $\texttt{IF}$ 语句对应一个内部节点，左右子节点分别对应 $\texttt{THEN}$ 和 $\texttt{ELSE}$ 分支。
2. **历史记录管理**：使用两个向量分别存储自己和对方的历史动作，方便按 $\texttt{LAST1}$、$\texttt{LAST2}$ 索引。
3. **条件求值**：支持 $\texttt{AND}$ / $\texttt{OR}$ 的短路求值逻辑，正确处理 $\texttt{NULL}$ 情况。
4. **对战模拟**：注意 $i$ 对 $j$ 时，双方历史记录的角色是互换的。
