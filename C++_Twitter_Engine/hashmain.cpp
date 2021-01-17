#include "hash.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	cout<< calculateHash("abc123") << endl << endl;

	cout << calculateHash("password") << endl;

	return 1;
}
