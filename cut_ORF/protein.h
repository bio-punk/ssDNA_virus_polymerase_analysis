class protein {
private:
	string __seq;
	string __name;
	unsigned short __ORFIndex;
public:
	const string seq() { return __seq; }
	const string name() { return __name; }
	const unsigned short ORFIndex() { return __ORFIndex; }
public:
	void setSeq(const string str) { __seq = str; }
	void setName(const string str) { __name = str; }
	void setORFIndex(const unsigned short us) { __ORFIndex = us; }
};