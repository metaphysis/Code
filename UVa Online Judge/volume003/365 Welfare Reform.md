[UVa 365 Welfare Reform](https://blog.csdn.net/metaphysis/article/details/161611349)


## 题目描述

联邦政府最近通过了一项改革，要求所有福利领取者必须工作才能获得福利。根据该规定，父母将为 $13$ 岁以下的儿童获得 $\texttt{childcare}$ 补贴（即截至今年 $9$ 月 $1$ 日，儿童必须小于 $13$ 岁）。

父母必须支付的 $\texttt{childcare}$ 部分（称为 $\texttt{parent fee}$）基于家庭收入和儿童数量。下图展示了如何确定 $\texttt{parent fee}$ 的示例。

从该表中，根据家庭规模和收入确定 $\texttt{base parent fee}$。$\texttt{base parent fee}$ 适用于最小的 $13$ 岁以下儿童；其他 $13$ 岁以下儿童的费用是 $\texttt{base parent fee}$ 的一半。例如，一个有 $4$ 个孩子的家庭，收入为 $8000$，$\texttt{base parent fee}$ 为 $1.60$。父母将为最小的孩子支付 $1.60$，为其他 $13$ 岁以下的孩子支付 $0.80$。注意：只有 $13$ 岁以下的孩子才能获得 $\texttt{childcare}$ 补贴，因此 $13$ 岁及以上儿童没有 $\texttt{parent fee}$。

任务：计算每个孩子的 $\texttt{parent fee}$。

### 输入格式

输入文件由两部分组成：
- **第一部分**：前 $12$ 行包含 $\texttt{parent fee}$ 表。每行包含一个非负实数（$\texttt{parent fee}$）和 $10$ 个非负整数（对应有 $1$ 到 $10$ 个孩子的家庭的收入阈值），由一个或多个空格分隔。
- **第二部分**：家庭记录从下一行开始。第一行包含一个正整数 $n$，表示要处理的家庭数量。每个家庭记录以父母姓名（$1$ 到 $20$ 个字符的字符串）开始（单独一行）。下一行包含整数 $k$（儿童数量，$0 \le k \le 10$）和整数 $s$（家庭收入）。接下来 $k$ 行每行包含一个孩子的生日，格式为 `mm dd yy`（月、日、年）。所有生日有效，没有孩子超过 $25$ 岁，同一家庭中孩子生日不重复。

假设输入文件的第一行包含 $10$ 个 $0$ 作为收入（如样例所示）。

### 输出格式

对于每个孩子，输出父母姓名、孩子年龄（截至 $1996$ 年 $9$ 月 $1$ 日）和 $\texttt{parent fee}$。孩子按输入顺序列出。每个家庭输出后跟一个空行。格式如样例输出所示。

### 样例输入

```
0.80 0 0 0 0 0 0 0 0 0 0
1.60 7650 11479 15305 19131 22957 26783 30609 34435 38261 42087
2.40 11479 19131 26783 34435 42087 49739 57391 65043 72695 80347
3.20 15305 26783 38261 49739 61217 72695 84173 95651 107129 118607
4.00 19131 34435 49739 65043 80347 95651 110955 126259 141563 156867
4.80 22957 42087 61217 80347 99477 118607 137737 156867 175997 195127
5.60 26783 49739 72695 95651 118607 141563 164519 187475 210431 233387
6.40 30609 57391 84173 110955 137737 164519 191301 218083 244865 271647
7.20 34435 65043 95651 126259 156867 187475 218083 248691 279299 309907
8.00 38261 72695 107129 141563 175997 210431 244865 279299 313733 348167
8.80 42087 80347 118607 156867 195127 233387 271647 309907 348167 386427
9.60 45913 87999 130085 172171 214257 256343 298429 340515 382601 424687
2
Smith
4 28000
1 1 92
3 5 94
5 6 96
9 12 95
Jones
2 20000
10 5 95
4 8 96
```

### 样例输出

```
Smith 4 1.60
Smith 2 0.80
Smith 0 0.80
Smith 0 0.80

Jones 0 1.00
Jones 0 0.50
```

---

## 题目分析

### 问题的本质

这是一个**数据查询与计算**问题。需要：
1. 根据家庭规模和收入，从表中查找对应的 $\texttt{base parent fee}$
2. 计算每个孩子在 $1996$ 年 $9$ 月 $1$ 日的年龄
3. 只有 $13$ 岁以下的孩子需要支付费用，其中最小的孩子支付 $\texttt{base fee}$，其他孩子支付一半

### 表结构

前 $12$ 行定义了 $12$ 个收入档次。第 $j$ 行（$1 \le j \le 12$）的第 $i$ 个整数（$1 \le i \le 10$）表示有 $i$ 个孩子的家庭的第 $j$ 档收入阈值。

- 第 $1$ 行是 $\texttt{base parent fee}$ = $0.80$ 的档位，收入阈值为 $0$（所有人）
- 后续行定义了更高的收入档次

规则：给定收入 $s$，找到最大的 $j$ 使得 `salary[number][j] <= s`，则 $\texttt{base fee}$ = `fee[j]`。

### 年龄计算

截止日期：$1996$ 年 $9$ 月 $1$ 日。

年龄计算公式：
- 如果出生年份 $> 1996$：不可能（题目保证不会）
- 如果出生年份 $= 1996$：年龄 $0$（$9$ 月 $1$ 日之前出生的可能 $0$ 岁？实际上月份 $<9$ 或 $=9$ 且日期 $\le 1$ 时年龄 $0$）
- 否则：年龄 $= 1996 - year$，如果出生日期在 $9$ 月 $1$ 日之后，则减 $1$（因为还没过生日）

```cpp
void setAge() {
    if (year == 96) age = 0;
    else {
        age = 96 - year;
        if (month > 9 || (month == 9 && day > 1))
            age--;
    }
}
```

### 找最小的孩子

年龄最小的孩子是指出生日期最晚的孩子（即年龄最小）。通过比较生日来找到最晚的出生日期。

---
## 参考代码

```cpp
// Welfare Reform
// UVa ID: 365
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.170s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct child
{
    int month, day, year, age;
    
    // 计算截至 1996 年 9 月 1 日的年龄
    void setAge()
    {
        if (year == 96) 
            age = 0;
        else
        {
            age = 96 - year;
            // 如果生日在 9 月 1 日之后，今年还没过生日
            if (month > 9 || (month == 9 && day > 1))
                age--;
        }
    }
};

int salary[20][20];  // salary[儿童数][档次] = 收入阈值
double fee[20];      // 每档的 $\texttt{base parent fee}$

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    // 读取 parent fee 表（12 行）
    for (int i = 1; i <= 12; i++)
    {
        cin >> fee[i];
        for (int j = 1; j <= 10; j++)
            cin >> salary[j][i];
    }
    
    int n, number, incomes;
    string family;
    
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> family >> number >> incomes;

        if (number > 0)
        {
            vector<child> children(number);
            
            // 找到最年轻的孩子（出生日期最晚）
            int youngest = -1; 
            for (int j = 0; j < number; j++)
            {
                cin >> children[j].month >> children[j].day >> children[j].year;
                children[j].setAge();

                if (youngest == -1 || 
                    children[j].year > children[youngest].year ||
                    (children[j].year == children[youngest].year && children[j].month > children[youngest].month) ||
                    (children[j].year == children[youngest].year && children[j].month == children[youngest].month && children[j].day > children[youngest].day))
                    youngest = j;
            }
            
            // 查找收入对应的档次
            int feeIndex;
            for (int k = 12; k >= 1; k--)
                if (incomes >= salary[number][k])
                {
                    feeIndex = k;
                    break;
                }

            // 输出每个孩子
            for (int k = 0; k < children.size(); k++)
            {
                cout << family << " " << children[k].age << " ";
                if (children[k].age < 13)
                {
                    if (k == youngest)
                        cout << fixed << setprecision(2) << fee[feeIndex] << endl;
                    else
                        cout << fixed << setprecision(2) << fee[feeIndex] / 2.0 << endl;
                }
                else
                    cout << "0.00" << endl;
            }
        }
        
        cout << endl;  // 每个家庭后空行
    }
    
    return 0;
}
```
