[UVa 205 Getting There](https://blog.csdn.net/metaphysis/article/details/161009619)

## 题目分析

本题是一个带有时间约束的最短路径问题。我们需要在给定的航班列表中，为每次旅行请求找到最优路线。优化目标可以是**最小化总费用**或**最小化总旅行时间**。如果存在多条最优路线（同样最小化费用或时间），则进一步比较另一个目标，选择更优的那一条。

主要特点：

- 航班信息包含：起点、终点、出发时间、到达时间、费用。
- 时间格式为 `HH:MMX`，其中 `X` 为 `A`（上午）或 `P`（下午）。
- 出发时间总是早于到达时间，且单次航班时长小于 $24$ 小时。
- 最多 $50$ 条航班，最多 $20$ 个城市。
- 总旅行时间小于 $10$ 天（$14400$ 分钟），总费用小于 $$1000.00$。
- 城市名称不区分大小写，但输出时首字母需大写。
- 输入由多个测试用例组成，每个用例以 `TRAVEL XXX` 开头，航班段和请求段均以 `#` 结束。

## 解题思路

### 1. 数据存储与预处理

- 使用 `map<string, int>` 将城市名称映射到整数索引，便于图的操作。
- 使用邻接表 `vector<vector<edge>>` 存储航班信息。
- 将时间字符串转换为从 `00:00` 开始的分钟数，便于计算时间差。
- 将费用字符串转换为整数（以“分”为单位），避免浮点数误差。

### 2. 时间与费用计算

- `getTime()`：将时间字符串转换为分钟数，注意 `P` 表示下午，需加 $720$ 分钟。
- `getCost()`：将费用字符串转换为整数分，删除小数点后转换为整数。
- `interval()`：计算两个时间点之间的分钟差，考虑跨午夜的情况。
- `wait()`：计算等待时间，同样考虑跨午夜。

### 3. 算法选择

由于城市数量少（$\le 20$），航班数量有限（$\le 50$），且题目保证有唯一解，我们可以使用 **$\texttt{DFS}$ 回溯** 来枚举所有可能的路径。

回溯函数 `backtrack(start, end, index)` 的参数：
- `start`：当前所在城市的索引
- `end`：目标城市的索引
- `index`：当前路径中的航班数量

剪枝条件：
- 如果当前累计时间 $\ge 14400$ 分钟或累计费用 $\ge 100000$ 分，则停止搜索。
- 使用 `visited[]` 数组防止形成环。

### 4. 最优解比较

根据当前请求的优化目标（`costFirst` 标志）进行判断：
- 若优化费用：优先比较 `totalCost`，相同时比较 `totalTime`。
- 若优化时间：优先比较 `totalTime`，相同时比较 `totalCost`。

### 5. 特殊情况处理

- 起点和终点相同：输出 `You are already in X.`
- 起点或终点不在任何航班中出现：输出 `There is no route from X to Y.`

### 6. 输出格式

- 每个测试用例输出标题 `Requests and optimal routes for travel X` 和分隔线。
- 不同请求之间空一行，不同测试用例之间空两行。
- 路径需按顺序输出每一段航班的起点、终点、出发时间、到达时间、费用。
- 最后一行输出总时间和总费用，右对齐。

## 代码实现

```cpp
// Getting There
// UVa ID: 205
// Verdict: Accepted
// Submission Date: 2016-04-23
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge {
    string startCity, endCity, leaveTime, arriveTime, costMoney;
    int start, end, leave, arrive, time, cost;
};

vector<vector<edge>> edges;
map<string, int> cityIndexs;
vector<string> cityNames;
set<string> startCities, endCities;
bool found;
vector<edge> path, best;
vector<bool> visited;
int bestTime = 14400, bestCost = 100000;
bool costFirst;

// 计算等待时间（从到达时间到下一次出发时间，考虑跨午夜）
int wait(int arrive, int leave) {
    if (leave >= arrive) return leave - arrive;
    else return (1440 - (arrive - leave));
}

// 计算飞行时间（从出发到到达，考虑跨午夜）
int interval(int leave, int arrive) {
    if (arrive > leave) return arrive - leave;
    else return (1440 - (leave - arrive));
}

// DFS 回溯搜索所有路径
void backtrack(int start, int end, int index) {
     // 到达目标城市
    if (start == end) {
        int totalTime = 0, totalCost = 0;
        for (int i = 0; i < index; i++) {
            totalTime += path[i].time;
            totalCost += path[i].cost;
            if (i > 0)
                totalTime += wait(path[i - 1].arrive, path[i].leave);
        }

        // 剪枝：超出限制
        if (totalTime >= 14400 || totalCost >= 100000) return;

        // 根据优化目标判断是否更优
        if ((costFirst && (totalCost < bestCost ||
                    (totalCost == bestCost && totalTime < bestTime))) ||
            (!costFirst && (totalTime < bestTime ||
                    (totalTime == bestTime && totalCost < bestCost)))) {
            best.clear();
            for (int i = 0; i < index; i++)
                best.push_back(path[i]);
            bestTime = totalTime;
            bestCost = totalCost;
            found = true;
        }
        return;
    }

    // 遍历所有从当前城市出发的航班
    for (int i = 0; i < edges[start].size(); i++)
        // 避免环路
        if (visited[edges[start][i].end] == false) {
            visited[edges[start][i].end] = true;
            path[index] = edges[start][i];
            backtrack(edges[start][i].end, end, index + 1);
            visited[edges[start][i].end] = false;
        }
}

// 将字符串转为小写（用于统一城市名）
string toLower(string source) {
    for (int i = 0; i < source.length(); i++)
        source[i] = tolower(source[i]);
    return source;
}

// 将字符串首字母大写（用于输出）
string toUpper(string source) {
    source[0] = toupper(source[0]);
    return source;
}

// 将时间字符串转换为分钟数
int getTime(string time) {
    int minutes = 0;
    int indexer = time.find(':');
    minutes = stoi(time.substr(0, indexer)) * 60;
    minutes += stoi(time.substr(indexer + 1, 2));
    if (time.back() == 'P')
        minutes += 720;
    return minutes;
}

// 将费用字符串转换为整数分
int getCost(string cost) {
    for (int i = 0; i < cost.length(); i++)
        if (cost[i] == '.') {
            cost.erase(cost.begin() + i);
            break;
        }
    return stoi(cost);
}

// 将分钟数转换为时间字符串（如 "1 day 4:35"）
string toTime(int time) {
    string text;
    int days = time / 1440;
    if (days >= 2) {
        text += to_string(days);
        text += " days ";
    } else if (days >= 1) {
        text += to_string(days);
        text += " day ";
    }
    time %= 1440;
    text += to_string(time / 60);
    text += ":";
    time %= 60;
    text += time >= 10 ? "" : "0";
    text += to_string(time);
    return text;
}

// 将整数分转换为货币字符串
string toCost(int cost) {
    string text = "$";
    text += to_string(cost / 100);
    text += '.';
    cost %= 100;
    text += cost >= 10 ? "" : "0";
    text += to_string(cost);
    return text;
}

// 去除时间字符串中小时部分的 leading zero
string trimTime(string time) {
    if (time[0] == '0' && time[1] != ':') time.erase(time.begin());
    return time;
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    bool printTwoBlankLine = false;

    while (getline(cin, line)) {
        edges.clear();
        cityIndexs.clear();
        cityNames.clear();
        startCities.clear();
        endCities.clear();

        // 最多 20 个城市
        edges.resize(20);
        visited.resize(20);
        path.resize(20);

        istringstream iss(line);
        string firstPart, secondPart;
        iss >> firstPart >> secondPart;

        // 输出两个空行分隔测试用例
        if (printTwoBlankLine) cout << "\n\n";
        else printTwoBlankLine = true;

        cout << "Requests and optimal routes for travel ";
        cout << stoi(secondPart) << "\n";
        cout << "------------------------------------------\n";
        cout << "\n";

        // 读取航班信息，直到 '#'
        while (getline(cin, line), line != "#") {
            edge aEdge;
            string startCity, endCity, leaveTime, arriveTime, costMoney;
            iss.clear();
            iss.str(line);
            iss >> startCity >> endCity >> leaveTime >> arriveTime >> costMoney;
            // 统一为小写处理
            startCity = toLower(startCity);
            endCity = toLower(endCity);
            if (cityIndexs.count(startCity) == 0) {
                cityNames.push_back(startCity);
                cityIndexs.insert({startCity, cityNames.size() - 1});
            }
            if (cityIndexs.count(endCity) == 0) {
                cityNames.push_back(endCity);
                cityIndexs.insert({endCity, cityNames.size() - 1});
            }
            startCities.insert(startCity);
            endCities.insert(endCity);
            // 构造边
            aEdge.startCity = toUpper(startCity);
            aEdge.endCity = toUpper(endCity);
            aEdge.start = cityIndexs[startCity];
            aEdge.end = cityIndexs[endCity];
            aEdge.leaveTime = trimTime(leaveTime);
            aEdge.arriveTime = trimTime(arriveTime);
            aEdge.leave = getTime(leaveTime);
            aEdge.arrive = getTime(arriveTime);
            aEdge.time = interval(aEdge.leave, aEdge.arrive);
            aEdge.cost = getCost(costMoney);
            aEdge.costMoney = toCost(aEdge.cost);
            edges[aEdge.start].push_back(aEdge);
        }

        bool printOneBlankLine = false;
        // 处理旅行请求，直到 '#'
        while (getline(cin, line), line != "#") {
            string startCity, endCity, target;
            iss.clear();
            iss.str(line);
            iss >> startCity >> endCity >> target;
            startCity = toLower(startCity);
            endCity = toLower(endCity);
            // 请求之间空一行
            if (printOneBlankLine) cout << "\n";
            else printOneBlankLine = true;
            // 起点与终点相同
            if (startCity == endCity) {
                cout << "You are already in " << toUpper(startCity) << ".\n";
                continue;
            }

            // 城市不存在于任何航班中
            if (startCities.count(startCity) == 0 || endCities.count(endCity) == 0) {
                cout << "There is no route from ";
                cout << toUpper(startCity);
                cout << " to ";
                cout << toUpper(endCity);
                cout << ".\n";
                continue;
            }

            // DFS 回溯搜索最优路线
            found = false;
            costFirst = target == "COST";
            bestTime = 14400;
            bestCost = 100000;
            fill(visited.begin(), visited.end(), false);
            backtrack(cityIndexs[startCity], cityIndexs[endCity], 0);

            // 输出结果
            if (found) {
                // 输出请求信息
                cout << "From: ";
                cout << setw(21) << left << toUpper(startCity);
                cout << "To: ";
                cout << setw(21) << left << toUpper(endCity);
                cout << "Optimize: ";
                cout << toUpper(toLower(target));
                cout << "\n";

                // 表头
                cout <<
                    "==================================================================\n";
                cout << setw(20) << left << "From";
                cout << setw(23) << left << "To";
                cout << setw(8) << left << "Leave";
                cout << setw(6) << left << "Arrive";
                cout << setw(9) << right << "Cost";
                cout << "\n";
                cout <<
                    "==================================================================\n";

                // 输出每一段航班
                for (int i = 0; i < best.size(); i++) {
                    cout << setw(20) << left << best[i].startCity;
                    cout << setw(23) << left << best[i].endCity;
                    cout << setw(8) << left << best[i].leaveTime;
                    cout << setw(6) << left << best[i].arriveTime;
                    cout << setw(9) << right << best[i].costMoney;
                    cout << "\n";
                }

                // 输出总时间和总费用
                cout << setw(66) << right << "-----------------------";
                cout << "\n";
                cout << setw(57) << right << toTime(bestTime);
                cout << setw(9) << right << toCost(bestCost);
                cout << "\n";
            } else {
                cout << "There is no route from ";
                cout << toUpper(startCity);
                cout << " to ";
                cout << toUpper(endCity);
                cout << ".\n";
            }
        }
    }

    return 0;
}
```

## 总结

本题的核心在于处理跨午夜的时间计算，以及在有约束条件下的多目标最优路径搜索。由于数据规模较小，使用 $\texttt{DFS}$ 回溯即可在时间限制内完成搜索。代码中需要仔细处理输入格式、时间转换和输出对齐，确保与样例输出完全一致。
