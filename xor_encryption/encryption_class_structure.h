#include <vector>
#include <bitset>
#include <ctime>

using namespace std;


class Encryption {

private:

	vector <bitset <8> > binCodes;
	bitset <8> key;

public:

	Encryption(string str);
	Encryption(vector <bitset <8> > bits, bitset <8> keyValue);
	~Encryption();
	vector <bitset <8> > encrypt();
	bitset <8> getKey();
	string decrypt();

};
