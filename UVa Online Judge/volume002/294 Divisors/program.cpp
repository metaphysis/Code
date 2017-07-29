// Divisors
// UVa ID: 294
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.010s
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> primes;
int isPrime[31263], N, L, U;

void sieve()
{
    memset(isPrime, 1, sizeof(isPrime));
    for (int i = 2; i < 31263; i++)
        if (isPrime[i])
        {
            for (int j = 2 * i; j < 31263; j += i) isPrime[j] = 0;
            primes.push_back(i);
        }
}

int getCountOfDivisors1(int n)
{
    if (n == 1) return 1;
    if (n < 31263 && isPrime[n]) return 2;
        
    set<int> numbers, divisors;
    numbers.insert(1);

    for (int i = 0; i < primes.size(); i++)
    {
        while (n % primes[i] == 0)
        {
            n /= primes[i];
            
            if (numbers.size())
            {
                for (auto it = numbers.begin(); it != numbers.end(); it++)
                {
                    divisors.insert(*it);
                    divisors.insert(*it * primes[i]);
                }
                numbers.clear();
            }
            else
            {
                for (auto it = divisors.begin(); it != divisors.end(); it++)
                {
                    numbers.insert(*it);
                    numbers.insert(*it * primes[i]);
                }
                divisors.clear();
            }
        }
        
        if (n == 1) break;
    }
    
    if (n > 1) return 2;
    
    return max(numbers.size(), divisors.size());
}

int getCountOfDivisors2(int n)
{
    if (n == 1) return 1;
    if (n < 31263 && isPrime[n]) return 2;
        
    map<int, int> divisors;
    
    for (int i = 0; i < primes.size(); i++)
    {
        while (n % primes[i] == 0)
        {
            n /= primes[i];
            divisors[primes[i]]++;
        }
        if (n == 1) break;
    }
    
    if (n > 1) return 2;
    
    int count = 1;
    for (auto pair : divisors) count *= (pair.second + 1);
    
    return count;
}

void findNumber()
{
    int minN = L, maxCountOfDivisors = 0, countOfDivisors;
    
    for (int i = L; i <= U; i++)
        if ((countOfDivisors = getCountOfDivisors2(i)) > maxCountOfDivisors)
        {
            maxCountOfDivisors = countOfDivisors;
            minN = i;
        }
    
    cout << "Between " << L << " and ";
    cout << U << ", " << minN << " has a maximum of ";
    cout << maxCountOfDivisors << " divisors.\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), cin.sync_with_stdio(false);
    
    sieve();
    
    cin >> N;
    while (N--)
    {
        cin >> L >> U;
        findNumber();
    }
    
	return 0;
}
