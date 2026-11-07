

> **摘要**：本文讨论如何高精度计算轴平行椭圆的周长。由于椭圆周长不存在初等函数闭式解，常见近似公式在离心率较大时误差显著，本文从第二类完全椭圆积分出发，推导周长积分表达式，并采用复合辛普森法进行数值积分，取 $N = 10000$ 等分即可将误差压缩至 $10^{-12}$ 量级，远优于题目 $10^{-5}$ 的精度要求。文中给出完整的 $\texttt{C++}$ 实现、复杂度分析与正确性论证，适用于任意 $a \ge b$ 的椭圆。

## 题目描述

给定一个轴平行椭圆，其中心在原点，长半轴为 $a$ ，短半轴为 $b$ 。要求计算该椭圆的周长。输入包含多组数据，每组给出 $b$ 和 $a$ 的值，输出对应的椭圆周长，结果需精确到小数点后至少 $6$ 位，允许绝对或相对误差小于 $10^{-5}$ 。

## 输入格式

第一行包含一个整数 $T$ （ $T \le 50$ ），表示测试用例的数量。  
接下来 $T$ 行，每行包含两个整数 $b$ 和 $a$ （ $1 \le b \le a \le 20$ ），分别代表短半轴和长半轴的长度。

## 输出格式

对于每个测试用例，输出一行，格式为 `Case X: Y` ，其中 $X$ 是从 $1$ 开始的用例编号， $Y$ 是计算得到的椭圆周长，保留 $6$ 位小数。

## 样例

输入

```text
2
5 10
3 4
```

输出

```text
Case 1: 48.442241
Case 2: 22.103492
```

## 题目分析

椭圆周长不存在由初等函数构成的闭式精确表达式。常见的近似公式如 $L \approx 2\pi b + 4(a - b)$ 在离心率较大时误差显著，无法满足本题 $10^{-5}$ 的精度要求。以样例 $\texttt{1}$ 为例（ $a = 10$ ， $b = 5$ ），该近似给出 $51.4159$ ，与真实值 $48.442241$ 的绝对误差超过 $2.9$ ，远大于容差。

精确计算椭圆周长需借助第二类完全椭圆积分。椭圆参数方程 $x = a\cos\theta$ ， $y = b\sin\theta$ ， $0 \le \theta \le 2\pi$ ，弧长微元为：

$$
ds = \sqrt{a^2\sin^2\theta + b^2\cos^2\theta}\,d\theta
$$

利用对称性，周长 $C$ 可表示为：

$$
C = 4\int_0^{\pi/2} \sqrt{a^2\sin^2\theta + b^2\cos^2\theta}\,d\theta
$$

令离心率 $e = \sqrt{1 - (b/a)^2}$ ，则：

$$
C = 4a \int_0^{\pi/2} \sqrt{1 - e^2\sin^2\theta}\,d\theta
$$

被积函数 $f(\theta) = \sqrt{1 - e^2\sin^2\theta}$ 在闭区间 $[0, \pi/2]$ 上无穷可导，且 $e \in [0, 1)$ ，无奇点。因此采用数值积分可高精度逼近该积分值。

复合辛普森法则对光滑函数具有四阶代数精度，误差项与步长 $h$ 的四次方成正比。当等分数 $N$ 足够大时，误差可被压缩到远低于 $10^{-5}$ 。由于 $a, b \le 20$ ，被积函数变化平缓，取 $N = 10000$ 可保证积分误差小于 $10^{-12}$ ，远优于题目要求。

## 解题思路

求解过程分为以下几个步骤：

步骤 $\texttt{1}$. 读入测试用例数 $T$ ，然后对每组数据读入 $b$ 和 $a$ 。  
步骤 $\texttt{2}$. 将 $b$ 、 $a$ 转换为双精度浮点数，计算离心率 $e = \sqrt{1 - (b/a)^2}$ 。  
步骤 $\texttt{3}$. 使用复合辛普森法计算积分 $I = \int_0^{\pi/2} f(\theta)\,d\theta$ ：
   - 取等分数 $N = 10000$ ，步长 $h = \frac{\pi/2}{N}$ 。
   - 生成节点 $\theta_i = i \cdot h$ ， $i = 0, 1, \dots, N$ 。
   - 计算各节点被积函数值 $f(\theta_i)$ 。
   - 按照辛普森系数累加：首尾节点系数为 $1$ ，奇数索引节点系数为 $4$ ，偶数索引节点（不含两端）系数为 $2$ 。
   - 求和后乘以 $h/3$ 得到积分近似值。  
步骤 $\texttt{4}$. 椭圆周长 $C = 4a \cdot I$ 。  
步骤 $\texttt{5}$. 按指定格式输出结果，保留 $6$ 位小数。

该方法的正确性建立在辛普森法则对光滑函数的收敛性上。由于 $f(\theta)$ 的四阶导数在区间内有界，复合辛普森误差上界为 $\frac{(b-a)}{180} h^4 \max |f^{(4)}(\theta)|$ 。经估算，当 $N = 10000$ 时误差远小于 $10^{-12}$ ，完全满足精度需求。

## 复杂度分析

- 时间复杂度：每个测试用例需计算 $N + 1 = 10001$ 个函数值，每次计算包含一次三角函数和一次平方根运算。 $T \le 50$ ，总运算次数约 $5 \times 10^5$ ，可在极短时间内完成。
- 空间复杂度：仅使用常数个双精度变量， $O(1)$ 。

## 代码实现

```cpp
// Elliptic Athletics Track
// UVa ID: 12475
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 被积函数：sqrt(1 - e^2 * sin^2(theta))
double integrand(double theta, double e) {
    return sqrt(1.0 - e * e * sin(theta) * sin(theta));
}

// 复合辛普森积分，区间 [0, pi/2]，等分数 N
double simpsonIntegral(double e, int N = 10000) {
    double a = 0.0, b = M_PI / 2.0;
    double h = (b - a) / N;
    double sum = 0.0;
    for (int i = 0; i <= N; ++i) {
        double theta = a + i * h;
        double fv = integrand(theta, e);
        if (i == 0 || i == N) sum += fv;
        else if (i % 2 == 0) sum += 2.0 * fv;
        else sum += 4.0 * fv;
    }
    return sum * h / 3.0;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; ++cs) {
        int bInt, aInt;
        scanf("%d %d", &bInt, &aInt);
        double a = (double)aInt;
        double b = (double)bInt;
        double e = sqrt(1.0 - (b * b) / (a * a));   // 离心率
        double integral = simpsonIntegral(e);       // 第二类完全椭圆积分 E(e)
        double circumference = 4.0 * a * integral;  // 椭圆周长
        printf("Case %d: %.6f\n", cs, circumference);
    }
    return 0;
}
```

## 总结

- 椭圆周长无法用初等函数精确表达，必须采用数值积分或特殊函数计算。  
- 复合辛普森法实现简单，对光滑周期函数收敛快，取 $10000$ 等分可轻松达到 $10^{-5}$ 精度。  
- 该方法不依赖任何近似公式，适用于任意 $a \ge b$ 的椭圆，且计算开销极小。  
- 本题的关键是识别出简单近似公式的不足，并选用可靠的数值积分手段，这也是处理类似非初等积分问题的通用策略。
