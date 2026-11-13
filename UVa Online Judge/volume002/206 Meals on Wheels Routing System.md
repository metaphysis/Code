[UVa 206 Meals on Wheels Routing System](https://blog.csdn.net/metaphysis/article/details/161009941)

## 题目分析

“流动餐车配送系统” 是一个典型的路径规划问题。题目要求根据顾客的极角将顾客分配到不同的配送路线中，使得每条路线的顾客数量尽可能均衡，并计算每条路线的曼哈顿距离总长度。

核心要点如下：

- 总部位于原点 `(0, 0)`。
- 每位顾客的位置用整数坐标 `(x, y)` 表示，单位为城市街区数量。
- 路线长度计算采用 **曼哈顿距离**（因为街区不能斜穿）：  
  $|x_1 - x_2| + |y_1 - y_2|$。
- 路线总长度为：总部 $\to$ 第一位顾客 $\to$ 第二位顾客 $\to \cdots \to$ 最后一位顾客 $\to$ 总部。
- 顾客分配策略：
  1. 计算每位顾客的极角（$\texttt{atan2}(y, x)$，$0^\circ$ 为正东，$90^\circ$ 为正北）。
  2. 按极角从小到大排序，相同极角时按距离原点近的优先。
  3. 将排序后的顾客均匀分配给 $n$ 条路线，每条路线顾客数最多相差 $1$。
  4. 从最小极角的顾客开始分配。

## 解题思路

1. **读取数据**  
   每组数据包含：数据集 ID、路线数 $n$、顾客数 $m$，以及 $m$ 组姓名和坐标。

2. **极角计算与排序**  
   使用 `atan2(y, x)` 计算极角，范围是 $(-\pi, \pi]$。为了便于按 $0^\circ \sim 360^\circ$ 排序，将负角 $+2\pi$。  
   自定义比较函数 `cmp`：先比较极角（容忍小误差 `EPSILON`），极角相同时比较距离原点的平方和（避免开方）。

3. **均匀分配**  
   $m$ 个顾客分给 $n$ 条路线：  
   - 基础数量 `base = m / n`  
   - 余数 `remain = m % n`  
   前 `remain` 条路线分配 `base + 1` 个顾客，其余分配 `base` 个顾客。

4. **路线长度计算**  
   按顺序累加曼哈顿距离：
   - 第一个顾客：总部到该顾客的距离  
     $|x| + |y|$
   - 中间顾客：与前一个顾客的距离  
     $|x_i - x_{i-1}| + |y_i - y_{i-1}|$
   - 最后一位顾客：返回总部的距离  
     $|x_{\text{last}}| + |y_{\text{last}}|$

5. **输出格式**  
   - 每组数据前输出 `***********************************`（第一组除外）。
   - 输出数据集 ID、顾客总数、路线数。
   - 每条路线输出序号、顾客姓名、路线长度。
   - 最后输出所有路线的总长度。

## 代码实现

```cpp
// Meals on Wheels Routing System
// UVa ID: 206
// Verdict: Accepted
// Submission Date: 2016-04-25
// UVa Run Time: 0.200s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358979323846, EPSILON = 1E-7;

// 顾客结构体：姓名、坐标
struct customer {
    string name;
    int x, y;
};

bool printStar = false;   // 控制是否输出星号分隔行
int n, m;                 // n = 路线数，m = 顾客数
string dataSetId;         // 数据集 ID
vector<customer> customers;   // 存储所有顾客

// 自定义排序函数：按极角从小到大，极角相同时按欧氏距离（平方和）从小到大
bool cmp(customer a, customer b) {
    double angleA = atan2(a.y, a.x);
    double angleB = atan2(b.y, b.x);
    
    // 将负角转换为 [0, 2π) 范围
    if (angleA < 0)
        angleA += 2 * PI;
    if (angleB < 0)
        angleB += 2 * PI;
    
    // 极角相近时（浮点误差），比较距离原点的长度
    if (fabs(angleA - angleB) <= EPSILON)
        return (a.x * a.x + a.y * a.y) < (b.x * b.x + b.y * b.y);
    else
        return angleA < angleB;
}

// 处理当前数据集的路线分配与输出
void route() {
    // 如果不是第一组数据，输出分隔星号线
    if (printStar)
        cout << "***********************************\n";
    else
        printStar = true;
        
    cout << dataSetId << "\n";
    cout << "Number of Customers: " << setw(11) << left << m;
    cout << "Number of Routes: " << n << "\n";
    cout << "\n";
    
    int customersPerRoute = m / n;   // 每条路线基础顾客数
    int customersRemains = m % n;    // 余数，前 remain 条路线各多一个顾客
    int totalLength = 0;             // 所有路线的总长度
    
    // 按极角排序
    sort(customers.begin(), customers.end(), cmp);
    
    int index = 0;   // 当前处理的顾客在排序后数组中的下标
    for (int i = 1; i <= n; i++) {
        int subRouteLength = 0;   // 当前路线长度
        
        cout << "Route ==> " << i << "\n";
        
        // 分配基础数量的顾客
        for (int j = 1; j <= customersPerRoute; j++) {
            cout << "Customer: " << customers[index].name << "\n";
            
            if (j == 1)
                // 第一个顾客：总部到该顾客的距离
                subRouteLength += (abs(customers[index].x) + abs(customers[index].y));
            else
                // 后续顾客：与前一个顾客的曼哈顿距离
                subRouteLength += (abs(customers[index].x - customers[index - 1].x) +
                    abs(customers[index].y - customers[index - 1].y));
            index++;
        }
        
        // 如果还有余数，当前路线再分配一个额外顾客
        if (customersRemains > 0) {
            customersRemains--;
            cout << "Customer: " << customers[index].name << "\n";
            subRouteLength += (abs(customers[index].x - customers[index - 1].x) +
                    abs(customers[index].y - customers[index - 1].y));
            index++;                    
        }
        
        // 加上从最后一个顾客返回总部的距离
        subRouteLength += (abs(customers[index - 1].x) + abs(customers[index - 1].y));
        
        cout << "Route Length ==> " << subRouteLength << "\n";
        cout << "\n";
        
        totalLength += subRouteLength;
    }
    
    cout << "Total Route Length ==> " << totalLength << "\n";
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    string customerName;
    int x, y;
    
    // 循环读取每组数据，直到 EOF
    while (getline(cin, dataSetId)) {
        cin >> n >> m;
        cin.ignore();   // 忽略换行符
        
        customers.clear();
        for (int i = 1; i <= m; i++) {
            getline(cin, customerName);   // 读取顾客姓名（可能包含空格）
            cin >> x >> y;
            cin.ignore();                 // 忽略换行符
            
            customers.push_back((customer){customerName, x, y});
        }
        
        route();   // 处理当前数据集的路线分配
    }
    
	return 0;
}
```
