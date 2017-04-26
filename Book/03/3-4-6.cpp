#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char *argv[])
{
	string float1 = " -5.236e-12  ", float2 = "6.e+12";
	string pattern = R"(^\s*[\+|-]?[1-9]\d*\.\d+e[\+|-]?[1-9]\d*\s*$)";
	regex e(pattern, regex_constants::icase);
	
	cout << (regex_match(float1, e) ? "Matched." : "Unmatched.") << endl;
	cout << (regex_match(float2, e) ? "Matched." : "Unmatched.") << endl;
	
	return 0;
}
