#include "hash.h"
#include <vector>
#include <iostream>

using namespace std;

unsigned long long calculateHash(string mystring)
{
  /* add your code here */
	unsigned long long sum = 0;
	unsigned long long mypow = 1;

	//int size = mystring.size();
	//pow returns a double
	for( int i = 0; i < (int)mystring.size(); i++)
	{
		for(int j = 0; j < i; j++) //have to do manually b/c it wouldn't return an unsigned long long 	
		{
			mypow *= 128;
		}
		sum += (mypow)*(mystring[mystring.size()-1-i]); //size was out of bounds

		mypow = 1;
	}

	//cout << "sum: " << sum << endl;

	//pn + (128 * pn-1) + (128^2 * pn-2) + ... + (128^(n-1) * p1)

	unsigned int myarray[4] = {0,0,0,0};

	for(int i = 0; i < 4; i++)
	{
		
		myarray[4-i-1] = (sum) % 65521; //^ not allowed becasue bitwise operations
		sum = sum/65521;

	}

	unsigned long long result = (45912 * myarray[0] + 35511 * myarray[1] + 65169 * myarray[2] 
		+ 4625 * myarray[3]) % 65521;

	return result;
}
//example on website?

//unsigned int firstDigit = 0,secondDigit = 0,thirdDigit = 0,fourthDigit = 0;
	//vector<int> digits;
		// unsigned int w1 = firstDigit;
	// unsigned int w2 = secondDigit;
	// unsigned int w3 = thirdDigit;
	// unsigned int w4 = fourthDigit;
	////step 4
	//int temp = sum;