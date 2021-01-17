#include <vector>
#include <iostream>

using namespace std;


// void mergeSort (std::vector<T>& myArray, Comparator comp);
// void mergeSortHelper(int start, int end, std::vector<T>& myArray, Comparator comp);



template <class T, class Comparator>
void mergeSortHelper(int start, int end, std::vector<T>& myArray, Comparator comp)
{
	if (start == end)
	{
		return;
	}
	if (start > end){
		return;
	}
	
	mergeSortHelper(start,(start+end)/2, myArray, comp);
	mergeSortHelper((start+end)/2 + 1, end, myArray, comp);

	int leftIndex = start;
	int rightIndex = (start+end)/2 + 1;
	
	std::vector<T> sortedArray; //at most push back nlogn times (nlogn comparisons??)
	while((leftIndex < (start+end)/2 + 1) && (rightIndex < end + 1)) //these are same distance //**
	{
		
		if (!comp(myArray[rightIndex],myArray[leftIndex]))
		{
			sortedArray.push_back(myArray[leftIndex]);
			
			leftIndex++;
		}

		// if (comp(myArray[leftIndex],myArray[rightIndex])
		else
		{
			sortedArray.push_back(myArray[rightIndex]);
		
			rightIndex++;
		}

	} 

	if (leftIndex >= (start+end)/2 + 1) //if left finished first
	{
		while (rightIndex <= end) //**
		{
			sortedArray.push_back(myArray[rightIndex]);
			
			rightIndex++;
		}
	}

	if (rightIndex >= end + 1) //if right finished first //**
	{
		while (leftIndex <= (start+end)/2)
		{
			sortedArray.push_back(myArray[leftIndex]);
			
			leftIndex++;
		}
	}



	for(int i = start; i <= end; i++) //load it up //pushing back nlogn timems into this temp guy
	{
		myArray[i] = sortedArray[i - start];
		//std::cout << myArray[i] << std::endl;
	}

	//std::cout << std::endl;

}


template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp)
{
	mergeSortHelper(0, myArray.size() -1, myArray, comp);
	 //check the start and end 
}
