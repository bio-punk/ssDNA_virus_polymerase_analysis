#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 

#define ever ;;
#define endl '\n'
#define tab '\t'

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::reverse;

const string spaces10 = "          ";
const string spaces5  = "     ";
const string spaces4  = "    ";
const char enter = 13;

int debugModel;

ofstream testOut("test.txt");

struct species {
	string name;
	string id;
	string host; //宿主
};

struct family {
	string name;
	vector<species> s;
	bool empty() { return s.size() < 1; }
	void clear() { name.clear(); s.clear(); }
};

struct superFamily {
	vector<family> f;
	string name;
};

inline bool isFamilyName(string s) {
	return (s[0] != ' ');
}

inline bool isSpecies(string s) {
	return (-1 != s.find(spaces10));
}

inline bool haveSubspecies(string s) {
	if (s[0] == ' ' && s[1] == s[0] && s[2] == s[0] && s[3] == s[0] && s[4] != s[0]) {
		int head;
		for (head = 0; head < s.size(); head++) { if (s[head] == tab) { break; } }
		head++;
		if (s[head] == '-') { return true; }
	}
	return false;
}

inline string find_host_of_spaces4(string s) {
	s.erase(s.begin(), s.begin() + 4);
	s.erase(s.end() - 2, s.end());
	for (int i = 0; i < 7; i++) {
		int tab_p = s.find(tab);
		if (tab_p == -1) { cout << "dm:" << debugModel << " fuck host a:" << s << endl; return s; }
		s.erase(s.begin(), s.begin() + tab_p + 1);
	}
	int tab_p = s.find(tab);
	if (tab_p == -1) { cout << "dm:" << debugModel << " fuck host b:" << s << endl; return s; }
	s.erase(s.begin() + tab_p, s.end());
	if (s == "") { s = "-"; }
	return s;
}

inline string find_name_of_spaces4(string s) {
	s.erase(s.begin(), s.begin() + 4);
	int tab_p = s.find(tab);
	if (tab_p == -1) { cout << "fuck name 4:" << s << endl; return s; }
	s.erase(s.begin() + tab_p, s.end());
	return s;
}

inline string find_name_of_spaces10(string s) {
	//cout << "enter ok" << endl;
	s.erase(s.begin(), s.begin() + 10);
	//cout << s << endl;
	int space_p = s.find(spaces5);
	if (space_p == -1) { s = spaces4 + s; return find_name_of_spaces4(s); }
	s.erase(s.begin() + space_p, s.end());
	//cout << s << endl;
	return s;
}

inline string find_id(string s) {
	int head = s.find("NC_");
	if (head == -1) { cout << "fuck id:" << s << endl; }
	
	string rt;
	rt.append(s, head, 9);

	return rt;
}

inline bool nonValue(string s) {
	if (s.find("Newbury-1 virus") != -1) { return true; }
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == enter) { continue; }
		if (s[i] == ' ') { continue; }
		if ('0' <= s[i] && s[i] <= '9') { continue; }
		if ('a' <= s[i] && s[i] <= 'z') { continue; }
		if ('A' <= s[i] && s[i] <= 'Z') { continue; }
		return false;
	}
	return true;
}

inline bool non_id(string s) {
	return (s.find("NC_") == -1);
}

superFamily get_family(string sffn) {
	ifstream fin(sffn);
	
	string name;
	getline(fin, name);
	
	int head = name.find(':');
	name.erase(name.begin(), name.begin() + head + 2);
	head = name.find('(');
	name.erase(name.begin() + head - 1, name.end());
	
	superFamily mySF;
	mySF.name = name;

	string table;
	getline(fin, table);

	family nowFamily;
	nowFamily.name = mySF.name;
	string hostName;
	for(ever) {
		debugModel =  -1;
		if (fin.eof()) { fin.close(); break; }
		string tmp;
		getline(fin, tmp);
		
		//cout << tmp << endl;

		if (isFamilyName(tmp)) {
			debugModel = 1;
			if (nowFamily.empty()) {
				//cout << "1" << endl;
				nowFamily.name = tmp;
				continue;
			}
			mySF.f.push_back(nowFamily);
			//cout << mySF.f.size() << endl;
			nowFamily.clear();
			nowFamily.name = tmp;
			continue;
		}

		if (haveSubspecies(tmp)) {
			debugModel = 2;
			hostName = find_host_of_spaces4(tmp);
			continue;
		}

		if (isSpecies(tmp)) {
			debugModel = 3;
			species nSp;
			nSp.host = hostName;
			nSp.name = find_name_of_spaces10(tmp);
			if (non_id(tmp)) { continue; }
			nSp.id = find_id(tmp);
			nowFamily.s.push_back(nSp);
			//cout << nSp.id << tab << nSp.name << tab << nSp.host << endl;
			continue;
		}

		if (nonValue(tmp)) { continue; }

		debugModel = 4;
		species nSp;
		nSp.host = find_host_of_spaces4(tmp);
		if (non_id(tmp)) { continue; }
		nSp.id = find_id(tmp);
		nSp.name = find_name_of_spaces4(tmp);
		nowFamily.s.push_back(nSp);
		//cout << nSp.id << tab << nSp.name << tab << nSp.host << endl;

		if (fin.eof()) { fin.close(); break; }
	}
	return mySF;
}

int main(void)
{
	string fileName;
	cin >> fileName;
	ifstream fn(fileName);
	
	vector<superFamily> ssRNAV;
	for(ever) {
		string superFamilyFile;
		fn >> superFamilyFile;

		superFamily tmp = get_family(superFamilyFile);
		ssRNAV.push_back(tmp);
		if (fn.eof()) { fn.close(); break; }
	}

	for (int i = 0; i < ssRNAV.size(); i++) {
		superFamily nowSF = ssRNAV[i];
		for (int k = 0; k < nowSF.f.size(); k++) {
			family nowF = nowSF.f[k];
			for (int w = 0; w < nowF.s.size(); w++) {
				species now = nowF.s[w];
				testOut << now.id << tab << now.name << tab << now.host << tab << nowF.name << tab << nowSF.name << endl;
			}
		}
	}

	testOut.close();
	return 0;
}
