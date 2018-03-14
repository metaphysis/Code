#include <bits/stdc++.h>

using namespace std;

int main(int ac, char *av[])
{
	srand(time(0));
	cout << "20" << endl;
	for (int j = 1; j <= 20; j++)
	{
		cout << endl;
		for (int i = 0; i < 200; i++)
			cout << (rand() % 500) / 10.0 << " " << (rand() % 500) / 10.0 << endl;
	}
	return 0;
}
