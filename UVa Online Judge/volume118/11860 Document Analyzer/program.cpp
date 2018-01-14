// Document Analyzer
// UVa ID: 11860
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, word;
    getline(cin, line);
    int cases = stoi(line);
    
    for (int c = 1; c <= cases; c++)
    {
        int p, q;
        int idx = 0, smallestDist = (1 << 20), biggestSize = 0;

        map<string, int> hashMap;
        map<int, string> heap;

        while (getline(cin, line), line != "END")
        {
            word.clear();
            for (int i = 0; i < line.length(); i++)
            {
                if (isalpha(line[i])) word += line[i];
                else
                {
                    if (word.length())
                    {
                        heap[idx] = word;
                        hashMap[word] = idx;

                        pair<int, string> pr;
                        while (true)
                        {
                            pr = *heap.begin();
                            if (hashMap[pr.second] != pr.first) heap.erase(heap.begin());
                            else break;
                        }
                        
                        int dist = idx - (pr = *heap.begin()).first;
                        if (heap.size() > biggestSize || dist < smallestDist)
                        {
                            biggestSize = heap.size(), smallestDist = dist;
                            p = (pr = *heap.begin()).first, q = idx;
                        }

                        idx++;
                        word.clear();
                    }
                }
            }
        }
        
        cout << "Document " << c << ": " << p << ' ' << q << '\n';
    }

    return 0;
}
