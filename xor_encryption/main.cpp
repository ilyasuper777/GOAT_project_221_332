#include "encryption_class_structure.h"
#include <iostream>

using namespace std;

int main() {

	// encryption string
	string str = "Hello World !";

	// initialize a class object
	Encryption enc(str);

	// calling encrypt method
	vector <bitset <8> > encrypted_string = enc.encrypt();

	// get the value of the KEY variable
	bitset<8> key = enc.getKey();

	// initialize a class object
	Encryption dec(encrypted_string, key);

	// calling decrypt method
	string decrypted_string = dec.decrypt();

	cout << decrypted_string << endl;

}