// Square of Primes
// UVa ID: 835
// Verdict: Accepted
// Submission Date: 2018-11-03
// UVa Run Time: 0.750s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, MAXP = 10000;

struct ANSWER
{
    int number[5];
    bool operator<(const ANSWER &A) const
    {
        for (int i = 0; i < 5; i++)
            if (number[i] != A.number[i])
                return number[i] < A.number[i];
    }
} output[256];

int primes[MAXN] = {}, cnt_of_primes, digits[MAXN][5], has_zero_digit[MAXN] = {};
vector<int> prime_sum_diagonal[50][10], prime_sum_tail[4][50][10][10][10], prime_odd_sum_tail[50][10];
int diagonal, pre_column, last_column, previous_digit[5], diagonal_digit[5], last_digit[5], rows[5];
int sum_of_digits, head_of_prime, cnt_of_answer = 0;

bool accepted()
{
    for (int c = 2; c <= 4; c++)
    {
        int n = 0, sum = 0;
        for (int r = 0; r < 5; r++)
        {
            n = n * 10 + digits[rows[r]][c];
            sum += digits[rows[r]][c];
        }
        if (sum != sum_of_digits || primes[n]) return false;
    }
    int n = 0, sum = 0;
    for (int r = 4; r >= 0; r--)
    {
        n = n * 10 + digits[rows[r]][r];
        sum += digits[rows[r]][r];
    }
    if (sum != sum_of_digits || primes[n]) return false;
    return true;
}

void dfs(int depth)
{
    if (depth == 4)
    {
        if (accepted())
        {
            for (int i = 0; i < 5; i++) output[cnt_of_answer].number[i] = rows[i];
            cnt_of_answer++;
        }
        return;
    }
    if (depth == -1)
    {
        for (auto u : prime_sum_diagonal[sum_of_digits][head_of_prime])
        {
            diagonal = u;
            for (auto v : prime_odd_sum_tail[sum_of_digits][digits[u][0]])
            {
                last_column = v;
                for (auto x : prime_odd_sum_tail[sum_of_digits][digits[u][0]])
                {
                    rows[4] = x;
                    for (auto y : prime_sum_tail[3][sum_of_digits][digits[u][1]][digits[u][1]][digits[x][1]])
                    {
                        pre_column = y;
                        dfs(0);
                    }
                }
            }
        }
    }
    else
    {
        for (auto u : prime_sum_tail[depth][sum_of_digits][digits[diagonal][4 - depth]][digits[pre_column][4 - depth]][digits[last_column][4 - depth]])
        {
            if (depth == 0 && has_zero_digit[u]) continue;
            rows[depth] = u;
            dfs(depth + 1);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cnt_of_primes = 0;
    for (int p = 2; p < MAXN; p++)
    {
        if (!primes[p])
        {
            primes[cnt_of_primes++] = p;
            if (p > MAXP)
            {
                int sum = 0, n = p, digit, has_even_digit = 0, idx = 0;
                while (n)
                {
                    digit = n % 10;
                    if (digit % 2 == 0) has_even_digit = 1;
                    if (digit == 0) has_zero_digit[p] = 1;
                    sum += digit;
                    digits[p][idx++] = digit;
                    n /= 10;
                }
                prime_sum_diagonal[sum][p / 10000].push_back(p);
                if (!has_even_digit) prime_odd_sum_tail[sum][p % 10].push_back(p);
                for (int mod = 100000, i = 0; i < 4; i++, mod /= 10)
                    prime_sum_tail[i][sum][(p % mod) / (mod / 10)][(p % 100) / 10][p % 10].push_back(p);
            }
        }
        for (int j = 0; j < cnt_of_primes && p * primes[j] < MAXN; j++)
        {
            primes[p * primes[j]] = 1;
            if (p % primes[j] == 0) break;
        }
    }

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        if (cs > 1) cout << '\n';
        cin >> sum_of_digits >> head_of_prime;
        if (sum_of_digits % 2 == 0)
        {
            cout << '\n';
            continue;
        }
        cnt_of_answer = 0;
        dfs(-1);
        sort(output, output + cnt_of_answer);
        for (int i = 0; i < cnt_of_answer; i++)
        {
            if (i) cout << '\n';
            for (int j = 0; j < 5; j++)
                cout << output[i].number[j] << '\n';
        }
    }

    return 0;
}
