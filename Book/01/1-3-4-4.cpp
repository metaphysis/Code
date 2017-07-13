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

string roundAngle(double angle)
{
    stringstream ss;
    string roundedAngle;
    
    ss << fixed << setprecision(2) << (angle + 1e-7);
    ss >> roundedAngle;

    if (roundedAngle == "360.00") roundedAngle = "0.00";
    
    return roundedAngle;
}

int main(int argc, char *argv[])
{
    double angle1 = 355.8762, angle2 = 359.9985;
    
    cout << roundAngle(angle1) << endl;
    cout << roundAngle(angle2) << endl;
    
    return 0;
}
