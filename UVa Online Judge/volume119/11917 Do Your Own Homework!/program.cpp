// Do Your Own Homework!
// UVa ID: 11917
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        map<string, int> subject;
        int ss, days;
        string name;

        cin >> ss;
        for (int i = 1; i <= ss; i++)
        {
            cin >> name >> days;
            subject[name] = days;
        }
        
        int due;
        cin >> due >> name;
        
        cout << "Case " << c << ": ";
        if (subject.find(name) == subject.end())
        {
            cout << "Do your own homework!";
        }
        else
        {
            if (due >= subject[name]) cout << "Yesss";
            else if ((due + 5) >= subject[name]) cout << "Late";
            else cout << "Do your own homework!";
        }
        cout << '\n';
    }

    return 0;
}
