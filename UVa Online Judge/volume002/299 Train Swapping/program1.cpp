// Train Swapping
// UVa ID: 299
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

vector < int > trains;
int cases, number;

int sortAndCount()
{
    int swaps = 0;
    for (int i = 1; i <= number; i++)
        for (int j = 0; j < trains.size(); j++)
            if (trains[j] == i)
            {
                swaps += j;
                trains.erase(trains.begin() + j);
                break;
            }
    return swaps;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
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
