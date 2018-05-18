#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define tab '\t'
#define ever ;;
#define endl '\n'

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

struct h {
	string name;
	int size;
	h() { name.clear(); size = 0; }
};

struct f {
	vector<h> host;
	string name;
};

int main(void)
{

	vector<h> host;
	ifstream hostin("host.txt");
	for(ever) {
		string hostName;
		//hostin >> hostName;
		getline(hostin, hostName);
		h tmp;
		tmp.name = hostName;
		host.push_back(tmp);

		if (hostin.eof()) { hostin.close(); break; }
	}

	cout << "#name";
	for (int i = 0; i < host.size(); i++) {
		cout << tab << host[i].name;
	}
	cout << endl;

	vector<f> family;
	ifstream familyin("family.txt");
	for(ever) {
		string familyName;
		//familyin >> familyName;
		getline(familyin, familyName);
		f tmp;
		tmp.name = familyName;
		tmp.host = host;
		family.push_back(tmp);

		if (familyin.eof()) { familyin.close(); break; }
	}

	ifstream fin("data.txt");
	for(ever) {
		string fname, hname;
		getline(fin, fname, tab);
		getline(fin, hname);

		vector<string> vn;
		vn.clear();
		for(ever) {
			int p = hname.find(',');
			if (p == -1) {
				if (hname.find(' ') != -1) {
					hname.erase(hname.begin() + hname.find(' '));
				}
				//cout << hname << endl;
			 	vn.push_back(hname); 
			 	break;
			}
			string tmp;
			for (int w = 0; w < p; w++) {
				if (hname[w] == ' ') { continue; } 
				tmp += hname.c_str()[w]; 
			}
			vn.push_back(tmp);
			hname.erase(hname.begin(), hname.begin() + p + 1);
		}

		for (int i = 0; i < family.size(); i++) {
			if (family[i].name != fname) { continue; }
			for (int k = 0; k < family[i].host.size(); k++) {
				for (int w = 0; w < vn.size(); w++) {
					if (vn[w] != family[i].host[k].name) { continue; }
					family[i].host[k].size++;
					//cout << family[i].host[k].name << tab <<vn[w] << endl;
				}
			}
		}

		if (fin.eof()) { fin.close(); break; }
	}

	//return 0;

	for (int i = 0; i < family.size(); i++) {
		cout << family[i].name << tab;
		for (int k = 0; k < family[i].host.size(); k++) {
			cout << family[i].host[k].size << "\t\n"[k == family[i].host.size() - 1];
		}
	}

	return 0;
}
