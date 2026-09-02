#include <bits/stdc++.h>
using namespace std;

const long long limitValue = 1000000000LL;
const long long infValue = limitValue + 1;
vector<int> primeList = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
vector<long long> divisorList;
long long bestValue;

long long multiplyPower(int prime, long long exponent) {
    long long result = 1;
    for (long long i = 0; i < exponent; i++) {
        if (result > limitValue / prime) return infValue;
        result *= prime;
    }
    return result;
}

void buildDivisors(int index, long long currentValue, const vector<pair<int, int> >& factorList) {
    if (index == static_cast<int>(factorList.size())) {
        divisorList.push_back(currentValue);
        return;
    }
    long long value = 1;
    for (int i = 0; i <= factorList[index].second; i++) {
        buildDivisors(index + 1, currentValue * value, factorList);
        value *= factorList[index].first;
    }
}

vector<long long> getDivisors(long long value) {
    vector<pair<int, int> > factorList;
    long long tempValue = value;
    for (long long prime = 2; prime * prime <= tempValue; prime++) {
        if (tempValue % prime != 0) continue;
        int count = 0;
        while (tempValue % prime == 0) {
            tempValue /= prime;
            count++;
        }
        factorList.push_back(make_pair(static_cast<int>(prime), count));
    }
    if (tempValue > 1) factorList.push_back(make_pair(static_cast<int>(tempValue), 1));
    divisorList.clear();
    buildDivisors(0, 1, factorList);
    sort(divisorList.begin(), divisorList.end(), greater<long long>());
    return divisorList;
}

void dfs(long long rest, long long lastFactor, int index, long long currentValue) {
    if (currentValue >= bestValue) return;
    if (rest == 1) {
        bestValue = currentValue;
        return;
    }
    if (index >= static_cast<int>(primeList.size())) return;
    for (long long factor : divisorList) {
        if (factor < 2) break;
        if (factor > lastFactor || factor > rest) continue;
        if (rest % factor != 0) continue;
        long long power = multiplyPower(primeList[index], factor - 1);
        if (power == infValue || currentValue > limitValue / power) continue;
        dfs(rest / factor, factor, index + 1, currentValue * power);
    }
}

long long getAnswer(long long divisorCount) {
    bestValue = infValue;
    getDivisors(divisorCount);
    dfs(divisorCount, divisorCount, 0, 1);
    return bestValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    unordered_map<long long, long long> answerMap;
    while (cin >> n && n != 0) {
        if (!answerMap.count(n)) answerMap[n] = getAnswer(n);
        if (answerMap[n] > limitValue) cout << "+INF\n";
        else cout << answerMap[n] << '\n';
    }
    return 0;
}
