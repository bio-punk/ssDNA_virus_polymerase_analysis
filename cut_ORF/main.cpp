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

static int PROTEIN_MIN_LENGTH;
static long long cnt = 0;
static int SEQ_NUM_GAP = 10000;
string outputFileName;
string outNum = "001";

ofstream outputFile;

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
		for (int i = 0; i < codeTable.size(); i++) {
			if (!codeTable[i].equal(s)) { continue; }
			ptSeq += codeTable[i].amiName();
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

void inc(string & s) {
	if (s[2] == '9' && s[1] == '9') { s[0]++; s[1] = '0'; s[2] = '0'; return; }
	if (s[2] == '9') { s[1]++; s[2] = '0'; return; }
	s[2]++;
}

void put_Protein(genome g) {
	string name = g.name();
	for (int i = 0; i < 6; i++) {
		string orfp = g.orfp(i);
		string proteinSeq;
		int protCnt = 1;
		for (int k = 0; k < orfp.size(); k++) {
			if ('*' == orfp[k]) {
				if (proteinSeq.size() <= PROTEIN_MIN_LENGTH) { proteinSeq.clear(); continue; }
				outputFile << ">" << name << "_orf:" << i << "_" << protCnt++ << endl << proteinSeq << endl;
				cnt++;
				proteinSeq.clear();
				if (cnt % SEQ_NUM_GAP != 0) { continue; }
				inc(outNum);
				//cout << cnt << endl;
				//cout << outputFileName << endl;
				outputFile.close();
				outputFileName.erase(outputFileName.size() - 9, 9);
				outputFileName += outNum;
				outputFileName += ".fasta";
				outputFile.open(outputFileName);
				//cout << outputFileName << endl;
				//system("pause");
				continue;
			}
			proteinSeq += orfp[k];
		}
	}
}

int main(void)
{
	cout << "output File:\t";
	cin >> outputFileName;
	cout << "PROTEIN MIN LENGTH(default:60):\t";
	cin >> PROTEIN_MIN_LENGTH;
	cout << "how many seqs in a file?\t";
	cin >> SEQ_NUM_GAP;
	if (PROTEIN_MIN_LENGTH < 1) { PROTEIN_MIN_LENGTH = 60; }

	//outputFile.open(outputFileName);

	vector<codon> codeTable;
	get_CT(codeTable);

	vector<genome> virusLib;
	get_VL0(virusLib);
	cout << "success read!" << endl;
	
	outputFileName += outNum;
	outputFileName += ".fasta";
	outputFile.open(outputFileName);

	for (int i = 0; i < virusLib.size(); i++) {
		set_ORFp(virusLib[i], codeTable);
		put_Protein(virusLib[i]);
		cout << "success calc virus:" << i + 1 << "/" << virusLib.size() << endl;
	}

	ofstream sizeFile;
	sizeFile.open("size.txt");
	sizeFile << cnt << endl;
	
	sizeFile.close();
	outputFile.close();

	//system("pause");

	return 0;
}
