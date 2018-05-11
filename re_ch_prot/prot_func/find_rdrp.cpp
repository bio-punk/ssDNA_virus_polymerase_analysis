#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define FOREVER for(;;)

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

const static string endl = "\n";

struct apple {
	string name;
	string md5;
	string length;
	string databaseName;
	string id;
	string protName;
	string head;
	string tail;
	string evalue;
	string t;
	string date;
	string interProNumber;
	string protFunc;
};


int main(void)
{
	vector<apple> pfomDB;

	ifstream in("pfam.tsv");
	ofstream pfam_id("pfam_id.txt");
	FOREVER {
		apple tmp;
		getline(in, tmp.name, '\t');
		getline(in, tmp.md5, '\t');
		getline(in, tmp.length, '\t');
		getline(in, tmp.databaseName, '\t');
		getline(in, tmp.id, '\t');
		getline(in, tmp.protName, '\t');
		getline(in, tmp.head, '\t');
		getline(in, tmp.tail, '\t');
		getline(in, tmp.evalue, '\t');
		getline(in, tmp.t, '\t');
		getline(in, tmp.date, '\t');
		getline(in, tmp.interProNumber, '\t');
		getline(in, tmp.protFunc);
		if (
			tmp.protFunc.find("RNA dependent RNA polymerase")!= -1 
			|| tmp.protFunc.find("RNA-directed RNA polymerase") != -1
			|| tmp.protName.find("RNA-directed RNA polymerase") != -1
			|| tmp.protName.find("RNA dependent RNA polymerase") != -1) 
			{ pfomDB.push_back(tmp); }
		if (in.eof()) { break; }
	}
	for (int i = 0; i < pfomDB.size(); i++) {
		cout 
			<< pfomDB[i].name << '\t'
			<< pfomDB[i].id << '\t'
			<< pfomDB[i].protName << '\t'
			<< pfomDB[i].evalue << '\t'
			<< pfomDB[i].protFunc 
		<< endl;
		bool ctn = false;
		for (int k = 0; k < i; k++) {
			if (pfomDB[i].id == pfomDB[k].id) { ctn = true; break; }
		}
		if (ctn) { continue; }
		pfam_id << pfomDB[i].id << endl;
	}

	return 0;
}