
> **摘要**：本文讲解一道产院选址优化问题：给定 $C$ 个城市的名称、人口与坐标，以及 $M$ 个已设产院的城市，需关闭恰好 $N$ 个产院，使所有城市到最近开放产院的曼哈顿距离加权总费用最小，费用相同时取关闭城市名称字典序最小的方案。由于 $M \le 20$、$N \le 10$，合法方案数最多 $\binom{20}{10}=184756$，可用二进制状态枚举全部关闭方案，逐方案计算总费用并维护最优解，时间复杂度 $O\left(\binom{M}{N}\times C\times M\right)$，空间复杂度 $O(C+M)$。

# 题目描述

$\texttt{Coviland}$ 中有 $C$ 个城市，每个城市具有唯一的名称、人口和坐标。部分城市当前设有产院，政府需要关闭其中的 $N$ 个服务，使剩余产院为所有城市提供服务。

每个城市的居民都前往距离最近的开放产院。由于道路只沿南北方向或东西方向连接，城市之间的实际最短距离为曼哈顿距离。某个城市产生的生育出行费用等于该城市人口乘以其到最近开放产院的距离。

需要选择恰好 $N$ 个关闭服务，使所有城市产生的总费用最小。若存在多个费用相同的方案，则将每个方案中的关闭城市名称按字典序排列，选择字典序最小的名称序列。

# 输入格式

输入包含多个测试用例，测试用例之间由一个空行分隔，输入以文件结束。

每个测试用例的输入格式如下：

- 第一行包含一个整数 $C$，表示城市数量，满足 $0 < C \le 100$。
- 接下来 $C$ 行，每行包含城市名称、人口以及坐标 $x$ 和 $y$。城市名称只包含小写字母，长度不超过 $31$。
- 下一行包含一个整数 $M$，表示当前设有产院的城市数量，满足 $0 < M \le C$ 且 $M \le 20$。
- 接下来 $M$ 行，每行包含一个设有产院的城市名称。
- 最后一行包含一个整数 $N$，表示需要关闭的服务数量，满足 $0 < N < M$ 且 $N \le 10$。

# 输出格式

对于每个测试用例，输出 $N$ 行，表示需要关闭服务的城市名称，名称按字典序排列。

相邻两个测试用例的输出之间使用一个空行分隔。

# 样例输入

```text
7
covi 2800 500 600
fund 1000 500 400
penam 500 900 600
castle 2500 700 300
belmont 600 900 900
butter 700 200 400
gard 5000 700 900
4
covi
gard
castle
fund
2
```

# 样例输出

```text
castle
covi
```

# 题目分析

关闭服务后，每个城市都必须由至少一个未关闭的产院提供服务。设城市 $i$ 的人口为 $p_i$，坐标为 $(x_i, y_i)$，开放产院集合为 $open$，则城市 $i$ 到最近开放产院的距离为

$$
minDist_i = \min_{j \in open} \left( |x_i - x_j| + |y_i - y_j| \right)
$$

该城市产生的费用为

$$
 p_i \times minDist_i
$$

因此，当前方案的总费用为

$$
 totalCost = \sum_{i=1}^{C} p_i \times minDist_i
$$

题目要求关闭恰好 $N$ 个产院，所以最终必须保留 $M - N$ 个产院。对于每一种关闭方案，都可以直接计算所有城市到开放产院的最近距离，并据此得到方案总费用。

当前设有产院的城市数量满足 $M \le 20$，需要关闭的数量满足 $N \le 10$。因此关闭方案总数最多为

$$
\binom{20}{10} = 184756
$$

这个数量可以直接枚举。每个方案最多检查 $C \times M$ 个城市与产院的组合，整体规模能够满足题目的限制。

题目中的“额外费用”不需要单独计算。所有方案面对的城市、人口和坐标均相同，原有产院全部开放时的总费用是固定值。关闭后的额外费用等于关闭后的总费用减去这个固定值，因此使额外费用最小，与使关闭后的总费用最小完全等价。

# 解题思路

使用长度为 $M$ 的二进制状态表示关闭方案。第 $i$ 位为 $1$ 时，表示关闭第 $i$ 个服务城市；第 $i$ 位为 $0$ 时，表示保留该服务城市。

枚举所有从 $0$ 到 $2^M - 1$ 的状态，仅处理其中二进制位中恰好有 $N$ 个 $1$ 的状态。对每个合法状态执行以下计算：

- 遍历全部城市。
- 遍历全部服务城市，跳过已经关闭的服务。
- 计算当前城市到每个开放服务城市的曼哈顿距离，取其中最小值。
- 将最小距离乘以当前城市人口，并累加到总费用中。
- 收集状态中被关闭的城市名称，排序后得到该方案的字典序序列。

维护当前最优费用和对应的关闭城市序列。当新方案的总费用更小时直接更新答案；当费用相等时，比较两个已经排序的名称序列，保留字典序更小的序列。

城市名称通过映射表转换为城市下标。读取服务城市名称时，可以在映射表中快速找到对应的城市信息，并保存到服务城市数组中。这样计算距离时可以直接访问坐标和人口。

由于 $N < M$，关闭服务后始终至少保留一个开放产院，所以最近距离一定存在。人口和距离均使用 `long long` 类型参与计算，避免总费用累加时发生整数溢出。

设合法关闭方案数量为 $\binom{M}{N}$。每个方案需要计算 $C$ 个城市到最多 $M$ 个服务城市的距离，因此时间复杂度为

$$
O\left( \binom{M}{N} \times C \times M \right)
$$

将所有状态都纳入上界时，也可以写为 $O(2^M \times C \times M)$。存储城市信息、服务城市信息、名称映射和当前最优名称序列所需的空间复杂度为

$$
O(C + M)
$$

不计枚举状态本身占用的常数级空间。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

struct City {
    string name;
    long long population, x, y;
};

long long getDistance(const City &a, const City &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

long long getCost(const vector<City> &cities, const vector<City> &services, int closeMask) {
    long long totalCost = 0;
    for (const City &city : cities) {
        long long minDistance = numeric_limits<long long>::max();
        for (int i = 0; i < static_cast<int>(services.size()); ++i)
            if ((closeMask & (1 << i)) == 0)
                minDistance = min(minDistance, getDistance(city, services[i]));
        totalCost += city.population * minDistance;
    }
    return totalCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cityCount;
    bool firstCase = true;
    while (cin >> cityCount) {
        vector<City> cities(cityCount);
        map<string, int> cityIndex;
        for (int i = 0; i < cityCount; ++i) {
            cin >> cities[i].name >> cities[i].population >> cities[i].x >> cities[i].y;
            cityIndex[cities[i].name] = i;
        }
        int serviceCount;
        cin >> serviceCount;
        vector<City> services(serviceCount);
        for (int i = 0; i < serviceCount; ++i) {
            string serviceName;
            cin >> serviceName;
            services[i] = cities[cityIndex[serviceName]];
        }
        int closeCount;
        cin >> closeCount;
        long long bestCost = numeric_limits<long long>::max();
        vector<string> bestNames;
        int totalMasks = 1 << serviceCount;
        for (int closeMask = 0; closeMask < totalMasks; ++closeMask) {
            if (__builtin_popcount(static_cast<unsigned int>(closeMask)) != closeCount)
                continue;
            long long currentCost = getCost(cities, services, closeMask);
            vector<string> currentNames;
            for (int i = 0; i < serviceCount; ++i)
                if (closeMask & (1 << i))
                    currentNames.push_back(services[i].name);
            sort(currentNames.begin(), currentNames.end());
            if (currentCost < bestCost || currentCost == bestCost && currentNames < bestNames) {
                bestCost = currentCost;
                bestNames = currentNames;
            }
        }
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        for (const string &name : bestNames)
            cout << name << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将关闭服务的选择表示为二进制状态，并枚举所有恰好关闭 $N$ 个服务的方案。每个方案的费用由所有城市到最近开放产院的曼哈顿距离确定，遍历城市和开放产院即可完成计算。

解题时需要注意以下关键点：

- 网格道路下的最短距离是曼哈顿距离 $|x_1 - x_2| + |y_1 - y_2|$。
- 只需最小化关闭后的总费用，因为原有状态的费用是所有方案共有的固定值。
- 必须筛选出恰好包含 $N$ 个关闭服务的二进制状态。
- 费用相同时，需要对关闭城市名称排序，再比较名称序列的字典序。
- 使用 `long long` 保存费用，保证人口与距离相乘以及总和计算的正确性。

