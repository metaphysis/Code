// Time
// UVa ID: 518
// Verdict: Accepted
// Submission Date: 2017-04-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int year1, month1, day1, hour1, minute1, second1;
int year2, month2, day2, hour2, minute2, second2;
long long period;
string unit;
int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


bool isLeapYear(int year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

long long getYears()
{
    long long years = 0;
    for (int i = year1 + 1; i < year2; i++) years++;
    return years;
}

long long getMonths()
{
    long long months = getYears() * 12;
    if (year1 != year2)
    {
        for (int i = month1 + 1; i <= 12; i++) months++;
        for (int i = 1; i < month2; i++) months++;
    }
    else
    {
        for (int i = month1 + 1; i < month2; i++)
            months++;
    }

    return months;
}

long long getDays()
{
    long long days = 0;
    for (int i = year1 + 1; i < year2; i++)
        days += (isLeapYear(i) ? 366 : 365);

    int start = day1 + 1;
    if (hour1 == 0 && minute1 == 0 && second1 == 0)
        start = day1;

    if (year1 != year2)
    {
        for (int i = month1 + 1; i < 13; i++)
        {
            if (i == 2) days += (isLeapYear(year1) ? 29 : 28);
            else days += daysInMonth[i];
        }
        for (int i = 1; i < month2; i++)
        {
            if (i == 2) days += (isLeapYear(year2) ? 29 : 28);
            else days += daysInMonth[i];
        }
    }
    else
    {
        for (int i = month1 + 1; i < month2; i++)
        {
            if (i == 2) days += (isLeapYear(year1) ? 29 : 28);
            else  days += daysInMonth[i];
        }
    }

    if (year1 != year2 || month1 != month2)
    {
        int totalDays = 0;
        if (month1 == 2)  totalDays = (isLeapYear(year1) ? 29 : 28);
        else totalDays = daysInMonth[month1];

        for (int i = start; i <= totalDays; i++) days++;
        for (int i = 1; i < day2; i++) days++;
    }
    else
    {
        for (int i = start; i < day2; i++)  days++;
    }

    return days;
}

long long getHours()
{
    long long hours = getDays() * 24;

    int start = hour1 + 1;
    if (minute1 == 0 && second1 == 0) start = hour1;

    if (year1 != year2 || month1 != month2 || day1 != day2)
    {
        if (hour1 != 0 || minute1 != 0 || second1 != 0)
            for (int i = start; i < 24; i++)
                hours++;

        for (int i = 0; i < hour2; i++)
            hours++;
    }
    else
    {
        for (int i = start; i < hour2; i++)
            hours++;
    }

    return hours;
}

long long getMinutes()
{
    long long minutes = getHours() * 60;

    int start = minute1 + 1;
    if (second1 == 0) start = minute1;

    if (year1 != year2 || month1 != month2 || day1 != day2 || hour1 != hour2)
    {
        if (minute1 != 0 || second1 != 0)
            for (int i = start; i < 60; i++)
                minutes++;

        for (int i = 0; i < minute2; i++)
            minutes++;
    }
    else
    {
        for (int i = start; i < minute2; i++)
            minutes++;
    }

    return minutes;
}

long long getSeconds()
{
    long long seconds = getMinutes() * 60;

    if (year1 != year2 || month1 != month2 || day1 != day2 || hour1 != hour2 || minute1 != minute2)
    {
        if (second1 != 0)
            for (int i = second1; i < 60; i++)
                seconds++;

        for (int i = 0; i < second2; i++)
            seconds++;
    }
    else
    {
        for (int i = second1; i < second2; i++)
            seconds++;
    }

    return seconds;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> year1)
    {
        cin >> month1 >> day1 >> hour1 >> minute1 >> second1;
        cin >> year2 >> month2 >> day2 >> hour2 >> minute2 >> second2;
        cin >> period >> unit;

        if (unit == "year")     cout << (getYears() / period);
        if (unit == "month")    cout << (getMonths() / period);
        if (unit == "day")      cout << (getDays() / period);
        if (unit == "hour")     cout << (getHours() / period);
        if (unit == "minute")   cout << (getMinutes() / period);
        if (unit == "second")   cout << (getSeconds() / period);

        cout << '\n';
    }

    return 0;
}
