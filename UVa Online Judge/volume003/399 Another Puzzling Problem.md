[UVa 399 Another Puzzling Problem](https://blog.csdn.net/metaphysis/article/details/161705501)

## 题目描述

你需要编写一个程序来解决拼图问题。输入文件包含拼图的尺寸、拼图片的尺寸以及拼图片的实际内容。拼图片由 `ASCII` 字符组成。你需要输出一个已解决的拼图。

### 输入格式

第一行包含整数 $N$（拼图数量）。每个拼图的描述如下：

- 第一行包含三个整数：拼图尺寸（正方形）、拼图片的高度和宽度。
  - 拼图尺寸范围 $2 \sim 10$，拼图片高度和宽度范围 $1 \sim 25$。
- 其余描述以任意顺序指定拼图片。每个拼图片由以下组成：
  - 一个图像（$h \times w$ 个字符，可能包含空格）
  - 一行包含四个整数（范围 $-5 \sim +5$），表示拼图片的上、左、下、右边缘的形状。
    - $0$：直边（外缘）
    - 正负相同数值的边可以互锁（如 $-5$ 与 $+5$ 互锁，$-4$ 与 $+4$ 互锁等）

拼图片不能旋转，所有拼图片都是唯一的（没有两片有完全相同的四边值）。每个拼图片后有一个空行，不同拼图之间也有空行。

### 输出格式

输出文件应包含已解决的拼图，按正确排列输出，两个连续拼图之间用一个空行分隔。每个输入拼图有且只有一个解。

### 样例输入

```
2
2 2 3
00C
BCC
-2 2 0 0

A00
AAB
5 0 0 -2

XXY
X00
0 0 -5 -5

YZZ
OOZ
0 5 2 0
```

### 样例输出

```
XXYYZZ
XOOOOZ
AOOOOC

0&'8888, 088'8888888. 8'- -:8888b 8' 8888 d8.- =.. ,==-. :888b >8 ^- :-'d8888 88 ,8888 88b. ^- ' :8888 888b -==- . :8888 88880--:':8888 '8888| ::' 8888b 888^~' 8888b d888 ,'888b. d88% %'%8--'- . /88: . , %-1 --- - ! ! ! :===.. -1 = - .
```

---

## 题目分析

### 问题的本质

这是一个**拼图求解**问题。已知：
- 拼图尺寸 $D \times D$（$D$ 为拼图片数量）
- 每个拼图片的高度 $h$ 和宽度 $w$
- 每个拼片的图像（$h \times w$ 字符矩阵）
- 每个拼片的四边形状值（上、左、下、右）

约束条件：
- 相邻拼片的边缘必须互锁（值相反，$x$ 与 $-x$）
- 外边缘（拼图边界）的边值必须为 $0$

### 搜索策略

使用**回溯法**按行优先顺序放置拼片：
- 对于每个位置，根据已放置的左边和上边的拼片，确定当前拼片需要的左边缘值和上边缘值
- 如果处于边界，则要求边缘值为 $0$
- 尝试所有未使用且边缘匹配的拼片

### 关键点

- 拼片不能旋转，所以每个拼片只有一种朝向
- 唯一解保证
- 拼片图像包含空格字符，需原样输出

---
## 参考代码

```cpp
// Another Puzzling Problem
// UVa ID: 399
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct piece
{
    int top, left, bottom, right;
    char image[30][30];
};

vector<piece> pieces;
vector<bool> visited;
int puzzle[15][15];           // 拼图布局（存储拼片索引）
int dimension, row, column;   // 拼图尺寸、拼片高度、宽度
char picture[110][900];       // 组合后的图像

// 深度优先搜索
bool backtrack(int depth)
{
    // 所有拼片都放置完毕
    if (depth == dimension * dimension)
    {
        // 组合图像
        int top = 0;
        for (int h = 0; h < dimension; h++)
        {
            int left = 0;
            for (int w = 0; w < dimension; w++)
            {
                int idx = puzzle[h][w];
                for (int r = 0; r < row; r++)
                    for (int c = 0; c < column; c++)
                        picture[top + r][left + c] = pieces[idx].image[r][c];
                left += column;
            }
            top += row;
        }

        // 输出结果
        for (int i = 0; i < dimension * row; i++)
        {
            for (int j = 0; j < dimension * column; j++)
                cout << picture[i][j];
            cout << endl;
        }
        return true;
    }

    int r = depth / dimension;
    int c = depth % dimension;
    
    // 确定当前拼片所需的上、左边缘值
    int topReq = (r == 0) ? 0 : -pieces[puzzle[r - 1][c]].bottom;
    int leftReq = (c == 0) ? 0 : -pieces[puzzle[r][c - 1]].right;
    
    // 确定当前拼片所需的下、右边缘值（如果位于边界，则需要为 0）
    int bottomReq = (r == dimension - 1) ? 0 : -10;
    int rightReq = (c == dimension - 1) ? 0 : -10;

    // 尝试所有未使用的拼片
    for (int i = 0; i < pieces.size(); i++)
    {
        if (!visited[i] && 
            (topReq == -10 || pieces[i].top == topReq) &&
            (leftReq == -10 || pieces[i].left == leftReq) &&
            (bottomReq == -10 || pieces[i].bottom == bottomReq) &&
            (rightReq == -10 || pieces[i].right == rightReq))
        {
            visited[i] = true;
            puzzle[r][c] = i;
            if (backtrack(depth + 1))
                return true;
            visited[i] = false;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    string line;
    istringstream iss;

    getline(cin, line);
    n = stoi(line);

    for (int i = 1; i <= n; i++)
    {
        if (i > 1)
            cout << endl;

        pieces.clear();

        // 读取拼图尺寸
        getline(cin, line);
        iss.clear();
        iss.str(line);
        iss >> dimension >> row >> column;

        // 读取所有拼片
        for (int j = 1; j <= dimension * dimension; j++)
        {
            piece aPiece;
            // 读取拼片图像
            for (int r = 0; r < row; r++)
            {
                getline(cin, line);
                for (int c = 0; c < column; c++)
                    aPiece.image[r][c] = line[c];
            }
            // 读取边缘值
            getline(cin, line);
            iss.clear();
            iss.str(line);
            iss >> aPiece.top >> aPiece.left >> aPiece.bottom >> aPiece.right;
            pieces.push_back(aPiece);
            // 跳过空行
            getline(cin, line);
        }

        visited.resize(dimension * dimension);
        fill(visited.begin(), visited.end(), false);

        backtrack(0);
    }

    return 0;
}
```
