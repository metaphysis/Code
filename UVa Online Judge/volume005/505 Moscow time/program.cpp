// Moscow time
// UVa ID: 505
// Verdict: Accepted
// Submission Date: 2017-04-24
// UVa Run Time: 0.000s
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

string dayName[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
string monthName[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

string sDayOfWeek, sDayOfMonth, sMonth, sYear, sTime, sTimezone;
int dayOfWeek, dayOfMonth, month, year, hour, minute, second, diffMinute;

void addDay(int day)
{
    dayOfWeek = (dayOfWeek + day + 7) % 7;
    
    bool isLeapYear = (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
    if (day == 1)
    {
        if (month == 1 && dayOfMonth == 29)
        {
            dayOfMonth = 1;
            month = 2;
        }
        else if (month == 1 && dayOfMonth == 28)
        {
            if (isLeapYear)
            {
                dayOfMonth = 29;
            }
            else
            {
                dayOfMonth = 1;
                month = 2;
            }
        }
        else if (month == 11 && dayOfMonth == 31)
        {
            month = 0;
            dayOfMonth = 1;
            year += 1;
        }
        else if (dayOfMonth == 31 || (dayOfMonth == 30 && (month == 3 || month == 5 || month == 8 || month == 10)))
        {
            dayOfMonth = 1;
            month += 1;
        }
        else
        {
            dayOfMonth += 1;
        }
    }
    else
    {
        if (dayOfMonth == 1)
        {
            if (month == 0)
            {
                month = 11;
                dayOfMonth = 31;
                year -= 1;
            }
            else if (month == 2)
            {
                if (isLeapYear)
                    dayOfMonth = 29;
                else
                    dayOfMonth = 28;
                month = 1;
            }
            else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)
            {
                dayOfMonth = 31;
                month -= 1;
            }
            else if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                dayOfMonth = 30;
                month -= 1;
            }
        }
        else
        {
            dayOfMonth -= 1;
        }
    }
}

// format: SUN, 03 DEC 1996 09:10:35 GMT
void parse(string line)
{
    istringstream iss(line);
    iss >> sDayOfWeek >> sDayOfMonth >> sMonth >> sYear >> sTime >> sTimezone;
    
    sDayOfWeek.pop_back();
    dayOfWeek = find(dayName, dayName + 7, sDayOfWeek) - dayName;
    //cout << sDayOfWeek << ' ' << dayName[dayOfWeek] << '\n';
    
    dayOfMonth = stoi(sDayOfMonth);
    //cout << sDayOfMonth << ' ' << dayOfMonth << '\n';
    
    month = find(monthName, monthName + 12, sMonth) - monthName;
    //cout << sMonth << ' ' << monthName[month] << '\n';
    
    year = stoi(sYear);
    if (sYear.length() == 2) year += 1900;
    //cout << sYear << ' ' << setfill('0') << setw(4) << year << '\n';
    
    hour = stoi(sTime.substr(0, 2));
    minute = stoi(sTime.substr(3, 2));
    second = stoi(sTime.substr(6, 2));
    
    if (sTimezone == "UT" || sTimezone == "GMT") diffMinute = 180;
    else if (sTimezone == "EDT") diffMinute = 420;
    else if (sTimezone == "CDT") diffMinute = 480;
    else if (sTimezone == "MDT") diffMinute = 540;
    else if (sTimezone == "PDT") diffMinute = 600;
    else
    {
        diffMinute = stoi(sTimezone.substr(1, 2)) * 60 + stoi(sTimezone.substr(3, 2));
        if (sTimezone.front() == '+')
            diffMinute = 180 - diffMinute;
        else
            diffMinute = 180 + diffMinute;
    }
    
    int totalMinute = hour * 60 + minute + diffMinute;
    if (totalMinute >= 0)
    {
        if (totalMinute >= 1440)
        {
            addDay(1);
            totalMinute -= 1440;
        }
    }
    else
    {
        addDay(-1);
        totalMinute += 1440;
    }

    hour = totalMinute / 60;
    minute = totalMinute % 60;
}

void print()
{
    cout << dayName[dayOfWeek] << ", ";
    cout << setfill('0') << setw(2) << dayOfMonth << ' ';
    cout << monthName[month] << ' ';
    cout << setfill('0') << setw(4) << year << ' ';
    cout << setfill('0') << setw(2) << hour << ':';
    cout << setfill('0') << setw(2) << minute << ':';
    cout << setfill('0') << setw(2) << second << ' ';
    cout << "+0300\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        parse(line);
        print();
    }
    
    return 0;
}
