// Copying Books
// UVa ID: 714
// Verdict: Accepted
// Submission Date: 2016-12-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long partition(long long data[], long long n, long long k)
{
    long long left = 0, right = 0;

    for (int i = 0; i < n; i++) right += data[i];
    
    while (left <= right)
    {
        long long middle = (left + right) / 2;
        long long j = 0, p = 0, sum = 0, ok = 1;

        while (j < n && p <= k)
        {
            if (sum + data[j] <= middle)
            {
                sum += data[j];
                j++;
            }
            else
            {
                sum = 0;
                p++;
            }
        }

        if (sum > 0) p++;

        if (p > k)
            left = middle + 1;
        else
            right = middle - 1;
    }
    
    return left;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long N, pages[510], M, K, low, high;
    
    cin >> N;
    
    for (int c = 1; c <= N; c++)
    {
        cin >> M >> K;

        for (int i = 0; i < M; i++) cin >> pages[i];
        
        // 二分查找确定和的最小值。
        long long low = partition(pages, M, K);
        
        // 贪心策略，从后往前划分，注意特殊情况的处理。
        vector<string> output;
        string buffer;
        
        long long j = M - 1, k = 1, sum = 0;
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
            
            if (sum + pages[j] <= low)
            {
                sum += pages[j];
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

                sum = 0;
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
