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
	//cout <<"ok" <<endl;
	string filename;
	cin >> filename;
	ifstream cfin(filename);
	//cout << "ok" <<endl;
	ifstream fin("test.txt");
	//cout << "ok" <<endl;

	vector<string> name;
	vector<string> family;

	for(ever) {
		if (cfin.eof()) { cfin.close(); break; }
		string tmp;
		getline(cfin, tmp);
		//cout << tmp << endl;
		int orf_p = tmp.find("_orf:");
		tmp.erase(tmp.begin() + orf_p - 2, tmp.end());
		//cout << tmp << endl;
		name.push_back(tmp);
		if (cfin.eof()) { cfin.close(); break; }
	}
	
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
			family.push_back(familyname);
			break;
		}

		getline(fin, filename);

		if (fin.eof()) { fin.close(); break; }
	}

	for (int i = 0; i < name.size(); i++) {
		cout << name[i] << endl << family[i] << endl;
	}
	return 0;
}