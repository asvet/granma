// binary_shift_insertion_sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
/*
* def binary_search_insertion_sort(x):
    l = x.copy()
    for i in range(1, len(l)-1):
        key = l[i]
        if key < l[0]:
            for j in range(i, 0):
                l[j]=l[j-1]
            l[0]=key
        #pos = binary_search_insert_pos(l,key)
        left = 0
        right = len(l)-1
        while left!= right:
            mid = (left+right)//2
            if key >= l[mid+1]:
                left = mid+1
            else:
                #---binary shift:---#
                for k in range(right+1, mid):
                    l[k]=l[k-1]
                right = mid
        l[right+1]=key
    return l
*/

void binary_shift_sort(vector<int>& list)
{
    for (size_t i = 1; i < list.size(); i++)
    {
        int key = list[i];  //if key is THE smallest compare at the end -> the shift is still done
        int left = 0;
        int right = i - 1;
        while (left != right)
        {
            int mid = (left + right) / 2;
            if (key >= list[mid + 1]) left = mid + 1;
            else
            {

                for (size_t j = right + 1; j > mid; j--)
                {
                    list[j] = list[j - 1];
                }

                right = mid;
            }
        }
        //list[right] = key;
        //if we shift all elements exept the 1st
        if (right == 0)
        {
            if (list[right] > key)
            {
                list[right + 1] = list[right];
                list[right] = key;
            }
            else list[right + 1] = key;
        }
        else list[right + 1] = key;


    }
}
int main()
{
    vector<int> list = { 6,3,7,9,3};
    for (size_t i = 0; i < list.size(); i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    binary_shift_sort(list);
    for (size_t i = 0; i < list.size(); i++)
    {
        cout << list[i] << " ";
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
