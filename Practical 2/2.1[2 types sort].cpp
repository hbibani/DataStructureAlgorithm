#include <iostream>

using namespace std;

void sortReverse(int sort[21], int size)
{
	int temp;
	int test = 0;
	do {
			 test = 0;
					
			for( int i =0; i < size; i++)
			{
				if(sort[i] > sort[i+1] && (i+1) != 21)
						{
							temp = sort[i+1];
							sort[i+1] = sort[i];
							sort[i] = temp;
							test++;
						}
			}
		} while (test > 0);
	
}


int partition(int arr[], int low, int high)
{
		int pivot = arr[high];    // pivot
		int i = (low - 1);

		for (int j = low; j <= high - 1; j++)
		{
				//if current element is greater than pivot, increment the low element
				//swap elements at i and j
				if (arr[j] >= pivot)
				{
						i++;    // increment index of smaller element
						int temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
				}
		}

		{
			int temp = arr[i+1];
			arr[i+1] = arr[high];
			arr[high] = temp;
		}
	
		//swap(&arr[i + 1], &arr[high]);

//		for (int k = 0; k <= i; k++)
//		{
//			cout << arr[k] << "\t";
//		}
//		cout << endl;
		return (i + 1);

		
}

//quicksort algorithm

void quickSort(int (&arr)[21], int low, int high)
{
		if (low < high)
		{
				//partition the array
				int pivot = partition(arr, low, high);

				//sort the sub arrays independently
				quickSort(arr, low, pivot - 1);
				quickSort(arr, pivot + 1, high);
		}
		
		
}

int main()
{
	int array[21] = {1,3,8,9,12,14,22,25,33,34,38,59,61,66,68,73,75,99,101,203,454};
	
		
	quickSort(array,0,21);
	
	for (int i = 0 ; i < 21; i++)
	{
		cout << array[i] << " ";
	}
	
	cout << endl << endl;
	
	sortReverse(array, 21); // note that works both ways [if you turn off either one, it will reverse it
	
    cout << endl << endl;
    
    	for (int i = 0 ; i < 21; i++)
	{
		cout << array[i] << " ";
	}
	

}
