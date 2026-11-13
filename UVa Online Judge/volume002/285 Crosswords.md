[UVa 285 Crosswords](https://blog.csdn.net/metaphysis/article/details/161361105)

## 题目分析

本题要求判断给定的填字游戏（$\texttt{Crossword}$）答案是否正确。填字游戏在一个矩形网格中进行，单词可以横向或纵向放置，且交叉位置共享同一个字母。题目输入包含两部分：

1. **单词放置信息**：若干行，每行格式为 `word x y d`，表示单词 `word` 从坐标 `(x, y)` 开始，沿着方向 `d` 放置。方向 `d` 可以是：
   - `r`：向右（x 增加）
   - `l`：向左（x 减少）
   - `d`：向下（y 增加）
   - `u`：向上（y 减少）

   坐标系统原点在左上角，`(1, 1)` 为左上角。输入以一行单独的 `#` 表示单词放置信息的结束。

2. **答案信息**：在 `#` 之后，第一行是填字游戏的最小宽度（最右边的列坐标），第二行是最小高度（最下边的行坐标），第三行是从左到右、从上到下排列的所有字母，末尾以 `$` 符号作为结束标记。

题目保证输入的单词放置信息本身是“正确”的（不会出现冲突），我们需要根据这些单词的放置位置，计算出实际占据的网格宽度和高度，然后与答案中给出的宽度和高度进行比较，同时将网格中的字母按行优先顺序拼接成字符串，与答案中的字母序列进行比较。若两者均一致，则输出 `The solution is correct.`，否则输出 `The solution is incorrect.`。

## 解题思路

### 核心步骤

解题代码的整体思路非常清晰，可以分为以下几个步骤：

1. **解析单词放置信息，构建填字网格**
2. **读取答案信息**
3. **比较实际网格尺寸与答案给出的尺寸**
4. **比较实际网格中的字母序列与答案给出的字母序列**

### 详细分析

#### 第一步：解析单词放置信息

由于输入中单词的起始坐标 `(x, y)` 中 `x` 和 `y` 均为正整数，且单词长度小于 $10$，坐标范围小于 $100$，因此我们可以用一个二维字符数组 `grid` 来表示整个填字网格，大小设为 $150 \times 150$ 足矣。

对于每一行单词信息，我们需要：
- 解析出单词 `word`、起始横坐标 `x`、起始纵坐标 `y` 和方向 `d`
- 根据方向 `d` 确定每一步的偏移量 `(offsetx, offsety)`：
  - `r`：`(1, 0)`
  - `l`：`(-1, 0)`
  - `d`：`(0, 1)`
  - `u`：`(0, -1)`
- 从起始位置开始，将单词的每个字母依次填入 `grid` 的对应位置
- 同时记录整个网格的**最右边列坐标**和**最下边行坐标**，即实际宽度和高度

这里需要注意：坐标 `(x, y)` 中 `x` 表示列，`y` 表示行。题目中 `minimal width` 和`minimal height` 的定义分别是“最右边边缘坐标”和“最下边边缘坐标”，因此我们在记录时取所有单词起始坐标和结束坐标中的最大值即可。

#### 第二步：读取答案信息

在遇到 `#` 后，接着读入三行：
- 第一行：宽度 `width`
- 第二行：高度 `height`
- 第三行：以 `$` 结尾的字母序列，其中可能包含空格（如样例中的 `second la nvis e ft 1 e $`），需要去除空格后得到纯字母字符串

#### 第三步：比较尺寸

将第一步中计算得到的 `right_most`（实际宽度）和 `bottom_most`（实际高度）与答案中的 `width` 和 `height` 进行比较。若不一致，则直接判定答案错误。

#### 第四步：比较字母序列

若尺寸一致，则需要比较字母序列。按照“从左到右、从上到下”的顺序遍历整个网格（行优先），将 `grid` 中**非空格**的字符依次取出，组成一个字符串 `text`，然后与答案中处理得到的纯字母字符串 `answer` 进行比较。若相等则正确，否则错误。

这里有一个细节：网格中有些位置可能没有被任何单词覆盖，这些位置在初始化时被填充为空格，遍历时需要跳过。

### 复杂度分析

- 单词数量未知，但每个单词长度小于 $10$，坐标范围小于 $100$，因此网格规模有限。
- 构建网格的时间复杂度为 $O($单词总数 $\times$ 单词长度$)$，网格遍历的时间复杂度为 $O($宽度 $\times$ 高度$)$，均在可接受范围内。

## 代码实现

```cpp
// Crosswords
// UVa ID: 285
// Verdict: Accepted
// Submission Date: 2016-06-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char grid[150][150], solution[150][150];
int right_most, bottom_most;

// 处理一行单词放置信息，将单词填入 grid，并更新实际宽度和高度
void process(string line)
{
    string word, x, y, d;
    istringstream iss(line);
    iss >> word >> x >> y >> d;

    // 根据方向确定步长偏移量
    int offsetx, offsety;
    if (d == "l")
        offsetx = -1, offsety = 0;
    else if (d == "r")
        offsetx = 1, offsety = 0;
    else if (d == "u")
        offsetx = 0, offsety = -1;
    else if (d == "d")
        offsetx = 0, offsety = 1;

    // 将字符串转换为整数坐标，注意 x 是列，y 是行
    int i = stoi(y), j = stoi(x), lasti = i, lastj = j;
    for (int k = 0; k < word.length(); k++)
    {
        grid[i][j] = word[k];       // 填入字母
        lasti = i, lastj = j;       // 记录最后一个位置
        i += offsety, j += offsetx; // 移动
    }

    // 更新实际宽度（最右边列坐标）和实际高度（最下边行坐标）
    right_most = max(right_most, max(stoi(x), lastj));
    bottom_most = max(bottom_most, max(stoi(y), lasti));
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        // 初始化
        right_most = 0, bottom_most = 0;
        memset(grid, ' ', sizeof(grid));

        // 处理第一行单词信息
        process(line);

        // 继续处理直到遇到 '#'
        while (getline(cin, line), line[0] != '#')
            process(line);

        // 读入答案中的宽度和高度
        int width = (getline(cin, line), stoi(line));
        int height = (getline(cin, line), stoi(line));

        // 读入答案中的字母序列（包含空格，以 $ 结尾）
        memset(solution, ' ', sizeof(solution));
        getline(cin, line);

        // 从答案行中提取纯字母序列，忽略空格，遇到 $ 停止
        string answer;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '$')
                break;
            if (!isblank(line[i]))
                answer += line[i];
        }

        bool correct = true;

        // 比较尺寸是否一致
        if (width != right_most || height != bottom_most)
            correct = false;
        else
        {
            // 按行优先顺序从 grid 中提取所有非空格字符
            string text;
            for (int i = 1; i <= height; i++)
                for (int j = 1; j <= width; j++)
                    if (!isblank(grid[i][j]))
                        text += grid[i][j];

            // 比较字母序列
            correct = (answer == text);
        }

        // 输出结果
        if (correct)
            cout << "The solution is correct." << endl;
        else
            cout << "The solution is incorrect." << endl;
    }

    return 0;
}
```

## 总结

本题的核心在于正确解析输入、构建网格并提取字母序列进行比对。解题代码采用直接模拟的方法，先根据单词放置信息填充网格并记录边界，再与答案信息进行比较。由于数据规模较小，这种方法简单且高效。需要注意坐标系的定义以及 `$` 符号作为结束标记的处理。
