// Booklet Printing
// UVa ID: 637
// Verdict: Accepted
// Submission Date: 2016-08-26
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

struct sheet
{
    int front_left, front_right, back_left, back_right;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    sheet sheets[100];
    
    int n;
    while (cin >> n, n)
    {
        memset(sheets, 0, sizeof(sheets));
        
        int sheet_number = 0;
        do
        {
            sheets[sheet_number].front_right = 2 * sheet_number + 1;
            if (2 * sheet_number + 2 <= n)
                sheets[sheet_number].back_left = 2 * sheet_number + 2;
            sheet_number++;
        } while (4 * sheet_number < n);
        
        int total_sheets = sheet_number, total_pages = 2 * sheet_number;
        while (total_pages < n)
        {
            sheets[total_sheets - 1].back_right = total_pages + 1;
            total_pages++;
            if (total_pages < n)
                sheets[total_sheets - 1].front_left = total_pages + 1;
            total_pages++;
            total_sheets--;
        }
        
        cout << "Printing order for " << n << " pages:\n";
        for (int i = 0; i < sheet_number; i++)
        {
            cout << "Sheet " << i + 1 << ", front: ";
            if (sheets[i].front_left == 0)
                cout << "Blank";
            else
                cout << sheets[i].front_left;
            cout << ", ";
            cout << sheets[i].front_right << '\n';
            
            if (sheets[i].back_left == 0 && sheets[i].back_right == 0)
                continue;
            else
            {
                cout << "Sheet " << i + 1 << ", back : ";
                cout << sheets[i].back_left;
                cout << ", ";
                if (sheets[i].back_right == 0)
                    cout << "Blank\n";
                else
                    cout << sheets[i].back_right << '\n';
            }
        }
    }
    
	return 0;
}
