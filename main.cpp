#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <set>

#include "ssdna.h"
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
		//printf("%c\n",amiName);
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

int get_VL0(vector<ssDNA> & v) {
	ifstream seqFile;
	seqFile.open("seq.txt");
	string buff;
	string name;
	string seq;
	while (getline(seqFile, buff)) {
		if ('>' == buff.c_str()[0]) {		
			ssDNA tmp;
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
	ssDNA tmp;
	tmp.setName(name);
	tmp.setSeq(seq);
	v.push_back(tmp);

	seqFile.close();
	return 0;
}

int main(void)
{
	testFile.open("test.txt");
	vector<codon> codeTable;
	get_CT(codeTable);

	vector<ssDNA> virusLib;
	get_VL0(virusLib);

	virusLib.erase(virusLib.begin());
	for (int i = 0; i < virusLib.size(); i++) { testFile << virusLib[i].name() << endl; }

	testFile.close();
	return 0;
}
