// What Day Is It?
// UVa ID: 602
// Verdict: Accepted
// Submission Date: 2016-08-29
// UVa Run Time: 0.050s
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

int isLeapYear(int year, bool isOldFormat)
{
    return (isOldFormat ? year % 4 == 0 : (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) ? 1 : 0;
}

// 从1年1月1日开始起算天数。
int getDay(date date1)
{
    int days = 0;
    for (int i = 1; i < date1.year; i++)
        days += (isLeapYear(i, date1.isOldFormat) ? 366 : 365);
    for (int i = 1; i < date1.month; i++)
        days += daysInMonth[isLeapYear(date1.year, date1.isOldFormat)][i - 1];
    days += date1.dayOfMonth;
    return days;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); cout.sync_with_stdio(false);

    date date1;

    int day1 = getDay((date){0, 2, 9, 1752, true});
    int day2 = getDay((date){0, 14, 9, 1752, false});
    
    while (cin >> date1.month >> date1.dayOfMonth >> date1.year)
    {
        if (date1.month == 0)
            break;
            
        // special case
        bool valid = true;
        if (date1.month > 12 || date1.dayOfMonth > 31 ||
            (date1.month == 2 && date1.dayOfMonth > 29) ||
            (date1.month == 4 && date1.dayOfMonth > 30) ||
            (date1.month == 6 && date1.dayOfMonth > 30) ||
            (date1.month == 9 && date1.dayOfMonth > 30) ||
            (date1.month == 11 && date1.dayOfMonth > 30) ||
            (date1.year == 1752 && date1.month == 9 && date1.dayOfMonth >= 3 && date1.dayOfMonth <= 13))
            valid = false;
        
        // leap year
        bool leap = false;
        if (date1.year > 1752)
            leap = date1.year % 400 == 0 || (date1.year % 4 == 0 && date1.year % 100 != 0);
        else
            leap = date1.year % 4 == 0;
        if (!leap && date1.month == 2 && date1.dayOfMonth > 28)
            valid = false;
        
        if (!valid)
        {
            cout << date1.month << '/' << date1.dayOfMonth << '/' << date1.year << " is an invalid date.\n";
            continue;
        }
        
        // September 2, 1752 is a Wednesday
        // September 14, 1752 is a Thursday
        cout << months[date1.month - 1] << ' ' << date1.dayOfMonth << ", " << date1.year << " is a ";

        if (date1.year < 1752 ||
            (date1.year == 1752 && date1.month < 9) ||
            (date1.year == 1752 && date1.month == 9 && date1.dayOfMonth <= 2))
        {
            date1.isOldFormat = true;
            int day3 = getDay(date1);
            cout << weekdays[(9 - (day1 - day3) % 7) % 7];
        }
        else
        {
            date1.isOldFormat = false;
            int day3 = getDay(date1);
            cout << weekdays[(3 + day3 - day2) % 7];
        }
        cout << '\n';
    }

    return 0;
}
