#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <set>

#include "genome.h"
//#include "amiacid.h"
#include "codon.h"

#define MAX_STR 256

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::array;
using std::vector;
using std::string;
using std::set;

ofstream testFile;

int get_CT(vector<codon> & a) {
	FILE *fp;
	fp = fopen("ami.in", "r+");
	if (nullptr == fp) { cout << "File \"ami.in\" cannot be 'read'!\n"; return (-21); }
	for (int i = 0; i < 21; i++) {
		char code[MAX_STR];
		char amiName;
		fscanf(fp, "%c%s\n", &amiName, code);

		char codeTh[4];
		for (int i = 0; i < strlen(code); i++) {
			if (',' == code[i]) {
				codon tmp;
				tmp.setAmiName(amiName);
				tmp.setCode(codeTh);
				codeTh[0] = '\0';
				a.push_back(tmp);
				continue;
			}
			int len = strlen(codeTh);
			codeTh[len] = code[i];
			codeTh[len + 1] = '\0';
			if (strlen(code) == i + 1) {
				codon tmp;
				tmp.setAmiName(amiName);
				tmp.setCode(codeTh);
				codeTh[0] = '\0';
				a.push_back(tmp);
				continue;
			}
		}
	}
	fclose(fp);
	return 0;
}

string record_Name(string buff) {
	string rt;
	for (int i = 1; i < buff.size(); i++) {
		if (' ' == buff.c_str()[i]) { return rt; }
		rt += buff.c_str()[i];
	}
	return rt;
}

int get_VL0(vector<genome> & v) {
	ifstream seqFile;
	seqFile.open("seq.txt");
	string buff;
	string name;
	string seq;
	while (getline(seqFile, buff)) {
		if ('>' == buff.c_str()[0]) {		
			genome tmp;
			tmp.setName(name);
			tmp.setSeq(seq);
			v.push_back(tmp);
			name.clear();
			seq.clear();
			name = record_Name(buff);
			continue;
		}
		seq+=buff;
	}
	genome tmp;
	tmp.setName(name);
	tmp.setSeq(seq);
	v.push_back(tmp);
	v.erase(v.begin());
	seqFile.close();
	return 0;
}

string translate(string gene, vector<codon> codeTable) {
	string ptSeq;
	for (int i = 2; i < gene.size(); i += 3) {
		string s;
		s.clear();
		s += gene[i - 2];
		s += gene[i - 1];
		s += gene[i - 0];
		testFile << s << "\t";
		for (int i = 0; i < codeTable.size(); i++) {
			if (!codeTable[i].equal(s)) { continue; }
			ptSeq += codeTable[i].amiName();
			testFile << codeTable[i].code() << '\t' <<codeTable[i].amiName() << endl;
		}
	}
	return ptSeq;
}

void set_ORFp(genome & g, vector<codon> codeTable) {
	string seq = g.seq();
	string ptSeq = translate(seq, codeTable);
	g.insert_orfp(ptSeq);
}

int main(void)
{
	testFile.open("test.txt");
	vector<codon> codeTable;
	get_CT(codeTable);

	vector<genome> virusLib;
	get_VL0(virusLib);

	for (int i = 0; i < virusLib.size(); i++) {
		testFile << virusLib[i].seq() << endl;
		set_ORFp(virusLib[i], codeTable);
		string s = virusLib[i].orfp(0);
		for (int i = 0; i < s.size(); i++) {
			testFile << s[i] << "  ";
		}
		testFile << endl;
	}

	testFile.close();
	return 0;
}
