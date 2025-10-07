// Polynomial Factorization
// UVa ID: 463
// Verdict: Accepted
// Submission Date: 2025-10-07
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

/**
 * 多项式除法：判断多项式a是否能被多项式b整除
 * @param a 被除多项式（系数向量，高次在前）
 * @param b 除多项式（系数向量，高次在前）
 * @param q 商多项式（输出参数）
 * @return 如果可整除返回true，否则返回false
 */
bool divisible(vector<int> a, vector<int> b, vector<int>& q) {
    q.clear();
    // 模拟多项式长除法过程
    for (int i = 0; i + b.size() <= a.size(); i++) {
        // 检查当前最高次项是否能整除
        if (a[i] % b[0]) return false;
        // 计算商的一项
        int r = a[i] / b[0]; q.push_back(r);
        // 从被除数中减去商乘以除数的结果
        for (int j = 0; j < b.size(); j++) a[i + j] -= r * b[j];
    }
    // 检查余数是否为零（完全整除）
    for (int x : a) if (x) return false;
    return true;
}

/**
 * 获取一个整数的所有因子（正因子）
 * @param n 输入整数
 * @param f 因子列表（输出参数）
 */
void getFactors(int n, vector<int>& f) {
    f.clear();
    // 遍历1到sqrt(n)寻找因子
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) { 
            f.push_back(i);          // 小因子
            f.push_back(n / i);      // 对应的配对因子
        }
    }
}

// 比较函数：按绝对值升序排序
bool cmpValue(int a, int b) { return abs(a) < abs(b); }

// 比较函数：多项式排序（先按次数升序，次数相同按字典序）
bool cmpPoly(vector<int> a, vector<int> b) { 
    return a.size() != b.size() ? a.size() < b.size() : a < b; 
}

/**
 * 深度优先搜索分解多项式
 * @param d 当前多项式的次数
 * @param in 当前要分解的多项式系数
 * @param out 分解结果（输出参数）
 * @return 是否成功分解
 */
bool dfs(int d, vector<int> in, vector<vector<int>>& out) {
    // 基本情况：次数为1，无法再分解
    if (d == 1) { out.push_back(in); return true; }
    
    vector<int> p, q, r;
    // 获取首项系数和常数项的所有因子
    getFactors(in[0], p);                    // 首项系数的因子
    getFactors(abs(in.back()), q);           // 常数项的因子（取绝对值）
    
    // 为常数项因子添加负值版本（因为根可能是负数）
    int qsize = q.size();
    for (int i = 0; i < qsize; i++) q.push_back(-q[i]);
    if (in.back() == 0) q.push_back(0);      // 处理常数项为零的情况
    
    // 按绝对值排序，优先尝试绝对值小的因子（提高效率）
    sort(p.begin(), p.end(), cmpValue); 
    sort(q.begin(), q.end(), cmpValue);
    
    // 尝试所有可能的线性因子 (a1*x + c1)
    for (int a1 : p) for (int c1 : q) {
        vector<int> t = {a1, c1};            // 构造线性因子
        if (divisible(in, t, r)) {           // 检查是否能整除
            out.push_back(t);                // 将因子加入结果
            return dfs(d - 1, r, out);       // 递归分解商式
        }
    }
    
    // 如果次数较低（2或3）且找不到线性因子，直接返回原多项式
    if (d <= 3) { out.push_back(in); return true; }
    
    // 对于4次多项式，尝试二次因子分解 (a1*x² + b1*x + c1)(a2*x² + b2*x + c2)
    for (int a1 : p) for (int c1 : q) {
        int a2 = in[0] / a1, c2 = in.back() / c1;  // 计算配对系数
        
        // 根据多项式乘法展开，建立方程组：
        // 原多项式: a0*x⁴ + a1*x³ + a2*x² + a3*x + a4
        // 分解形式: (a1*x² + b1*x + c1)(a2*x² + b2*x + c2)
        // 展开后系数对应关系：
        // x⁴: a1*a2 = a0
        // x³: a1*b2 + a2*b1 = a1
        // x²: a1*c2 + b1*b2 + a2*c1 = a2  
        // x¹: b1*c2 + b2*c1 = a3
        // x⁰: c1*c2 = a4
        
        // 从x³和x¹的方程中解出b1和b2
        // 设方程为：a2*b1 + a1*b2 = a1  (x³系数)
        //          c2*b1 + c1*b2 = a3  (x¹系数)
        // 这可以看作关于b1, b2的线性方程组
        
        int aa = -a2, bb = in[1];            // 系数矩阵参数
        int cc = -(a1 * in[2] - a1 * a1 * c2 - a2 * c1 * a1);  // 计算判别式参数
        
        // 计算判别式
        int delta = bb * bb - 4 * aa * cc;
        if (delta < 0) continue;             // 无实数解
        int hh = sqrt(delta + 0.5);          // 开方（加0.5用于四舍五入）
        if (hh * hh != delta) continue;      // 检查是否为完全平方数
        
        // 尝试两个可能的根（正负两个解）
        for (int sign = -1; sign <= 1; sign += 2) {
            // 检查解是否为整数
            if ((sign * hh - bb) % (2 * aa)) continue;
            int b1 = (sign * hh - bb) / (2 * aa);  // 计算b1
            
            // 从x³方程计算b2，检查是否为整数
            if ((in[1] - b1 * a2) % a1) continue;
            int b2 = (in[1] - b1 * a2) / a1;
            
            // 验证x¹系数方程
            if (b1 * c2 + b2 * c1 != in[3]) continue;
            
            // 找到有效的二次因子分解
            out.push_back({a1, b1, c1}); 
            out.push_back({a2, b2, c2});
            return true;
        }
    }
    
    // 无法分解，返回原多项式
    out.push_back(in); 
    return false;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(false);  // 加速IO
    int a, b, c, d, e;
    
    while (cin >> a >> b >> c >> d >> e) {
        // 读取5个系数（4次多项式）
        vector<int> in = {a, b, c, d, e};
        
        // 如果首项系数为负，整体取反（保证首项系数为正）
        bool reversed = in[0] < 0;
        if (reversed) for (int& x : in) x *= -1;
        
        // 分解多项式
        vector<vector<int>> out;
        dfs(4, in, out);
        
        // 计算所有因子的最大公约数，用于归一化系数
        int g = 1;
        for (auto& poly : out) {
            int tmpg = 0;
            // 计算当前多项式的系数的GCD
            for (int x : poly) if (x) tmpg = tmpg ? __gcd(tmpg, abs(x)) : abs(x);
            if (!tmpg) tmpg = 1;  // 处理全零情况
            g *= tmpg;
            // 将当前多项式系数除以GCD进行归一化
            for (int& x : poly) x /= tmpg;
        }
        
        // 如果之前取反过，现在将整体符号调整回来
        if (reversed) g = -g;
        
        // 对因子排序：先按次数升序，次数相同按字典序
        sort(out.begin(), out.end(), cmpPoly);
        
        // 将整体符号乘到最后一个因子上
        for (int& x : out.back()) x *= g;
        
        // 输出结果
        for (auto& poly : out) {
            for (auto it = poly.begin(); it != poly.end(); ++it) {
                cout << *it; 
                if (next(it) != poly.end()) cout << " ";  // 空格分隔，最后无空格
            }
            cout << "\n";
        }
        cout << "\n";  // 每个测试用例后输出空行
    }
    return 0;
}
