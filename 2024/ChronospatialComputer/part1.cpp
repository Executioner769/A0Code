#include <bits/stdc++.h>
using namespace std;

class Machine {
private:
	int A, B, C;

	int ip = 0;
	string output;
	vector<int> program;
	
	// get Operand
	int getOp(bool isLiteral) {
		int operand = program[ip++];
		assert(operand >= 0 && operand <= 7);
		
		if(!isLiteral) {
			if(operand >= 0 && operand <= 3) return operand;
			else if(operand == 4) return A;
			else if(operand == 5) return B;
			else if(operand == 6) return C;
		}
		return operand;
	}
	
	// execute Opcode
	void executeOp() {
		int opcode = program[ip++];
		assert(opcode >= 0 && opcode <= 7);
		
		switch(opcode) {
			case 0: {
				A = A >> getOp(false);
				break;
			}
			case 1: {
				B ^= getOp(true);
				break;
			}
			case 2: {
				B = getOp(false) % 8;
				break;
			}
			case 3: {
				int nip = getOp(true);
				if(A != 0) {
					if(nip >= 0 && nip < program.size()) {
						ip = nip;
					}
				}
				break;
			}
			case 4: {
				getOp(true);
				B ^= C;
				break;
			}
			case 5: {
				int out = getOp(false) % 8;
				if(output.length() != 0) {
					output += ',';
				}
				output += (out + '0');
				break;
			}
			case 6: {
				B = A >> getOp(false);
				break;
			}
			case 7: {
				C = A >> getOp(false);
				break;
			}
		}
	}
	
	void reset() {
		ip = 0;
		output = "";
		program.clear();
	}
	
public:
	Machine(int a, int b, int c) {
		A = a;
		B = b;
		C = c;
		reset();
	}
	
	print() {
		printf("A:%d B:%d C:%d\n",A,B,C);
		printf("Ip:%d\n", ip);
		if(ip < program.size()) {
			printf("Op:%d\n", program[ip]);
		}
		printf("Output: %s\n", output.c_str());
	}

	run(const vector<int>& input, bool printFlag) {
		reset();
		program = input;
		if(printFlag) print();
		while(ip < program.size()) {
			executeOp();
			if(printFlag) print();
		}
	}
	
	string getOutput() {
		return output;
	}
	
};


int main(int argc, char const *argv[]) {
	
	char str[64];
	vector<int> reg;
	int num;
	while(scanf(" %s", &str) != EOF) {
		if(str == "Program:") break;
		num = -1;
		scanf("%s", &str);
		scanf("%d", &num);
		if(num != -1) {
			reg.push_back(num);
		}
	}
	
	scanf("%s", &str);
	vector<int> input;
	for(auto& ch: str) {
		if(isdigit(ch)) {
			input.push_back(ch - '0');
		}
	}
	
	int a = reg[0], b = reg[1], c = reg[2];
	Machine machine(a,b,c);
	
	machine.run(input,false);
	
	machine.print();
	
	return 0;
}
