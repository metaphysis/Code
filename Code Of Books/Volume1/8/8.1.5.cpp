vector<int> findDivisor(int n)
{
    map<int, int> factors;
    for (int i = 0; i < cnt; i++)
    {
        if (primes[i] * primes[i] > n) break;
        while (n % primes[i] == 0)
        {
            n /= primes[i];
            factors[primes[i]]++;
        }
    }

    if (n > 1) factors[n]++;

    vector<int> divisors = {1};
    for (auto f : factors)
    {
        int base = 1, countOfDivisors = divisors.size();
        for (int i = 1; i <= f.second; i++)
        {
            base *= f.first;
            for (int j = 0; j < countOfDivisors; j++)
                divisors.push_back(divisors[j] * base);
        }
    }

    sort(divisors.begin(), divisors.end());
    divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());
    
    return divisors;
}
