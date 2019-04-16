#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int N = 10000;
    cout << N << '\n';
    vector<string> words;
    for (int i = 0; i < N; i++)
    {
        int L = rand() % 4 + 1;
        string s;
        for (int j = 0; j < L; j++)
            s += (char)('a' + rand() % 26);
        cout << s << '\n';
        words.push_back(s);
    }
    int Q = 200;
    cout << Q << '\n';
    for (int i = 0; i < Q; i++)
    {
        int u = rand() % N;
        int v = rand() % N;
        cout << words[u] << " TO " << words[v] << '\n';
    }
    return 0;
}
