[UVA 243 Theseus and the Minotaur (II)](https://blog.csdn.net/metaphysis/article/details/161246648)

## 题目分析

本题是一道基于图论的模拟题，讲述了忒修斯（$\texttt{Theseus}$）与弥诺陶洛斯（$\texttt{Minotaur}$）在迷宫中的追逐故事。迷宫由若干洞穴（$\texttt{cavern}$）和连接洞穴的通道（$\texttt{passage}$）组成，每个洞穴用一个大写字母表示。

### 关键规则

**忒修斯的移动规则**：
- 忒修斯是左撇子，因此他进入洞穴后会**向右转**（即逆时针方向），沿着洞穴边缘摸索，直到找到一个未标记的出口。
- 如果找到的出口未标记，他会标记该出口并进入。
- 如果找到的出口已标记，他会忽略并继续寻找下一个。
- 如果忒修斯进入一个**弥诺陶洛斯曾经进入过的洞穴**，他会点燃一支蜡烛并留在该洞穴，然后像往常一样右转，但会**走弥诺陶洛斯离开时使用的出口**。

**弥诺陶洛斯的移动规则**：
- 弥诺陶洛斯进入洞穴后会**向左转**（即顺时针方向），沿着洞穴边缘移动，直到找到一个未被自己标记的出口。
- 找到后他会标记该出口并进入。
- 如果弥诺陶洛斯即将进入的洞穴**有蜡烛在燃烧**，他会转身逃回刚刚使用的通道，回到上一个洞穴继续他的“回合”。

**相遇判定**：
- 如果两者在**同一洞穴**相遇，弥诺陶洛斯会被杀死（因为蜡烛的光芒使其失明）。
- 如果两者在**通道中相遇**，忒修斯会被杀死（通道狭窄，无法战斗或点蜡烛）。

## 解题思路

### 数据结构设计

1. **洞穴存储**：使用 `vector<int> caverns[26]` 存储每个洞穴的邻接洞穴列表，输入给出的顺序是**逆时针**顺序。
2. **标记记录**：使用 `set<string> markedTheseus` 和 `set<string> markedMinotaur` 记录双方已标记的通道。通道用 `"from#to"` 的字符串表示，注意通道是**双向**的，但标记是方向相关的。
3. **蜡烛记录**：使用 `bool lighted[26]` 记录洞穴是否有蜡烛。
4. **弥诺陶洛斯足迹**：使用 `int entered[26]` 记录弥诺陶洛斯从某个洞穴离开时进入的下一个洞穴，初始化为 `-1`。

### 核心函数

#### 1. 读取输入（`buildGraph`）

- 逐行读取，直到遇到以 `'@'` 开头的行。
- 每行格式为 `A:BCD`，表示洞穴 `A` 可到达 `B`、`C`、`D`（按逆时针顺序）。
- `'@'` 行后跟两对字母，如 `@ACFH`：
  - 第一对 `AC` 表示忒修斯起点在通道 `A-C` 之间，**朝向 `C`**（即从 `A` 向 `C` 移动）。
  - 第二对 `FH` 表示弥诺陶洛斯起点在通道 `F-H` 之间，**朝向 `H`**。

#### 2. 选择下一个出口（`pickNextPassage`）

```cpp
int pickNextPassage(set<string> &marker, bool clockwise, int from, int to)
```

参数说明：
- `marker`：当前角色的标记集合。
- `clockwise`：`true` 表示顺时针（弥诺陶洛斯），`false` 表示逆时针（忒修斯）。
- `from`：当前洞穴 `to` 中，角色是从哪个洞穴来的。
- `to`：当前所在的洞穴。

**算法步骤**：
1. 找到 `from` 在 `caverns[to]` 中的索引位置。
2. 根据 `clockwise` 决定方向：顺时针索引减 `1`，逆时针索引加 `1`（注意取模处理）。
3. 检查该方向对应的出口是否已被标记。若未标记，则标记并返回该出口；若已标记，继续旋转寻找下一个。
4. 如果所有出口都被标记，返回 `-1`（表示卡住）。

#### 3. 模拟追逐（`startPursuit`）

模拟的核心是一个无限循环，每轮同时处理忒修斯和弥诺陶洛斯的一步移动。

**第一步：检查相遇**

```cpp
if (theseusTo == minotaurTo) {
    // 同一洞穴，弥诺陶洛斯被杀死
} else if (theseusFrom == minotaurTo && theseusTo == minotaurFrom) {
    // 通道中迎面相遇，忒修斯被杀死
}
```

注意：通道相遇的条件是忒修斯和弥诺陶洛斯正好在同一通道中相向而行。

**第二步：忒修斯移动**

```cpp
if (entered[theseusTo] >= 0) {
    // 这个洞穴弥诺陶洛斯来过，点蜡烛并跟随弥诺陶洛斯的出口
    lighted[theseusTo] = true;
    theseusFrom = theseusTo;
    theseusTo = entered[theseusTo];
} else {
    // 正常选择出口
    int passage = pickNextPassage(markedTheseus, false, theseusFrom, theseusTo);
    if (passage >= 0) {
        theseusFrom = theseusTo;
        theseusTo = passage;
    }
    // 如果 passage == -1，忒修斯卡住（理论上不会发生）
}
```

**第三步：弥诺陶洛斯移动**

```cpp
int passage = pickNextPassage(markedMinotaur, true, minotaurFrom, minotaurTo);
if (passage >= 0) {
    entered[minotaurTo] = passage;  // 记录足迹
    
    if (lighted[passage]) {
        // 目标洞穴有蜡烛，检查是否在通道相遇
        if (theseusFrom == passage && theseusTo == minotaurTo) {
            // 通道相遇，忒修斯死
        }
        // 弥诺陶洛斯逃回原洞穴
        minotaurFrom = passage;
        // minotaurTo 不变
    } else {
        // 正常进入目标洞穴
        minotaurFrom = minotaurTo;
        minotaurTo = passage;
    }
}
```

### 模拟终止条件

程序会在以下情况终止并输出结果：
1. 两者进入同一洞穴 → 输出 `"The Minotaur is slain in X"`
2. 两者在通道中迎面相遇 → 输出 `"Theseus is killed between X and Y"`

## 注意事项

1. **方向理解**：
   - 忒修斯**右转** = 逆时针方向 = 在邻接列表中向后移动（索引 `+1`）。
   - 弥诺陶洛斯**左转** = 顺时针方向 = 在邻接列表中向前移动（索引 `-1`）。

2. **通道标记**：通道是双向的，但标记是方向相关的。忒修斯标记 `(C, D)` 与弥诺陶洛斯标记 `(D, C)` 是不同标记。

3. **蜡烛机制**：蜡烛点燃后持续存在，弥诺陶洛斯检测到蜡烛后**不会进入**该洞穴，而是**逃回原洞穴**。

4. **足迹记录**：`entered[x]` 记录弥诺陶洛斯从洞穴 `x` 离开时进入的下一个洞穴。忒修斯进入有足迹的洞穴时，会**直接走**那个出口。

## 代码实现

```cpp
// Theseus and the Minotaur (II)
// UVa ID: 243
// Verdict: Accepted
// Submission Date: 2016-05-31
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector < vector < int > > caverns;      // 存储每个洞穴的邻接洞穴列表（逆时针顺序）
int theseusFrom, theseusTo;             // 忒修斯当前位置（来自哪个洞穴，在哪个洞穴）
int minotaurFrom, minotaurTo;           // 弥诺陶洛斯当前位置
int lighted[26];                        // 洞穴是否有蜡烛
int entered[26];                        // 弥诺陶洛斯从该洞穴进入的下一洞穴（足迹）
set < string > markedTheseus;           // 忒修斯标记的通道（格式："from#to"）
set < string > markedMinotaur;          // 弥诺陶洛斯标记的通道

// 读取迷宫数据，成功返回 true，遇到 '#' 终止返回 false
bool buildGraph()
{
    // 清空邻接表
    for (int i = 0; i < 26; i++)
        caverns[i].clear();

    string line;
    while (getline(cin, line), line.front() != '@')
    {
        if (line.front() == '#')
            return false;

        // 解析洞穴描述，格式：A:BCD
        for (int i = 2; i < line.length(); i++)
            caverns[line.front() - 'A'].push_back(line[i] - 'A');
    }

    // 解析起始位置，格式：@ACFH
    theseusFrom = line[1] - 'A', theseusTo = line[2] - 'A';
    minotaurFrom = line[3] - 'A', minotaurTo = line[4] - 'A';

    return true;
}

// 为当前角色选择下一个出口
// marker: 标记集合，clockwise: true=顺时针（弥诺陶洛斯），false=逆时针（忒修斯）
// from: 进入当前洞穴时所经过的洞穴，to: 当前所在洞穴
int pickNextPassage(set < string > &marker, bool clockwise, int from, int to)
{
    // 找到 from 在 caverns[to] 中的位置索引
    int index = find(caverns[to].begin(), caverns[to].end(), from) - caverns[to].begin();
    int passage = -1;

    // 遍历所有出口，直到找到一个未标记的
    for (int counter = 0; counter < caverns[to].size(); counter++)
    {
        // 顺时针向左（索引减1），逆时针向右（索引加1）
        index += (clockwise ? -1 : 1);
        index += (index < 0 ? caverns[to].size() : 0);
        index %= caverns[to].size();

        passage = caverns[to][index];
        string key = to_string(to) + "#" + to_string(passage);

        if (marker.find(key) != marker.end())
            continue;   // 已标记，继续寻找
        else
        {
            marker.insert(key); // 标记该通道
            break;
        }
    }

    return passage; // 若所有出口都已标记，返回 -1
}

// 模拟追逐过程
void startPursuit()
{
    markedTheseus.clear();
    markedMinotaur.clear();

    fill(lighted, lighted + 26, false);
    fill(entered, entered + 26, -1);

    while (true)
    {
        // 检查相遇情况
        if (theseusTo == minotaurTo)
        {
            cout << "The Minotaur is slain in " << (char)('A' + theseusTo) << "\n";
            break;
        }
        else if (theseusFrom == minotaurTo && theseusTo == minotaurFrom)
        {
            cout << "Theseus is killed between " << (char)('A' + theseusFrom);
            cout << " and " << (char)('A' + theseusTo) << "\n";
            break;
        }

        // 忒修斯的移动
        if (entered[theseusTo] >= 0)
        {
            // 当前洞穴弥诺陶洛斯来过，点蜡烛并跟随其足迹
            lighted[theseusTo] = true;
            theseusFrom = theseusTo;
            theseusTo = entered[theseusTo];
        }
        else
        {
            int passage = pickNextPassage(markedTheseus, false, theseusFrom, theseusTo);
            if (passage >= 0)
                theseusFrom = theseusTo, theseusTo = passage;
            else
                // 理论上不会发生：所有出口都被标记，忒修斯卡住
                theseusFrom = theseusTo, theseusTo = theseusTo;
        }

        // 弥诺陶洛斯的移动
        int passage = pickNextPassage(markedMinotaur, true, minotaurFrom, minotaurTo);
        if (passage >= 0)
        {
            // 记录足迹
            entered[minotaurTo] = passage;

            // 检查目标洞穴是否有蜡烛
            if (lighted[passage])
            {
                // 检查是否在通道中与忒修斯相遇
                if (theseusFrom == passage && theseusTo == minotaurTo)
                {
                    cout << "Theseus is killed between " << (char)('A' + theseusFrom);
                    cout << " and " << (char)('A' + theseusTo) << "\n";
                    break;
                }

                // 目标洞穴有蜡烛，弥诺陶洛斯逃回原洞穴
                minotaurFrom = passage;     // 注意：minotaurTo 保持不变
            }
            else
            {
                // 正常进入目标洞穴
                minotaurFrom = minotaurTo;
                minotaurTo = passage;
            }
        }
        else
            // 所有出口都被标记，弥诺陶洛斯卡住（理论上不会发生）
            minotaurFrom = minotaurTo, minotaurTo = minotaurTo;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    // 初始化邻接表
    for (int i = 0; i < 26; i++)
    {
        vector < int > cavern;
        caverns.push_back(cavern);
    }

    // 循环处理每个迷宫，直到遇到 '#'
    while (buildGraph())
        startPursuit();

    return 0;
}
```

## 总结

本题的核心难点在于：
1. 正确理解“左转/右转”与“顺时针/逆时针”的对应关系。
2. 处理蜡烛机制和足迹跟随机制。
3. 通道相遇条件的正确判定。

通过合理的状态表示和按步骤模拟，可以清晰地解决这一问题。
