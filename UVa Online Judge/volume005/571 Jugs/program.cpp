// Jugs
// UVa ID: 571
// Verdict: Accepted
// Submission Date: 2016-09-02
// UVa Run Time: 0.000s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int Ca, Cb, N;
    while (cin >> Ca >> Cb >> N)
    {
        int A = 0, B = 0;
        while (true)
        {
            if (B == Cb)
            {
                cout << "empty B\n";
                B = 0;
            }
            
            if (A == 0)
            {
                cout << "fill A\n";
                A = Ca;
            }

            if (A == N)
            {
                cout << "success\n";
                break;
            }
            
            cout << "pour A B\n";
            
            B += A;
            if (B > Cb)
            {
                A = B - Cb;
                B = Cb;
            }
            else
                A = 0;
            
            if (A == N || B == N)
            {
                cout << "success\n";
                break;
            }
        }
    }
    
	return 0;
}
