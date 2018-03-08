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

const double PI = 2.0 * acos(0.0);

double degreeToRadians(double degree)
{
    return degree / 180.0 * PI;
}

double radiansToDegree(double radians)
{
    return radians / PI * 180;
}

int main(int argc, char* argv[])
{
    double degree = 100.0;

    cout << degreeToRadians(degree) << endl;
    cout << radiansToDegree(degreeToRadians(degree)) << endl;

    return 0;
}
