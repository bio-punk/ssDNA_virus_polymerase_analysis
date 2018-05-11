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

struct data {
	string name;
	string seq;
};

vector<data> base;

void n2f(string fn) {
	ifstream fin(fn + ".txt");
	ofstream fout(fn + ".fasta");

	FOREVER {
		string name;
		fin >> name;
		for (int i = 0; i < base.size(); i++) {
			if (base[i].name != name) { continue; }
			fout << ">" << name << endl << base[i].seq << endl; 
		}
		if (fin.eof()) { fin.close(); fout.close(); return; }
	}
}

int main(void)
{
	ifstream idin("pfam_id.txt");

	vector<string> id;
	FOREVER {
		string tmp;
		idin >> tmp;
		id.push_back(tmp);
		if (idin.eof()) { idin.close(); break; }
	}

	cout << "okk" << endl;

	ifstream database("base001.fasta");
	base.clear();
	FOREVER {
		string name;
		string seq;
		data tmp;
		database >> tmp.name >> tmp.seq;
		tmp.name.erase(tmp.name.begin());
		base.push_back(tmp);

		if (database.eof()) { database.close(); break; } 
	}

	cout << "ok" << endl;

	for (int i = 0; i < id.size(); i++) { n2f(id[i]); }

	return 0;
}