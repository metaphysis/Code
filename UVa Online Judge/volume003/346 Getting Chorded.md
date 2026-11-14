[UVa 346 Getting Chorded](https://blog.csdn.net/metaphysis/article/details/161557172)

## 题目描述

标准 $88$ 键钢琴键盘上的音符名称从 `A` 开始（键盘上最低的音），然后依次为 `A#`（升 `A`）、`B`、`C`、`C#`、`D`、`D#`、`E`、``F、`F#`、`G`、`G#`。命名完前 $12$ 个音符后，模式重复，直到最后一个键被命名为 `C`。有些音符有其他常见的名称：`A#` 也可以称为 `Bb`（降 `B`），`C#` 可以称为 `Db`，`D#` 可以称为 `Eb`，`F#` 可以称为 `Gb`，`G#` 可以称为 `Ab`。

大多数音乐包含**和弦**，即同时演奏的一组音符。许多和弦有标准名称。例如，同时演奏音符 `C`、`E`、`G` 构成 `C` 大三和弦。键盘上音符之间的间隔区分了大三和弦与其他和弦：`C` 和 `E` 之间正好跳过 $3$ 个音符（`C#`、`D`、`D#`），`E` 和 `G` 之间跳过 $2$ 个音符（`F`、`F#`）。

小三和弦的间隔模式不同：`C` 小三和弦由 `C`、`D#`、`G` 组成，`C` 和 `D#` 之间跳过 $3$ 个音符（`C#`、`D`、`E`）实际上是 $3$ 个半音间隔。

### 音名与半音数

在十二平均律中，相邻半音为一个半音。音符之间的间隔用半音数表示：
- 大三和弦：根音到三音 $4$ 个半音，三音到五音 $3$ 个半音
- 小三和弦：根音到三音 $3$ 个半音，三音到五音 $4$ 个半音

### 输入格式

输入包含多行，每行包含三个音符名称。大小写不敏感，降号用字母 `b` 表示。音符之间可能有多个空格，行首和行尾也可能有空格。

### 输出格式

对于每行输入，输出一行，格式如样例所示。如果三个音符构成大三和弦或小三和弦，输出和弦名称；否则输出 `unrecognized`。

### 样例输入

```
C E G
C E F#
G C E
C Eb G
c# a f#
f g# C
```

### 样例输出

```
C E G is a C Major chord.
C E F# is unrecognized.
G C E is a C Major chord.
C Eb G is a C Minor chord.
c# a f# is a F# Minor chord.
f g# C is a F Minor chord.
```

---

## 题目分析

### 问题的本质

这是一个**和弦识别**问题。给定三个音符，需要判断它们是否构成大三和弦或小三和弦，并输出对应的和弦名称。

### 音名标准化

由于同一个音高可能有多个名称（如 `A#` = `Bb`），需要将所有音符名称标准化为一种表示形式，以便比较间隔。

### 半音间隔

将 $12$ 个半音映射到 $0 \sim 11$ 的整数：

| 音名 | 半音数 | 别名 |
|------|--------|------|
| `C` | $0$ | `B#` |
| `C#/Db` | 1 | |
| `D` | $2$ | |
| `D#/Eb` | 3 | |
| `E` | $4$ | `Fb` |
| `F` | $5$ | `E#` |
| `F#/Gb` | $6$ | |
| `G` | $7$ | |
| `G#/Ab` | $8$ | |
| A | $9$ | |
| `A#/Bb` | $10$ | |
| `B` | $11$ | `Cb` |

### 和弦判定

将三个音符转换为半音数后，排序并计算间隔：

- 如果间隔模式为 $(4,3,5)$（模 $12$），则是大三和弦
- 如果间隔模式为 $(3,4,5)$，则是小三和弦

另一种方法：枚举每个音符作为根音，检查后两个音符是否与根音相差 $4$ 和 $7$ 个半音（大三）或 $3$ 和 $7$ 个半音（小三）。

---

## 解题思路

### 步骤一：定义音名字典

```cpp
vector<set<string>> chordes = {
    {"A"}, {"A#", "Bb"}, {"B", "Cb"}, {"C", "B#"},
    {"C#", "Db"}, {"D"}, {"D#", "Eb"}, {"E", "Fb"},
    {"F", "E#"}, {"F#", "Gb"}, {"G"}, {"G#", "Ab"}
};
```

### 步骤二：别名映射

将降号和升号名称统一为升号形式（或统一为某种标准形式）：

```cpp
map<string, string> alternatives = {
    {"Ab", "G#"}, {"Bb", "A#"}, {"Cb", "B"}, {"Db", "C#"},
    {"Eb", "D#"}, {"Fb", "E"}, {"Gb", "F#"}, {"B#", "C"},
    {"E#", "F"}
};
```

### 步骤三：标准化输入

将输入转换为首字母大写，降号用小写 `b` 的形式。

### 步骤四：排序

为了便于枚举根音，先对三个音符按字母顺序排序（而不是按半音数）。

### 步骤五：枚举根音

将三个音符的每个作为可能的根音，检查另外两个音符是否与根音构成大三或小三和弦。

```cpp
for (int i = 0; i < 3; i++) {
    // 检查大三和弦：根音 +4 和 +7 半音
    if (chordes[j].count(notes[i]) && 
        chordes[(j + 4) % 12].count(notes[(i+1)%3]) && 
        chordes[(j + 7) % 12].count(notes[(i+2)%3])) {
        // 大三和弦
    }
    // 检查小三和弦：根音 +3 和 +7 半音
    else if (chordes[j].count(notes[i]) && 
             chordes[(j + 3) % 12].count(notes[(i+1)%3]) && 
             chordes[(j + 7) % 12].count(notes[(i+2)%3])) {
        // 小三和弦
    }
}
```

### 步骤六：输出和弦名称

根音名称需要标准化：如果根音是降号形式（如 `Eb`），则输出升号形式（`D#`）。

---
## 参考代码

```cpp
// Getting Chorded
// UVa ID: 346
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    // 12 个半音，每个半音对应的音名集合（包含等音）
    vector<set<string>> chordes = {
        {"A"}, {"A#", "Bb"}, {"B", "Cb"}, {"C", "B#"},
        {"C#", "Db"}, {"D"}, {"D#", "Eb"}, {"E", "Fb"},
        {"F", "E#"}, {"F#", "Gb"}, {"G"}, {"G#", "Ab"}
    };

    // 别名映射：将降号形式转换为升号形式
    map<string, string> alternatives = {
        {"Ab", "G#"}, {"Bb", "A#"}, {"Cb", "B"}, {"Db", "C#"},
        {"Eb", "D#"}, {"Fb", "E"}, {"Gb", "F#"}, {"B#", "C"},
        {"E#", "F"}
    };

    vector<string> notes(3);
    while (cin >> notes[0] >> notes[1] >> notes[2])
    {
        cout << notes[0] << " " << notes[1] << " " << notes[2] << " is ";
        
        // 标准化：首字母大写，其余保持不变（b 保持小写）
        notes[0].front() = toupper(notes[0].front());
        notes[1].front() = toupper(notes[1].front());
        notes[2].front() = toupper(notes[2].front());
        
        // 对音符排序（按字母序，便于枚举）
        if (notes[0].front() > notes[1].front()) swap(notes[0], notes[1]);
        if (notes[0].front() > notes[2].front()) swap(notes[0], notes[2]);
        if (notes[1].front() > notes[2].front()) swap(notes[1], notes[2]);
        
        bool recognized = false;
        // 枚举每个音符作为可能的根音
        for (int i = 0; i < notes.size(); i++)
        {
            for (int j = 0; j < chordes.size(); j++)
            {
                // 大三和弦：根音 +4 半音 和 根音 +7 半音
                if (chordes[j].count(notes[i]) && 
                    chordes[(j + 4) % 12].count(notes[(i + 1) % 3]) && 
                    chordes[(j + 7) % 12].count(notes[(i + 2) % 3]))
                {
                    recognized = true;
                    // 输出根音名称（如有别名则转换）
                    string root = notes[i];
                    if (root.back() == 'b' || root == "B#" || root == "E#")
                        root = alternatives[root];
                    cout << "a " << root << " Major chord.\n";
                    goto get_out;
                }
                // 小三和弦：根音 +3 半音 和 根音 +7 半音
                else if (chordes[j].count(notes[i]) && 
                         chordes[(j + 3) % 12].count(notes[(i + 1) % 3]) && 
                         chordes[(j + 7) % 12].count(notes[(i + 2) % 3]))
                {
                    recognized = true;
                    string root = notes[i];
                    if (root.back() == 'b' || root == "B#" || root == "E#")
                        root = alternatives[root];
                    cout << "a " << root << " Minor chord.\n";
                    goto get_out;
                }
            }
        }
   
        get_out:
        if (!recognized) 
            cout << "unrecognized.\n";
    }

    return 0;
}
```
