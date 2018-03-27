#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void inc(string & s) {
	if (s[2] == '9' && s[1] == '9') { s[0]++; s[1] = '0'; s[2] = '0'; return; }
	if (s[2] == '9') { s[1]++; s[2] = '0'; return; }
	s[2]++;
}

int main(void)
{
	string No = "000";
	for (int i = 1; i <= 897; i++) {
		cout << "echo `date +\"%Y/%m/%d-%H:%M:%S\"`" << endl;
		inc(No);
		cout 
			<< "echo " 
			<< No
			<< " is working!"
		<< endl;
		cout 
			<< "blastp -query input" 
			<< No
			<< ".fasta -outfmt 6 -evalue 1e-3 -db psb -num_threads 2 -max_target_seqs 10 -out out"
			<< No
			<< ".txt"
		<< endl;
	}
	return 0;
}