
#include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;

// function used for randomizing numbers and filling our array
void randomize(int num[], int size)
{
	int random;
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		random = rand() % 10; // using the rand() function and modulus by 10 to get a single digit integer
		num[i] = random;
	}
}

// function used for displaying the contents of our array for testing purposes
void display(int nums[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << nums[i] << " ";
	}
	cout << endl;
}

// Iterative version of a binary search which functions as a way to determine the proper index placement for sorting.
// Our min,max and middle variables are essentially going to be moving around the array a bit depending on where we're making comparisons within each iteration.
// For further details, please see the readme file.
int binarySearch(int nums[], int number, int min, int max)
{
	int middle; // represents the "middle" of our array for checking elements. while this number frequently changes, it's mostly a reference to where we're comparing inbetween our min and max variables
	
	while (min <= max) // checks to see if our minimum element is less than or equal to our maximum element
	{
		middle = (min + max) / 2; // sets a placement for the "middle" of where we're working in our array

		if (number > nums[middle]) // checking to see if our number is greater than the middle element
			min = middle + 1; // if our number is greater than the middle element of our array, we move our minimum to 1 element past the middle
		else if (number < nums[middle]) // checking to see if our number is less than the middle element in our array
			max = middle - 1; // if our number is less than the middle, we set our maximum working space to be 1 element lower than the middle
		else
		{
			//cout << "middle: " << middle << endl;
			return middle; // returns the "middle" index to be swapped, based off our operations above
		}
	}
	//cout << "min: " << min << endl;
	return min; // returns the min index of the element to be swapped
}

// This version of insertion sort was found as pseudocode in our book. Alterations were made to make it functional with a binary search function.
// For details, please view the readme file included with this submission.
void binaryInsertSort(int nums[], int length)
{
	int num, i, location; // num is used for comparisons to hold values in our array, location is the index to be found by our binary search function, i is used as a reference to manuever around our array

	for (int j = 1; j < length; j++) // we start at 1 since we can consider element 0 to be already "sorted" then iterate through the length of our array
	{
		i = j - 1; // we set i to be j - 1 which starts i at 0
		num = nums[j]; // num is iteratively set to each element (starting at 1) in our array for comparison in our binary search function
		location = binarySearch(nums, num, 0, i); // to find the appropriate index, we call our binary search function and pass in our array, the number we're analyzing, our default minimum of 0 and our default maximum of i

		while (i >= location) // shifting elements down while swapping based on the index location and i
		{
			nums[i + 1] = nums[i]; // we're "moving" (more like copying) the value one element ahead in the array
			i = i - 1; // decrementing i by 1 so we have a reference to properly complete the swap
			//display(nums, 10); // observing to make sure the element is copied
		}
		nums[i + 1] = num; // completing the swap (thanks to the decremented i) by putting our lower number behind our higher number
		display(nums, 10);
	}
}

// function which performs some fun math on a number based on n = 2^k
// detailed explanation can be found in readme file
// runtime is O(n log n)
double timeComplexity(int n)
{
	double time; // variable for holding an accurate measurement of time for testing
	clock_t begin; // variable to record clock ticks to be used for measuring time 
	int i, j; // i is used to store n and j will do calculations based on i

	begin = clock(); // we begin recording clock ticks
	i = n; // the data we took in becomes i, which will act as a basis for j to process
	while (i >= 1) // as long as i >= 1, our outer loop will iterate
	{
		j = i; // j is set to the value of i
		while (j <= n) // as long as j <= n then our inner loop will iterate
		{
			j = 2 * j; // j is multiplied by 2 and set to the result
			//cout << j << endl; // used for observing the pattern of calculations j is undergoing based on i and n
		}
		i = i / 2; // our data set is divided by two before the loop ends and begins another iteration (clear sign of log behavior)
	}
	time = (clock() - begin) / (double)CLOCKS_PER_SEC; // subtracting our current clock ticks minus the clock ticks from our begin variable then converting them to clock ticks per second for an accurate reading of time
	return time;
}

int main()
{
	int numlist[10]; // array to be sorted
	int size = sizeof(numlist) / sizeof(numlist[0]); // determining how large our array is
	
	cout << "Question 1.) Implement a Binary Insertion Sort" << endl;
	cout << "Let's fill an array with 10 random integers" << endl;
	randomize(numlist, size);
	cout << "Here's our array: " << endl;
	display(numlist, size);

	cout << endl << "Here's our Binary Insertion Sort step by step!" << endl;
	display(numlist, size);
	binaryInsertSort(numlist, size);
	cout << endl << "Here's our array after the completed sort!" << endl;
	display(numlist, size);

	cout << endl << endl <<  "Question 2.) What is the time complexity T(n) for the nested loops below?" << endl;
	cout << "Processing time where n = 512: " << timeComplexity(512) <<endl;
	cout << "Processing time where n = 1024: " << timeComplexity(1024) << endl;
	cout << "Processing time where n = 2048: " << timeComplexity(2048) << endl;
	cout << "Time complexity is O(n log n) because: " << endl;
	cout << "1.) Our data set (i) is being halved after each iteration." << endl;
	cout << "2.) Our inner loop relies on N." << endl;

    return 0;
}

