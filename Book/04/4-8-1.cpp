#include <iostream>
#include <algorithm>

using namespace std;

int find(string data[], int n, string target)
{
    for (int i = 0; i < n; i++)
        if (data[i] == target)
            return i;
    return -1;
}

int main(int argc, char *argv[])
{
    string months[12] = {
        "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October",
        "November", "December"
    };

    string weekdays[7] = {
        "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday"
    };
    
    int monthIndex = find(months, months + 12, "July") - months;
    cout << monthIndex << endl;
    
    monthIndex = find(months, 12, "March");
    cout << monthIndex << endl;
        
    int weekdayIndex = find(weekdays, weekdays + 7, "Someday") - weekdays;
    cout << weekdayIndex << endl;
    
    weekdayIndex = find(weekdays, 7, "Sunday");
    cout << weekdayIndex << endl;
    
    return 0;
}
