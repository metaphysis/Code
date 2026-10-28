## 题目描述

给定一张矩形纸片，其初始宽度为 $W$，高度为 $H$。纸片正面朝上，左上角坐标为 $(0, 0)$，向右为 $x$ 轴正方向，向下为 $y$ 轴正方向。在纸片上有一个点，初始位置为 $(x, y)$，且初始时点可能位于纸片的正面（`T`）或反面（`B`）。

随后会执行一系列折叠操作，每次折叠选择纸片的某一条边（上 `T`、下 `B`、左 `L`、右 `R`），并指定折叠方向：将选中的边 **覆盖**（`O`）到另一侧上，或者 **垫在**（`U`）另一侧下方。折叠后纸片尺寸相应减半，点的新位置和所在纸面（正/反）以及所在层数（页号）都可能发生变化。

输入包含多组数据，每组数据以一个 `S` 表示折叠结束。要求输出折叠前和折叠后纸片的尺寸、点的坐标、点的朝向以及点所在的页号（从第 $1$ 页开始计数）。

## 输入格式

每组数据由若干条记录组成，记录类型如下：

- **类型 1**：包含两个实数 $W$ 和 $H$，分别表示纸片的宽度和高度。
- **类型 2**：包含两个实数 $x$、$y$ 和一个字符 $c$（`T` 或 `B`），分别表示点的横坐标、纵坐标以及点所在的纸面（`T` 为正面，`B` 为反面）。
- **类型 3**：包含两个连续的大写字母，第一个字母表示折叠边（`T` 上，`B` 下，`L` 左，`R` 右），第二个字母表示折叠方式（`O` 覆盖，`U` 垫下）。例如 `TO` 表示将上边向下折叠并覆盖在下半部分之上。
- **类型 4**：包含一个大写字母 `S`，表示结束该组数据的折叠指令。

所有输入数据均保证点不会落在纸的边缘或折线上。

## 输出格式

对于每组数据，输出以下信息（格式与样例严格一致）：

- 第一行：`Paper number X`，其中 $X$ 为数据组编号。
- 第二行：`Beginning paper dimensions W X H`，精度为 $6$ 位小数。
- 第三行：`Dot is on SIDE of page 1. Position: x X y`，其中 `SIDE` 为 `TOP` 或 `BOTTOM`。
- 空行。
- 第五行：`After folding paper. Paper dimensions: W X H`。
- 第六行：`Dot is on SIDE of page P. Position x X y`，其中 $P$ 为折叠后点所在的页号。
- 再空一行（两组数据之间有一个空行）。

允许输出与标准答案有 $10^{-6}$ 的绝对误差。

## 样例

输入
```
5.0 8.25
3.25 8.00 T
TO
LU
S
1.0 2.0
.55 1.3 B
LO
S
```
输出
```
Paper number 1
Beginning paper dimensions 5.000000 X 8.250000
Dot is on TOP of page 1. Position: 3.250000 X 8.000000

After folding paper. Paper dimensions: 2.500000 X 4.125000
Dot is on TOP of page 2. Position 0.750000 X 3.875000

Paper number 2
Beginning paper dimensions 1.000000 X 2.000000
Dot is on BOTTOM of page 1. Position: 0.550000 X 1.300000

After folding paper. Paper dimensions: 0.500000 X 2.000000
Dot is on BOTTOM of page 2. Position 0.050000 X 1.300000

```

## 题目分析

本题的核心是精确模拟纸片折叠过程中点的位置、朝向和所在层数的变化。每一次折叠都会将纸片沿中线对折，纸片尺寸减半，同时点的坐标可能需要镜像，点的朝向（正/反）也可能翻转。此外，由于多次折叠后纸片由多层叠加而成，点所在的“页号”（即层号）也需要根据折叠方向和点落在被折叠侧还是固定侧来动态更新。

直接按照物理过程模拟即可：维护当前纸片的宽度 $W$、高度 $H$，点的坐标 $(x, y)$，点的朝向 `side`（`T` 或 `B`），以及点当前所在的层号 `page` 和总层数 `totalLayers`。每执行一次折叠，根据折叠边和方向，计算点的新坐标、新的朝向，以及新的层号。

## 解题思路

### 坐标变换

折叠总是沿着纸片的中线（水平或垂直）进行。设折叠前的宽度为 $W_0$，高度为 $H_0$。

- **折叠上边（`T`）**：中线为 $y = H_0 / 2$。若点位于上半部分（$y < H_0/2$），则它被折叠，其新纵坐标为 $y' = H_0/2 - y$（关于中线镜像）；若点位于下半部分，则它未被折叠，但坐标系原点下移，所以 $y' = y - H_0/2$。折叠后高度变为 $H_0 / 2$。
- **折叠下边（`B`）**：若点位于下半部分（$y > H_0/2$），则被折叠，新纵坐标 $y' = H_0 - y$；若在上半部分，则 $y$ 不变。高度减半。
- **折叠左边（`L`）**：类似，关于 $x = W_0/2$ 镜像，宽度减半。
- **折叠右边（`R`）**：类似，宽度减半。

### 纸面翻转

每次折叠，被折叠的那一半纸片会翻转过来，因此点如果位于被折叠的那一半，其纸面（`T`/`B`）会翻转（`T` 变 `B`，`B` 变 `T`）。未被折叠的一半，纸面保持不变。

### 层号更新

纸片折叠后，原来的一层变成两层，总层数翻倍。假设当前总层数为 $L$，点所在层号为 $p$（$1 \le p \le L$），第 $1$ 层为最顶层。

- **若点位于被折叠的那一半**：  
  该半部分翻转后，其内部层序反转（原来的第 $p$ 层变为第 $L - p + 1$ 层）。再根据折叠方向 `O`（覆盖）或 `U`（垫下）决定该翻转后的部分放置在顶部还是底部。
  - 若为 `O`（覆盖），则翻转后的部分置于最上方，因此新层号 $p' = L - p + 1$。
  - 若为 `U`（垫下），则翻转后的部分置于最下方，因此新层号 $p' = L + (L - p + 1)$。

- **若点位于未被折叠的那一半**：  
  该半部分保持原顺序，且其相对位置（上或下）由折叠方向决定。
  - 若为 `O`（覆盖），被折叠的一半覆盖在上面，即在当前未折叠部分的上方增加了 $L$ 层，所以新层号 $p' = p + L$。
  - 若为 `U`（垫下），被折叠的一半垫在下面，未折叠部分仍在上面，层号不变 $p' = p$。

每次折叠后，总层数更新为 $2L$。

### 算法流程

对每组数据：

1. 读入初始纸片尺寸 $W$、$H$。
2. 读入点坐标 $(x, y)$ 和朝向 `side`。
3. 初始化 `page = 1`，`totalLayers = 1`。
4. 输出初始状态。
5. 循环读取折叠指令，直到遇到 `S`：
   - 解析折叠边 `edge` 和方向 `dir`。
   - 保存折叠前的旧尺寸 `oldW`、`oldH` 和旧层数 `oldL`。
   - 根据折叠边执行坐标变换，并标记点是否被折叠（`folded`）。
   - 若 `folded` 为真，则翻转纸面。
   - 根据 `folded` 和 `dir` 更新 `page`。
   - 更新 `totalLayers *= 2`，尺寸相应减半。
6. 输出最终状态。

## 复杂度分析

每组数据处理的折叠指令数为 $k$，每次折叠操作的时间复杂度为 $O(1)$。因此总时间复杂度为 $O(k)$，空间复杂度为 $O(1)$。

## 代码实现

```cpp
// Follow the Folding Dot
// UVa ID: 733
// Verdict: Accepted
// Submission Date: 2026-07-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 翻转纸面：T<->B
char flipSide(char c) { return c == 'T' ? 'B' : 'T'; }

int main() {
    int paperNo = 0;
    double W, H, x, y;
    char side;
    string token;

    while (cin >> W >> H) {                     // 类型1：宽 高
        ++paperNo;
        cin >> x >> y >> side;                  // 类型2：坐标 面

        double initW = W, initH = H, initX = x, initY = y;
        char initSide = side;
        int page = 1;                           // 当前点所在页（层）号
        int totalLayers = 1;                    // 当前纸张总层数

        // 输出开始信息
        cout << "Paper number " << paperNo << "\n";
        cout << "Beginning paper dimensions " << fixed << setprecision(6)
             << initW << " X " << initH << "\n";
        cout << "Dot is on " << (initSide == 'T' ? "TOP" : "BOTTOM")
             << " of page 1. Position: " << initX << " X " << initY << "\n";

        // 循环执行折叠指令，直到 'S'
        while (cin >> token) {
            if (token == "S") break;

            char edge = token[0];               // 折叠边：T/B/L/R
            char dir = token[1];                // 方向：O（over）或 U（under）

            double oldW = W, oldH = H;
            int oldL = totalLayers;
            bool folded = false;                // 点是否位于被折叠的那一半

            if (edge == 'T') {                  // 折叠上边
                if (y < oldH / 2.0) {           // 点在上半部分（被折叠）
                    folded = true;
                    y = oldH / 2.0 - y;         // 关于中线镜像
                    side = flipSide(side);
                } else {                        // 点在下半部分（未折叠）
                    y = y - oldH / 2.0;         // 新原点下移
                }
                H = oldH / 2.0;
            } else if (edge == 'B') {           // 折叠下边
                if (y > oldH / 2.0) {           // 点在下半部分（被折叠）
                    folded = true;
                    y = oldH - y;               // 镜像
                    side = flipSide(side);
                }                               // 上半部分未折叠，y 不变
                H = oldH / 2.0;
            } else if (edge == 'L') {           // 折叠左边
                if (x < oldW / 2.0) {           // 点在左半（被折叠）
                    folded = true;
                    x = oldW / 2.0 - x;
                    side = flipSide(side);
                } else {                        // 点在右半（未折叠）
                    x = x - oldW / 2.0;         // 新原点右移
                }
                W = oldW / 2.0;
            } else if (edge == 'R') {           // 折叠右边
                if (x > oldW / 2.0) {           // 点在右半（被折叠）
                    folded = true;
                    x = oldW - x;
                    side = flipSide(side);
                }                               // 左半未折叠，x 不变
                W = oldW / 2.0;
            }

            // 更新点所在的页号（层号）
            if (folded) {                       // 被折叠的那一半翻转后重新堆叠
                if (dir == 'O')                 // over：被折叠部分置于顶部
                    page = oldL - page + 1;     // 内部顺序反转，再放在最上面
                else if (dir == 'U')            // under：被折叠部分置于底部
                    page = oldL + (oldL - page + 1);
            } else {                            // 未被折叠的一半
                if (dir == 'O')                 // over：上面增加了 oldL 层
                    page = page + oldL;
                // dir == 'U' 时，下面增加层，页号不变
            }

            totalLayers = oldL * 2;             // 层数加倍
        }

        // 输出最终结果
        cout << '\n';
        cout << "After folding paper. Paper dimensions: " << fixed << setprecision(6)
             << W << " X " << H << "\n";
        cout << "Dot is on " << (side == 'T' ? "TOP" : "BOTTOM")
             << " of page " << page << ". Position " << x << " X " << y << "\n";
        cout << "\n";                           // 每组数据后空一行
    }

    return 0;
}
```

## 总结

本题的关键在于准确模拟折叠过程中的物理变化：坐标镜像、纸面翻转以及层号更新。通过维护当前纸片的尺寸、点的坐标和朝向，以及当前点所在的层号和总层数，可以 $O(1)$ 处理每次折叠。层号更新的规律需要仔细推导，特别是区分折叠方向 `O` 和 `U` 对层序的影响。本题没有复杂的数据结构或算法，只需细心处理边界条件（点不在边缘和折线上保证了判断的严格性）和输出格式即可。
