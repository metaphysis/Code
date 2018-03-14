// Prime Cuts
// UVa ID: 406
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    vector<bool> primes(2000, true);
    for (int i = 2; i <= 1200; i++)
        if (primes[i])
            for (int j = i + i; j <= 1200; j += i)
                primes[j] = false;
                
    vector<int> prime_numbers;
    prime_numbers.push_back(1);
    for (int i = 2; i <= 1200; i++)
        if (primes[i])
            prime_numbers.push_back(i);
    
    //for (auto p : prime_numbers) cout << p << " ";
    //cout << endl;
    
    int N, C;
    while (cin >> N >> C)
    {
        cout << N << " " << C << ":";
        int count = upper_bound(prime_numbers.begin(), prime_numbers.end(), N) - prime_numbers.begin();
        
        int cuts = 0;
        if (count % 2 == 0) cuts = 2 * C;
        else cuts = 2 * C - 1;
        
        if (cuts >= count)
        {
            for (int i = 0; i < count; i++)
                cout << " " << prime_numbers[i];
            cout << endl;
        }
        else
        {
            if (count % 2 == 0)
            {
                for (int i = count / 2 - C; i <= count / 2 + C - 1; i++)
                    cout << " " << prime_numbers[i];
                cout << endl;
            }
            else
            {
                for (int i = count / 2 - C + 1; i <= count / 2 + C - 1; i++)
                    cout << " " << prime_numbers[i];
                cout << endl;
            }   
        }
        
        cout << endl;
    }
        
	return 0;
}
