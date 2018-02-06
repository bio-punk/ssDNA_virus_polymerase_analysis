using std::string;
using std::vector;

class SSDNA {
public:
	virtual const string name() = 0;
	virtual const string seq() = 0;
	virtual const string orfp(const int x) = 0;
public:
	virtual void setName(const string str) = 0;
	virtual void setSeq(const string str) = 0;
};

class ssDNA : public SSDNA {
private:
	string __name;
	string __seq;
	vector<string> __orfp;
public:
	void clear() {
		__name.clear();
		__seq.clear();
		__orfp.clear();
	}
public:
	const string name() { return __name; }
	const string seq() { return __seq; }
	const string orfp(const int x) { return __orfp.at(x); }
public:
	void setSeq(const string str) { __seq = str; }
	void setName(const string str) { __name = str; }
	void setOrfp(const string str) { __orfp.push_back(str); }
};