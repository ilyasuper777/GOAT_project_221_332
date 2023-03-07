#include "encryption_class_structure.h"

Encryption::Encryption(string str) {
	// initialization a variable KEY with a random value
	srand(unsigned(time(nullptr)));
	key = bitset <8>(65 + rand() % (122 - 64));

	// converting a string into binary codes
	for (int i = 0; i < str.size(); i++) {
		binCodes.push_back(bitset <8>(str[i]));
	}
}

Encryption::Encryption(vector <bitset <8> > bits, bitset <8> keyValue) {
	binCodes = bits;
	key = keyValue;
}

Encryption::~Encryption() {
	binCodes.erase(binCodes.begin(), binCodes.end());
}

vector <bitset <8> > Encryption::encrypt() {
	vector < bitset <8> > encryptingBits;
	for (int item = 0; item < binCodes.size(); item++) {
		bitset <8> bitsAddtion;
		for (int idx = 0; idx < binCodes[item].size(); idx++) {
			binCodes[item][idx] != key[idx] ? bitsAddtion.set(idx, 1) : bitsAddtion.set(idx, 0);
		}
		encryptingBits.push_back(bitsAddtion);
	}
	return encryptingBits;
}

bitset <8> Encryption::getKey() {
	return key;
}

string Encryption::decrypt() {
	string decryptedBits;
	for (int item = 0; item < binCodes.size(); item++) {
		bitset <8> bitsAddition;
		for (int idx = 0; idx < binCodes[item].size(); idx++) {
			binCodes[item][idx] != key[idx] ? bitsAddition.set(idx, 1) : bitsAddition.set(idx, 0);
		}
		decryptedBits.push_back(char(bitset<8>(bitsAddition).to_ulong()));
	}
	return decryptedBits;
}
