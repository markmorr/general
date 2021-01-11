#include "heap.h"

using namespace std;

int main()
{	
	
	Heap<int,std::equal_to<int>, std::less<int>, std::hash<int> > myheap(2);
	
	myheap.push(3);
	myheap.push(5);
	myheap.push(9);
	myheap.push(68);
	myheap.push(1);
	myheap.push(7);
	myheap.push(15);
	myheap.push(4);
	myheap.push(10);
	myheap.push(2);
	myheap.push(2);
	myheap.push(21);



	cout << "elements popped from top are are: " << endl;
	for (int i = 0; i < 12; i++)
	{
		cout << "currtop: " << myheap.top() << endl;
		myheap.pop();
	}
	cout << endl;


	myheap.push(4);
	myheap.push(10);
	myheap.push(1);
	myheap.push(7);
	myheap.push(33);
	myheap.push(99);
	myheap.push(14);


	cout << endl;
	cout << endl;	

	cout << "elements popped from top are : " << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "currtop: " << myheap.top() << endl;
		myheap.pop();
	}
	cout << endl;
	//cout << myheap.empty() << endl;


	cout << "Decreasing Key Version" << endl;
	myheap.push(4);
	myheap.push(10);
	myheap.push(1);
	myheap.push(7);
	myheap.push(33);
	myheap.push(99);
	myheap.push(14);



	cout << endl;
	cout << endl;	

	myheap.decreaseKey(99,8);


	//myheap.decreaseKey(8,0);
	//cout << myheap.size() << endl;

	cout << "elements popped from top are : " << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "currtop: " << myheap.top() << endl;
		cout << "PRINT POP STATEMENT" << endl;
		myheap.pop();
	}
	cout << endl;

	//1 4 7 10 99 33 14

	// cout << "is it empty? " << myheap.empty() << endl;

	// myheap.push(1);
	// myheap.push(2);

	// cout << "currtop should be 1 or 2, actual is: " << myheap.top() << endl;
 // 	myheap.pop();

 // 	myheap.push(3);
 // 	myheap.push(1);
 // 	cout << "currtop should be something, actual is: " << myheap.top() << endl;






	



	//want to check stuff is in right order after you push tem
	//draw it out follow indexes
	


	return 1;
}

//function printstuff to output file

