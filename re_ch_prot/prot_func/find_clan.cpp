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

int main(void)
{
	ifstream fin("rdrp.txt");

	vector<prot> clanInfo;
	get_clan_info(clanInfo);

	vector<CLAN> clans(128);
	int clansSize = 0;
	for (int i = 0; i < clanInfo.size(); i++) {
		bool sameClan = false;
		int k;
		for (k = 0; k < clansSize; k++) {
			if (clans[k].name != clanInfo[i].clansName) { continue; }
			sameClan = true;
			break;
		}
		if (sameClan) {
			clans[k].family.push_back(clanInfo[i].familyName);
			continue;
		}
		CLAN & tmp = clans[clansSize];
		tmp.name = clanInfo[i].clansName;
		tmp.family.push_back(clanInfo[i].familyName);
		clansSize++;
		//clans.push_back(tmp);
	}

	for (int i = 0; i < clansSize; i++) {
		for (int k = 0; k < clans[i].name.size(); k++) {
			if (clans[i].name[k] != ' ') { continue; }
			clans[i].name[k] = '_';
		}
	}

	for (int i = 0; i < clansSize; i++) {
		clans[i].outp.open("0a" + clans[i].name + ".clan.txt");
	}

	FOREVER {
		string name;
		string id;
		string othe;
		getline(fin, name, tab);
		getline(fin, id, tab);
		getline(fin, othe);
		for (int i = 0; i < clansSize; i++) {
			for (int k = 0; k < clans[i].family.size(); k++) {
				if (clans[i].family[k].find(id) == -1) { continue; }
				clans[i].outp << name << tab <<clans[i].family[k] << endl;
				break;
			}
		}
		if (fin.eof()) { fin.close(); break; }
	}

	return 0;
}