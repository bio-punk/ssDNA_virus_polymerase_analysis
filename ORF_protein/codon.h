using std::string;

class codon {
private:
	string __code;
	char __amiName;
public: //code & set code
	inline int setCode(char str[4]) {
		if ('\0' != str[3]) { return -11; } //illegal input : IO error is 1x
		__code.clear();
		for (int i = 0; i < 3; i++) { __code += str[i]; }
	}
	
	inline int setCode(string str) {
		if ('\0' != str.c_str()[3]) { return -11; }
		__code.clear();
		__code = str;
	}
	
	inline void code(char str[4]) {
		str[0] = __code[0];
		str[1] = __code[1];
		str[2] = __code[2];
		str[3] = '\0';
	}

	inline const string code() { return __code; }

	inline const void code(string & str) { str = __code; }

public: //amiName & set amiName
	inline const char amiName() { return __amiName; }
	inline void setAmiName(const char c) { __amiName = c; }

public:
	inline bool equal(char str[4]) {
		if ('\0' != str[3]) { return false; } //illegal input : IO error is 1x
		if (__code[0] != str[0]) { return false; }
		if (__code[1] != str[1]) { return false; }
		if (__code[2] != str[1]) { return false; }
		return true;
	}

	inline bool equal(string str) {
		if ('\0' != str.c_str[3]) { return false; }
		if (3 != str.size()) { return false; } //illegal input
		if (__code[0] != str[0]) { return false; }
		if (__code[1] != str[1]) { return false; }
		if (__code[2] != str[1]) { return false; }
		return true;	
	}

	inline void copy(codon & obj) {
		char str[4];
		char ch;
		obj.code(str);
		ch = obj.amiName();

		setCode(str);
		setAmiName(ch);
	}
};