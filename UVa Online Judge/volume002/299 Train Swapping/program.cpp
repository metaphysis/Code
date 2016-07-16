// Train Swapping
// UVa ID: 299
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

vector < int > trains;

int sortAndCount()
{
    int swaps = 0;
    
    for (int i = trains.size() - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (trains[j] > trains[j + 1])
            {
                swaps++;
                swap(trains[j], trains[j + 1]);
            }

    return swaps;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int cases, number;
    cin >> cases;
    
    while (cases--)
    {
        cin >> number;
        trains.clear();
        
        int index;
        for (int i = 1; i <= number; i++)
        {
            cin >> index;
            trains.push_back(index);
        }
        
        cout << "Optimal train swapping takes " << sortAndCount() << " swaps.\n";
    }
    
	return 0;
}
