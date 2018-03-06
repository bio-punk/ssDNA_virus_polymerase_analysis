using std::string;
using std::vector;

class SSRNA {
public:
	virtual const string name() = 0;
	virtual const string seq() = 0;
	virtual const string orfp(const int x) = 0;
public:
	virtual void setName(const string str) = 0;
	virtual void setSeq(const string str) = 0;
};

class genome : public SSRNA {
private: //variable
	string __name;
	string __seq;
	string __comStr;
	vector<string> __orfp;
public:  //clear
	void clear() {
		__name.clear();
		__seq.clear();
		__orfp.clear();
		__comStr.clear();
	}
public:
	const string name() { return __name; }
	const string seq() { return __seq; }
	const string orfp(const int x) { return __orfp.at(x); }
	string compStrand() {
		if (__comStr.size() == __seq.size()) { return __comStr; }
		for (int i = __seq.size() - 1; i >= 0; i--) {
			char ch = __seq.c_str()[i];
			if ('A' == ch) { __comStr += 'T'; }
			if ('T' == ch) { __comStr += 'A'; }
			if ('C' == ch) { __comStr += 'G'; }
			if ('G' == ch) { __comStr += 'C'; }
		}
		return __comStr;
	}
public:
	void setSeq(const string str) { __seq = str; }
	void setName(const string str) { __name = str; }
	void insert_orfp(const string str) { __orfp.push_back(str); }
};
