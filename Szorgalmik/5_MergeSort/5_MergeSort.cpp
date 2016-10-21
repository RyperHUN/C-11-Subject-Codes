// 5_MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>


class MergeSorter
{
private:
	void merge(int* in, int begin, int mid, int end, int* out) {
		int i = begin, j = mid;
		for (int c = begin; c < end; ++c) {
			if (i < mid && (j >= end || in[i] <= in[j])) {
				out[c] = in[i];
				i++;
			}
			else {
				out[c] = in[j];
				j++;
			}
		}
	}

	void copy(int* in, int begin, int end, int* out) {
		for (int c = begin; c < end; ++c) {
			out[c] = in[c];
		}
	}

	void merge_sort(int *tomb, int begin, int end, int *temp) {
		if (end - begin < 2)
			return;
		int mid = (begin + end) / 2;
		merge_sort(tomb, begin, mid, temp);
		merge_sort(tomb, mid, end, temp);
		merge(tomb, begin, mid, end, temp);
		copy(temp, begin, end, tomb);
	}

	int *temp;
public:

	
	void sort(int* tomb, int begin, int end)
	{
		const size_t size = end - begin;
		temp = (int*)malloc(sizeof(int) * size);

		merge_sort (tomb, begin, end, temp);

		free (temp);
	}
};


int main()
{
	const int size = 7;
	int nums[size] = { 5, 2 , 3, 4, 6, 1, 0};

	for (auto num : nums)
		std::cout << num << " ";
	std::cout << std::endl;

	MergeSorter sorter;
	sorter.sort(nums, 0, 7);

	for (auto num : nums)
		std::cout << num << " ";
	std::cout << std::endl;


    return 0;
}

