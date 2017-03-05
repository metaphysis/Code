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

string round_angle(double angle)
{
    stringstream ss;
    string rounded_angle;
    
    ss << fixed << setprecision(2) << (angle + 1e-7);
    ss >> rounded_angle;

    if (rounded_angle == "360.00") rounded_angle = "0.00";
    
    return rounded_angle;
}

int main(int argc, char *argv[])
{
    double angle1 = 355.8762, angle2 = 359.9985;
    
    cout << round_angle(angle1) << endl;
    cout << round_angle(angle2) << endl;
    
    return 0;
}
