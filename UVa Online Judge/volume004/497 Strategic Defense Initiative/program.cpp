// Strategic Defense Initiative
// UVa ID: 497
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> numbers, parent, indexer;

int lis()
{
    parent.clear();
    indexer.clear();
    
    parent.resize(numbers.size());
    
    vector<int> m;
    m.push_back(numbers.front());
    indexer.push_back(0);
    parent[0] = -1;
    
    for (int i = 1; i < numbers.size(); i++)
    { 
        if (numbers[i] > m.back())
        {
            m.push_back(numbers[i]);
            parent[i] = indexer.back();
            indexer.push_back(i);
        }
        else
        {
            int n = lower_bound(m.begin(), m.end(), numbers[i]) - m.begin();
            m[n] = numbers[i];
            if (n == 0)
                parent[i] = -1;
            else
                parent[i] = indexer[n - 1];
            
            indexer[n] = i;
        }
    }
    
    return m.size();
}

void findPath(int i)
{
    if (parent[i] != -1)
        findPath(parent[i]);
    cout << numbers[i] << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        numbers.clear();
        while (getline(cin, line), line.length() > 0)
            numbers.push_back(stoi(line));
        
        cout << "Max hits: " << lis() << '\n';
        findPath(indexer.back());
    }
    
	return 0;
}
