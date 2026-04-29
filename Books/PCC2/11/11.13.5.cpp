#include <bits/stdc++.h>

using namespace std;

string lnrs(string source)
{
    if (source.length() == 0)
        return "";
        
    vector <int> latest(256);    
    fill(latest.begin(), latest.end(), -1);
    
    int currentMaxLength = 1, maxLength = 1, maxLengthStartAt = 0;
    for (int i = 1; i < source.size(); i++)
    {
        if (latest[source[i]] == -1 ||
            latest[source[i]] < (i  - currentMaxLength))
            currentMaxLength++;
        else
            currentMaxLength = i - latest[source[i]];
        
        latest[source[i]] = i;
        
        if (currentMaxLength > maxLength)
        {
            maxLength = currentMaxLength;
            maxLengthStartAt = i - currentMaxLength + 1;
        }
    }
    
    return source.substr(maxLengthStartAt, maxLength);
}

int main(int argc, char *argv[])
{
    string source = "j;aie;a3suil3[a.vh7903846==190u8iavm.cgtyqaphnlht1450[602v6ajhi;hji75dz3sio827-p00-0-263455hshuanv21,/mnbcdx5wo9";
    
    cout << lnrs(source) << endl;
    
    return 0;
}
