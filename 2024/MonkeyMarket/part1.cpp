#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 16777216;

void mixAndPrune(ll& secretNumber,const ll& number) {
	// Mix
	secretNumber ^= number;
	// Prune
	secretNumber %= MOD;
}

void nextSecretNumber(ll& secretNumber) {
	// Step1
	ll result = secretNumber * 64;
	mixAndPrune(secretNumber, result);
	
	// Step2
	result = secretNumber / 32;
	mixAndPrune(secretNumber, result);
	
	// Step3
	result = secretNumber * 2048;
	mixAndPrune(secretNumber, result);
}

void getNthSecretNumber(ll& secretNumber, int n) {
	for(int i = 1; i <= n; ++i) {
		nextSecretNumber(secretNumber);
		// printf("%lld\n", secretNumber);
	}
}

int main(int argc, char const *argv[]) {
	
	string line;
	ll secretNumber;
	ll sum = 0;
	while(getline(cin,line)) {
		secretNumber = stoll(line);
		// printf("%lld: ", secretNumber);
		getNthSecretNumber(secretNumber,2000);
		// printf("%lld\n", secretNumber);
		sum += secretNumber;
	}
	
	printf("%lld\n", sum);

	return 0;
}