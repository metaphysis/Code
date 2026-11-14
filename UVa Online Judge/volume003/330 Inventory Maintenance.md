[UVa 330 Inventory Maintenance](https://blog.csdn.net/metaphysis/article/details/161533073)

## 题目描述

$\texttt{Madam Phoenix}$ 正在向西南地区搬迁，开设一家名为“阳光乐趣”的商店，销售太阳镜、防晒霜等商品。她决定雇佣你来为她的新店编写一个库存管理程序。

每个需要处理的“活动”在输入文件中占据单独一行。输入结束标记为第一列为星号（`*`）的行。活动行以小写关键字开头，表示要执行的操作。库存中的商品名称区分大小写，每个名称不超过 $10$ 个非空白字符。活动行中的所有字段由空格分隔。

### 活动类型

| 活动 | 格式 | 说明 |
|------|------|------|
| `new` | `new item-name item-cost item-selling-price` | 添加新商品（之前未销售过）。不改变库存数量，但记录成本和售价。最多 $100$ 种商品。成本和售价 $\leq 100.00$。 |
| `delete` | `delete item-name` | 删除商品。库存中该商品的所有单位作为亏损处理。 |
| `buy` | `buy item-name quantity` | 购买商品（按之前的成本价）。单次购买数量 $\leq 5000$，总库存量可能达到 $10000$。 |
| `sell` | `sell item-name quantity` | 销售商品（按之前的售价）。销售数量不能超过当前库存。 |
| `report` | `report` | 生成报告。按商品名称字母顺序输出：商品名、成本价、售价、库存数量、库存价值（数量 × 成本价）。报告末尾显示库存总价值和自上次报告以来的总利润。 |

**利润定义**：总销售额 - 已售商品的成本 - 已删除商品的成本。

### 输出格式

报告格式如样例所示。所有数字必须精确。每个报告后输出一个空行。

### 样例输入

```
new Shade01 0.50 3.79
new Towel01 1.47 6.98
new Shade02 0.63 4.29
new BluBlock 1.00 4.98
buy BluBlock 100
sell BluBlock 2
buy Towel01 500
buy Shade01 100
buy Shade02 100
sell Towel01 1
sell Towel01 1
sell BluBlock 2
report
delete Shade01
sell BluBlock 5
new Shade03 0.51 1.98
buy Shade03 250
sell Towel01 5
sell Shade03 4
sell Shade02 10
report
*
```

### 样例输出

```
                  INVENTORY REPORT
Item Name     Buy At      Sell At      On Hand        Value
---------     ------      -------      -------        -----
BluBlock         1.00         4.98           96         96.00
Shade01          0.50         3.79          100         50.00
Shade02          0.63         4.29          100         63.00
Towel01          1.47         6.98          498        732.06
------------------------
Total value of inventory                            941.06
Profit since last report                             26.94

                  INVENTORY REPORT
Item Name     Buy At      Sell At      On Hand        Value
---------     ------      -------      -------        -----
BluBlock         1.00         4.98           91         91.00
Shade02          0.63         4.29           90         56.70
Shade03          0.51         1.98          246        125.46
Towel01          1.47         6.98          493        724.71
------------------------
Total value of inventory                            997.87
Profit since last report                             39.93
```

---

## 题目分析

### 问题的本质

这是一个**库存管理系统**的模拟问题。需要处理五种操作：
- 添加商品
- 删除商品
- 购买（增加库存）
- 销售（减少库存，记录利润）
- 报告（输出当前状态）

### 关键计算

1. **库存价值**：`数量 × 成本价`
2. **自上次报告以来的利润**：
   ```
   利润 = 总销售额 - 已售商品的成本 - 已删除商品的成本
   ```
   - 销售额：销售数量 × 售价
   - 售出成本：销售数量 × 成本价
   - 删除亏损：删除数量 × 成本价

3. **报告后重置利润统计**：每次 `report` 后，利润相关变量归零

### 数据结构

使用 `map<string, item>` 存储库存，`map` 自动按键（商品名称）排序，方便报告输出。

每个商品包含：
- `item_name`：商品名称
- `quantity`：当前库存数量
- `item_cost`：成本价
- `item_selling_price`：售价

---

## 解题思路

### 步骤一：定义数据结构

```cpp
struct item {
    string item_name;
    int quantity;
    double item_cost, item_selling_price;
};
```

### 步骤二：维护全局利润变量

```cpp
double selling = 0.0;  // 总销售额
double cost = 0.0;     // 已售商品的成本
double loss = 0.0;     // 删除商品的亏损
```

### 步骤三：实现各操作

#### `new` 操作

```cpp
void add() {
    string name; double buy, sell;
    cin >> name >> buy >> sell;
    inventory[name] = {name, 0, buy, sell};
}
```

#### `buy` 操作

```cpp
void buy() {
    string name; int qty;
    cin >> name >> qty;
    inventory[name].quantity += qty;
}
```

#### `sell` 操作

```cpp
void sell() {
    string name; int qty;
    cin >> name >> qty;
    if (inventory[name].quantity >= qty) {
        selling += inventory[name].item_selling_price * qty;
        cost += inventory[name].item_cost * qty;
        inventory[name].quantity -= qty;
    } else {
        // 理论上不会发生，但代码做了防护
        selling += inventory[name].item_selling_price * inventory[name].quantity;
        cost += inventory[name].item_cost * inventory[name].quantity;
        inventory[name].quantity = 0;
    }
}
```

#### `delete` 操作

```cpp
void remove() {
    string name;
    cin >> name;
    if (inventory[name].quantity > 0)
        loss += inventory[name].quantity * inventory[name].item_cost;
    inventory.erase(name);
}
```

#### `report` 操作

```cpp
void report() {
    double total_value = 0.0;
    
    // 输出表头
    cout << "                  INVENTORY REPORT\n";
    cout << "Item Name     Buy At      Sell At      On Hand        Value\n";
    cout << "---------     ------      -------      -------        -----\n";
    
    // 遍历库存（按名称自动排序）
    for (auto& p : inventory) {
        item& it = p.second;
        double value = it.item_cost * it.quantity;
        total_value += value;
        
        cout << setw(14) << left << it.item_name;
        cout << setw(6) << right << fixed << setprecision(2) << it.item_cost;
        cout << setw(13) << right << fixed << setprecision(2) << it.item_selling_price;
        cout << setw(13) << right << it.quantity;
        cout << setw(13) << right << fixed << setprecision(2) << value << "\n";
    }
    
    cout << "------------------------\n";
    cout << "Total value of inventory                      ";
    cout << setw(13) << right << fixed << setprecision(2) << total_value << "\n";
    cout << "Profit since last report                      ";
    cout << setw(13) << right << fixed << setprecision(2) << (selling - cost - loss) << "\n\n";
    
    // 重置利润变量
    selling = cost = loss = 0.0;
}
```

---



## 参考代码

```cpp
// Inventory Maintenance
// UVa ID: 330
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.290s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 商品结构体
struct item
{
    string item_name;       // 商品名称
    int quantity;           // 库存数量
    double item_cost;       // 成本价
    double item_selling_price;  // 售价
};

// 全局利润统计变量
double selling = 0.0;   // 总销售额
double cost = 0.0;      // 已售商品的成本
double loss = 0.0;      // 删除商品的亏损

// 库存映射表，自动按商品名称排序
map<string, item> inventory;

// 生成库存报告
void report()
{
    double total_value = 0.0;
    
    // 输出表头
    cout << "                  INVENTORY REPORT" << endl;
    cout << "Item Name     Buy At      Sell At      On Hand        Value" << endl;
    cout << "---------     ------      -------      -------        -----" << endl;
    
    // 遍历所有商品（自动按名称排序）
    for (auto something : inventory)
    {
        cout << setw(14) << left << something.second.item_name;
        cout << setw(6) << right << fixed << setprecision(2) << something.second.item_cost;
        cout << setw(13) << right << fixed << setprecision(2) << something.second.item_selling_price;
        cout << setw(13) << right << something.second.quantity;
        
        double value = something.second.item_cost * something.second.quantity;
        total_value += value;
        cout << setw(13) << right << fixed << setprecision(2) << value;
        cout << endl;
    }

    // 输出总计和利润
    cout << "------------------------" << endl;
    cout << "Total value of inventory                      ";
    cout << setw(13) << right << fixed << setprecision(2) << total_value << endl;
    cout << "Profit since last report                      ";
    cout << setw(13) << right << fixed << setprecision(2) << (selling - cost - loss) << endl;
    cout << endl;
    
    // 重置利润统计
    selling = 0.0, cost = 0.0, loss = 0.0;
}

// 添加新商品
void add()
{
    string item_name; 
    double item_cost, item_selling_price;
    cin >> item_name >> item_cost >> item_selling_price;
    inventory[item_name] = (item){item_name, 0, item_cost, item_selling_price};
}

// 删除商品（库存数量作为亏损）
void remove()
{
    string item_name;
    cin >> item_name;
    if (inventory[item_name].quantity > 0)
        loss += inventory[item_name].quantity * inventory[item_name].item_cost;
    inventory.erase(item_name);
}

// 销售商品
void sell()
{
    string item_name; 
    int quantity;
    cin >> item_name >> quantity;
    
    if (inventory[item_name].quantity >= quantity)
    {
        selling += inventory[item_name].item_selling_price * quantity;
        cost += inventory[item_name].item_cost * quantity;
        inventory[item_name].quantity -= quantity;
    }
    else
    {
        // 防护性代码：理论不会发生
        selling += inventory[item_name].item_selling_price * inventory[item_name].quantity;
        cost += inventory[item_name].item_cost * inventory[item_name].quantity;
        inventory[item_name].quantity = 0;
    }
}

// 购买商品（增加库存）
void buy()
{
    string item_name; 
    int quantity;
    cin >> item_name >> quantity;
    inventory[item_name].quantity += quantity;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string action;
    while (cin >> action)
    {
        if (action == "*") break;
        if (action == "report") report();
        if (action == "new") add();
        if (action == "delete") remove();
        if (action == "sell") sell();
        if (action == "buy") buy();
    }
    
    return 0;
}
```
