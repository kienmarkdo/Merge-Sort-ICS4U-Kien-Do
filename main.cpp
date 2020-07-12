/*
Name: Kien Do
ICS4U - Mr. Maloley
Last Edit: November 14, 2019
Purpose: Create a merge sort algorithm
*/

#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

void displayArray(int[], int);
void generateRandomArray(int[], int);

void mergeSort(int arr[], int leftIndex, int rightIndex);
void mergeBothSides(int arr[], int leftIndex, int middleIndex, int rightIndex);

void displayArray(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl << endl;
    return;
}

void generateRandomArray(int arr[], int arrSize) // arrays are sent as pointers therefore I can use void instead of int*
{
    srand(time(nullptr));
    for (int i = 0; i < arrSize; i++)
    {
        arr[i] = rand() % 1000 + 1;
    }
    return;
}

void mergeSort(int arr[], int leftIndex, int rightIndex)
{
    /** if leftIndex == rightIndex, that means the left most number and right most number
                        in the array is the same. Therefore, the array now contains only 1 number.
                        So the left and right indexes could be (0, 0), (1, 1), etc. This will result in a return;
    **/
    if (leftIndex == rightIndex)
    {
        return;
    }
    int middleIndex = (leftIndex + rightIndex) / 2;
    mergeSort(arr, leftIndex, middleIndex); // sorts only the LEFT half
    mergeSort(arr, middleIndex + 1, rightIndex); // sorts only the RIGHT half
    mergeBothSides(arr, leftIndex, middleIndex, rightIndex); // merge both sides together
    return;
}

void mergeBothSides(int arr[], int leftIndex, int middleIndex, int rightIndex)
{
    int sizeLeftArr = middleIndex - leftIndex + 1;
    int sizeRightArr = rightIndex - middleIndex;

    int leftArr[sizeLeftArr] = {};
    int rightArr[sizeRightArr] = {};

    int counterLeftArr = 0;
    int counterRightArr = 0;
    int counterTemp = leftIndex;

    for (int i = 0; i < sizeLeftArr; i++) // copy values of the OG array (from position 0 to the middle) to leftArr
    {
        leftArr[i] = arr[leftIndex + i];
    }
    for (int i = 0; i < sizeRightArr; i++) // copy the remaining values of from the OG array to rightArr
    {
        rightArr[i] = arr[middleIndex + 1 + i];
    }

    // which ever value is lower (either in the left or right array), copy that value to the original array
    // then increment BOTH the counter of the array of which the value was just transferred AND the counterTemp
    // this is because we want to compare the value that comes after the value that was just transferred to the OG array
    // as well as move the next number into the next position of the OG array
    while (counterLeftArr < sizeLeftArr && counterRightArr < sizeRightArr)
    {
        if (leftArr[counterLeftArr] <= rightArr[counterRightArr])
        {
            arr[counterTemp] = leftArr[counterLeftArr];
            counterLeftArr++;
        }
        else
        {
            arr[counterTemp] = rightArr[counterRightArr];
            counterRightArr++;
        }
        counterTemp++;
    }

    // there will be remaining values in either leftArr or rightArr. Copy them all into the merged array.
    while(counterLeftArr < sizeLeftArr)         //extra element(s) in left array
    {
        arr[counterTemp] = leftArr[counterLeftArr];
        counterLeftArr++;
        counterTemp++;
    }
    while(counterRightArr < sizeRightArr)       //extra element(s) in right array
    {
        arr[counterTemp] = rightArr[counterRightArr];
        counterRightArr++;
        counterTemp++;
    }
    return;
}

int main()
{
    int arrSize = 0;
    string repeat = "1";
    do
    {
        cout << "Enter array size    : ";
        cin >> arrSize;
        while (arrSize < 0 || arrSize > 1000000) // error trap
        {
            cout << "ERROR: Please enter a positive integer from 1 to 1000 inclusive." << endl;
            cout << "Enter array size    : ";
            cin >> arrSize;
        }
        int arr[arrSize] = {}; // create array after size is determined
        generateRandomArray(arr, arrSize);
        cout << "Random array values : ";
        displayArray(arr, arrSize);
        cout << endl;

// mergeSort works with indexes instead of size. Therefore arrSize-1 is the index of the last value in the array.
        mergeSort(arr, 0, arrSize-1);
        cout << "Sorted Array        : ";
        displayArray(arr, arrSize);

        cout << "Would you like to repeat?      1. Yes     2. No" << endl;
        cin >> repeat;
        while (repeat != "1" && repeat != "2")
        {
            cout << "ERROR: Enter 1 for yes, 2 for no." << endl;
            cin.ignore();
            getline(cin, repeat);
        }
        system("CLS");
    } while (repeat == "1");

    return 0;
}
