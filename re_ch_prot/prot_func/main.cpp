#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void)
{
	const string target = "polymerase";
	string input;
	int ans = 0;
	while (getline(cin, input)) {
		if (string::npos == input.find(target)) { continue; }
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == '\t') { break; }
			cout << input[i];
		}
		cout << endl;
	}
	//cout << ans << endl;
	return 0;
}
