[UVa 316 Stars](https://blog.csdn.net/metaphysis/article/details/161477281)

## 题目描述

在晴朗无月的夜晚，你可以看到天空中闪烁的无数星星。为了给这混乱的景象带来秩序，希腊人在大约 $2000$ 年前开始识别星群，称之为星座，并赋予它们名字（大多来自希腊神话），这些名字沿用至今。例如“小熊座”、“双鱼座”、“巨蟹座”等。

给定一个星座的轮廓图，业余爱好者很难在天空中实际找到该星座。此外，简单的星座（如只有三颗星的“三角座”）可能在天空中出现多次。如何找出“正确”的出现位置呢？

传统上，星图就是为了这个目的而印刷的。但在本问题中，我们将看到计算机如何帮助我们在天空中寻找星座。

你将获得一张星图（平面上的一组点，每个点有亮度值），以及一个星座（平面上的一组点）。需要确定：
- 星座在星图中出现的次数
- 最亮出现位置（如果存在）的星星坐标

**出现**：星图中某个子集的星星经过**任意旋转和/或缩放**后，与星座中的星星完全匹配。

**亮度**：出现位置中星星亮度的平均值（即亮度总和除以星座星星数量）。

### 输入格式

输入文件包含多个星图的描述。每个星图以一行整数 $n$（$1 \leq n < 1000$）开始，表示星图中星星的数量。接下来 $n$ 行，每行包含三个整数：$x$、$y$ 坐标和亮度值。

接下来一行包含一个整数 $m$（$1 \leq m < 50$），表示接下来要处理的星座数量。每个星座描述以一行整数 $s_i$ 和字符串 $N_i$ 开始（$s_i$ 为星座星星数量，$N_i$ 为星座名称）。接下来 $s_i$ 行包含星座的坐标（$x/y$ 对）。

星图与下一个星图之间由一个空行分隔。输入文件以空星图（$n = 0$）结束，该星图不处理。

注意：由于所有星星坐标都是整数，你可以轻松排除那些变换后坐标不是整数的匹配。

### 输出格式

对于每个星图，首先输出一行 `Map #1`、`Map #2` 等。对于每个星座，按输入顺序输出：
- 第一行：星座名称和出现次数
- 如果至少有一次出现，输出最亮出现位置中所有星星的坐标（按 $x$ 升序，$x$ 相同时按 $y$ 升序）

每个星座前输出一个空行。每个星图后输出一行 `-----`。

### 样例输入

```
6
1 2 1
2 1 4
2 4 3
3 2 1
4 1 5
4 3 2
2
3 Triangulum
1 1
3 1
2 4
4 Cancer
1 3
4 3
6 1
7 5
0
```

### 样例输出

```
Map #1

Triangulum occurs 2 time(s) in the map.
Brightest occurrence: (1,2) (4,1) (4,3)

Cancer occurs 0 time(s) in the map.
-----
```

---

## 题目分析

### 问题的本质

这是一个**点集匹配**问题。给定两个点集 $S$（星图，$|S| = n$）和 $C$（星座，$|C| = s$），需要找出 $S$ 中所有与 $C$ 通过**旋转和缩放**（不包含反射）相匹配的子集。由于坐标是整数，我们可以利用这个性质简化问题。

### 匹配条件

两个点集 $C$ 和 $C'$ 匹配，当且仅当存在一个**相似变换**（旋转 $+$ 缩放）$T$，使得 $T(C) = C'$。

相似变换由四个参数决定：
- 旋转角度 $\theta$
- 缩放因子 $\lambda > 0$
- 平移向量 $(t_x, t_y)$

即：
$$
\begin{pmatrix} x' \\ y' \end{pmatrix} = \lambda \begin{pmatrix} \cos\theta & -\sin\theta \\ \sin\theta & \cos\theta \end{pmatrix} \begin{pmatrix} x \\ y \end{pmatrix} + \begin{pmatrix} t_x \\ t_y \end{pmatrix}
$$

### 整数坐标约束

由于星图中所有星星的坐标都是整数，匹配后的坐标也必须是整数。这为搜索提供了强有力的剪枝：我们可以只考虑那些能够将星座点映射到整数坐标的变换。

### 算法思路

一种经典的方法是：枚举星座中的两个点作为“锚点”，将它们映射到星图中的两个点，从而确定变换参数。然后验证其他星座点是否也映射到星图中的星星。

---

## 解题思路

### 步骤一：数据存储

- 使用 `vector<star>` 存储星星信息（坐标、亮度）
- 使用嵌套 `map<int, map<int, int>>` 建立坐标到索引的映射，用于 $O(1)$ 查询

### 步骤二：特殊情况处理

- 如果星座大小 $s > n$，不可能出现，次数为 $0$
- 如果 $s = 1$，每个星星都是一个出现，次数为 $n$
- 如果 $s = 2$，任意两个不同的星星构成一个出现，次数为 $C(n, 2)$

### 步骤三：一般情况匹配

对于 $s \geq 3$，使用锚点法：

1. 选择星座中的前两个点 $C_0$ 和 $C_1$ 作为锚点
2. 枚举星图中的点对 $(P_i, P_j)$（$i \neq j$）作为候选映射：
   - 计算从 $(C_0, C_1)$ 到 $(P_i, P_j)$ 的变换参数
   - 检查所有星座点变换后是否都落在星图中的星星上
   - 如果是，则找到一个出现

### 步骤四：变换参数计算

给定两点对应关系：
- $C_0 \rightarrow P_i$
- $C_1 \rightarrow P_j$

可以计算出：
- 旋转角度：$\theta = \text{atan2}(P_j.y - P_i.y, P_j.x - P_i.x) - \text{atan2}(C_1.y - C_0.y, C_1.x - C_0.x)$
- 缩放因子：$\lambda = dist(P_i, P_j) / dist(C_0, C_1)$

对于每个星座点 $C_k$，计算：
$$
\begin{aligned}
dx &= C_k.x - C_0.x \\
dy &= C_k.y - C_0.y \\
rx &= dx \cdot \cos\theta - dy \cdot \sin\theta \\
ry &= dx \cdot \sin\theta + dy \cdot \cos\theta \\
x' &= P_i.x + \lambda \cdot rx \\
y' &= P_i.y + \lambda \cdot ry
\end{aligned}
$$

检查 $(x', y')$ 是否为整数且存在于星图中。

### 步骤五：去重

由于锚点对的选择可能会多次检测到同一个出现，需要去重。一个简单的方法是：在验证成功后，将匹配到的星星索引集合排序后存入 `set` 中，最后统计不同的集合。

代码中采用了一种巧妙的方法：先在星座自身的坐标上运行一次匹配（以星座为“星图”），得到匹配的基准次数 `times2`，然后用星图匹配的次数 `times1` 除以 `times2` 得到实际的出现次数。这种方法利用了星座的自对称性。

### 步骤六：最亮出现

在匹配过程中，记录每个出现的亮度总和。亮度总和最大的即为最亮出现。如果多个出现亮度相同，任选一个输出。

---

## 算法复杂度分析

### 时间复杂度

- 枚举锚点对：$O(n^2)$，$n < 1000$，最多 $10^6$ 对
- 每对验证 $s$ 个点：$O(s)$，$s$ 最大约 $n$（但星座通常较小）
- 总复杂度：$O(n^2 \cdot s)$，最坏情况 $10^6 \times 1000 = 10^9$ 过大
- 但实际中 $s$ 通常较小，且很多对会因坐标非整数提前退出
- UVa 评测时间 $0.220$ 秒，说明剪枝有效

### 空间复杂度

- 存储星星：$O(n)$
- 坐标索引：$O(n)$
- 总空间复杂度：$O(n)$

---

## 正确性证明

**引理 1**：两个点确定一个相似变换（旋转+缩放+平移）。

证明：给定两个点 $A, B$ 及其对应点 $A', B'$，可以唯一确定旋转角度和缩放因子（因为三角形 $OAB$ 与 $OA'B'$ 相似）。$\square$

**引理 2**：所有相似变换都可以通过锚点对枚举得到。

证明：任何匹配必然将星座中的某两个点映射到星图中的两个点。枚举所有可能的锚点对即可覆盖所有变换。$\square$

**引理 3**：坐标整数性剪枝是安全的。

证明：如果变换后坐标不是整数，则不可能匹配星图中的整数坐标点。直接排除这些变换不会遗漏任何匹配。$\square$

---

## 参考代码

```cpp
// Stars
// UVa ID: 316
// Verdict: Accepted
// Submission Date: 2017-05-27
// UVa Run Time: 0.220s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-6;

struct star
{
    int x, y, brightness;
};

vector<star> stars1, stars2, constellation1;
map<int, map<int, int>> starsIdx1, starsIdx2;
    
// 按坐标排序（用于输出）
bool cmpXY(int i, int j)
{
    if (stars1[i].x != stars1[j].x) return stars1[i].x < stars1[j].x;
    return stars1[i].y < stars1[j].y;
}

// 按亮度排序（亮度高的优先）
bool cmpBrightness(const star &s1, const star &s2)
{
    if (s1.brightness != s2.brightness) return s1.brightness > s2.brightness;
    if (s1.x != s2.x) return s1.x < s2.x;
    return s1.y < s2.y;
}

// 寻找星座在星图中的所有出现，并记录最亮出现
// stars: 星图星星
// starsIdx: 坐标到索引的映射
// constellation: 星座点集
// brightest: 输出最亮出现的星星索引
// 返回出现次数
int findPolygon(vector<star> &stars, map<int, map<int, int>> &starsIdx, 
                vector<star> &constellation, vector<int> &brightest)
{
    int maxBrightness = 0, times = 0;
    int n = stars.size(), m = constellation.size();

    // 枚举锚点对 (i, j)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            
            // 计算旋转角
            double theta1 = atan2(stars[j].y - stars[i].y, stars[j].x - stars[i].x);
            double theta2 = atan2(constellation[1].y - constellation[0].y, 
                                  constellation[1].x - constellation[0].x);
            double rtheta = theta1 - theta2;
            
            // 计算缩放因子
            double dist1 = pow(stars[j].x - stars[i].x, 2) + pow(stars[j].y - stars[i].y, 2);
            double dist2 = pow(constellation[1].x - constellation[0].x, 2) + 
                           pow(constellation[1].y - constellation[0].y, 2);
            double scaling = sqrt(dist1 / dist2);

            int k = 0, sumOfBrightness = 0;
            vector<int> similar;

            // 验证所有星座点
            for (k = 0; k < m; k++) 
            {
                double tx = constellation[k].x - constellation[0].x;
                double ty = constellation[k].y - constellation[0].y;

                // 旋转
                double rx = tx * cos(rtheta) - ty * sin(rtheta);
                double ry = tx * sin(rtheta) + ty * cos(rtheta);
                
                // 缩放
                rx *= scaling, ry *= scaling;
                
                // 平移
                rx += stars[i].x;
                ry += stars[i].y;
                
                // 检查坐标是否为整数
                int ix = (int)floor(rx + EPSILON);
                int iy = (int)floor(ry + EPSILON);
                
                if (fabs(rx - ix) > EPSILON || fabs(ry - iy) > EPSILON) 
                    break;
                
                // 检查坐标是否存在于星图中
                if (starsIdx.find(ix) == starsIdx.end()) break;
                if (starsIdx[ix].find(iy) == starsIdx[ix].end()) break;
                
                int idx = starsIdx[ix][iy];
                similar.push_back(idx);
                sumOfBrightness += stars[idx].brightness;
            }

            // 所有点都匹配成功
            if (k == m)
            {
                times++;
                if (sumOfBrightness > maxBrightness)
                {
                    maxBrightness = sumOfBrightness;
                    brightest.swap(similar);
                }
            }
        }
        
    return times;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, m, si, x1, y1, brightness;
    string name;

    while (cin >> n, n > 0)
    {
        stars1.clear();
        starsIdx1.clear();

        // 读取星图
        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1 >> brightness;
            stars1.push_back(star{x1, y1, brightness});
            starsIdx1[x1][y1] = i;
        }

        cout << "Map #" << ++cases << '\n';
                    
        cin >> m;
        for (int c = 0; c < m; c++)
        {
            cin >> si >> name;

            constellation1.clear();
            stars2.clear();
            starsIdx2.clear();

            // 读取星座
            for (int i = 0; i < si; i++)
            {
                cin >> x1 >> y1;
                constellation1.push_back(star{x1, y1, 0});
                stars2.push_back(star{x1, y1, 0});
                starsIdx2[x1][y1] = i;
            }

            cout << '\n';

            // 特殊情况：星座比星图还大
            if (si > n)
            {
                cout << name << " occurs 0 time(s) in the map.\n";
                continue;
            }
            
            // 特殊情况：1 或 2 个点
            if (si == 1 || si == 2)
            {
                sort(stars1.begin(), stars1.end(), cmpBrightness);

                int times = stars1.size();
                if (si == 2) times = times * (times - 1) / 2;

                cout << name << " occurs " << times << " time(s) in the map.\n";

                if (times > 0)
                {
                    cout << "Brightest occurrence:";
                    for (int i = 0; i < si; i++)
                        cout << " (" << stars1[i].x << ',' << stars1[i].y << ")";
                    cout << '\n';
                }
                
                continue;
            }

            // 一般情况
            vector<int> brightest;

            // 先在星座自身中匹配（用于去重）
            int times2 = findPolygon(stars2, starsIdx2, constellation1, brightest);
            // 再在星图中匹配
            int times1 = findPolygon(stars1, starsIdx1, constellation1, brightest);

            // 去重：每个星图出现对应星座的多个锚点对
            if (times2 > 0) times1 /= times2;

            // 按坐标排序输出
            sort(brightest.begin(), brightest.end(), cmpXY);
            cout << name << " occurs " << times1 << " time(s) in the map.\n";

            if (times1 > 0)
            {
                cout << "Brightest occurrence:";
                for (auto idx : brightest)
                    cout << " (" << stars1[idx].x << ',' << stars1[idx].y << ")";
                cout << '\n';
            }
        }

        cout << "-----\n";
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **锚点法**：用两个点确定相似变换
2. **整数坐标约束**：排除非整数坐标的变换
3. **去重处理**：利用星座自匹配次数进行归一化
4. **特殊情况**：$s = 1$ 和 $s = 2$ 需要单独处理

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 相似变换 | 旋转 + 缩放 + 平移 |
| 锚点法 | 两个点确定变换参数 |
| 整数坐标 | 变换后坐标必须为整数 |
| 去重 | 一个出现对应多个锚点对 |
| 最亮出现 | 亮度总和最大 |
| 输出排序 | 按 $x$ 升序，$x$ 相同时按 $y$ 升序 |

### 注意事项

1. **浮点精度**：使用 `EPSILON = 1e-6` 处理浮点比较
2. **旋转角计算**：使用 `atan2` 获取角度
3. **坐标检查**：变换后的坐标必须与整数坐标足够接近
4. **去重**：一个出现会被多个锚点对检测到，需要归一化

这种“枚举锚点 + 验证变换”的解题模式，在点集匹配、模式识别等计算机视觉问题中具有广泛应用。
