[UVa 150 Double Time](https://blog.csdn.net/metaphysis/article/details/157510544)

## 题目描述

儒略·恺撒于公元前 $45$ 年采用了一种标准历法，每年 $365$ 天，每四年增加一天（$2$ 月 $29$ 日）。但这一历法并不完全准确，季节的开始时间在一年中逐渐偏移。$1582$ 年，教皇格里高利十三世颁布了一种新历法（格里高利历），规定世纪年只有能被 $400$ 整除才是闰年。同时，为了将历法与季节重新对齐，当年进行了一次调整：$1582$ 年 $10$ 月 $4$ 日（星期四）之后直接是 $10$ 月 $15$ 日（星期五）。天主教国家立即采用了这一新历法，而英国和美国直到 $1752$ 年才改用（$1752$ 年 $9$ 月 $2$ 日星期三之后是 $9$ 月 $14$ 日星期四）。因此，有一段很长的时期，历史记录使用了两种不同的历法。

本题要求编写程序，读入一个日期，判断它是旧式（儒略历）还是新式（格里高利历），并将其转换为另一种历法的日期。

## 输入格式

输入由多行组成，每行包含一个 `星期 日期 月份 年份` 的格式，例如 `Friday 25 December 1992`。日期范围在 $1600$ 年 $1$ 月 $1$ 日至 $2099$ 年 $12$ 月 $31$ 日之间，但转换后的日期可能超出此范围。所有星期和月份的名称首字母大写，其余小写。输入以一行仅包含 `#` 的行结束。

## 输出格式

输出对应于输入的每一行，输出转换后的日期，格式与输入相同，但旧式日期在日期数字后紧跟一个星号（`*`），中间无空格。

## 样例输入

```
Saturday 29 August 1992
Saturday 16 August 1992
Wednesday 19 December 1991
Monday 1 January 1900
#
```

## 样例输出

```
Saturday 16* August 1992
Saturday 29 August 1992
Wednesday 1 January 1992
Monday 20* December 1899
```

## 题目分析

本题的核心在于历法转换与星期匹配。我们需要判断一个给定的日期（带有星期信息）是属于儒略历还是格里高利历，然后将其转换为另一种历法下的日期，并保持星期一致。

### 关键点

1. **闰年规则不同**：
   - 儒略历：年份能被 $4$ 整除即为闰年。
   - 格里高利历：年份能被 $400$ 整除，或能被 $4$ 整除但不能被 $100$ 整除。

2. **日期调整**：
   - $1582$ 年 $10$ 月 $4$ 日（儒略历）之后直接跳到 $10$ 月 $15$ 日（格里高利历）。
   - $1752$ 年 $9$ 月 $2$ 日（儒略历）之后直接跳到 $9$ 月 $14$ 日（格里高利历）。

3. **星期匹配**：
   - 输入中给出了星期，我们可以利用星期信息来判断该日期原本属于哪种历法。如果日期在儒略历下计算出的星期与给定星期一致，则它是旧式日期；否则是新式日期。

### 解题思路

1. **统一基准日期**：
   - 选择一个共同的基准日期（例如 $1583$ 年 $1$ 月 $1$ 日），计算给定日期距离该基准的天数。
   - 分别按照儒略历和格里高利历的规则计算天数。

2. **判断历法类型**：
   - 根据基准日期的星期（已知为星期一），分别计算出两种历法下给定日期对应的星期。
   - 如果与输入星期一致，则该日期属于该历法。

3. **进行转换**：
   - 如果日期是儒略历，则将其转换为格里高利历；反之亦然。
   - 转换时，根据两种历法的天数差调整日期。

4. **输出格式**：
   - 输出转换后的日期，如果是旧式（儒略历）则在日期后加 `*`。

### 算法步骤

1. 读入一行日期，解析星期、日、月、年。
2. 计算该日期在儒略历和格里高利历下距离基准日期的天数。
3. 根据星期匹配判断原历法。
4. 根据原历法，使用另一种历法的规则重新计算日期。
5. 输出转换结果，旧式日期后加 `*`。

## 代码实现

```cpp
// Double Time
// UVa ID: 150
// Verdict: Accepted
// Submission Date: 2016-01-30
// UVa Run Time: 0.019s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct date {
    int dayOfWeek, dayOfMonth, month, year;
    bool isOldFormat;
};

const string months[12] = { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December"
};

const string weekdays[7] = { "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
};

const int daysInMonth[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isLeapYear(int year, bool useOldFormat) {
    return (useOldFormat ? year % 4 == 0 : (year % 400 == 0 || (year % 4 == 0
                && year % 100 != 0))) ? 1 : 0;
}

void addDays(date & startDate, int days, bool useOldFormat) {
    while (days > 0) {
        int leapYear = isLeapYear(startDate.year, useOldFormat);
        // 注意判断条件
        if (leapYear && days > 366) {
            days -= 366;
            startDate.year += 1;
        } else if (!leapYear && days > 365) {
            days -= 365;
            startDate.year += 1;
        } else {
            for (int i = 0; i < 12; i++)
                if (days > daysInMonth[leapYear][i]) {
                    days -= daysInMonth[leapYear][i];
                    startDate.month += 1;
                } else break;
            startDate.dayOfMonth += days;
            days = 0;
        }
    }
}

int getDays(date aDate, bool useOldFormat) {
    int days = useOldFormat ? 88 : 78;
    for (int i = 1583; i < aDate.year; i++) days += (isLeapYear(i, useOldFormat) ? 366 : 365);
    for (int i = 0; i < aDate.month; i++) days += daysInMonth[isLeapYear(aDate.year, useOldFormat)][i];
    days += aDate.dayOfMonth;
    return days;
}

void convertToOtherDate(date aDate) {
    // 计算新旧两种日期格式两个日期之间的相隔天数，分别从旧的基准日期和
    // 新的基准日期计算间隔天数，统一调整为从 1583-01-01 开始计算天数。
    int oldDays = getDays(aDate, true);
    int newDays = getDays(aDate, false);
    // 根据星期几是否吻合来判断日期格式并转换
    aDate.dayOfMonth = 0;
    aDate.month = 0;
    aDate.year = 1583;
    aDate.isOldFormat = (3 + oldDays) % 7 == aDate.dayOfWeek;
    if (aDate.isOldFormat) {
        aDate.dayOfWeek = (3 + oldDays) % 7;
        oldDays -= 78;
        addDays(aDate, oldDays, false);
    } else {
        aDate.dayOfWeek = (3 + newDays) % 7;
        newDays -= 88;
        addDays(aDate, newDays, true);
    }
    aDate.isOldFormat = !aDate.isOldFormat;
    cout << weekdays[aDate.dayOfWeek] << " " << aDate.dayOfMonth;
    if (aDate.isOldFormat) cout << "*";
    cout << " " << months[aDate.month] << " " << aDate.year << "\n";
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);
    string weekDayText, monthText;
    date aDate;
    while (cin >> weekDayText, weekDayText != "#") {
        cin >> aDate.dayOfMonth >> monthText >> aDate.year;
        aDate.dayOfWeek = find(weekdays, weekdays + 7, weekDayText) - weekdays;
        aDate.month = find(months, months + 12, monthText) - months;
        convertToOtherDate(aDate);
    }
    return 0;
}
```

## 总结

本题通过历法转换与星期匹配，考查了对日期处理的基本能力。关键在于理解两种历法的闰年规则和历史上的日期调整，以及如何通过星期信息判断原历法类型。算法上，我们采用统一的基准日期，分别计算天数，再根据星期匹配进行转换。代码中注意处理闰年和月份天数，确保转换的准确性。
