// Mapmaker
// UVa ID: 394
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct arrayInfo
{
    int base, bytes, dimensions;
    vector<pair<int, int>> bounds;
};

int main(int argc, char *argv[])
{
    int N, R;
    while (cin >> N >> R)
    {
        vector<arrayInfo> arrays;
        map<string, int> indexer;
        
        for (int i = 1; i <= N; i++)
        {
            string name;
            int base, bytes, dimensions;
            
            cin >> name >> base >> bytes >> dimensions;
            
            arrayInfo aArray;
            aArray.base = base, aArray.bytes = bytes, aArray.dimensions = dimensions;
            for (int j = 1; j <= dimensions; j++)
            {
                int low, up;
                cin >> low >> up;
                aArray.bounds.push_back(make_pair(low, up));
            }
            
            indexer[name] = arrays.size();
            arrays.push_back(aArray);
        }
        
        for (int i = 1; i <= R; i++)
        {
            string name;
            cin >> name;
            
            cout << name << "[";
            vector<int> ds(arrays[indexer[name]].dimensions);
            for (int j = 0; j < arrays[indexer[name]].dimensions; j++)
            {
                if (j > 0) cout << ", ";
                cin >> ds[j];
                cout << ds[j];
            }
            
            cout << "] = ";
            
            int address = 0, length = 1;
            for (int i = arrays[indexer[name]].dimensions - 1; i >= 0; i--)
            {
                address += (ds[i] - arrays[indexer[name]].bounds[i].first) * length;
                length *= arrays[indexer[name]].bounds[i].second - arrays[indexer[name]].bounds[i].first + 1;
            }
            
            address = arrays[indexer[name]].base + address * arrays[indexer[name]].bytes;
            cout << address << endl;
        }
    }
    
	return 0;
}
