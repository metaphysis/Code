[UVa 209 Triangluar Vertices](https://blog.csdn.net/metaphysis/article/details/161010462)

## 题目分析

题目要求在无限等边三角形网格上判断给定的顶点集合是否能构成符合特定条件的三角形、平行四边形或六边形。题目给出了一个按行编号的三角网格（从左到右、从上到下编号），并规定：

1. 图形的每条边必须与网格的边重合；
2. 图形的所有边长必须相等。

输入包含若干行，每行是 $1$ 到 $6$ 个不重复的整数（范围 $1 \sim 32767$），表示顶点编号。输出需要判断这些点是否能构成“可接受的”三角形、平行四边形或六边形，并按照样例格式输出。

## 解题思路

本题的核心在于如何利用三角网格的几何性质来判断形状。
### 方法一：基于坐标投影的数值方法

第一份代码（`209-2.txt`）为每个顶点计算平面直角坐标。观察网格规律：每层（行）的 $y$ 坐标递减 $\sqrt{3}$，$x$ 坐标每次偏移 $2$ 个单位，且每层起点 $x$ 坐标向左偏移 $1$ 个单位。通过这种规律可以给每个编号分配 $(x, y)$ 坐标。

得到坐标后：
- **三角形**：三个顶点中至少有两个在同一水平线上（$y$ 相等），且三条边等长。
- **平行四边形**：四顶点分成两组水平线（上下底平行），且四条边等长；或者一组相邻顶点共线，另一组相邻顶点共竖线。
- **六边形**：六个顶点分成三组水平线，相邻边平移交替，且六条边等长。

这种方法直观但需要处理浮点误差，使用 `EPSILON` 进行容差比较。

### 方法二：基于网格编号的代数方法

基于编号的代数关系，避免了浮点运算。代码预计算了三个数组：

- `level[n]`：编号 $n$ 所在的行号（从上往下，起点为 $1$）。
- `principal[n]`：编号 $n$ 所属的“主对角线”族（向右下方向）。
- `secondary[n]`：编号 $n$ 所属的“副对角线”族（向左下方向）。

在三角网格中，每个顶点唯一地由 `(level, principal, secondary)` 确定。利用这些索引关系，可以快速判断点之间的几何关系：

- **三角形**：检查两点是否在同一副对角线上，另外两点是否在同一主对角线上。
- **平行四边形**：利用水平间距和对角线族的一致性来判断。
- **六边形**：检查三组水平点对，间距满足 $d, d, 2d$ 的规律，且对角线族交替匹配。

这种方法效率高且精确，是本题的推荐解法。

## 注意事项

1. 输入的点集可能包含重复编号，需要先去重。若去重后点数与原来不同，直接输出“不可接受”。
2. 输出时严格按照原输入行的顺序输出，且每个结论占一行。
3. 题目保证每组点最多 $6$ 个，因此可以直接按点数分类判断。

## 代码实现

下面是第二种方法（代数法）的完整代码，并添加了详细的中文注释：

```cpp
// Triangular Vertices
// UVa ID: 209
// Verdict: Accepted
// Submission Date: 2016-04-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> vertices, levels;
int principal[33000], secondary[33000], level[33000];

// 预处理每个编号的行号以及所属的主、副对角线族
void makeSet() {
    // 计算 principal 数组：向右下方向的对角线族
    // 每条对角线的起始点编号为 n + step
    for (int n = 1, step = 0; (n + step) < 33000; n += step, step++) {
        int parent = n + step;
        principal[parent] = parent;               // 对角线起点标记为自己
        // 沿着对角线往下，步长每次 +1
        for (int i = parent, j = step + 2; (i + j) < 33000; i += j, j++)
            principal[i + j] = parent;
    }

    // 计算 secondary 数组：向左下方向的对角线族
    for (int n = 0, step = 1; (n + step) < 33000; n += step, step++) {
        int parent = n + step;
        secondary[parent] = parent;
        for (int i = parent, j = step; (i + j) < 33000; i += j, j++)
            secondary[i + j] = parent;
    }

    // 计算 level 数组：每个编号所在的行号
    // 第 step 行有 step 个点
    for (int n = 1, step = 1; n < 33000; step++)
        for (int i = 1; i <= step && n < 33000; i++)
            level[n++] = step;
}

// 判断三个点能否构成等边三角形（网格边重合）
bool triangle() {
    // 情况1：前两个点在同一行
    if (levels[1] == levels[2]) {
        // 检查 0 和 1 是否在同一副对角线上
        if (secondary[vertices[0]] != secondary[vertices[1]])
            return false;
        // 检查 0 和 2 是否在同一主对角线上
        if (principal[vertices[0]] != principal[vertices[2]])
            return false;
        return true;
    }
    // 情况2：第0个和第1个在同一行
    else if (levels[0] == levels[1]) {
        if (principal[vertices[0]] != principal[vertices[2]])
            return false;
        if (secondary[vertices[1]] != secondary[vertices[2]])
            return false;
        return true;
    }

    return false;
}

// 判断四个点能否构成等边平行四边形
bool parallelogram() {
    // 情况1：上下底水平（第0、1行相同，第2、3行相同）
    if (levels[0] == levels[1] && levels[2] == levels[3]) {
        // 边长必须相等
        if ((vertices[1] - vertices[0]) != (vertices[3] - vertices[2]))
            return false;
        if ((vertices[1] - vertices[0]) != (levels[2] - levels[0]))
            return false;
        // 检查对角线族一致性
        if (secondary[vertices[0]] == secondary[vertices[2]])
            return true;
        if (principal[vertices[0]] == principal[vertices[2]])
            return true;
        return false;
    }
    // 情况2：中间两点在同一行（菱形摆放）
    else if (levels[1] == levels[2]) {
        if ((levels[1] - levels[0]) != (vertices[2] - vertices[1]))
            return false;
        if ((levels[3] - levels[1]) != (vertices[2] - vertices[1]))
            return false;
        if (secondary[vertices[0]] != secondary[vertices[1]])
            return false;
        if (principal[vertices[1]] != principal[vertices[3]])
            return false;
        return true;
    }
    return false;
}

// 判断六个点能否构成等边六边形
bool hexagon() {
    // 六边形顶点应分成三组水平对
    if (levels[0] != levels[1] || levels[2] != levels[3] || levels[4] != levels[5])
        return false;

    // 检查各边长度关系
    if ((vertices[1] - vertices[0]) != (vertices[5] - vertices[4]))
        return false;
    if ((vertices[1] - vertices[0]) != (levels[2] - levels[0]))
        return false;
    if ((vertices[1] - vertices[0]) != (levels[4] - levels[2]))
        return false;
    if ((vertices[3] - vertices[2]) != 2 * (vertices[1] - vertices[0]))
        return false;

    // 检查对角线族交替匹配
    if (secondary[vertices[0]] != secondary[vertices[2]])
        return false;
    if (principal[vertices[2]] != principal[vertices[4]])
        return false;

    return true;
}

// 分析一行输入
void analyze(string line) {
    cout << line;

    levels.clear();
    for (int i = 0; i < vertices.size(); i++)
        levels.push_back(level[vertices[i]]);

    if (vertices.size() == 3 && triangle())
        cout << " are the vertices of a triangle\n";
    else if (vertices.size() == 4 && parallelogram())
        cout << " are the vertices of a parallelogram\n";
    else if (vertices.size() == 6 && hexagon())
        cout << " are the vertices of a hexagon\n";
    else
        cout << " are not the vertices of an acceptable figure\n";
}

int main() {
    makeSet();      // 预处理所有编号的几何属性

    string line;
    while (getline(cin, line)) {
        vertices.clear();

        int index;
        istringstream iss(line);
        while (iss >> index)
            vertices.push_back(index);

        // 排序并去重
        sort(vertices.begin(), vertices.end());
        int n = unique(vertices.begin(), vertices.end()) - vertices.begin();

        // 若有重复点，直接判为不可接受
        if (n != vertices.size())
            cout << line << " are not the vertices of an acceptable figure\n";
        else
            analyze(line);
    }

    return 0;
}
```

## 总结

本题是典型的网格几何推理题，既可以通过坐标映射转为平面计算几何，也可以利用编号间的代数关系高效求解。第二种方法避免了浮点误差，且时间复杂度低，是竞赛中的首选方法。理解三角网格的编号规律以及“主对角线族”和“副对角线族”的概念，是解决本题的关键。
