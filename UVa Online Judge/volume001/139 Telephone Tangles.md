[UVa 139 Telephone Tangles](https://blog.csdn.net/metaphysis/article/details/157426937)

## 题目分析

本题是一道**电话计费模拟**题，要求根据拨打的号码和通话时长，结合给定的区号（或国家代码）与费率表，计算出每一通电话的费用。

### 输入格式

输入分为两部分：

1. **费率表**  
   每行格式为：  
   ```
   代码 地区名称$每分钟费用（美分）
   ```
   地区名称不超过 $25$ 个字符，费率以美分为单位。  
   此部分以一行 `000000` 结束。

2. **通话记录**  
   每行格式为：  
   ```
   号码 时长（分钟）
   ```
   号码与时长之间至少有一个空格。  
   此部分以一行 `#` 结束。

### 号码分类

- **国际长途（$\texttt{IDD}$）** ：以 `00` 开头，后接 $1$ 至 $3$ 位国家代码，再后接 $4$ 至 $10$ 位用户号码。
- **国内长途（$\texttt{STD}$）** ：以 `0` 开头（但非 `00`），后接 $1$ 至 $5$ 位区号，再后接 $4$ 至 $7$ 位用户号码。
- **本地通话** ：不以 `0` 开头，免费。
- **无效号码** ：若号码以 `0` 或 `00` 开头，但未在费率表中找到匹配的代码，或用户号码长度不符合规定，则视为 `Unknown`，费用为 $-1.00$。

### 输出格式

输出每行包含：
- 拨打的号码（左对齐，宽度 $16$）
- 地区名称
- 用户号码
- 通话时长（右对齐，宽度 $5$）
- 每分钟费用（右对齐，宽度 $6$，保留两位小数）
- 总费用（右对齐，宽度 $7$，保留两位小数）

若为未知号码，则每分钟费用处留空。

---

## 解题思路

### 步骤分解

1. **解析费率表**  
   将每行的代码、地区名称、费率分别提取出来，存储在一个结构体数组中。

2. **处理通话记录**  
   对每条记录：
   - 提取号码和时长。
   - 根据号码前缀判断类型：
     - 若以 `00` 开头，尝试匹配国际代码。
     - 若以 `0` 开头（非 `00`），尝试匹配国内区号。
     - 否则为本地通话。
   - 匹配时需检查用户号码长度是否符合规定。
   - 若未匹配成功，则为 `Unknown`。

3. **计算费用**  
   费率以美分存储，计算时需除以 $100.0$ 转换为美元。

4. **格式化输出**  
   使用 `cout` 的格式化输出功能（如 `setw`、`setprecision`）控制对齐与精度。

### 关键点

- 匹配代码时使用 `find` 判断前缀是否一致。
- 用户号码长度需在匹配后验证。
- 输出格式需严格对齐，包括空格数量。

---

## 代码实现

```cpp
// Telephone Tangles
// UVa ID: 139
// Verdict: Accepted
// Submission Date: 2016-01-19
// UVa Run Time: 0.085s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
struct price {
    string code;
    string area;
    int cost;
};

int main() {
    string line;
    vector < price > prices;
    // 处理第一部分输入
    while (getline(cin, line), line.find("000000") != 0) {        
        string code, area, fee;
        int index = 0;
        while (index < line.length() && isdigit(line[index]))
            code += line[index++];
        // 跳过空格，直到 $ 都属于国家或地区名称   
        index++;  
        while (index < line.length() && line[index] != '$')
            area += line[index++];
        // 跳过 $
        index++;  
        while (index < line.length()) {
            if (isdigit(line[index]))
                fee += line[index];
            index++;
        }
        // cout << code << " "  << area << " " << fee << endl;
        prices.push_back((price) { code, area, stoi(fee) });
    }
    // 处理第二部分输入并输出
    while (getline(cin, line), line != "#") {
        int index = 0;
        string calledNumber, duration;
        while (index < line.length() && isdigit(line[index]))
            calledNumber += line[index++];
        while (index < line.length() && isblank(line[index]))
            index++;
        while (index < line.length() && isdigit(line[index]))
            duration += line[index++];
        string area, subscriber;
        double cost, totalCost;
        bool unknown = true;
        for (int i = 0; i < prices.size(); i++) {
            if (calledNumber.find(prices[i].code) == 0) {
                area = prices[i].area;
                subscriber = calledNumber.substr(prices[i].code.length());
                if (calledNumber.find("00") == 0) {
                    if (subscriber.length() < 4 || subscriber.length() > 10)
                        continue;
                } else if (calledNumber.find("0") == 0) {
                    if (subscriber.length() < 4 || subscriber.length() > 7)
                        continue;
                }
                cost = prices[i].cost / 100.00;
                totalCost = stoi(duration) * cost;
                unknown = false;
                break;
            }
        }
        if (unknown) {
            if (calledNumber.find("00") == 0 || calledNumber.find("0") == 0) {
                area = "Unknown";
                subscriber.clear();
                totalCost = -1.0;
            } else {
                area = "Local";
                subscriber = calledNumber;
                cost = 0.00;
                totalCost = 0.0;
                unknown = false;     
            }
        }
        cout.setf(ios::fixed);
        cout << setw(16) << left << calledNumber;
        cout << area;
        cout << string(35 - area.length() - subscriber.length(), ' ');
        cout << subscriber;
        cout << setw(5) << right << duration;
        if (unknown) cout << string(6, ' ');
        else cout << setw(6) << right << setprecision(2) << cost;
        cout << setw(7) << right << setprecision(2) << totalCost;
        cout << endl;
    }
    return 0;
}
```

---

## 总结

本题主要考察**字符串处理**与**格式化输出**能力，同时需要注意细节处理（如号码长度验证、费用单位转换）。通过合理设计数据结构并逐步匹配，即可正确计算并输出每通电话的费用。

---
