[UVa 176 City Navigation](https://blog.csdn.net/metaphysis/article/details/160860241)

## 题目分析

本题描述了一种特殊的城市布局：街道（$\texttt{Street}$）和大道（$\texttt{Avenue}$）分别呈东西向和南北向，构成网格状结构。每条道路上的门牌号按照特定规律排列：

- 大道编号从西向东递增，街道编号从北向南递增
- 每个街区（`block`）两侧各有 $50$ 个 `driveway`，一侧编号为 $00, 02, \dots, 98$，另一侧为 $01, 03, \dots, 99$
- 当沿门牌号增加方向行驶时，奇数号在右侧
- 部分路段可能缺失（不连续），形成死胡同

题目要求：给定若干对地址（表示 `driveway` 的位置），计算两点间的最短合法路径长度，距离定义为经过的 `driveway` 数量（不包括起点和终点）。

合法驾驶规则：
- 靠右行驶
- 只能在交叉口穿越车道
- 进入或离开 `driveway` 时必须右转
- 除非在死胡同尽头，否则禁止 $\texttt{U}$ 形转弯

## 解题思路

### 1. 地址编码与状态表示

每个地址由三部分唯一标识：道路类型（`A` 或 `S`）、道路编号（$00$ 到 $49$）、门牌号（$0000$ 到 $4899$）。可以使用一个整数进行编码：

$$id = (code - \texttt{A}) \times 1000000 + index \times 10000 + number $$

### 2. 缺失路段处理

输入中每个缺失路段给出道路标识和一段连续的门牌号范围（包含边界）。需要注意：缺失的是整个 `section` 边界上的道路段，因此如果 $1612$ 不可通行，那么 $1613$ 也不可通行。处理时将范围内的所有门牌号对应的 `driveway` 标记为不可用。

### 3. 图模型抽象

将每个 `driveway` 视为图中的一个节点。从一个节点移动到相邻节点的规则取决于：

- 当前所在道路的类型（`A` 或 `S`）
- 当前门牌号的奇偶性（决定行驶方向）
- 当前是否处于道路端点（门牌号为 $00$、$99$ 等）

### 4. $\texttt{BFS}$ 搜索

由于边权均为 $1$，使用 $\texttt{BFS}$ 可以求出最短路径。从起点开始，每一步根据当前位置和方向生成后继节点，跳过被标记为缺失的节点。

### 5. 关键移动规则

以大道（$\texttt{Avenue}$）为例：

- **北向行驶**（门牌号为偶数，即左侧 `driveway`）：
  - 普通情况：向前移动到同一条大道的下一个 `driveway`（门牌号 $-2$）
  - 若该位置缺失，则只能进入当前街区对应的街道（右转）
  - 在端点（门牌号 $00$）时，可考虑右转、直行、左转三种选择

- **南向行驶**（门牌号为奇数，即右侧 `driveway`）：
  - 对称处理，门牌号 $+2$ 向前移动

街道（$\texttt{Street}$）的移动规则类似，只是方向换为东西向。

### 6. $\texttt{U}$ 形转弯处理

只有在死胡同末端（所有三个方向都缺失）时才允许 $\texttt{U}$ 形转弯，即掉头沿原路返回。

## 代码实现

```cpp
// City Navigation
// UVa ID: 176
// Verdict: Accepted
// Submission Date: 2016-02-26
// UVa Run Time: 0.338s

#include <bits/stdc++.h>

using namespace std;

// 存储一个 driveway 的结构体
struct house {
    char code;      // 'A' 或 'S'
    int index;      // 道路编号 00~49
    int number;     // 门牌号 0000~4899
    int step;       // BFS 步数
};

set<int> missing;     // 缺失的 driveway 集合
set<int> discovered;  // BFS 已访问集合
house from, to;       // 起点和终点

// 将 driveway 编码为唯一整数
int getHouseId(house h) {
    return (h.code - 'A') * 1000000 + h.index * 10000 + h.number;
}

// 判断 driveway 是否缺失
bool isMissing(house h) {
    return missing.count(getHouseId(h)) > 0;
}

// 判断是否已访问
bool isVisited(house h) {
    return discovered.count(getHouseId(h)) > 0;
}

// 创建 driveway 对象
house makeHouse(char code, int index, int number, int step) {
    return (house){code, index, number, step};
}

// BFS 搜索最短路径
void bfs() {
    queue<house> next;
    next.push(from);

    discovered.clear();
    discovered.insert(getHouseId(from));

    while (next.empty() == false) {
        house v = next.front();
        next.pop();

        // 到达终点，输出步数（减去起点和终点）
        if (v.number == to.number && v.index == to.index && v.code == to.code) {
            cout << (v.step - 2) << "\n";
            break;
        }

        // 当前在大道上（南北向）
        if (v.code == 'A') {
            int sNumber = v.number / 100;      // 对应的街道编号
            int houseNumber = v.number % 100;  // 门牌号后两位

            // 北向行驶（偶数门牌号，位于左侧）
            if (houseNumber % 2 == 0) {
                if (houseNumber == 0) {  // 到达北端点
                    bool nextFound = false;
                    vector<house> temp;

                    // 右转进入街道（东向）
                    if (v.index > 0)
                        temp.push_back(makeHouse('S', sNumber, (v.index - 1) * 100 + 98, v.step + 1));

                    // 直行继续向北（上一条街道）
                    if (sNumber > 0)
                        temp.push_back(makeHouse('A', v.index, (sNumber - 1) * 100 + 98, v.step + 1));

                    // 左转进入街道（西向）
                    if (v.index < 49)
                        temp.push_back(makeHouse('S', sNumber, v.index * 100 + 1, v.step + 1));

                    for (int i = 0; i < temp.size(); i++) {
                        if (isMissing(temp[i]) == false) {
                            if (isVisited(temp[i]) == false) {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                    }

                    // 所有方向都缺失 -> U 形转弯
                    if (nextFound == false) {
                        house tempHouse = makeHouse('A', v.index, v.number + 1, v.step + 1);
                        if (isVisited(tempHouse) == false) {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                } else {  // 非端点情况
                    house temp = makeHouse('A', v.index, v.number - 2, v.step + 1);
                    if (isMissing(temp))  // 前方缺失，只能右转进入街道
                        temp = makeHouse('A', v.index, v.number + 1, v.step + 1);

                    if (isVisited(temp) == false) {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }

            // 南向行驶（奇数门牌号，位于右侧）对称处理
            if (houseNumber % 2 == 1) {
                if (houseNumber == 99) {  // 到达南端点
                    bool nextFound = false;
                    vector<house> temp;

                    // 右转进入街道（西向）
                    if (v.index < 49)
                        temp.push_back(makeHouse('S', sNumber + 1, v.index * 100 + 1, v.step + 1));

                    // 直行继续向南（下一条街道）
                    if (sNumber < 48)
                        temp.push_back(makeHouse('A', v.index, (sNumber + 1) * 100 + 1, v.step + 1));

                    // 左转进入街道（东向）
                    if (v.index > 0)
                        temp.push_back(makeHouse('S', sNumber + 1, (v.index - 1) * 100 + 98, v.step + 1));

                    for (int i = 0; i < temp.size(); i++) {
                        if (isMissing(temp[i]) == false) {
                            if (isVisited(temp[i]) == false) {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                    }

                    // U 形转弯
                    if (nextFound == false) {
                        house tempHouse = makeHouse('A', v.index, v.number - 1, v.step + 1);
                        if (isVisited(tempHouse) == false) {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                } else {
                    house temp = makeHouse('A', v.index, v.number + 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('A', v.index, v.number - 1, v.step + 1);

                    if (isVisited(temp) == false) {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }
        }

        // 当前在街道上（东西向）处理逻辑类似
        if (v.code == 'S') {
            int aNumber = v.number / 100;      // 对应的大道编号
            int houseNumber = v.number % 100;

            // 东向行驶（偶数门牌号）
            if (houseNumber % 2 == 0) {
                if (houseNumber == 0) {  // 东端点
                    bool nextFound = false;
                    vector<house> temp;

                    // 右转进入大道（南向）
                    if (v.index < 49)
                        temp.push_back(makeHouse('A', aNumber, v.index * 100 + 1, v.step + 1));

                    // 直行继续向东（上一条大道）
                    if (aNumber > 0)
                        temp.push_back(makeHouse('S', v.index, (aNumber - 1) * 100 + 98, v.step + 1));

                    // 左转进入大道（北向）
                    if (v.index > 0)
                        temp.push_back(makeHouse('A', aNumber, (v.index - 1) * 100 + 98, v.step + 1));

                    for (int i = 0; i < temp.size(); i++) {
                        if (isMissing(temp[i]) == false) {
                            if (isVisited(temp[i]) == false) {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                    }

                    // U 形转弯
                    if (nextFound == false) {
                        house tempHouse = makeHouse('S', v.index, v.number + 1, v.step + 1);
                        if (isVisited(tempHouse) == false) {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                } else {
                    house temp = makeHouse('S', v.index, v.number - 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('S', v.index, v.number + 1, v.step + 1);

                    if (isVisited(temp) == false) {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }

            // 西向行驶（奇数门牌号）
            if (houseNumber % 2 == 1) {
                if (houseNumber == 99) {  // 西端点
                    bool nextFound = false;
                    vector<house> temp;

                    // 右转进入大道（北向）
                    if (v.index > 0)
                        temp.push_back(makeHouse('A', aNumber + 1, (v.index - 1) * 100 + 98, v.step + 1));

                    // 直行继续向西（下一条大道）
                    if (aNumber < 48)
                        temp.push_back(makeHouse('S', v.index, (aNumber + 1) * 100 + 1, v.step + 1));

                    // 左转进入大道（南向）
                    if (v.index < 49)
                        temp.push_back(makeHouse('A', aNumber + 1, v.index * 100 + 1, v.step + 1));

                    for (int i = 0; i < temp.size(); i++) {
                        if (isMissing(temp[i]) == false) {
                            if (isVisited(temp[i]) == false) {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                    }

                    // U 形转弯
                    if (nextFound == false) {
                        house tempHouse = makeHouse('S', v.index, v.number - 1, v.step + 1);
                        if (isVisited(tempHouse) == false) {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                } else {
                    house temp = makeHouse('S', v.index, v.number + 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('S', v.index, v.number - 1, v.step + 1);

                    if (isVisited(temp) == false) {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    int start, end;

    // 读取缺失路段部分，直到 '#'
    while (cin >> line, line != "#") {
        cin >> start >> end;

        // 标记该路段上连续的门牌号为缺失
        for (int i = start; i <= end + 1; i++) {
            house temp = (house){line.front(), stoi(line.substr(1)), i, 0};
            missing.insert(getHouseId(temp));
        }
    }

    // 读取地址对部分，直到 '#'
    while (cin >> line, line != "#") {
        cin >> start;
        from = (house){line.front(), stoi(line.substr(1)), start, 1};

        cin >> line >> end;
        to = (house){line.front(), stoi(line.substr(1)), end, 0};

        bfs();  // 对每一对地址进行 BFS 搜索
    }

    return 0;
}
```

## 总结

本题的核心在于将城市道路网络转化为图模型，并模拟靠右行驶的交通规则。$\texttt{BFS}$ 保证找到最短路径，关键在于正确处理各种移动情况：直行、左转、右转以及死胡同中的 $\texttt{U}$ 形转弯。理解门牌号与行驶方向的关系是解决问题的前提。
