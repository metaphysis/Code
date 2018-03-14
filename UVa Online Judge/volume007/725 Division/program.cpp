// Division
// UVa ID: 725
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.290s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct item
{
    string numerator, denominator;
    int number1, number2, quotient;
    
    bool operator<(const item &x) const
    {
        if (number2 == x.number2)
            return number1 < x.number1;
        else
            return number2 < x.number2;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    vector<item> answer[100];
    
    string n = "0123456789";
    do
    {
        string numerator = n.substr(0, 5), denominator = n.substr(5, 5);
        int number1 = stoi(numerator), number2 = stoi(denominator);

        if (number1 > number2 && number1 % number2 == 0)
        {
            int quotient = number1 / number2;
            answer[quotient].push_back((item){numerator, denominator, number1, number2, quotient});
        }
    } while (next_permutation(n.begin(), n.end()));
    
    for (int i = 2; i <= 79; i++)
        if (answer[i].size() > 0)
            sort(answer[i].begin(), answer[i].end());

    int N, cases = 0;
    while (cin >> N, N > 0)
    {
        if (cases++ > 0) cout << '\n';
        if (answer[N].size() == 0)
            cout << "There are no solutions for " << N << ".\n";
        else
        {
            for (auto a : answer[N])
                cout << a.numerator << " / " << a.denominator << " = " << a.quotient << '\n';
        }
    }
    
	return 0;
}
