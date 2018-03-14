// Simple division
// UVa ID: 10407
// Verdict: Accepted
// Submission Date: 2017-03-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    int t;
    while (b != 0) t = a, a = b, b = t % b;
    return a;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<int> numbers;
    int number;

    while (cin >> number, number != 0)
    {
        numbers.push_back(number);
        while (cin >> number, number != 0) numbers.push_back(number);

        sort(numbers.begin(), numbers.end());
        numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

        if (numbers.size() == 1) cout << abs(numbers.front()) << '\n';
        else
        {
            int g = numbers[1] - numbers[0];
            for (int i = 2; i < numbers.size(); i++)
                g = gcd(g, numbers[i] - numbers[i - 1]); 
            cout << g << '\n';
        }

        numbers.clear();
    }

    return 0;
}
