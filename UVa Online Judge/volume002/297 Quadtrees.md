[UVa 297 Quadtrees](https://blog.csdn.net/metaphysis/article/details/161389482)

## 题目分析

本题涉及一种名为 **四叉树** 的图像编码格式。四叉树的基本思想是将图像递归地划分为四个象限，直到每个象限内的像素颜色一致为止。每个节点可以是以下三种类型：

- $\texttt{p}$（`parent`）：表示内部节点，需要进一步划分四个子象限。
- $\texttt{f}$（`full`）：表示该区域全部为黑色像素。
- $\texttt{e}$（`empty`）：表示该区域全部为白色像素。

题目中处理的图像尺寸为 $32 \times 32$ 像素，总计 $1024$ 个像素。艺术家要执行的操作是将两张图像进行 **叠加**：在结果图像中，若某个像素在至少一张原图像中为黑色，则该像素为黑色，否则为白色。

**输入** 包含多个测试用例，每个测试用例给出两个字符串，分别代表两张图像的四叉树先序遍历序列。树的深度不超过 $5$（因为 $2^5 = 32$）。

**输出** 需要计算叠加后图像中黑色像素的数量。

### 样例分析

以第一个样例为例：
- 输入：`ppeeefpffeefe` 和 `pepeefe`
- 输出：$640$ 个黑色像素

## 解题思路

### 核心问题转化

直接对四叉树进行“叠加”操作比较棘手，因为两棵树的结构可能不同（深度、分支情况各异）。一个更简单的方法是：

1. 将四叉树的表示 **还原** 为 $32 \times 32$ 的像素网格。
2. 在两幅网格上分别进行“着色”。
3. 最后统计黑色像素的数量。

由于图像尺寸固定为 $32 \times 32$，我们可以使用一个二维数组 `image[32][32]` 来存储每个像素的颜色状态。

### 四叉树的解析与着色

四叉树的先序遍历序列中，每个节点按以下规则处理：

- 遇到 $\texttt{p}$：该区域需要继续划分。按照固定的象限顺序（题目图示中明确），递归处理四个子区域。
- 遇到 $\texttt{e}$：该区域全部为白色，将其标记为白色。
- 遇到 $\texttt{f}$：该区域全部为黑色，将其标记为黑色。

#### 象限划分顺序

从题目图示可以看出，四叉树的子节点顺序（先序遍历）为：

1. 右上象限- 实际上根据代码实现：
   - 第一个递归：`(x, y + width/2)` —— 右上
   - 第二个递归：`(x, y)` —— 左上
   - 第三个递归：`(x + width/2, y)` —— 左下
   - 第四个递归：`(x + width/2, y + width/2)` —— 右下

### 叠加逻辑的实现

在代码中，叠加操作是通过 **顺序执行两次解析** 隐式完成的：

1. 首先解析第一棵树，将对应区域标记为黑色（$\texttt{b}$）或白色（$\texttt{w}$）。
2. 然后解析第二棵树。在解析过程中：
   - 如果遇到白色区域（$\texttt{e}$），只将尚未被标记为黑色的像素设为白色。
   - 如果遇到黑色区域（$\texttt{f}$），将对应区域 **强制覆盖** 为黑色（无论之前是什么颜色）。

这样，最终 `image` 数组中，$\texttt{b}$ 表示该像素在至少一张图像中为黑色，$\texttt{w}$ 表示两张图像中均为白色，`0` 表示尚未被任何树处理过的区域（实际上在解析完两棵树后不会存在）。

### 为什么这样做是正确的？

叠加的定义是：结果图像中某像素为黑色 $\iff$ 它在图像 `A` 中为黑色 **或** 在图像 `B` 中为黑色。

- 第一棵树解析后，黑色像素已被正确标记。
- 第二棵树解析时，遇到黑色区域直接将其涂黑，这符合“或”操作。
- 白色区域不会覆盖已有的黑色，这保证了黑色像素不会被错误地擦除。

因此，最终统计 $\texttt{b}$ 的数量即可得到答案。

### 复杂度分析

- 每个测试用例需要遍历 $32 \times 32 = 1024$ 个像素。
- 四叉树的节点数最多为 $1 + 4 + 4^2 + 4^3 + 4^4 + 4^5 \approx 1365$ 个，每个节点处理的区域大小与深度相关。
- 总体时间复杂度为 $O(\text{像素数} + \text{节点数})$，对于本题规模完全可行。

## 代码实现

```cpp
// Quadtrees
// UVa ID: 297
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储 32x32 图像的像素颜色
// '0' 表示未处理，'b' 表示黑色，'w' 表示白色
char image[32][32];

// 递归解析四叉树的先序遍历序列
// tree: 先序遍历字符串
// index: 当前处理到的位置（引用传递，便于递归推进）
// x, y: 当前区域左上角坐标
// width: 当前区域的边长
void parse(string &tree, int &index, int x, int y, int width)
{
    if (index < tree.length() && tree[index] == 'p')
    {
        // 内部节点：递归处理四个子象限
        // 顺序：右上、左上、左下、右下
        parse(tree, ++index, x, y + width / 2, width / 2);
        parse(tree, ++index, x, y, width / 2);
        parse(tree, ++index, x + width / 2, y, width / 2);
        parse(tree, ++index, x + width / 2, y + width / 2, width / 2);
    }
    else if (index < tree.length() && tree[index] == 'e')
    {
        // 空节点：整个区域为白色
        // 只有当像素尚未被标记为黑色时，才标记为白色
        for (int i = x; i < x + width; i++)
            for (int j = y; j < y + width; j++)
                if (image[i][j] == '0' || image[i][j] == 'w')
                    image[i][j] = 'w';
    }
    else if (index < tree.length() && tree[index] == 'f')
    {
        // 满节点：整个区域为黑色，直接覆盖
        for (int i = x; i < x + width; i++)
            for (int j = y; j < y + width; j++)
                    image[i][j] = 'b';
    }
}

// 统计图像中黑色像素的数量
int count()
{
    int counter = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
            if (image[i][j] == 'b')
                counter++;
    return counter;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int n;
    cin >> n;
    
    string first, second;
    while (n--)
    {
        // 初始化图像数组，所有像素标记为未处理 '0'
        for (int i = 0; i < 32; i++)
            for (int j = 0; j < 32; j++)
                image[i][j] = '0';
                
        cin >> first >> second;

        // 解析第一棵树，标记黑色和白色区域
        int index = 0;
        parse(first, index, 0, 0, 32);

        // 解析第二棵树，叠加黑色区域
        index = 0;
        parse(second, index, 0, 0, 32);
        
        cout << "There are " << count() << " black pixels.\n";
    }
    
	return 0;
}
```

## 总结

本题的核心技巧是将树形结构的图像表示 **展开为二维网格**，利用网格的固定尺寸简化叠加操作。这种方法避免了直接对两棵不同结构的四叉树进行合并的复杂性，代码实现清晰且易于理解。对于图像处理类问题，当图像尺寸固定且较小时，这种“暴力展开”的策略往往是高效且可靠的。
