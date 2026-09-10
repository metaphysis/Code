#include <bits/stdc++.h>
using namespace std;

const int primeLimit = 1111111;
vector<bool> isPrime(primeLimit, true);
unordered_map<int, bool> resultCache;

void buildPrimeTable() {
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i < primeLimit; i++)
        if (isPrime[i])
            for (int j = i * i; j < primeLimit; j += i)
                isPrime[j] = false;
}

bool checkPermutationPrime(int number) {
    auto cacheIterator = resultCache.find(number);
    if (cacheIterator != resultCache.end())
        return cacheIterator->second;
    string digitString = to_string(number);
    sort(digitString.begin(), digitString.end());
    bool answer = false;
    do {
        int permutationNumber = 0;
        for (char digit : digitString)
            permutationNumber = permutationNumber * 10 + digit - '0';
        if (permutationNumber != number) {
            int difference = abs(number - permutationNumber);
            if (difference % 9 == 0) {
                int primeNumber = difference / 9;
                if (primeNumber > 0 && primeNumber < primeLimit && isPrime[primeNumber]) {
                    answer = true;
                    break;
                }
            }
        }
    } while (next_permutation(digitString.begin(), digitString.end()));
    resultCache[number] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildPrimeTable();
    int testCaseCount;
    cin >> testCaseCount;
    for (int testCase = 1; testCase <= testCaseCount; testCase++) {
        int leftBound;
        int rightBound;
        cin >> leftBound >> rightBound;
        if (leftBound > rightBound)
            swap(leftBound, rightBound);
        int answer = 0;
        for (int number = leftBound; number <= rightBound; number++)
            if (checkPermutationPrime(number))
                answer++;
        cout << "Case " << testCase << ": " << answer << '\n';
    }
    return 0;
}
