#include <iostream>

using namespace std;

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

int main(int argc, char* argv[])
{
    int dayOfWeek = 5;
    for (int i = 1600; i <= 1601; i++)
        for (int j = 0; j < 12; j++)
            for (int k = 1; k <= daysInMonth[isLeapYear(i, false)][j]; k++)
            {
                cout << weekdays[dayOfWeek % 7] << " " << k << " " << months[j] << " " << i << "\n";
                dayOfWeek++;
            }
            
    cout << "#";
    
    return 0;
}
