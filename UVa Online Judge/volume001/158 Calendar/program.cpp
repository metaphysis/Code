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
