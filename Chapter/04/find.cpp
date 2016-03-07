#include <iostream>
#include <algorithm>

using namespace std;

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
        
    int weekdayIndex = find(weekdays, weekdays + 7, "Someday") - weekdays;
        cout << weekdayIndex << endl;
        
    return 0;
}
