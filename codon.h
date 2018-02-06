class codon {
private:
	char __code[4];
	char __amiName;
public: //code & set code
	inline int setCode(char str[4]) {
		if ('\0' != str[3]) { return -11; } //illegal input : IO error is 1x
		__code[0] = str[0];
		__code[1] = str[1];
		__code[2] = str[2];
		__code[3] = '\0';
		return 0;
	}
	
	inline void code(char str[4]) {
		str[0] = __code[0];
		str[1] = __code[1];
		str[2] = __code[2];
		str[3] = '\0';
	}

public: //amiName & set amiName
	inline const char amiName() { return __amiName; }
	inline void setAmiName(const char c) { __amiName = c; }

public:
	inline bool equal(char str[4]) {
		if ('\0' != str[3]) { return -11; } //illegal input : IO error is 1x
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