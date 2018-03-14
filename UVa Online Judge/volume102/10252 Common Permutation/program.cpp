// Common Permutation （公共排列）
// PC/UVa IDs: 110303/10252, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.044s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 统计公共字符数目然后输出
void findCommonThenPrint(string a, string b)
{
    int acount[26] = { 0 }, bcount[26] = { 0 };

    for (int i = 0; i < a.length(); i++)
        acount[a[i] - 'a']++;
    for (int i = 0; i < b.length(); i++)
        bcount[b[i] - 'a']++;

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < min(acount[i], bcount[i]); j++)
            cout << (char)('a' + i);

    cout << endl;
}

// 先排序然后输出共有字符
void sortThenFindCommon(string a, string b)
{
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0, j = 0; i < a.length() && j < b.length();)
    {
        if (a[i] == b[j])
        {
            cout << a[i];
            i++;
            j++;
        }
        else
        {
            if (a[i] < b[j])
                i++;
            else
                j++;

        }
    }

    cout << endl;
}

int main(int ac, char *av[])
{
    string a, b;
    while (getline(cin, a), getline(cin, b))
    {
        findCommonThenPrint(a, b);
        // sortThenFindCommon(a, b);    
    }

    return 0;
}
