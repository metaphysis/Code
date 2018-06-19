// Calendar Game
// UVa ID: 1557
// Verdict: Accepted
// Submission Date: 2018-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[2002][13][32];

struct date
{
    int year, month, day;
    date (int year = 0, int month = 0, int day = 0): year(year), month(month), day(day) {}
} dt;

bool isLeapYear(int year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

bool isBiggerMonth(int month)
{
    return month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12;
}

bool isValid()
{
    return dt.year < 2001 || (dt.year == 2001 && dt.month < 11) || (dt.year == 2001 && dt.month == 11 && dt.day <= 4);
}

bool getNextDay(int year, int month, int day)
{
    if (day == 31)
    {
        if (month == 12) dt = date(year + 1, 1, 1);
        else dt = date(year, month + 1, 1);
    }
    else if (day == 30)
    {
        if (isBiggerMonth(month)) dt = date(year, month, day + 1);
        else dt = date(year, month + 1, 1);
    }
    else if (day == 29)
    {
        if (month == 2) dt = date(year, month + 1, 1);
        else dt = date(year, month, day + 1);
    }
    else if (day == 28)
    {
        if (month == 2)
        {
            if (isLeapYear(year)) dt = date(year, month, day + 1);
            else dt = date(year, month + 1, 1);
        }
        else
            dt = date(year, month, day + 1);
    }
    else
        dt = date(year, month, day + 1);
    
    return isValid();
}

bool getNextMonthDay(int year, int month, int day)
{
    dt = date(2002, 12, 31);
    if (month == 12) dt = date(year + 1, 1, day);
    else if (month == 1)
    {
        if (day <= 28) dt = date(year, month + 1, day);
        if (day == 29 && isLeapYear(year)) dt = date(year, month + 1, day);
    }
    else
    {
        if (isBiggerMonth(month))
        {
            if (day <= 30) dt = date(year, month + 1, day);
        }
        else
        {
            dt = date(year, month + 1, day);
        }
        
    }
    return isValid();
}

int dfs(int year, int month, int day)
{
    if (~cache[year][month][day]) return cache[year][month][day];
    if (getNextMonthDay(year, month, day))
    {
        if (!dfs(dt.year, dt.month, dt.day)) return cache[year][month][day] = 1;
    }
    if (getNextDay(year, month, day))
    {
        if (!dfs(dt.year, dt.month, dt.day)) return cache[year][month][day] = 1;
    }
    return cache[year][month][day] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    cache[2001][11][4] = 0;
    int cases, year, month, day;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> year >> month >> day;
        cout << (dfs(year, month, day) ? "YES" : "NO") << '\n';
    }

    return 0;
}
