#include <bits/stdc++.h>
using namespace std;

#define ll long long

set<char> valid = {'m','u','l','d','o','\'','n','t','(',')',',','0','1','2','3','4','5','6','7','8','9'};
set<char> digits = {'0','1','2','3','4','5','6','7','8','9'};


char ch;
ll result = 0;
string command = "";
string enable = "";
bool commaFlag = false, isEnabled = true;

void reset() {
	command = "";
	commaFlag = false;
}

void processCommand() {
	// cout << command << "\n";
	ll a = 0, b = 0;
	for(int i = 4; i < command.size(); ++i) {
		if(command[i] == ',') {
			a = b;
			b = 0;
			continue;
		}
		if(command[i] == ')') break;
		b *= 10;
		b += command[i] - '0';
	}
	result += a * b;
}

void processEnable() {
	if(enable == "do()") {
		isEnabled = true;
	}
	
	if(enable == "don't()") {
		isEnabled = false;
	}
}

void handleMul() {
	if(ch == 'm') {
		reset();
		command += ch;
	} else if(ch == 'u') {
		if(command.back() == 'm') command += ch;
		else reset();
	} else if(ch == 'l') {
		if(command.back() == 'u') command += ch;
		else reset();
	} else if(ch == '(') {
		if(command.back() == 'l') command += ch;
		else reset();
	} else if(digits.count(ch) != 0) {
		if(command.back() == '(' || command.back() == ',' || digits.count(command.back()) != 0) command += ch;
		else reset();
	} else if(ch == ',') {
		if(digits.count(command.back()) != 0) {
			command += ch;
			commaFlag = true;
		}
		else reset();
	} else if(ch == ')') {
		if(digits.count(command.back()) != 0 && commaFlag) {
			command += ch;
			// Process the valid command if enabled
			if(isEnabled) {
				processCommand();
			}
			reset();
		} else reset();
	}
}

void handleDoDont() {
	if(ch == 'd') {
		enable = "";
		enable += ch;
	} else if(ch == 'o') {
		if(enable.back() == 'd') enable += ch;
		else enable = "";
	} else if(ch == 'n') {
		if(enable.back() == 'o') enable += ch;
		else enable = "";
	} else if(ch == '\'') {
		if(enable.back() == 'n') enable += ch;
		else enable = "";
	} else if(ch == 't') {
		if(enable.back() == '\'') enable += ch;
		else enable = "";
	} else if(ch == '(') {
		if(enable.back() == 'o' || enable.back() == 't') enable += ch;
		else enable = "";
	} else if(ch == ')') {
		if(enable.back() == '(') {
			// toggle the isEnabled boolean
			enable += ch;
			processEnable();
		}
		enable = "";
	}
}

int main(int argc, char const *argv[]) {

	ios::sync_with_stdio(0);
    cin.tie(0);
	
	#ifdef ONLINEJUDGE
	   // freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
	#endif
	   
	ifstream file("input.txt");

    if (!file.is_open()) {
        return 1;
    }
    
    while (file.get(ch)) {
       	if(valid.count(ch) != 0) {
       		handleDoDont();
       		handleMul();
       	} else {
       		reset();
       	}
    }
    
    cout << result << "\n";

    file.close();

	return 0;
}