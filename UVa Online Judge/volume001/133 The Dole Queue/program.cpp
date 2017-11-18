// The Dole Queue
// UVa ID: 133
// Verdict: Accepted
// Submission Date: 2015-12-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n, k, m;
vector<int> circle;

// count off in counter-clockwise and return the index of target.
int findCCW(int right, int number)
{
    for (int i = right; i < circle.size(); i++)
        if (circle[i] > 0 && ((--number) == 0))
            return i;

    while (true)
    {
        for (int i = 0; i < circle.size(); i++)
            if (circle[i] > 0 && ((--number) == 0))
                return i;
    }
}

// count off in clockwise and return the index of target.
int findCW(int left, int number)
{
    for (int i = left; i >= 0; i--)
        if (circle[i] > 0 && ((--number) == 0))
            return i;

    while (true)
    {
        for (int i = circle.size() - 1; i >= 0; i--)
            if (circle[i] > 0 && ((--number) == 0))
                return i;
    }
}

int main(int argc, char *argv[])
{
    setfill(' ');
    
    while (cin >> n >> k >> m, n || k || m)
    {
        circle.clear();
        for (int i = 1; i <= n; i++)
            circle.push_back(i);

        int right = 0, left = n - 1;
        while (n > 0)
        {
            right = findCCW(right, k);
            left = findCW(left, m);

            cout << setw(3) << circle[right];
            circle[right] = 0;
            n--;
                
            if (right != left)
            {
                cout << setw(3) << circle[left];
                circle[left] = 0;
                n--;
            }

            if (n > 0)
                cout << ",";
        }

        cout << endl;
    }

    return 0;
}
