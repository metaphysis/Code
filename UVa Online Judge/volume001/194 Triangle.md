[UVa 194 Triangle](https://blog.csdn.net/metaphysis/article/details/160942271)

## 题目分析

本题要求根据给定的三角形部分参数，计算出所有缺失的参数。三角形的六个参数分别为三条边长 $a, b, c$ 和三个角 $\alpha, \beta, \gamma$（对应顶点 $A, B, C$ 的对角）。输入中未知参数用 $-1$ 表示，输出需要给出全部六个参数的数值。

需要处理的特殊情况包括：

1. **无效输入**：边长或角度为非法值（边长 $\le 0$，角度 $\le 0$ 或 $\ge \pi$），或者参数之间矛盾（如三个角之和不为 $\pi$，两边之和不大于第三边等）。
2. **多解情况**：在边角边（`SAS`）或角边角（`ASA`）等情形下，三角形可能有两解（例如已知两边及其中一边的对角，且该角为锐角、已知边大于另一边但小于其正弦倍时）。
3. **唯一解**：参数足以唯一确定三角形，且有效。

## 解题思路

代码采用逐步尝试不同已知条件组合的方式求解：

1. **三边已知（`SSS`）**：用余弦定理计算三个角。
2. **两角已知**：若已知两角，则第三角可由三角形内角和为 $\pi$ 求得。
3. **三角已知**：需至少已知一边，用正弦定理计算另外两边。
4. **两边及夹角已知（`SAS`）**：用余弦定理求第三边，再用余弦定理求另外两角。
5. **两边及其中一边的对角已知（`SSA`）**：这是多解的可能来源。通过正弦定理计算对角，根据已知角是锐角还是钝角、边的大小关系判断解的个数。若有两解，标记 `multiSolution = true`。

每一步计算前都检查参数合法性，计算后验证与原给定值是否一致（精度 $10^{-6}$）。

## 代码实现

```cpp
// Triangle
// UVa ID: 194
// Verdict: Accepted
// Submission Date: 2016-03-24
// UVa Run Time: 0.006s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-6, PI = 2.0 * acos(0.0), HALF_PI = PI / 2.0;

map<char, double> p, old;       // p存储当前计算值，old存储输入原始值
map<char, bool> defined;        // 标记参数是否已定义
string variable = "aAbBcC";     // 六个参数，小写字母为边，大写字母为角
bool multiSolution = false;     // 标记是否有多解

// 已知两边及对角求第三边的余弦值，用于余弦定理
double acos(double x, double y, double z) {
    return acos((x * x + y * y - z * z) / (2 * x * y));
}

// 核心求解函数，尝试各种已知条件组合
bool calculate() {
    // 情况1：已知三边（SSS），用余弦定理求三个角
    if (defined['a'] && defined['b'] && defined['c']) {
        if (p['a'] + p['b'] <= p['c'] ||
            p['b'] + p['c'] <= p['a'] || p['a'] + p['c'] <= p['b'])
            return false;
            
        p['A'] = acos(p['b'], p['c'], p['a']);
        p['B'] = acos(p['a'], p['c'], p['b']);
        p['C'] = acos(p['a'], p['b'], p['c']);
        
        return true;
    }
    
    // 情况2：已知两角，可求第三角
    string angles[] = { "ABC", "ACB", "BCA" };
    for (int i = 0; i < 3; i++) {
        string v = angles[i];
        if (defined[v[0]] && defined[v[1]] && !defined[v[2]]) {
            if (p[v[0]] + p[v[1]] >= PI)
                return false;
            old[v[2]] = p[v[2]] = PI - p[v[0]] - p[v[1]];
            defined[v[2]] = true;
            break;
        }
    }
    
    // 情况3：已知三角和一边，用正弦定理求其余两边
    if (defined['A'] && defined['B'] && defined['C']) {
        if (abs(p['A'] + p['B'] + p['C'] - PI) > EPSILON) return false;
           
        if (!defined['a'] && !defined['b'] && !defined['c']) return false;

        string sideAngles[] = {"aABCbc", "bBACac", "cCABab"};
        for (int i = 0; i < 3; i++) {
            string v = sideAngles[i];
            if (defined[v[0]]) {
                p[v[4]] = p[v[0]] / sin(p[v[1]]) * sin(p[v[2]]);
                p[v[5]] = p[v[0]] / sin(p[v[1]]) * sin(p[v[3]]);
                
                return true;
            }
        }
    }

    // 情况4：已知两边及夹角（SAS），用余弦定理求第三边和另外两角
    string cosines[] = {"abCcAB", "acBbAC", "bcAaBC"};
    for (int i = 0; i < 3; i++) {
        string v = cosines[i];
        
        if (defined[v[0]] && defined[v[1]] && defined[v[2]]) {
            if (p[v[2]] >= PI) return false;
                
            p[v[3]] = sqrt(p[v[0]] * p[v[0]] + p[v[1]] * p[v[1]] -
                2 * p[v[0]] * p[v[1]] * cos(p[v[2]]));
            p[v[4]] = acos(p[v[1]], p[v[3]], p[v[0]]);
            p[v[5]] = acos(p[v[0]], p[v[3]], p[v[1]]);
            
            return true;
        }
    }

    // 情况5：已知两边及其中一边的对角（SSA），可能有多解
    string sines[] = { "abABCc", "baBACc", "acACBb", "caCABb", "bcBCAa", "cbCBAa" };
    for (int i = 0; i < 6; i++) {
        string v = sines[i];
        if (defined[v[0]] && defined[v[1]] && defined[v[2]]) {
            if (p[v[2]] >= PI) return false;
                
            // 钝角时对边必须最大
            if (p[v[2]] >= HALF_PI && p[v[0]] <= p[v[1]]) return false;
                
            double temp = p[v[1]] * sin(p[v[2]]);
            // 边太小，无法构成三角形
            if (p[v[2]] < HALF_PI && p[v[0]] < temp) return false;
            
            // 两解情况：已知角为锐角，已知边小于另一边且大于其对边的高
            if (p[v[2]] < HALF_PI && p[v[0]] < p[v[1]] && p[v[0]] > temp) {
                multiSolution = true;
                return true;
            }
  
            // 唯一解：计算另一角及剩余边角
            p[v[3]] = asin(p[v[1]] * sin(p[v[2]]) / p[v[0]]);
            p[v[4]] = PI - p[v[2]] - p[v[3]];
            p[v[5]] = p[v[0]] * sin(p[v[4]]) / sin(p[v[2]]);
                           
            return true;
        }
    }
    
    return false;   // 无法由已知条件确定三角形
}

int main() {
    int n;
    double temp;
    
    cout.precision(6);      // 输出保留6位小数
    
    cin >> n;
    while (n--) {
        bool valid = true;
        int counter = 0;

        // 读入六个参数，-1表示未知
        for (int i = 0; i < variable.length(); i++) {
            cin >> temp;
            old[variable[i]] = p[variable[i]] = temp;
            
            defined[variable[i]] = false;
            // 非法值：非-1且非正数
            if (temp <= 0 && temp != -1.0) valid = false;
            else if (temp > 0) {
                defined[variable[i]] = true;
                counter++;
            }
        }
 
        multiSolution = false;
        // 已知参数少于3个，或输入有非法值，或无法计算
        if (counter <= 2 || !valid || !calculate()) cout << "Invalid input.\n";
        else if (multiSolution) cout << "More than one solution.\n";
        else {
            // 验证计算结果与输入是否一致
            valid = true;
            for (int i = 0; i < variable.length(); i++)
                if (defined[variable[i]] && abs(p[variable[i]] - old[variable[i]]) > EPSILON) {
                    cout << "Invalid input.\n";
                    valid = false;
                    break;
                }
            
            if (valid) {
                // 输出全部六个参数
                for (int i = 0; i < variable.length(); i++) cout << (i > 0 ? " " : "") << fixed << p[variable[i]];
                cout << "\n";
            }       
        }
    }

    return 0;
}
```
