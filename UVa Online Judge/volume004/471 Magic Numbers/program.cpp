// Magic Numbers
// UVa ID: 471
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<long long> numbers(200000, 0);
vector<bool> visited(10);
int counter = 0;

void backtrack(long long current, int depth)
{
    if (depth == 6)
        return;
        
    for (int i = 0; i < visited.size(); i++)
        if (visited[i] == false)
        {
            visited[i] = true;
            numbers[counter++] = current * 10 + i;
            backtrack(current * 10 + i, depth + 1);
            visited[i] = false;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    fill(visited.begin(), visited.end(), false);
    backtrack(0, 0);
    
    sort(numbers.begin(), numbers.end());
    counter = unique(numbers.begin(), numbers.end()) - numbers.begin();
    
    int cases;
    cin >> cases;
    
    long long n;
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        cin >> n;
        
        for (int j = 1; j < counter; j++)
        {
            long long multiplication = n * numbers[j];
            if (multiplication <= 9876543210LL)
            {
                string text = to_string(multiplication);
                sort(text.begin(), text.end());
                bool same = false;
                for (int k = 0; k < text.length() - 1; k++)
                    if (text[k] == text[k + 1])
                    {
                        same = true;
                        break;
                    }
                if (same == false)
                    cout << multiplication << " / " << numbers[j] << " = " << n << '\n';
            }
            else
                break;
        }
    }
    
	return 0;
}
