[UVa 163 City Directions](https://blog.csdn.net/metaphysis/article/details/158732555)

## 题目大意

在一个特殊的城市中，道路网络由三种类型的道路组成：
- **`Avenue`**：南北向的道路
- **`Street`**：东西向的道路
- **`Boulevard`**：对角线方向的道路（$45$ 度角）

城市中心是 `A0` 和 `S0` 的交汇处。整个城市范围是 $100 \times 100$ 的网格，每个象限 $50 \times 50$ 个街区。外围的快速路标记为 `Fifty`，主要和次要的对角线道路在标记为 `Twentyfive` 的道路处相交。

快速路（图中灰色标记的道路）是**高架路**，大部分路段可以轻松穿过，但在交汇处会有一个**环岛**，所有道路在此交汇。进入或离开快速路只能通过**左转**（对于对角线道路是**急左转**），且不能在快速路上停车。

位置由**最后一个经过的路口**（`Avenue` 和 `Street` 的编号）和**当前朝向**（$8$ 个方向之一）确定。方向指令必须符合特定的语法规则：
- $\texttt{TURN [HALF | SHARP] [LEFT | RIGHT]}$：转弯指令
- $\texttt{GO [STRAIGHT] n (1≤n≤99)}$：直行指令

如果指令不符合语法，或者会导致非法/不可能的转弯，则忽略该指令。

## 输入格式

每个场景包含：
1. 起始位置（如 $\texttt{A2W S1N E}$）和朝向
2. 若干行指令
3. 以 $\texttt{STOP}$ 结束
4. 文件以 $\texttt{END}$ 结束

## 输出格式

每个场景输出一行：最终位置和朝向，如果最终位置非法则输出 `Illegal stopping place`。

## 解题思路

本题是一个**模拟题**，需要仔细处理各种边界条件和规则。解题的核心在于：

1. **坐标系的建立**
2. **方向变化规则**
3. **快速路进入/离开规则**
4. **指令验证**

### 1. 坐标系设计

题目中道路编号以中心为原点，向西/向南为负，向东/向北为正。为了方便计算，我们可以将坐标系映射为 $0 \sim 100$ 的整数网格：

- `A0` → 坐标 $50$
- `A50E` → 坐标 $100$
- `A50W` → 坐标 $0$
- `S0` → 坐标 $50$
- `S50N` → 坐标 $100$
- `S50S` → 坐标 $0$

这样整个城市范围就是 $x \in [0, 100], y \in [0, 100]$ 的网格。

### 2. 方向表示

使用整数表示 $8$ 个方向：
- $0$: `N` (北)
- $1$: `E` (东)
- $2$: `S` (南)
- $3$: `W` (西)
- $4$: `NE (东北)
- $5$: `NW` (西北)
- $6$: `SE` (东南)
- $7$: `SW` (西南)

### 3. 方向变化表

对于每种当前方向，执行 $7$ 种指令（$6$ 种转弯 + 直行）后，新方向可以通过预先计算的表格 $\texttt{aheadAfterTurn}$ 获得。例如：
- 当前方向为 `N`($0$)，执行 `TURN LEFT` → 新方向为 `W`($3$)
- 当前方向为 `N`($0$)，执行 `TURN SHARP LEFT` → 新方向为 `NW`($5$)

### 4. 步长计算

每个方向对应的坐标增量：
- `N`: $(0, 1)$
- `E`: $(1, 0)$
- `S`: $(0, -1)$
- `W`: $(-1, 0)$
- `NE`: $(1, 1)$
- `NW`: $(-1, 1)$
- `SE`: $(1, -1)$
- `SW`: $(-1, -1)$

### 5. 快速路判断

快速路包括：
- **`Avenue` 快速路**：坐标为 $50$ 的倍数（$0, 50, 100$），且方向为 `N` 或 `S`
- **`Street` 快速路**：坐标为 $50$ 的倍数（$0, 50, 100$），且方向为 `E` 或 `W`
- **`Boulevard` 快速路**：满足 $x - y = 0$ 或 $x + y = 100$，且方向为 `NE/SW` 或 `NW/SE`

函数 $\texttt{isStayOnThroughways}$ 返回：
- $-1$：在 `Avenue/Street` 快速路上
- $-2$：在 `Boulevard` 快速路上
- $1$：不在快速路上

### 6. 转弯合法性验证

关键规则：
- 进入/离开快速路只能通过**左转**（对于 `Boulevard` 是**急左转**）
- $9$ 个特殊路口（坐标均为 $0, 50, 100$ 的组合）允许任何转弯
- 不能走出城市边界
- 不能朝着离开城市的方向行驶（如在北边界不能向北走）

### 7. 指令验证

指令必须符合语法：
- $\texttt{TURN}$ 指令：后面必须跟 $\texttt{HALF}$ 或 $\texttt{SHARP}$，然后跟 $\texttt{LEFT}$ 或 $\texttt{RIGHT}$
- $\texttt{GO}$ 指令：可选的 $\texttt{STRAIGHT}$ 后跟 $1 \sim 99$ 的数字

使用 $\texttt{validateCommand}$ 函数检查语法，$\texttt{validateMove}$ 函数检查移动的合法性。

### 8. 模拟过程

1. 读取起始位置，解析坐标和方向
2. 逐条读取指令，直到 $\texttt{STOP}$
3. 对每条指令进行语法验证和移动合法性验证
4. 如果验证通过，更新位置和方向
5. 遇到 $\texttt{STOP}$ 时输出最终位置

## 代码实现

```cpp
// City Directions
// UVa ID: 163
// Verdict: Accepted
// Submission Date: 2016-04-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string cmds[7] = {
    "_TURN_LEFT", "_TURN_RIGHT", "_TURN_HALF_LEFT", "_TURN_HALF_RIGHT",
    "_TURN_SHARP_LEFT", "_TURN_SHARP_RIGHT", "_GO"
};

int TURN_LEFT = 0, TURN_RIGHT = 1, TURN_HALF_LEFT = 2, TURN_HALF_RIGHT = 3,
    TURN_SHARP_LEFT = 4, TURN_SHARP_RIGHT = 5, GO = 6, NONE = 7;

string directions[8] = { "N", "E", "S", "W", "NE", "NW", "SE", "SW" };

int N = 0, E = 1, S = 2, W = 3, NE = 4, NW = 5, SE = 6, SW = 7;

int aheadAfterTurn[8][7] = {
    {W, E, NW, NE, SW, SE, N}, {N, S, NE, SE, NW, SW, E},
    {E, W, SE, SW, NE, NW, S}, {S, N, SW, NW, SE, NE, W},
    {NW, SE, N, E, W, S, NE}, {SW, NE, W, N, S, E, NW},
    {NE, SW, E, S, N, W, SE}, {SE, NW, S, W, E, N, SW}
};

int step[8][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
};

int command, intersections, avenue, street, ahead;
vector<string> texts;

void parseDirection(string line)
{
    string text;
    texts.clear();
    istringstream iss(line);
    while (iss >> text)
        texts.push_back(text);
}

int isStayOnThroughways(int x, int y, int heading)
{
    if ((x % 50 == 0) && (heading == N || heading == S))
        return -1;
    if ((y % 50 == 0) && (heading == E || heading == W))
        return -1;
    if ((x - y) == 0 && (heading == NE || heading == SW))
        return -2;
    if ((x + y) == 100 && (heading == NW || heading == SE))
        return -2;
    return 1;
}

void displayDestination()
{
    if (isStayOnThroughways(avenue, street, ahead) < 0)
        cout << "Illegal stopping place" << endl;
    else
    {
        cout << "A" << abs(avenue - 50) << (avenue >= 50 ? 'E' : 'W');
        cout << " S" << abs(street - 50) << (street >= 50 ? 'N' : 'S');
        cout << " " << directions[ahead] << endl;
    }
}

int getAvenueOrStreet(string text)
{
    int index = 0;
    if (isalpha(text.back()))
        index = stoi(text.substr(1, text.length() - 2));
    index = 50 + (text.back() == 'E' || text.back() == 'N' ? index : -index);
    return index;
}

void setStartPosition()
{
    avenue = getAvenueOrStreet(texts[0]);
    street = getAvenueOrStreet(texts[1]);
    ahead = find(directions, directions + 8, texts[2]) - directions;
}

bool validateCommand()
{
    if (texts.size() < 2 || texts.size() > 3)
        return false;

    string target;
    for (int i = 0; i < texts.size(); i++)
        target += "_" + texts.at(i);

    if (texts.front() == "TURN")
    {
        command = find(cmds, cmds + 7, target) - cmds;
        intersections = 1;

        return command < GO;
    }
    else if (texts.front() == "GO")
    {
        if (texts.size() == 3 && texts[1] != "STRAIGHT")
            return false;

        if (texts.back().length() > 2 || !isdigit(texts.back().front()))
            return false;

        if (texts.back().length() == 2 && !isdigit(texts.back().back()))
            return false;

        command = GO;
        intersections = stoi(texts.back());

        return 1 <= intersections && intersections <= 99;
    }

    return false;
}

bool validateDirection(int x, int y, int heading)
{
    if (x == 100 && y == 100)
        return (heading == SW || heading == W || heading == S);
    if (x == 100 && y == 50)
        return (heading == NW || heading == SW || heading == N || heading == S || heading == W);
    if (x == 100 && y == 0)
        return (heading == NW || heading == N || heading == W);
    if (x == 50 && y == 100)
        return (heading == SE || heading == SW || heading == E || heading == S || heading == W);
    if (x == 50 && y == 0)
        return (heading == NE || heading == NW || heading == E || heading == N || heading == W);
    if (x == 0 && y == 100)
        return (heading == SE || heading == E || heading == S);
    if (x == 0 && y == 50)
        return (heading == NE && heading == SE || heading == N || heading == E || heading == S);
    if (x == 0 && y == 0)
        return (heading == NE || heading == N || heading == E);

    if ((x - y == -50 || x - y == 0 || x - y == 50) && (heading == NE || heading == SW))
        return true;
    if ((x + y == 50 || x + y == 100 || x + y == 150) && (heading == NW || heading == SE))
        return true;

    if (y == 100 && (heading == N || heading == NE || heading == NW))
        return false;
    if (y == 0 && (heading == SE || heading == S || heading == SW))
        return false;
    if (x == 0 && (heading == SW || heading == W || heading == NW))
        return false;
    if (x == 100 && (heading == NE || heading == E || heading == SE))
        return false;

    if (heading == N || heading == E || heading == S || heading == W)
        return true;

    return false;
}

bool validateMove()
{
    int x = avenue + step[ahead][0] * intersections;
    int y = street + step[ahead][1] * intersections;
    int heading = aheadAfterTurn[ahead][command];

    bool validMove = false;

    if (command == GO)
    {
        validMove = true;

        if (x < 0 || x > 100 || y < 0 || y > 100)
            validMove = false;

        return validMove;
    }

    // make sure the direction is valid
    if (validateDirection(x, y, heading) == false)
        return false;

    int before = isStayOnThroughways(avenue, street, ahead);
    int after = isStayOnThroughways(x, y, heading);

    // check enter or exiting throughways or boulevards
    if (before < 0 && after > 0)
    {
        if (before == -1)
            validMove = command == TURN_LEFT;
        else
            validMove = command == TURN_SHARP_LEFT;
    }
    else if (before > 0 && after < 0)
    {
        if (after == -1)
            validMove = command == TURN_LEFT;
        else
            validMove = command == TURN_SHARP_LEFT;
    }
    else
        validMove = true;

    // At nine intersections, any turn is valid
    if ((x == 0 || x == 50 || x == 100) && (y == 0 || y == 50 || y == 100))
        validMove = true;

    return validMove;
}

int main(int argc, char *argv[])
{
    string line;
    bool startPositionReaded = false;

    while (getline(cin, line), line != "END")
    {
        parseDirection(line);

        if (line == "STOP")
        {
            displayDestination();
            startPositionReaded = false;
            continue;
        }

        if (startPositionReaded == false)
        {
            setStartPosition();
            startPositionReaded = true;
            continue;
        }

        if (validateCommand() && validateMove())
        {
            avenue += step[ahead][0] * intersections;
            street += step[ahead][1] * intersections;
            ahead = aheadAfterTurn[ahead][command];
        }
    }

    return 0;
}
```
