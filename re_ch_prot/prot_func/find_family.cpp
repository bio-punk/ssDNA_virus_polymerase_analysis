#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define endl '\n'
#define tab '\t'

#define FOREVER for(;;)

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

struct prot {
	string id;
	string familyName;
	string clansName;
};

struct CLAN {
	vector<string> family;
	string name;
	ofstream outp;
	~CLAN(){
		outp.close();
	}
};

void get_clan_info(vector<prot> & v) {
	ifstream clanfile("pfam_id_clan.txt");
	FOREVER {
		prot tmp;
		getline(clanfile, tmp.id, tab);
		getline(clanfile, tmp.familyName, tab);
		getline(clanfile, tmp.clansName);
		v.push_back(tmp);
		if (clanfile.eof()) { clanfile.close(); return; }
	}
}

struct family {
	ofstream outp;
	string id;
	~family() {
		outp.close();
	}
};

int main(void)
{
	ifstream fin("rdrp.txt");

	vector<prot> clanInfo;
	get_clan_info(clanInfo);

	vector<family> pf(clanInfo.size());
	for (int i = 0; i < clanInfo.size(); i++) {
		pf[i].id = clanInfo[i].id;
		pf[i].outp.open(pf[i].id + ".txt");
	}

	FOREVER {
		string name;
		string id;
		string othe;
		getline(fin, name, tab);
		getline(fin, id, tab);
		getline(fin, othe);
		for (int i = 0; i < pf.size(); i++) {
			if (id != pf[i].id) { continue; }
			pf[i].outp << name << endl;
		}
		if (fin.eof()) { fin.close(); break; }
	}

	return 0;
}