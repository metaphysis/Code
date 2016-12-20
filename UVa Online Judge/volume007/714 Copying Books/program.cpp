// Copying Books
// UVa ID: 714
// Verdict: Accepted
// Submission Date: 2016-12-19
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

    long long N, pages[510], M, K, low, high;
    
    cin >> N;
    
    for (int c = 1; c <= N; c++)
    {
        cin >> M >> K;

        low = 0, high = 0;
        for (int i = 0; i < M; i++)
        {
            cin >> pages[i];
            low = max(low, pages[i]);
            high += pages[i];
        }
        
        long long middle, j, k, partition;
        bool successed;

        while (low <= high)
        {
            middle = (low + high) / 2;
            j = 0, k = 0, partition = 0;
            successed = true;
            
            while (j < M)
            {
                if (partition + pages[j] <= middle)
                {
                    partition += pages[j];
                    j++;
                }
                else
                {
                    k++;
                    partition = 0;
                }
                
                if (k > K) break;
            }
            
            if (partition > middle) successed = false;
            if (partition > 0) k++;
            if (k > K) successed = false;
            
            if (successed)
                high = middle - 1;
            else
                low = middle + 1;
        }
        
        vector<string> output;
        string buffer;
        
        j = M - 1, k = 1, partition = 0;
        while (j >= 0)
        {
            if ((K - k) == (j + 1))
            {
                if (buffer.length() > 0)
                {
                    output.push_back(buffer);
                    output.push_back(" / ");
                }
                
                while (j > 0)
                {
                    output.push_back(to_string(pages[j]));
                    output.push_back(" / ");
                    j--;
                }
                
                output.push_back(to_string(pages[j]));
                
                break;
            }
            
            if (partition + pages[j] <= low)
            {
                partition += pages[j];
                if (buffer.length() > 0) buffer.insert(buffer.begin(), ' ');
                buffer.insert(0, to_string(pages[j]));
                j--;
                
                if (j == -1)
                {
                    output.push_back(buffer);
                    break;
                }
            }
            else
            {
                k++;

                output.push_back(buffer);
                buffer.clear();

                partition = 0;
                output.push_back(" / ");
            }
        }

        reverse(output.begin(), output.end());
        
        for (auto part : output)
            cout << part;
            
        cout << '\n';
    }
    
	return 0;
}
