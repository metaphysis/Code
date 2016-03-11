// Double Time
// UVa IDs: 150
// Verdict: Accepted
// Submission Date: 2016-01-30
// UVa Run Time: 0.019s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

struct date
{
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

int isLeapYear(int year, bool useOldFormat)
{
    return (useOldFormat ? year % 4 == 0 : (year % 400 == 0 || (year % 4 == 0
                && year % 100 != 0))) ? 1 : 0;
}

void addDays(date & startDate, int days, bool useOldFormat)
{
    while (days > 0)
    {
        int leapYear = isLeapYear(startDate.year, useOldFormat);
        
        // 注意判断条件
        if (leapYear && days > 366)
        {
            days -= 366;
            startDate.year += 1;
        }
        else if (!leapYear && days > 365)
        {
            days -= 365;
            startDate.year += 1;
        }
        else
        {
            for (int i = 0; i < 12; i++)
                if (days > daysInMonth[leapYear][i])
                {
                    days -= daysInMonth[leapYear][i];
                    startDate.month += 1;
                }
                else
                {
                    break;
                }

            startDate.dayOfMonth += days;
            days = 0;
        }
    }
}

int getDays(date aDate, bool useOldFormat)
{
    int days = useOldFormat ? 88 : 78;
    for (int i = 1583; i < aDate.year; i++)
        days += (isLeapYear(i, useOldFormat) ? 366 : 365);
    for (int i = 0; i < aDate.month; i++)
        days += daysInMonth[isLeapYear(aDate.year, useOldFormat)][i];
    days += aDate.dayOfMonth;
    return days;
}

void convertToOtherDate(date aDate)
{
    // 计算新旧两种日期格式两个日期之间的相隔天数，分别从旧的基准日期和
    // 新的基准日期计算间隔天数，统一调整为从 1583-01-01 开始计算天数。
    int oldDays = getDays(aDate, true);
    int newDays = getDays(aDate, false);

    // 根据星期几是否吻合来判断日期格式并转换
    aDate.dayOfMonth = 0;
    aDate.month = 0;
    aDate.year = 1583;
    aDate.isOldFormat = (3 + oldDays) % 7 == aDate.dayOfWeek;
    if (aDate.isOldFormat)
    {
        aDate.dayOfWeek = (3 + oldDays) % 7;
        oldDays -= 78;
        addDays(aDate, oldDays, false);
    }
    else
    {
        aDate.dayOfWeek = (3 + newDays) % 7;
        newDays -= 88;
        addDays(aDate, newDays, true);
    }
    aDate.isOldFormat = !aDate.isOldFormat;

    cout << weekdays[aDate.dayOfWeek] << " " << aDate.dayOfMonth;
    if (aDate.isOldFormat)
        cout << "*";
    cout << " " << months[aDate.month] << " " << aDate.year << "\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);

    string weekDayText, monthText;
    date aDate;
    while (cin >> weekDayText, weekDayText != "#")
    {
        cin >> aDate.dayOfMonth >> monthText >> aDate.year;
        aDate.dayOfWeek = find(weekdays, weekdays + 7, weekDayText) - weekdays;
        aDate.month = find(months, months + 12, monthText) - months;

        convertToOtherDate(aDate);
    }

    return 0;
}
