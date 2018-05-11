#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "fasta.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

int main(void)
{
	ifstream nameFile("out.txt");
	ifstream database("base001.fasta");
	ofstream pmf("polymerase_seq.fasta");

	vector<fasta> base;
	string name, seq;
	while (!database.eof()) {
		database >> name >> seq;
		name.erase(name.begin());
		fasta tmp(name, seq);
		base.push_back(tmp);
	}
	database.close();
	cout << "init\n";

	vector<fasta> outp;
	while (!nameFile.eof()) {
		nameFile >> name;
		cout << name << endl;
		bool haven = false;
		for (int i = outp.size() - 1; i >= 0; i--) { 
			if (name == outp[i].name()) { haven = true; break; }
		}
		if (haven) { continue; }
		for (int i = 0; i < base.size(); i++) {
			if (name != base[i].name()) { continue; }
			outp.push_back(base[i]);
			break;
		}
	}
	nameFile.close();

	for (int i = 0; i < outp.size(); i++) {
		pmf << '>' << outp[i].name() << endl << outp[i].seq() << endl;
	}
	pmf.close();

	return 0;
}