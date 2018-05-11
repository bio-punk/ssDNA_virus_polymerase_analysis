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

	ifstream in("archivetempnewdbout.tsv");
	ofstream pfam_id("pfam_id.txt");
	FOREVER {
		apple tmp;
		string line, name;
		name.clear();
		getline(in, line);
		int st, tab = 0;
		for (st = 0; st < line.size(); st++) {
			if (line[st] == '\t') { tab++; } 
			if (tab == 3) { break; }
		}
		for (int i = st + 1; i < line.size(); i++) {
			if (line[i] == '\t') { break; }
			name += line[i];
		}
		//cout << name << endl;
		if (line.find("Pfam") != -1 && 
			line[line.size() - 1] == '8' && line[line.size() - 2] == '1' && line[line.size() - 3] == '0' && line[line.size() - 4] == '2')
		{
			cout << line << "\t" << "fuck" << "\t" << "EMBL-EBI" << endl;
			continue;
		}
		if (line.find("Pfam") != -1) { cout << line << endl; }
		/*
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
		//getline(in, tmp.date, '\t');
		cin >> tmp.date;
		getline(in, tmp.interProNumber, '\t');
		getline(in, tmp.protFunc);
		*/
		//cout << tmp.protFunc << endl;
		//if (tmp.databaseName == "Pfam") { pfomDB.push_back(tmp); }
		if (in.eof()) { break; }
	}
	return 0;
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