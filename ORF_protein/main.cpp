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
#include "codon.h"
#include "protein.h"

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

static const int PROTEIN_MIN_LENGTH = 100;

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
		//testFile << s << "\t";
		for (int i = 0; i < codeTable.size(); i++) {
			if (!codeTable[i].equal(s)) { continue; }
			ptSeq += codeTable[i].amiName();
			//testFile << codeTable[i].code() << '\t' <<codeTable[i].amiName() << endl;
		}
	}
	return ptSeq;
}

void set_ORFp(genome & g, vector<codon> codeTable) {
	string seq = g.seq();
	string ptSeq = translate(seq, codeTable);
	g.insert_orfp(ptSeq);//1

	seq.erase(seq.begin());
	ptSeq = translate(seq, codeTable);
	g.insert_orfp(ptSeq);//2

	seq.erase(seq.begin());
	ptSeq = translate(seq, codeTable);
	g.insert_orfp(ptSeq);//3

	string cSeq = g.compStrand();
	ptSeq = translate(cSeq, codeTable);
	g.insert_orfp(ptSeq);//4

	cSeq.erase(cSeq.begin());
	ptSeq = translate(cSeq, codeTable);
	g.insert_orfp(ptSeq);//5

	cSeq.erase(cSeq.begin());
	ptSeq = translate(cSeq, codeTable);
	g.insert_orfp(ptSeq);//6
}

void put_Protein(genome g) {
	string name = g.name();
	for (int i = 0; i < 6; i++) {
		string orfp = g.orfp(i);
		string proteinSeq;
		for (int k = 0; k < orfp.size(); k++) {
			if ('*' == orfp[k]) {
				if (proteinSeq.size() <= PROTEIN_MIN_LENGTH) { proteinSeq.clear(); continue; }
				testFile << ">" << name << " orf:" << i << endl << proteinSeq << endl;
				proteinSeq.clear();
				continue;
			}
			proteinSeq += orfp[k];
		}
	}
}

int main(void)
{
	testFile.open("test.txt");
	vector<codon> codeTable;
	get_CT(codeTable);

	vector<genome> virusLib;
	get_VL0(virusLib);
	cout << "success read!" << endl;

	//vector<protein> proteinLib;

	for (int i = 0; i < virusLib.size(); i++) {
		set_ORFp(virusLib[i], codeTable);
		put_Protein(virusLib[i]);
		cout << "success calc virus:" << i + 1 << "/" << virusLib.size() << endl;
	}
	/*
	for (int i = 0; i < proteinLib.size(); i++) {
		testFile << ">" << proteinLib[i].name() << " " << proteinLib[i].ORFIndex() << endl << proteinLib[i].seq() << endl;
	}
	*/

	/*
	string p = virusLib[0].orfp(2);
	string s = virusLib[0].seq();
	ifstream stdFile;
	stdFile.open("std.txt");
	string buff;
	string stdp;
	while (getline(stdFile, buff)) {
		for (int i = 0; i < buff.size(); i++) {
			if ('A' <= buff.c_str()[i] && buff.c_str()[i] <= 'Z') { stdp += buff[i]; }
			if ('*' == buff.c_str()[i]) { stdp += buff[i]; }
 		}
 		getline(stdFile, buff);
	}

	cout << stdp.size() << "\t" << p.size() << endl;

	if (stdp == p) { cout << "right!\n"; }
	if (stdp != p) {
		for (int i = 0; i < stdp.size(); i++) {
			if (stdp[i] != p[i]) { cout << "error ! " << stdp[i] << "\t" << p[i] << endl; }
		}
	}
	*/
	testFile.close();
	return 0;
}