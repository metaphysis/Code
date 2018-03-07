#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<double> datas = {1.111, 2.222, 3.333, 4.444, 5.555, 6.666};

    cout.setf(ios::fixed);
    cout.precision(2);

    for (int i = 0; i < datas.size(); i++)
    {
        if (i > 1) cout << ' ';
        cout << datas[i];
    }
    cout << endl;
        
    return 0;
}
