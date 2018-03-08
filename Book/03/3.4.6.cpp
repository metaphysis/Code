#include <iostream>
#include <regex>

using namespace std;

void match()
{
    string float1 = " -5.236e-12  ", float2 = "6.e+12";
	string pattern = R"(^\s*[\+|-]?[1-9]\d*\.\d+e[\+|-]?[1-9]\d*\s*$)";
	regex e(pattern, regex_constants::icase);
	
	cout << (regex_match(float1, e) ? "Matched." : "Unmatched.") << endl;
	cout << (regex_match(float2, e) ? "Matched." : "Unmatched.") << endl;
}

void search()
{
    string ip = "192.168.1.100, 192.168.1.200, 192.168.1.300.";
    string pattern = R"((\d+)(\.\d+){3})";
    regex e(pattern);
    
    cout << "First matched:";
    smatch sm;
    if (regex_search(ip, sm, e)) cout << " [" << sm[0].str() << "]";
    cout << endl;

    cout << "All matched:";
    regex_iterator<string::iterator> it(ip.begin(), ip.end(), e);
    regex_iterator<string::iterator> end;
    while (it != end)
    {
        cout << " [" << it->str() << "]";
        it++;
    }
    cout << endl;
}

void replace()
{
    string ip = "192.168.1.100, 192.168.1.200, 192.168.1.300.";
    string pattern = R"((\d+)\.(\d+)\.(\d+)\.(\d+))";
    regex e(pattern);
    
    cout << "Replaced: [" << regex_replace(ip, e, "$1.$2.2.$4") << "]" << endl;
}

int main(int argc, char *argv[])
{
	match();
	search();
	replace();

	return 0;
}
