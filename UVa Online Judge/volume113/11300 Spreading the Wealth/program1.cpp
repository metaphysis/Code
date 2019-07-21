// Spreading the Wealth
// UVa ID: 11300
// Verdict: Accepted
// Submission Date: 2019-07-21
// UVa Run Time: 0.130s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long int LLI;

const int MAXN = 1000010;

LLI C[MAXN], A[MAXN];

int partition(int left, int right)
{
    LLI pivot = A[left];
    while (true) {
        while (left < right && pivot <= A[right]) right--;
        if (left >= right) break;
        A[left++] = A[right];
        while (left < right && A[left] <= pivot) left++;
        if (left >= right) break;
        A[right--] = A[left];
    }
    A[right] = pivot;
    return right;
}

LLI kth_element(int left, int right, int k)
{
    while (true) {
        int middle = partition(left, right);
        if(middle == k) return A[k];
        else
        {
            if(middle < k) left = middle + 1;
            else right = middle - 1;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            cout << "0\n";
            continue;
        }
        LLI S = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> C[i];
            S += C[i];
        }
        LLI M = S / n;
        A[0] = 0;
        for (int i = 1; i < n; i++)
            A[i] = A[i - 1] + M - C[i];
        LLI m = 0;
        m += kth_element(0, n - 1, n / 2);
        if (n % 2 == 0) m += kth_element(0, n - 1, (n - 1) / 2);
        else m *= 2;
        //nth_element(A, A + n / 2, A + n);
        //m += A[n / 2];
        //if (n % 2 == 0)
        //{
        //    nth_element(A, A + (n - 1) / 2, A + n);
        //    m += A[(n - 1) / 2];
        //}
        //else m *= 2;
        LLI T = 0;
        for (int i = 0; i < n; i++)
            T += abs(m - 2 * A[i]);
        cout << T / 2 << '\n';
    }
    return 0;
}
