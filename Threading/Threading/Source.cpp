#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <thread>
#include <time.h>
#include <Windows.h>

using namespace std;

const int size = 250000;

void writeIntegersInFile(int arr[], int size, string fileName)
{
	ofstream outData(fileName);
	int i;
	for (i = 0; i < size; i++)
	{
		outData << arr[i] << " ";
	}
	outData.close();
}

void generateRandomNumbers(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int number = 1 + rand() % (INT_MAX / 2);
		arr[i] = number;
	}
}

void writeIntegers(int arr[], int size, string fileName)
{
	generateRandomNumbers(arr, size);
	writeIntegersInFile(arr, size, fileName);
}

void display(int A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}

void SelectionSort(int arr[], int size)
{
	
	cout << "\nSelection sort:- Thread ID: ";
	cout <<endl<<this_thread::get_id()<<"\n";

	int i, j, min;
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++)
			if (arr[j] < arr[min])
				min = j;
		swap(arr[i], arr[min]);
	}
}

void Merge(int A[], int low, int mid, int high)
{
	int LH = mid - low + 1;
	int  RH = high - mid;
	int *left = new int[LH];
	int *right = new int[RH];
	for (int i = 0; i < LH; i++)
		left[i] = A[low + i];
	for (int j = 0; j < RH; j++)
		right[j] = A[j + mid + 1];
	int s = 0, j = 0, k = low;
	while (s < LH&&j < RH)
	{
		if (left[s] < right[j])
			A[k++] = left[s++];
		else
			A[k++] = right[j++];
	}
	while (s < LH)
		A[k++] = left[s++];
	while (j < RH)
		A[k++] = right[j++];
	delete[]left;
	delete[]right;
}

void MergeSort(int A[], int low, int high,int count)
{
	if (count == 0)
	{
		cout << "\nMerge sort:- Thread ID: ";
		cout <<endl <<this_thread::get_id()<<"\n";
	}
	int mid = (low + high) / 2;
	if (low < high)
	{
		MergeSort(A, low, mid,1);
		MergeSort(A, mid + 1, high,1);
		Merge(A, low, mid, high);
	}
}

int partition(int A[], int low, int high)
{
	int i = low;
	for (int j = low; j < high; j++)
	{
		if (A[j] < A[high])
		{
			swap(A[i], A[j]);
			i++;
		}
	}
	swap(A[i], A[high]);
	//i++;
	return i;
}

void QuickSort(int A[], int low, int high,int count)
{
	if (count == 0)
	{
		cout << "\nQuick sort:- Thread ID: ";
		cout <<endl <<this_thread::get_id()<<"\n";
	}
	if (low < high)
	{
		int index = partition(A, low, high);
		QuickSort(A, low, index - 1,1);
		QuickSort(A, index + 1, high,1);
	}
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void InsertionSort(int arr[], int size)
{
	cout << "\nInsertion sort:- Thread ID: ";
	cout <<endl <<this_thread::get_id()<<"\n";

	int i, key, j;
	for (i = 1; i < size; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void mergeArrays(int arr1[], int arr2[], int size1,
	int size2, int arr3[])
{
	int i = 0, j = 0, k = 0;

	while (i < size1 && j < size2)
	{
		//if element of arr1 is smaller 
		if (arr1[i] < arr2[j])
			arr3[k++] = arr1[i++];
		else
			arr3[k++] = arr2[j++];
	}

	//loop terminates but if there are elements in either of the two arrays then store them in arr3
	while (i < size1)
		arr3[k++] = arr1[i++];

	while (j < size2)
		arr3[k++] = arr2[j++];
}

void printTime(string msg)
{
	time_t my_time = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &my_time);
	cout << msg <<": "<<str;
}


int main()
{
	srand(time(NULL));
	int *list1 = new int[size];
	int *list2 = new int[size];
	int *list3 = new int[size];
	int *list4 = new int[size];
	int numberOfLists = 4;
	string fileName;

	writeIntegers(list1, size, "Unsorted_00.txt");
	writeIntegers(list2, size, "Unsorted_01.txt");
	writeIntegers(list3, size, "Unsorted_02.txt");
	writeIntegers(list4, size, "Unsorted_03.txt");


	thread thread1(MergeSort, list1, 0, size - 1,0);

	thread thread2(SelectionSort, list2, size);
	
	thread thread3(InsertionSort, list3, size);
	
	thread thread4(QuickSort, list4, 0, size - 1,0);


	if (thread1.joinable())
	{
		Sleep(1000);
		cout << "\nMerge Sort" << " ";
		printTime("Start Time");
		thread1.join();
		printTime("End Time");
	}

	if (thread2.joinable())
	{
		cout << "\nSelection Sort" << " ";
		printTime("Start Time");
		thread2.join();
		printTime("End Time");
	}

	if (thread3.joinable())
	{
		cout << "\nInsertion Sort" << " ";
		printTime("Start Time");
		thread3.join();
		printTime("End Time");
	}
	if (thread4.joinable())
	{
		cout << "\nQuick Sort" << " ";
		printTime("Start Time");
		thread4.join();
		printTime("End Time");
	}
	int *finalArray = new int[size * 2];
	int *finalArray1 = new int[size * 3];
	int *finalArray2 = new int[size * 4];

	mergeArrays(list1, list2, size, size, finalArray);
	mergeArrays(finalArray, list2, size * 2, size, finalArray1);
	mergeArrays(finalArray1, list2, size * 3, size, finalArray2);

	writeIntegersInFile(finalArray2, size * 4, "Sorted.txt");

	delete[]list1;
	delete[]list2;
	delete[]list3;
	delete[]list4;
	delete[]finalArray;
	delete[]finalArray1;
	delete[]finalArray2;

	system("pause");
}