#include <bits/stdc++.h>

using namespace std;

int kLimit = 40;

vector<int> hCandidate, kCandidate, kValue;
set<int> valueProduced;
int maxK, maxH, maxSequenceLength;
int countH;

void backtrackH(int index)
{
    if (countH > maxH)
        return;
        
    if (index == maxK)
    {
        int value = 0;
        for (int i = 0; i < hCandidate.size(); i++)
            value += (hCandidate[i] * kCandidate[i]);
        valueProduced.insert(value);
    }
    else
    {
        for (int i = 0; i <= maxH; i++)
        {
            countH += i;
            hCandidate[index] = i;
            backtrackH(index + 1);
            countH -= i;
        }
    }
}

void findMaxSequenceLength()
{
    valueProduced.clear();
    
    countH = 0;
    backtrackH(0);
    
    int length = 0;
    while (valueProduced.count(length + 1) == 1)
        length++;
        
    if (length > maxSequenceLength)
    {
        kValue.clear();
        for (int i = 0; i < kCandidate.size(); i++)
            kValue.push_back(kCandidate[i]);
        maxSequenceLength = length;
    }
}

void backtrackK(int index, int start)
{
    if (index == maxK)
    {
        findMaxSequenceLength();
        return;
    }
    
    for (int i = start + 1; i <= kLimit; i++)
    {
        kCandidate[index] = i;
        backtrackK(index + 1, i);
    } 
}

void search(int h, int k)
{
    cout << "maxSequence[" << (h * 10 + k) << "] = \"";
    
    if (h == 0 || k == 0)
    {
        cout << "  0 ->  0\";\n";
        return;
    }
    
    if (h == 1)
    {
        for (int i = 1; i <= k; i++)
            cout << setw(3) << right << i;
        cout << " ->" << setw(3) << right << k;
        cout << "\";\n";
        return;
    }
    
    if (k == 1)
    {
        cout << "  1 ->  " << h << "\";\n";
        return;
    }
    
    maxH= h;
    maxK = k;
    maxSequenceLength = 0;
    
    hCandidate.clear();
    for (int i = 1; i <= k; i++)
        hCandidate.push_back(0);
        
    kCandidate.clear();
    kCandidate.push_back(1);
    for (int i = 2; i <= k; i++)
        kCandidate.push_back(0);
        
    backtrackK(1, 1);
    
    sort(kValue.begin(), kValue.end());
    for (int i = 0; i < kValue.size(); i++)
        cout << right << setw(3) << kValue[i];
    cout << " ->" << right << setw(3) << maxSequenceLength << "\";\n";
}

int main(int argc, char *argv[])
{
    for (int h = 1; h <= 9; h++)
        for (int k = 1; k <= 9 - h; k++)
            search(h, k);
    
    return 0;
}
