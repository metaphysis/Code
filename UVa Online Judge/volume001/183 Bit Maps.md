[UVa 183 Bit Maps](https://blog.csdn.net/metaphysis/article/details/160890704)

## 题目分析

本题涉及两种位图的表示方式：

- **`B` 格式**：直接使用二维数组存储，按行优先顺序给出 `0` 和 `1` 字符序列。
- **`D` 格式**：基于四分法的递归分解表示。如果当前区域全为 `1`，输出 `1`；全为 `0`，输出 `0`；否则输出 `D`，然后按左上、右上、左下、右下的顺序递归处理四个子区域。

需要实现两种格式之间的相互转换。行列数不超过 $200$，且当行数或列数为奇数时，分割时左上方或上方会多出一行或一列。

## 解题思路

### `B` → `D` 转换（位图转四分码）

1. 将输入的 `B` 格式字符序列填充到二维矩阵中。
2. 编写递归函数 `getCode(top, left, bottom, right)`：
   - 如果当前区域所有格子相同，直接返回 `"0"` 或 `"1"`。
   - 否则返回 `"D"` 加上四个子区域的编码。
3. 注意处理边界情况：当区域只有一行或一列时，分割成两个子区域（水平或垂直切分）。
4. 输出时每行最多 $50$ 个字符。

### `D` → `B` 转换（四分码转位图）

1. 输入 `D` 格式的编码字符串，存储在 `buffer` 中。
2. 编写递归函数 `getBit(index, top, left, bottom, right)`：
   - 使用引用传递的 `index` 表示当前读取位置。
   - 如果当前位置字符为 `0` 或 `1`，则将整个区域填充为该字符。
   - 如果为 `D`，则 `index` 自增后递归处理各子区域（分割规则同 B → D）。
3. 递归完成后，按行优先顺序输出矩阵中的字符，每行最多 $50$ 个字符。

### 关键细节

- 行列均为 $1$ 时直接输出对应字符。
- 分割中点计算：`midRow = (top + bottom) / 2`，`midCol = (left + right) / 2`。由于整数除法，奇数维度时会自动使左/上部分多一列/行。
- 输出格式要求：`B` 或 `D` 后跟宽为 $4$ 的右对齐行列数。

## 代码实现

```cpp
// Bit Maps
// UVa ID: 183
// Verdict: Accepted
// Submission Date: 2016-03-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string category, buffer;
int row, column;
char matrix[210][210];

// 去除字符串首尾的空白字符
string trim(string line) {
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);
        else
            break;

    while (line.length() > 0 && isblank(line.front()))
        line.erase(line.begin());

    return line;
}

// B → D：递归获取四分码
string getCode(int top, int left, int bottom, int right) {
    // 只有一行的情况：检查该行是否全相同
    if (top == bottom)
    {
        bool allSame = true;
        for (int i = left; i < right; i++)
            if (matrix[top][i] != matrix[top][i + 1])
            {
                allSame = false;
                break;
            }

        if (allSame)
            return matrix[top][left] == '1' ? "1" : "0";
    }
    // 只有一列的情况：检查该列是否全相同
    else if (left == right)
    {
        bool allSame = true;
        for (int i = top; i < bottom; i++)
            if (matrix[i][left] != matrix[i + 1][left])
            {
                allSame = false;
                break;
            }

        if (allSame)
            return matrix[top][left] == '1' ? "1" : "0";
    }

    // 计算分割中点
    int middleRow = (top + bottom) / 2;
    int middleColumn = (left + right) / 2;

    vector<string> codes;
    if (left != right && top != bottom)
    {
        // 四个子区域：左上、右上、左下、右下
        codes.push_back(getCode(top, left, middleRow, middleColumn));
        codes.push_back(getCode(top, middleColumn + 1, middleRow, right));
        codes.push_back(getCode(middleRow + 1, left, bottom, middleColumn));
        codes.push_back(getCode(middleRow + 1, middleColumn + 1, bottom, right));
    }
    else if (left == right)
    {
        // 只有一列时，分为上下两个子区域
        codes.push_back(getCode(top, left, middleRow, middleColumn));
        codes.push_back(getCode(middleRow + 1, left, bottom, middleColumn));
    }
    else if (top == bottom)
    {
        // 只有一行时，分为左右两个子区域
        codes.push_back(getCode(top, left, middleRow, middleColumn));
        codes.push_back(getCode(top, middleColumn + 1, middleRow, right));
    }

    // 合并子区域的编码
    string bitCode;
    bool allOne = true, allZero = true;
    for (int i = 0; i < codes.size(); i++)
    {
        if (codes[i].front() == '1')
        {
            allZero = false;
            bitCode += '1';
        }
        else if (codes[i].front() == '0')
        {
            allOne = false;
            bitCode += '0';
        }
        else
        {
            allOne = false;
            allZero = false;
            bitCode += codes[i];
        }
    }

    // 如果所有子区域都是 1，返回 "1"；都是 0，返回 "0"；否则返回 "D" + 子编码
    if (allOne)
        return "1";
    if (allZero)
        return "0";
    return "D" + bitCode;
}

// B → D：主处理函数
void bitToCode() {
    // 将输入字符串填充到矩阵中
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            matrix[i][j] = buffer[i * column + j];

    // 输出 D 格式头
    cout << "D" << right << setw(4)
         << row << right << setw(4) << column << "\n";

    string code = getCode(0, 0, row - 1, column - 1);

    // 每行最多 50 个字符
    while (code.length() > 50)
    {
        cout << code.substr(0, 50) << endl;
        code = code.substr(50);
    }
    if (code.length() > 0)
        cout << code << endl;
}

// D → B：递归填充矩阵，index 为当前读取位置（引用传递）
void getBit(int &index, int top, int left, int bottom, int right) {
    if (buffer[index] != 'D')
    {
        // 当前区域全部填充为相同字符
        for (int i = top; i <= bottom; i++)
            for (int j = left; j <= right; j++)
                matrix[i][j] = buffer[index];
    }
    else
    {
        int middleRow = (top + bottom) / 2;
        int middleColumn = (left + right) / 2;

        if (left != right && top != bottom)
        {
            // 四个子区域：左上、右上、左下、右下
            getBit(++index, top, left, middleRow, middleColumn);
            getBit(++index, top, middleColumn + 1, middleRow, right);
            getBit(++index, middleRow + 1, left, bottom, middleColumn);
            getBit(++index, middleRow + 1, middleColumn + 1, bottom, right);
        }
        else if (left == right)
        {
            // 只有一列时，分为上下两个子区域
            getBit(++index, top, left, middleRow, middleColumn);
            getBit(++index, middleRow + 1, left, bottom, middleColumn);
        }
        else if (top == bottom)
        {
            // 只有一行时，分为左右两个子区域
            getBit(++index, top, left, middleRow, middleColumn);
            getBit(++index, top, middleColumn + 1, middleRow, right);
        }
    }
}

// D → B：主处理函数
void codeToBit() {
    int index = 0;
    getBit(index, 0, 0, row - 1, column - 1);

    // 输出 B 格式头
    cout << "B" << right << setw(4)
         << row << right << setw(4) << column << "\n";

    string bit;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            bit += matrix[i][j];

    // 每行最多 50 个字符
    while (bit.length() > 50)
    {
        cout << bit.substr(0, 50) << endl;
        bit = bit.substr(50);
    }

    if (bit.length() > 0)
        cout << bit << endl;
}

// 根据输入格式类型选择转换方向
void process() {
    if (category == "B")
        bitToCode();
    else
        codeToBit();
}

// 解析格式、行数、列数
void read(string line) {
    istringstream iss(line);
    iss >> category >> row >> column;
}

int main() {
    string line;
    bool categorySetted = false;

    while (getline(cin, line))
    {
        line = trim(line);

        if (line.find(' ') != line.npos)
        {
            if (categorySetted == false)
            {
                categorySetted = true;
                read(line);
            }
            else
            {
                process();
                buffer.clear();
                read(line);
            }
        }
        else if (line != "#")
        {
            buffer += trim(line);
        }
        else if (line == "#")
        {
            process();
            break;
        }
    }

    return 0;
}
```
