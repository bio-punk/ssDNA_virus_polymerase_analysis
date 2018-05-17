#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ever ;;
#define endl '\n'
#define tab '\t'

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

int main(void)
{
	string filename;
	cin >> filename;
	ifstream cfin(filename);
	ifstream fin("test.txt");

	vector<string> name;

	for(ever) {
		if (cfin.eof()) { cfin.close(); break; }
		string tmp;
		getline(cfin, tmp);
		int orf_p = tmp.find("_orf:");
		tmp.erase(tmp.begin() + orf_p - 2, tmp.end());
		//cout << tmp << endl;
		name.push_back(tmp);
		if (cfin.eof()) { cfin.close(); break; }
	}

	vector<string> family(name.size());

	for(ever) {
		if (fin.eof()) { fin.close(); break; }

		string n, familyname;
		getline(fin, n, tab);

		if (fin.eof()) { fin.close(); break; }

		getline(fin, familyname, tab);
		getline(fin, familyname, tab);
		getline(fin, familyname, tab);
		for (int i = 0; i < name.size(); i++) {
			if (name[i] != n) { continue; }
			family[i] = familyname;
			break;
		}

		getline(fin, filename);

		if (fin.eof()) { fin.close(); break; }
	}
	//cout << name.size() << endl << family.size() << endl;
	for (int i = 0; i < name.size(); i++) {
		cout << name[i] << "\t" << family[i] << endl;
	}
	return 0;
}