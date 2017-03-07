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

int main(int argc, char *argv[])
{
    string s = "ABCDEF";
    
    int indexer = 1;
    do {
        if (indexer == 193) {
            cout << s << '\n';
            break;
        }
        indexer++;
    } while (next_permutation(s.begin(), s.end()));
    
    return 0;
}
