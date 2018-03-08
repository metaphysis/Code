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

int main(int argc, char* argv[])
{
    cout << fixed << setprecision(6);
    cout << atan(0.0) << endl;
    cout << atan(1E20) << endl;
    cout << atan(-1E20) << endl;
    cout << atan2(0, 1) << endl;
    cout << atan2(1, 0) << endl;
    cout << atan2(-1, 0) << endl;
    cout << atan2(0, -1) << endl;
    cout << atan2(-1E-10, -1) << endl;
    cout << atan2(0, 0) << endl;

    return 0;
}
