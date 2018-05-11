using std::string;

class fasta{
private:
	string __name;
	string __seq;
public:
	fasta() {
		__name.clear();
		__seq.clear();
	}
	fasta(string n, string s) {
		__name = n;
		__seq = s;
	}
	void setName(string str) {
		__name = str;
	}
	void setSeq(string str) {
		__seq = str;
	}
	const string name(void) { return __name; }
	const string seq(void) { return __seq; }
};