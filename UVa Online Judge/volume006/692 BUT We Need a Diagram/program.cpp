// BUT We Need a Diagram
// UVa ID: 692
// Verdict: Accepted
// Submission Date: 2026-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 表达式树的节点结构
// label: 节点的字母标签
// type: 0-叶子，1-一元，2-二元
// left, right: 左右子节点指针
struct Node {
    char label;
    int type;
    Node *left, *right;
    Node(char g, int t = 0) : label(g), type(t), left(0), right(0) {}
};

// 递归下降解析表达式，idx为当前读取位置
// 返回解析得到的树根节点
Node* parse(const string& s, int& idx) {
    char label = s[idx++];
    // 如果当前字符后紧跟 '('，说明有子表达式
    if (idx < s.size() && s[idx] == '(') {
        idx++;
        Node* left = parse(s, idx);
        // 如果遇到 ','，则是二元节点
        if (idx < s.size() && s[idx] == ',') {
            idx++;
            Node* right = parse(s, idx);
            idx++; // 跳过 ')'
            Node* node = new Node(label, 2);
            node->left = left;
            node->right = right;
            return node;
        } else { // 否则是一元节点
            idx++; // 跳过 ')'
            Node* node = new Node(label, 1);
            node->left = left;
            return node;
        }
    }
    // 无括号，叶子节点
    return new Node(label, 0);
}

// 图表类型：二维字符矩阵，每行是一个 vector<char>
using Grid = vector<vector<char>>;
using Row = vector<char>;

// 去除图表的公共前导空格和尾随空格，使图表最紧凑
void cut(Grid& g) {
    // 循环去除所有行的公共前导空格
    while (1) {
        int space = 1;
        for (int i = 0; i < g.size(); i++)
            if (g[i].front() != ' ')
                space = 0;
        if (space) {
            for (int i = 0; i < g.size(); i++)
                g[i].erase(g[i].begin());
        } else break;
    }
    // 循环去除所有行的公共尾随空格
    while (1) {
        int space = 1;
        for (int i = 0; i < g.size(); i++)
            if (g[i].back() != ' ')
                space = 0;
        if (space) {
            for (int i = 0; i < g.size(); i++)
                g[i].pop_back();
        } else break;
    }
}

// 合并左右子图，返回合并后的紧凑图表
Grid merge(Grid g1, Grid g2) {
    Grid g;
    // 确定垂直对齐所需的最大行数（根行对齐到底部）
    int rows = max(g1.size(), g2.size());
    // 高度不足的子图在顶部插入空行
    while (g1.size() < rows) g1.insert(g1.begin(), Row(g1.back().size(), ' '));
    while (g2.size() < rows) g2.insert(g2.begin(), Row(g2.back().size(), ' '));
    
    // 关键技巧：给左子图右侧增加一个空格列，保证初始状态左右子图至少隔一列
    for (int i = 0; i < rows; i++) g1[i].push_back(' ');
    
    // 将左右子图宽度统一补齐到相同值 s，便于使用统一的下标索引
    int s = max(g1[0].size(), g2[0].size());
    while (g1[0].size() < s) for (int i = 0; i < rows; i++) g1[i].insert(g1[i].begin(), ' ');
    while (g2[0].size() < s) for (int i = 0; i < rows; i++) g2[i].push_back(' ');
    
    // 计算每行左右最近非空字符之间的列差（即间隔空格数），取最小值 d
    // d 表示至少需要间隔多少列（包括新增的那一列）
    int d = INT_MAX;
    for (int i = 0; i < rows; i++) {
        int j = s - 1, c = 0;
        // 左子图右侧连续空格数
        while (g1[i][j] == ' ') j--, c++;
        j = 0;
        // 右子图左侧连续空格数
        while (g2[i][j] == ' ') j++, c++;
        d = min(d, c);
    }
    
    // md 为尝试向左重叠的列数（即右子图向左移动 md 列）
    // 因为至少需要保留一列空格（列差 ≥ 2 等价于至少一个空格间隔），所以最大重叠量为 d-1
    int md = 0;
    while (md <= d - 1) {
        int ok = 1;
        // 检查在重叠区域内，是否有叶子正上方被减号覆盖
        for (int i = 1; i < rows; i++) {
            // 检查左子图靠近重叠区域的叶子
            for (int j = 0, k = md; j < md; j++, k--)
                if (g1[i][s - j - 1] != ' ' && g1[i - 1][s - j - 1] == ' ' && g2[i - 1][k - 1] == '-')
                    ok = 0;
            // 检查右子图靠近重叠区域的叶子
            for (int j = 0, k = md; j < md; j++, k--) {
                if (g2[i][j] != ' ' && g2[i - 1][j] == ' ' && g1[i - 1][s - k] == '-')
                    ok = 0;
            }
        }
        if (!ok) break;   // 当前重叠量不可行，停止增加
        md++;             // 尝试更大的重叠量（更紧凑）
    }
    md--; // 回退到最后一个可行的重叠量
    
    // 按最终确定的重叠量 md 合并左右子图
    for (int i = 0; i < rows; i++) {
        Row r(g1[i]);                     // 左子图内容
        for (int j = 0; j < s; j++) r.push_back(' '); // 预留右侧空间
        // 放置右子图，起始列 = s - md（左图宽度 - 重叠量）
        for (int j = 0; j < s; j++) if (g2[i][j] != ' ') r[s - md + j] = g2[i][j];
        g.push_back(r);
    }
    // 整体去除多余空白
    cut(g);
    return g;
}
    
// 递归构建图表的深度优先遍历
Grid dfs(Node *root) {
    Grid g;
    // 叶子节点：单行单字母
    if (root->type == 0) {
        g.push_back(Row(1, root->label));
        return g;
    }
    // 一元节点：子图 + 减号行 + 父字母行
    if (root->type == 1) {
        g = dfs(root->left);
        // 找到子图根字母所在的列（子图最后一行的非空格字符）
        int c = -1;
        for (int i = 0; i < g.back().size(); i++)
            if (g.back()[i] != ' ') {
                c = i;
                break;
            }
        // 添加减号行
        Row r(g.back().size(), ' '); r[c] = '-'; g.push_back(r);
        // 添加父字母行
        r[c] = root->label; g.push_back(r);
        return g;
    }
    // 二元节点：合并左右子图，然后添加连线
    g = merge(dfs(root->left), dfs(root->right));
    Row last = g.back();              // 合并后的最后一行（左右根所在行）
    int fc = -1, rc = -1, n = last.size();
    // 找到左根列（第一个非空格字符）
    for (int i = 0; i < n; i++)
        if (last[i] != ' ') {
            fc = i;
            break;
        }
    // 找到右根列（第二个非空格字符）
    for (int i = fc + 1; i < n; i++)
        if (last[i] != ' ') {
            rc = i;
            break;
        }
    // 添加连续减号线（从左根到右根）
    Row r1(n, ' ');
    for (int i = fc; i <= rc; i++) r1[i] = '-'; g.push_back(r1);
    // 添加父字母行，放在中央减号下方（偶数取左中央）
    Row r2(n, ' '); r2[(fc + rc) / 2] = root->label; g.push_back(r2);
    return g;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    char c; string tree; int id = 1;
    // 逐字符读入，cin >> c 自动跳过空白字符
    while (cin >> c) {
        // 遇到分号或句点表示一个表达式结束
        if (c == ';' || c == '.') {
            cout << id++ << ":\n";
            int idx = 0;
            Node* root = parse(tree, idx); // 解析表达式树
            Grid G = dfs(root);            // 生成图表
            // 输出图表，去除每行尾部空格
            for (auto r : G) {
                int end = r.size() - 1;
                while (r[end] == ' ') end--;
                for (int i = 0; i <= end; i++) cout << r[i];
                cout << '\n';
            }
            tree.clear();
        } else tree += c; // 累积当前表达式的字符
        if (c == '.') break; // 遇到句点，输入结束
    }
    return 0;
}
