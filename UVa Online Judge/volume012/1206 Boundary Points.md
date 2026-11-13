
> **摘要**：本文讲解如何用 $\texttt{Graham}$ 扫描算法求解平面点集的凸包。文章从题目描述与输入输出格式出发，介绍叉积、极角排序等几何基础，详细剖析 $\texttt{Graham}$ 扫描的构造过程与重复点、共线边界点的处理方式，并给出完整的正确性证明与复杂度分析，最后附上可运行的 $\texttt{C++}$ 实现代码，整体时间复杂度为 $O(n\log n)$。

# 题目描述

给定平面上的一组点，要求求出包含所有给定点的最小凸多边形，即这些点的凸包。

凸包可以理解为：用一根橡皮筋包围所有点，橡皮筋收紧后形成的多边形边界就是这些点的凸包边界。

输入中的每个点表示为：

```text
(x,y)
```

其中 $x,y$ 为实数。每一行表示一组点，也就是一个测试用例。需要对每一行输入分别求出凸包，并按顺序输出凸包顶点。输出序列的第一个点和最后一个点必须相同，从而表示一个闭合多边形。

# 输入格式

输入包含多组测试数据，每组数据占一行。

每行包含若干个点，点的格式为：

```text
(x, y)
```

点之间使用空格分隔。输入持续到文件结束。

# 输出格式

对于每组测试数据，输出一行凸包顶点。

相邻点之间使用空格分隔，每个点按照如下格式输出：

```text
(x,y)
```

输出的第一个点和最后一个点必须相同。凸包顶点的遍历方向不作要求，只要输出的是合法的凸包边界即可。

# 样例输入

```text
(-2,1) (-1,-2) (-1,1) (-1,2) (-1,3) (0,0) (1,-1) (1,1) (2,-2) (2,1) (3,2)
```

# 样例输出

```text
(-1,-2) (2,-2) (3,2) (-1,3) (-2,1) (-1,-2)
```

# 题目分析

直接判断任意点是否位于凸包内部并不方便。常用做法是先将点按照某种规则排序，再依次构造凸包边界。

本题使用 $\texttt{Graham}$ 扫描算法。算法的核心步骤如下：

1. 删除重复点。
2. 选择一个确定的起点。
3. 按照相对于起点的极角排序其他点。
4. 按顺序扫描排序后的点，并利用叉积判断当前边界是否保持凸性。
5. 如果新加入的点使边界出现右转，则删除之前的边界点，直到重新满足凸性。

代码将点按照：

- $y$ 坐标升序；
- 若 $y$ 相同，则按照 $x$ 坐标升序；

进行排序。因此排序后的第一个点一定是最下方、最靠左的点。这个点必然位于凸包上，将其记为参考点 $\textit{pr}$。

随后按照相对于 $\textit{pr}$ 的极角逆时针排序其他点。如果两个点与参考点共线，则距离参考点较近的点排在前面。

# 几何基础

## 叉积

对于三个点 $A,B,C$，定义：

$$
\operatorname{cross}(A,B,C)=
(B_x-A_x)(C_y-A_y)-
(B_y-A_y)(C_x-A_x)
$$

它表示向量 $\overrightarrow{AB}$ 和 $\overrightarrow{AC}$ 的叉积。

根据叉积的符号，可以判断三个点的转向：

- $\operatorname{cross}(A,B,C)>0$：逆时针转向；
- $\operatorname{cross}(A,B,C)<0$：顺时针转向；
- $\operatorname{cross}(A,B,C)=0$：三点共线。

代码中对应的函数为：

```cpp
double cp(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}
```

由于坐标是浮点数，代码使用 $\varepsilon=10^{-7}$ 判断两个数是否足够接近 $0$：

```cpp
bool cw(point a, point b, point c)
{
    return cp(a, b, c) < -EPSILON;
}

bool ccw(point a, point b, point c)
{
    return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c)
{
    return fabs(cp(a, b, c)) <= EPSILON;
}
```

## 极角排序

参考点固定后，任意两个点 $A,B$ 的相对极角顺序可以通过叉积判断：

- 若 $\operatorname{cross}(\textit{pr},A,B)>0$，则 $A$ 的极角小于 $B$；
- 若两者与参考点共线，则距离参考点较近的点排在前面。

代码中的比较函数如下：

```cpp
bool cmpAngle(point &a, point &b)
{
    if (collinear(pr, a, b))
        return pr.distTo(a) <= pr.distTo(b);
    return ccw(pr, a, b);
}
```

需要注意，代码只比较平方距离：

$$
(x_1-x_2)^2+(y_1-y_2)^2
$$

而没有使用平方根，因此计算更简单，也足以比较距离大小规律。

# $\texttt{Graham}$ 扫描过程

设当前已经构造出的凸包栈中最后三个点为：

$$
A,B,C
$$

如果 $A\to B\to C$ 形成顺时针转向，则说明点 $B$ 不可能是凸包顶点，需要将 $B$ 删除。

如果三点共线，则代码保留更远的点，删除中间点。这样可以避免将同一条凸包边上的非端点列入结果。

代码中的核心扫描部分为：

```cpp
int top = 2, next = 2, total = ch.size() - 1;

while (next <= total)
{
    if (cw(ch[top - 2], ch[top - 1], ch[next]))
        top--;
    else 
    {
        if (collinear(ch[top - 2], ch[top - 1], ch[next]))
            ch[top - 1] = ch[next++];
        else
            ch[top++] = ch[next++];
    }
}
```

其中：

- `top` 表示当前凸包栈中有效元素的数量；
- `next` 表示下一个待处理的点；
- `ch[0]` 到 `ch[top-1]` 是当前凸包序列。

当出现顺时针转向时，执行：

```cpp
top--;
```

相当于弹出当前凸包的最后一个点，然后重新检查新的最后两个点与待加入点之间的关系。

如果三点共线，则执行：

```cpp
ch[top - 1] = ch[next++];
```

用更远的点替换原来的点，从而保留凸包边界上的最外侧端点。

# 重复点和边界点处理

在正式构造凸包前，代码先对所有点进行排序，并删除重复点：

```cpp
sort(ch.begin(), ch.end());
ch.erase(unique(ch.begin(), ch.end()), ch.end());
```

`operator<` 按照 $y$ 坐标、$x$ 坐标排序，`operator==` 使用 $\varepsilon$ 判断两个浮点坐标是否相等：

```cpp
bool operator==(const point &p) const
{
    return fabs(x - p.x) <= EPSILON &&
           fabs(y - p.y) <= EPSILON;
}
```

如果去重后的点数少于 $3$，这些点本身就构成最小凸包，因此代码直接返回：

```cpp
if (ch.size() < 3) return ch;
```

对于同一条凸包边上的多个共线点，代码只保留距离更远的端点。这是因为凸包多边形通常只需要输出顶点，不需要输出边上的中间点。

# 正确性证明

下面证明代码得到的结果确实是所有输入点的凸包。

## 引理 1：参考点一定在凸包上

代码选择排序后的第一个点作为参考点。该点具有最小的 $y$ 坐标；若有多个点的 $y$ 坐标相同，则它具有最小的 $x$ 坐标。

这样的点不可能严格位于其他点构成的凸包内部，因为在该方向上没有输入点比它更低或在相同高度上更靠左。因此，参考点一定是凸包顶点。

## 引理 2：极角排序后，凸包点按边界顺序被处理

所有点都按照相对于参考点的极角升序排列。对于任意两个非共线点，叉积可以正确判断其极角先后；对于共线点，则按照距离从近到远排列。

因此，扫描顺序相当于从参考点沿一个方向绕一周依次观察所有点。

## 引理 3：顺时针转向的中间点不属于凸包

假设当前连续三个点为 $A,B,C$，且：

$$
\operatorname{cross}(A,B,C)<0
$$

这说明从 $A$ 到 $B$ 再到 $C$ 形成顺时针转向。由于所有点按极角顺序处理，点 $B$ 位于当前外边界的内侧，不可能成为最终凸包的顶点。

因此，删除 $B$ 不会删除真正的凸包顶点。

## 引理 4：扫描结束后，栈中的点构成凸包边界

扫描过程中：

- 只有顺时针转向的点会被删除；
- 共线点只保留最远端点；
- 其他点按照逆时针方向加入栈中。

因此，栈中的相邻边始终保持逆时针转向或共线，且所有被删除的点都位于当前边界内部。扫描完成后，栈中的点按顺序形成包含所有输入点的最小凸多边形。

## 定理：算法输出的是最小凸包

由上述引理，参考点位于凸包上，所有点按照正确的极角顺序处理，扫描过程中删除的点均不可能是凸包顶点，最终保留的点恰好是凸包顶点。因此，算法输出的闭合点序列就是所有输入点的凸包。

# 解题步骤

对于每一行输入，执行以下步骤：

1. 读取整行字符串。
2. 删除空格和左括号，将输入转换为便于分段解析的形式。
3. 按右括号 `)` 分割每个点。
4. 从每个分段中读取横坐标、逗号和纵坐标。
5. 对点进行排序并删除重复点。
6. 如果点数少于 $3$，直接输出这些点。
7. 选择排序后的第一个点作为参考点。
8. 按相对于参考点的极角对其余点排序。
9. 使用 $\texttt{Graham}$ 扫描构造凸包。
10. 输出凸包点序列。

代码的输入处理部分如下：

```cpp
string line;
while (getline(cin, line))
{
    polygon pg;
    
    string modified;
    for (int i = 0; i < line.length(); i++)
    {
        if (isblank(line[i]) || line[i] == '(')
            continue;
        modified += line[i];
    }
    
    istringstream iss1(modified);
    string block;
    while (getline(iss1, block, ')'))
    {
        if (block.length() == 0)
            continue;

        istringstream iss2(block);
        double x, y;
        char comma;
        iss2 >> x >> comma >> y;
        pg.push_back(point(x, y));
    }

    polygon ch = grahamConvexHull(pg);
    ...
}
```

由于一组点占据一整行，不能直接使用普通的 `cin >> x >> y` 读取，因此代码使用 `getline` 读取整行，再通过字符串流进行解析。

# 复杂度分析

设一组测试数据包含 $n$ 个点。

- 排序点的时间复杂度为 $O(n\log n)$；
- 删除重复点的时间复杂度为 $O(n)$；
- 按极角排序的时间复杂度为 $O(n\log n)$；
- $\texttt{Graham}$ 扫描中每个点最多入栈、出栈一次，时间复杂度为 $O(n)$。

因此，总时间复杂度为：

$$
O(n\log n)
$$

排序和辅助数组需要的空间为：

$$
O(n)
$$

# 代码实现

```cpp
// Boundary Points
// UVa ID: 1206
// Verdict: Accepted
// Submission Date: 2018-04-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    
    point (double x = 0, double y = 0): x(x), y(y) {}

    bool operator<(const point &p) const
    {
        if (fabs(y - p.y) > EPSILON)
            return y < p.y;
        return x < p.x;
    }

    bool operator==(const point &p) const
    {
        return fabs(x - p.x) <= EPSILON &&
               fabs(y - p.y) <= EPSILON;
    }

    double distTo(const point &p)
    {
        return pow(x - p.x, 2) + pow(y - p.y, 2);
    }
};

typedef vector<point> polygon;

point pr;

double cp(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

bool cw(point a, point b, point c)
{
    return cp(a, b, c) < -EPSILON;
}

bool ccw(point a, point b, point c)
{
    return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c)
{
    return fabs(cp(a, b, c)) <= EPSILON;
}

bool cmpAngle(point &a, point &b)
{
    if (collinear(pr, a, b))
        return pr.distTo(a) <= pr.distTo(b);

    return ccw(pr, a, b);
}

polygon grahamConvexHull(polygon &pg)
{
    polygon ch(pg);

    sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());

    if (ch.size() < 3)
        return ch;

    pr = ch.front();

    sort(ch.begin() + 1, ch.end(), cmpAngle);

    // 将起点放到末尾，便于扫描闭合边界
    ch.push_back(pr);

    int top = 2;
    int next = 2;
    int total = ch.size() - 1;

    while (next <= total)
    {
        if (cw(ch[top - 2], ch[top - 1], ch[next]))
        {
            top--;
        }
        else
        {
            if (collinear(ch[top - 2], ch[top - 1], ch[next]))
                ch[top - 1] = ch[next++];
            else
                ch[top++] = ch[next++];
        }
    }

    ch.erase(ch.begin() + top, ch.end());

    return ch;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    string line;

    while (getline(cin, line))
    {
        polygon pg;

        string modified;

        for (int i = 0; i < line.length(); i++)
        {
            if (isblank(line[i]) || line[i] == '(')
                continue;

            modified += line[i];
        }

        istringstream iss1(modified);
        string block;

        while (getline(iss1, block, ')'))
        {
            if (block.length() == 0)
                continue;

            istringstream iss2(block);

            double x, y;
            char comma;

            iss2 >> x >> comma >> y;
            pg.push_back(point(x, y));
        }

        polygon ch = grahamConvexHull(pg);

        for (int i = 0; i < ch.size(); i++)
        {
            if (i)
                cout << ' ';

            cout << '(' << ch[i].x << ',' << ch[i].y << ')';
        }

        cout << '\n';
    }

    return 0;
}
```

# 总结

本题的核心是使用 $\texttt{Graham}$ 扫描算法求平面点集的凸包。

关键步骤如下：

- 使用最低且最靠左的点作为参考点；
- 按相对于参考点的极角排序；
- 通过叉积判断连续三点是否发生顺时针转向；
- 删除使边界向内凹的点；
- 对共线点只保留最远端点；
- 最终得到按边界顺序排列的凸包顶点。

由于点坐标使用浮点数，比较坐标和叉积时必须设置误差范围 $\varepsilon$。整体复杂度为 $O(n\log n)$，能够高效处理本题中的多组点集。
