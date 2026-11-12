[UVa 158 Calendar](https://blog.csdn.net/metaphysis/article/details/158611356)

## 题目分析

本题要求实现一个日历提醒服务程序。我们需要处理两类输入：纪念日事件（包含日期、重要程度和事件描述）和查询日期。对于每个查询日期，程序需要输出该日期及未来若干天内需要提醒的所有事件，并根据事件的紧急程度用不同数量的星号标记。

### 关键点理解

1. **时间范围** ：年份范围是 $1901$ 到 $1999$ 年，在这个区间内，能被 $4$ 整除的年份都是闰年（符合公历规则），因此 $2$ 月有 $29$ 天。

2. **事件优先级** ：每个事件有一个优先级 $P$（$1 \le P \le 7$），表示应该提前 $P$ 天开始提醒。例如 $P = 5$ 表示从事件发生前 $5$ 天就开始在输出中显示该事件。

3. **提醒规则** ：
   - 如果事件发生在今天，标记为 $\texttt{*TODAY*}$
   - 如果事件发生在明天，显示 $P$ 个星号
   - 如果事件发生在后天，显示 $P-1$ 个星号
   - 以此类推，直到事件发生当天为止

4. **排序规则** ：
   - 首先按事件距离查询日期的天数排序
   - 同一天的事件按星号数量（即优先级）降序排列
   - 如果星号数量相同，按输入顺序排列

5. **周年纪念处理** ：每个 $\texttt{A}$ 类型的事件都是周年纪念，需要在当前年份和下一年的同一天都提醒。这是因为有些纪念日（如生日）每年都会发生。

## 解题思路

### 1. 日期转换

为了便于计算两个日期之间的天数差，我们需要将日期转换为从某个固定起点开始的天数。这里选择从 $1901$ 年 $1$ 月 $1$ 日作为第 $0$ 天。

日期转换函数 $\texttt{dateToDays}$ 的实现：
- 先累加从 $1901$ 年到目标年份前一年的所有天数
- 再累加目标年份中从 $1$ 月到目标月份前一月的所有天数
- 最后加上目标日期的天数减 $1$（因为 $1$ 月 $1$ 日是第 $0$ 天）

### 2. 数据结构设计

使用结构体存储每个事件：
```cpp
struct event {
    int index;        // 输入顺序索引
    int year;         // 年份
    int month;        // 月份
    int day;          // 日期
    int priority;     // 优先级 P
    int days;         // 转换为天数的值
    string description; // 事件描述
};
```

### 3. 事件处理

对于 $\texttt{A}$ 类型的事件：
- 读取日期、优先级和描述
- 计算当前年份的日期天数，存入 $\texttt{calendar}$ 向量
- 计算下一年的日期天数（年份加 $1$），也存入 $\texttt{calendar}$ 向量

这样就能同时处理今年的纪念日和明年的纪念日。

### 4. 排序算法

排序是比较关键的部分。我们需要考虑三种情况：

1. **事件发生在今天**：无论优先级如何，都应该排在所有未来事件的前面
2. **未来事件**：按 $\texttt{priority - days}$ 降序排序（因为 $\texttt{days}$ 是绝对天数，差值越大表示离事件越近）
3. **过去事件**：不输出，直接跳过

排序规则的核心代码：
```cpp
bool operator<(event x, event y) {
    if (x.days == y.days) {
        if (x.days == todayDays)
            return x.index < y.index;
        else
            return x.priority > y.priority;
    }
    else if (x.days != todayDays && y.days != todayDays) {
        if ((x.priority - x.days) != (y.priority - y.days))
            return (x.priority - x.days) > (y.priority - y.days);
        else
            return x.days < y.days;
    }
    else
        return x.days < y.days;
}
```

### 5. 输出处理

对于每个查询日期：
- 输出 $\texttt{Today is:}$ 加上日期
- 遍历排序后的事件列表
- 计算 $\texttt{remain = event.days - todayDays}$
- 如果 $\texttt{remain < 0}$（事件已过）或 $\texttt{remain > event.priority}$（还没到提醒时间），跳过
- 否则按规则输出：
  - $\texttt{remain == 0}$ 输出 $\texttt{*TODAY*}$
  - 否则输出 $\texttt{priority - remain + 1}$ 个星号

### 6. 注意事项

- 输入描述字符串前可能有空格，需要使用 $\texttt{trimLeft}$ 去除
- 每个查询块之间留一个空行
- 输出格式要求严格：日期右对齐，宽度 $3$；星号左对齐，宽度 $7$

## 实现细节

1. **月份天数数组** ：
```cpp
int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
```

2. **闰年判断** ：由于年份范围固定，只需判断 $\texttt{year \% 4 == 0}$ 即可

3. **字符串处理** ：使用 $\texttt{getline}$ 读取描述，然后去除前导空格

## 样例验证

输入：
```
1993
A 23 12 5 Partner's birthday
A 25 12 7 Christmas
A 20 12 1 Unspecified Anniversary
D 20 12
#
```

输出：
```
Today is: 20 12
 20 12 *TODAY* Unspecified Anniversary
 23 12 ***   Partner's birthday
 25 12 ***   Christmas
```

分析输出：
- $12$ 月 $20$ 日：$\texttt{Unspecified Anniversary}$ 正好在今天，标记为 $\texttt{*TODAY*}$
- $12$ 月 $23$ 日：$\texttt{Partner's birthday}$ 在 $3$ 天后，优先级 $P=5$，所以显示 $5-3+1=3$ 个星号
- $12$ 月 $25$ 日：$\texttt{Christmas}$ 在 $5$ 天后，优先级 $P=7$，所以显示 $7-5+1=3$ 个星号

## 完整代码

```cpp
// Calendar
// UVa ID: 158
// Verdict: Accepted
// Submission Date: 2016-02-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct event
{
    int index, year, month, day, priority, days;
    string description;
};

vector<event> calendar;
int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int todayDays;

int dateToDays(int year, int month, int day)
{
    int days = 0;
    for (int i = 1901; i <= year - 1; i++)
        days += (i % 4 == 0 ? 366 : 365);
    for (int i = 1; i <= month - 1; i++)
        days += daysInMonth[i - 1] + (i == 2 && year % 4 == 0 ? 1 : 0);
    days += day - 1;
    return days;
}

bool operator<(event x, event y)
{
    if (x.days == y.days)
    {
        if (x.days == todayDays)
            return x.index < y.index;
        else
            return x.priority > y.priority;
    }
    else if (x.days != todayDays && y.days != todayDays)
    {
        if ((x.priority - x.days) != (y.priority - y.days))
            return (x.priority - x.days) > (y.priority - y.days);
        else
            return x.days < y.days;
    }
    else
        return x.days < y.days;
}

void showCalendar(int year, int month, int day)
{
    todayDays = dateToDays(year, month, day);
            
    sort(calendar.begin(), calendar.end());
    
    cout << "Today is:" << right << setw(3) << day;
    cout << right << setw(3) << month << endl;
    
    for (int i = 0; i < calendar.size(); i++)
    {
        int remain = calendar[i].days - todayDays;
        if (remain < 0 || remain > calendar[i].priority)
            continue;
        
        cout << right << setw(3) << calendar[i].day;
        cout << right << setw(3) << calendar[i].month << " ";
        if (remain == 0)
            cout << "*TODAY*";
        else
        {
            string stars = string(calendar[i].priority - remain + 1, '*');
            cout << setw(7) << left << stars;
        }
        cout << " " << calendar[i].description << endl;
    }
}

string trimLeft(string description)
{
    while (description.length() > 0)
    {
        if (description[0] == ' ' || description[0] == '\t')
            description.erase(description.begin());
        else
            break;
    }
    return description;
}

int main(int argc, char* argv[])
{   
    string line, category, description;
    int year, month, day, priority, index = 1;
    int cases = 0;
    
    cin >> year;
    while (cin >> category, category != "#")
    {
        if (category == "A")
        {
            cin >> day >> month >> priority;
            getline(cin, description);
            calendar.push_back(
                (event){index++, year, month, day, priority, 
                dateToDays(year, month, day), trimLeft(description)});
            calendar.push_back(
                (event){index++, year + 1, month, day, priority, 
                dateToDays(year + 1, month, day), trimLeft(description)});
            continue;
        }
        if (cases++) cout << '\n';
        cin >> day >> month;
        showCalendar(year, month, day);
    }
    
	return 0;
}
```

## 总结

本题的核心是日期转换和复杂的排序规则。通过将日期统一转换为天数，可以简化日期差的计算。排序时需要仔细考虑多种情况：今天的事件、未来事件、优先级、天数差值等。输出格式要求严格，需要注意对齐和星号数量计算。

解题的关键在于理解提醒规则：事件提前 $P$ 天开始提醒，距离事件越近，显示的星号越多，最多 $P$ 个，最少 $1$ 个。这个规则通过 $\texttt{priority - remain + 1}$ 实现。
