// 487–3279
// UVa ID: 755
// Verdict: Accepted
// Submission Date: 2017-12-02
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void quickSort(int data[], int left, int right)
{
    if (left < right)
    {
        int pivot = data[(left + right) >> 1];
        int i = left - 1, j = right + 1;
        while (i < j)
        {
            do i++; while (data[i] < pivot);
            do j--; while (data[j] > pivot);
            if (i < j) swap(data[i], data[j]);
        }
        quickSort(data, left, i - 1);
        quickSort(data, j + 1, right);
    }
}

inline void number2string(int n, int c)
{
    int d[7] = {0}, k = 6;
    while (n > 0) d[k--] = n % 10, n /= 10;
    for (int i = 0; i < 3; i++) cout << d[i];
    cout << '-';
    for (int i = 3; i < 7; i++) cout << d[i];
    cout << ' ' << c << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int keypad[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
    int cases = 0, n, dict[100010];
    string telephone;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> telephone;
            
            int t = 0;
            for (auto c : telephone)
            {
                if (c == '-') continue;
                t *= 10;
                if (isdigit(c)) t += (c - '0');
                else t += keypad[c - 'A'];
            }
            dict[i] = t;
        }
        
        //sort(dict, dict + n);
        //qsort(dict, n, sizeof(int), cmp);
        quickSort(dict, 0, n - 1);
        
        bool outputed = false;
        int current = -1, counter = 0;
        for (int i = 0; i < n; i++)
        {
            if (dict[i] == current) counter++;
            else
            {
                if (counter > 1)
                {
                    outputed = true;
                    number2string(current, counter);
                }
                current = dict[i];
                counter = 1;
            }
        }
        if (counter > 1)
        {
            outputed = true;
            number2string(current, counter);
        }
                
        if (!outputed) cout << "No duplicates.\n";
    }
    
	return 0;
}
