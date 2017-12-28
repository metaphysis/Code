// Dates
// UVa ID: 11356
// Verdict: Accepted
// Submission Date: 2017-12-28
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

struct date
{
    int yyyy, mm, dd;
    date (int yyyy = 0, int mm = 0, int dd = 0): yyyy(yyyy), mm(mm), dd(dd) {}
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
date toDate(int days)
{
    int yyyy = 0, mm = 0, dd = 0, cntOf100Years, cntOfYear;
    
    yyyy += (days / daysOf400Years) * 400, days %= daysOf400Years;
    yyyy += (cntOf100Years = days / daysOf100Years) * 100, days %= daysOf100Years;
    yyyy += (days / daysOf4Years) * 4, days %= daysOf4Years;
    yyyy += (cntOfYear = days / daysOfYear), days %= daysOfYear;
    if (days == 0)
    {
        if (cntOf100Years == 4 || cntOfYear == 4) return date(yyyy, 12, 30);
        return date(yyyy, 12, 31);
    }

    yyyy++;
    int leapYear = isLeapYear(yyyy);
    for (int i = 1; i <= 12; i++)
        if (daysBeforeMonth[leapYear][i] >= days)
        {
            mm = i;
            dd = days - daysBeforeMonth[leapYear][i - 1];
            break;
        }

    return date(yyyy, mm, dd);
}

string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    int cases, diff;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line >> diff;
        
        istringstream iss(line);
        string dtext, mtext, ytext;
        getline(iss, ytext, '-');
        getline(iss, mtext, '-');
        getline(iss, dtext, '-');
        
        int yyyy = stoi(ytext);
        int mm = find(months, months + 12, mtext) - months + 1;
        int dd = stoi(dtext);
        
        date next = toDate(toDays(yyyy, mm, dd) + diff);
        cout << "Case " << c << ": ";
        cout << next.yyyy << '-' << months[next.mm - 1];
        cout << '-' << setw(2) << setfill('0') << next.dd << '\n';
    }

    return 0;
}
