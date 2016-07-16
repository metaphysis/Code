// Welfare Reform
// UVa ID: 365
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.170s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct child
{
    int month, day, year, age;
    
    void setAge()
    {
        if (year == 96) age = 0;
        else
        {
            age = 96 - year;
            if (month > 9 || (month == 9 && day > 1))
                age--;
        }
    }
};

int salary[20][20];
double fee[20];

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    for (int i = 1; i <= 12; i++)
    {
        cin >> fee[i];
        for (int j = 1; j <= 10; j++)
            cin >> salary[j][i];
    }
    
    int n, number, incomes;
    string family;
    
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> family >> number >> incomes;

        if (number > 0)
        {
            vector<child> children(number);
            
            int youngest = -1; 
            for (int j = 0; j < number; j++)
            {
                cin >> children[j].month >> children[j].day >> children[j].year;
                children[j].setAge();

                if (youngest == -1 || (children[j].year > children[youngest].year) ||
                    (children[j].year == children[youngest].year && children[j].month > children[youngest].month) ||
                    (children[j].year == children[youngest].year && children[j].month == children[youngest].month && children[j].day > children[youngest].day))
                    youngest = j;
            }
            
            int feeIndex;
            for (int k = 12; k >= 1; k--)
                if (incomes >= salary[number][k])
                {
                    feeIndex = k;
                    break;
                }

            int times = 0;
            for (int k = 0; k < children.size(); k++)
            {
                cout << family << " " << children[k].age << " ";
                if (children[k].age < 13)
                {
                    if (k == youngest)
                    {
                        times++;
                        if (times >= 2) assert(false);
                        cout << fixed << setprecision(2) << fee[feeIndex] << endl;
                    }
                    else
                        cout << fixed << setprecision(2) << fee[feeIndex] / 2.0 << endl;
                }
                else
                    cout << "0.00" << endl;
            }
        }
        
        cout << endl;
    }
    
	return 0;
}
