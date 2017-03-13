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

int main(int argc, char *argv[])
{
    double a = 0.005, b = 0.005, epsilon = 1e-7;
    
    if (a < b + epsilon) cout << "a is smaller than b." << endl;
    if (b > a + epsilon) cout << "b is bigger than a." << endl;
    if (fabs(a - b) < epsilon) cout << "a is equal to b." << endl;   
    
    return 0;
}
