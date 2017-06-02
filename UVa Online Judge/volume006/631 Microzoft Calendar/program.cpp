// Microzoft Calendar
// UVa ID: 631
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int daysOfYear = 365;
const int daysOf4Years = daysOfYear * 4 + 1;
const int daysOf100Years = daysOf4Years * 25 - 1;
const int daysOf400Years = daysOf4Years * 100 - 3;
const int daysBeforeMonth[2][13] = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
    {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
};

bool isLeapYear(int yyyy)
{
    return ((yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0);
}

// 以公元元年1月1日为基准日期，将公元元年以后的日期转换为天数。
int toDays(int yyyy, int mm, int dd)
{
    int days = 0, year = yyyy - 1;

    days += (year / 400) * daysOf400Years, year %= 400;
    days += (year / 100) * daysOf100Years, year %= 100;
    days += (year / 4) * daysOf4Years, year %= 4;
    days += year * daysOfYear;
    days += daysBeforeMonth[isLeapYear(yyyy)][mm - 1] + dd;

    return days;
};

// 将天数转换为日期。
void toDate(int dayOfStart, int dayOfCurrent)
{
    int yyyy = 1, dayDiff = abs(dayOfCurrent - dayOfStart);

    // calculate the year and elpased days since the start of a year.
    if (dayOfCurrent >= dayOfStart)
    {
        dayDiff += 1;
        
        while (true)
        {
            int dayOfYear = isLeapYear(yyyy) ? 366 : 365;
            if (dayDiff > dayOfYear)
            {
                yyyy += 1;
                dayDiff -= dayOfYear;
            }
            else break;
        }

        dayDiff -= 1;
    }
    else
    {
        while (true)
        {
            int dayOfYear = isLeapYear(yyyy) ? 366 : 365;
            if (dayDiff > dayOfYear)
            {
                yyyy += 1;
                dayDiff -= dayOfYear;
            }
            else break;
        }
        
        int dayOfYear = isLeapYear(yyyy) ? 366 : 365;
        dayDiff = dayOfYear - dayDiff;
    }

    // output.
    int dayToYearStart = dayDiff;
    
    string monthNames[] = {"Sun", "Water", "Forest", "Mountains", "Money"};
    string weekNames[] = {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"};

    if (dayToYearStart > 359)
        cout << "Feast " << (dayToYearStart - 359);
    else
    {
        if (dayToYearStart > 180) cout << "Bates"; else cout << "Gill";
        dayToYearStart %= 180;
        cout << '-' << monthNames[dayToYearStart / 36];
        dayToYearStart %= 36;
        cout << '-' << weekNames[dayToYearStart / 6];
        dayToYearStart %= 6;
        cout << '-' << (dayToYearStart + 1);
    }

    cout << '-' << yyyy;
    if (dayOfCurrent < dayOfStart) cout << "bd";
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string date;
    
    int dayOfStart = toDays(1998, 6, 25);
    
    while (getline(cin, date), date != "END")
    {
        if (date.find("Bates") != date.npos ||
            date.find("Gill") != date.npos ||
            date.find("Feast") != date.npos)
        {
            cout << "Enter date in old format\n";
            continue;
        }
        
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        
        int dayOfCurrent = toDays(year, month, day);
        
        toDate(dayOfStart, dayOfCurrent);
    }
    
    return 0;
}
