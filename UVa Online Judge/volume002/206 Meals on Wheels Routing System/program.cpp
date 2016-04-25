// Meals on Wheels Routing System
// UVa IDs: 206
// Verdict: Accpted
// Submission Date: 2016-04-25
// UVa Run Time: 0.200s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979323846, EPSILON = 1E-7;

struct customer
{
    string name;
    int x, y;
};

bool printStar = false;
int n, m;
string dataSetId;
vector <customer> customers;

bool cmp(customer a, customer b)
{
    double angleA = atan2(a.y, a.x);
    double angleB = atan2(b.y, b.x);
    
    if (angleA < 0)
        angleA += 2 * PI;
    if (angleB < 0)
        angleB += 2 * PI;
    
    if (fabs(angleA - angleB) <= EPSILON)
        return (a.x * a.x + a.y * a.y) < (b.x * b.x + b.y * b.y);
    else
        return angleA < angleB;
}

void route()
{
    if (printStar)
        cout << "***********************************\n";
    else
        printStar = true;
        
    cout << dataSetId << "\n";
    cout << "Number of Customers: " << setw(11) << left << m;
    cout << "Number of Routes: " << n << "\n";
    cout << "\n";
    
    int customersPerRoute = m / n;
    int customersRemains = m % n;
    int totalLength = 0;
    
    sort(customers.begin(), customers.end(), cmp);
    
    int index = 0;
    for (int i = 1; i <= n; i++)
    {
        int subRouteLength = 0;
        
        cout << "Route ==> " << i << "\n";
        for (int j = 1; j <= customersPerRoute; j++)
        {
            cout << "Customer: " << customers[index].name << "\n";
            if (j == 1)
                subRouteLength += (abs(customers[index].x) + abs(customers[index].y));
            else
                subRouteLength += (abs(customers[index].x - customers[index - 1].x) +
                    abs(customers[index].y - customers[index - 1].y));
            index++;
        }
        
        if (customersRemains > 0)
        {
            customersRemains--;
            cout << "Customer: " << customers[index].name << "\n";
            subRouteLength += (abs(customers[index].x - customers[index - 1].x) +
                    abs(customers[index].y - customers[index - 1].y));
            index++;                    
        }
        
        subRouteLength += (abs(customers[index - 1].x) + abs(customers[index - 1].y));
        
        cout << "Route Length ==> " << subRouteLength << "\n";
        cout << "\n";
        
        totalLength += subRouteLength;
    }
    
    cout << "Total Route Length ==> " << totalLength << "\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string customerName;
    int x, y;
    
    while (getline(cin, dataSetId))
    {
        cin >> n >> m;
        cin.ignore();
        //cout << n << " " << m << endl;
        
        customers.clear();
        for (int i = 1; i <= m; i++)
        {
            getline(cin, customerName);
            cin >> x >> y;
            cin.ignore();
            
            customers.push_back((customer){customerName, x, y});
            //cout << customerName << endl;
            //cout << x << " " << y << endl;
        }
        
        route();
    }
    
	return 0;
}
