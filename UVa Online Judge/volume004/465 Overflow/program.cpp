// Overflow
// UVa ID: 465
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool is_too_big(string number, long long max_value)
{
    if (number.length() > 10 || (number.length() == 10 && number.front() > '2'))
        return true;
    else
    {
        long long number_value = stoll(number);
        if (number_value > max_value)
            return true;
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line, first, middle, second;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> first >> middle >> second;
        
        assert(middle == "*" || middle == "+" || middle == "-");
        
        cout << line << '\n';
        
        int maxLength = max(first.length(), second.length());
        
        while (first.front() == '0' && first.length() > 1) first.erase(first.begin());
        while (second.front() == '0' && second.length() > 1) second.erase(second.begin());
        
        if (is_too_big(first, numeric_limits<int>::max())) cout << "first number too big\n";
        if (is_too_big(second, numeric_limits<int>::max())) cout << "second number too big\n";
        
        // beware of that one of numbers is zero
        if (middle == "*")
        {
            if (first == "0" || second == "0") continue;
            
            if (first.length() + second.length() >= 12)
            {
                cout << "result too big\n";
            }
            else
            {
                long long first_value = stoll(first), second_value = stoll(second);
                long long result_value = first_value * second_value;
                if (result_value > numeric_limits<int>::max())
                    cout << "result too big\n";
            }
            
            continue;
        }
        
        int sign = 1;
        string result(maxLength + 1, '0');
        
        while (first.length() < result.length()) first.insert(first.begin(), '0');
        while (second.length() < result.length()) second.insert(second.begin(), '0');
        
        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        if (middle == "+")
        {
            int sum = 0, carry = 0;
            for (int i = 0; i < result.length(); i++)
            {
                sum = first[i] - '0' + second[i] - '0' + carry;
                result[i] = sum % 10 + '0';
                carry = sum / 10;
            }
        }
        else
        {
            for (int i = first.length() - 1; i >= 0; i--)
                if (second[i] > first[i])
                {
                    sign = -1;
                    swap(first, second);
                    break;
                }
            
            int sum = 0, borrow = 0;
            for (int i = 0; i < result.length(); i++)
            {
                sum = first[i] - '0' - second[i] - '0' - borrow;
                if (sum < 0)
                {
                    sum += 10;
                    borrow = 1;
                }
                else
                {
                    borrow = 0;
                }
                result[i] = sum + '0';
            }
        }
        
        reverse(result.begin(), result.end());
        while (result.front() == '0' && result.length() > 1) result.erase(result.begin());

        if (sign > 0)
        {
            if (is_too_big(result, numeric_limits<int>::max())) cout << "result too big\n";
        }
        else
        {
            if (is_too_big(result, (long long)numeric_limits<int>::max() + 1)) cout << "result too big\n";
        }
    }
    
	return 0;
}
