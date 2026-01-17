// Single-Player Games
// UVa ID: 664
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 26;          // 最大变量数（小写字母数量）
const double EPS = 1e-12;     // 数值精度容差

// 系数矩阵：mt[i][j] 表示第i个方程中E[j]的系数，mt[i][n]为常数项
double mt[MAXN][MAXN + 1];
double x[MAXN];               // 解向量
bool freeX[MAXN];             // 标记自由变量（未定义）

// 树节点结构
struct TreeNode {
    int type;                 // 0:数字, 1:变量引用, 2:内部节点
    int value;                // 数字值或变量索引(0-25)
    vector<TreeNode*> children; // 子节点列表
    
    TreeNode() : type(0), value(0) {}
    ~TreeNode() { for (auto child : children) delete child; }
};

// 高斯消元法求解线性方程组
void gauss(int n) {
    memset(freeX, true, sizeof(freeX));  // 初始假设所有变量都是自由变量
    int row = 0, col = 0;
    
    // 高斯-约旦消元：化为行简化阶梯形
    for (; row < n && col < n; row++, col++) {
        // 寻找当前列绝对值最大的元素作为主元
        int pivot = row;
        for (int i = row + 1; i < n; i++)
            if (fabs(mt[i][col]) > fabs(mt[pivot][col]))
                pivot = i;
        
        // 如果主元接近0，跳过该列
        if (fabs(mt[pivot][col]) < EPS) {
            row--;
            continue;
        }
        
        // 交换行使主元到对角线位置
        if (pivot != row)
            for (int j = col; j <= n; j++)
                swap(mt[row][j], mt[pivot][j]);
        
        // 归一化主元行
        double base = mt[row][col];
        for (int j = col; j <= n; j++) 
            mt[row][j] /= base;
        
        // 使用主元行消去其他行的当前列元素
        for (int i = 0; i < n; i++)
            if (i != row && fabs(mt[i][col]) > EPS) {
                double factor = mt[i][col];
                for (int j = col; j <= n; j++)
                    mt[i][j] -= factor * mt[row][j];
            }
    }
    
    // 提取解
    memset(x, 0, sizeof(x));
    for (int i = 0; i < n; i++) {
        int varIdx = -1;  // 尝试找到该方程确定的变量
        
        // 检查该方程是否只包含一个变量（系数为1）
        for (int j = 0; j < n; j++)
            if (fabs(mt[i][j]) > EPS)
                if (varIdx == -1) varIdx = j;  // 第一个非零系数
                else { varIdx = -1; break; }   // 多个非零系数，不是唯一变量
        
        // 如果找到唯一变量且其系数接近1，则提取解
        if (varIdx != -1 && fabs(mt[i][varIdx] - 1.0) < EPS) {
            x[varIdx] = mt[i][n];
            freeX[varIdx] = false;  // 该变量有唯一解，不是自由变量
        }
    }
}

// 深度优先遍历表达式树，建立线性方程
// root: 当前节点
// eqIdx: 当前方程的索引（对应哪个变量）
// n: 变量总数
// weight: 当前路径的权重（概率）
void dfs(TreeNode* root, int eqIdx, int n, double weight) {
    if (root->type == 0) {  // 数字叶子节点
        mt[eqIdx][n] += weight * root->value;  // 加到常数项
    }
    else if (root->type == 1) {  // 变量引用节点
        mt[eqIdx][root->value] -= weight;  // 减去系数（因为方程是 E[i] - Σ... = 0）
    }
    else {  // 内部节点
        // 权重平均分配给子节点
        double child_weight = weight / root->children.size();
        for (auto child : root->children)
            dfs(child, eqIdx, n, child_weight);
    }
}

// 递归解析表达式字符串
// s: 表达式字符串
// idx: 当前解析位置
// n: 变量总数（用于验证变量引用是否有效）
TreeNode* parseExpression(const string& s, int& idx, int n) {
    TreeNode* node = new TreeNode();
    
    // 跳过空白字符
    while (idx < s.size() && isspace(s[idx])) idx++;
    if (idx >= s.size()) return node;
    
    if (s[idx] == '(') {  // 括号表达式（内部节点）
        node->type = 2;
        idx++;  // 跳过 '('
        
        // 解析所有子表达式
        while (true) {
            while (idx < s.size() && isspace(s[idx])) idx++;
            if (idx >= s.size() || s[idx] == ')') break;
            
            TreeNode* child = parseExpression(s, idx, n);
            node->children.push_back(child);
        }
        
        if (idx < s.size() && s[idx] == ')') idx++;  // 跳过 ')'
    }
    else if (isdigit(s[idx]) || s[idx] == '-') {  // 数字（可能为负）
        node->type = 0;
        int sign = 1;
        
        // 处理负号
        if (s[idx] == '-') {
            sign = -1;
            idx++;
        }
        
        // 解析数字
        int v = 0;
        while (idx < s.size() && isdigit(s[idx])) {
            v = v * 10 + (s[idx] - '0');
            idx++;
        }
        node->value = v * sign;
    }
    else if (islower(s[idx])) {  // 变量引用
        node->type = 1;
        node->value = s[idx] - 'a';  // 转换为0-25的索引
        idx++;
    }
    
    return node;
}

int main() {
    int n, T = 0;  // n: 变量数，T: 测试用例编号
    
    while (cin >> n && n) {
        T++;
        cin.ignore(128, '\n');  // 忽略换行符
        
        // 初始化系数矩阵
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= n; j++)
                mt[i][j] = 0.0;
        
        // 读取并解析每个变量的定义
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            
            // 找到等号位置
            size_t equal = line.find('=');
            string expr = line.substr(equal + 1);
            
            // 解析表达式为树结构
            int idx = 0;
            TreeNode* root = parseExpression(expr, idx, n);
            
            // 建立方程：E[i] = Σ(子节点期望)
            // 转换为：E[i] - Σ(子节点期望) = 0
            mt[i][i] = 1.0;  // E[i]的系数为1
            dfs(root, i, n, 1.0);  // 遍历树建立方程
            
            delete root;  // 释放树内存
        }
        
        // 使用高斯消元法求解线性方程组
        gauss(n);
        
        // 输出结果
        cout << "Game " << T << '\n';
        for (int i = 0; i < n; i++) {
            char id = 'a' + i;
            if (freeX[i]) {  // 自由变量（未定义）
                cout << "Expected score for " << id << " undefined\n";
            }
            else {  // 有唯一解
                cout << fixed << setprecision(3);
                cout << "Expected score for " << id << " = " << x[i] << '\n';
            }
        }
        cout << '\n';  // 测试用例间空行
    }
    
    return 0;
}
