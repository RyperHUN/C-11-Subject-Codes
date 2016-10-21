// 5_MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

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

// Begin = 0. elem;
// End   = Last elem + 1;
void merge_sort(int *tomb, int begin, int end, int *temp) {
	if (end - begin < 2)
		return;
	int mid = (begin + end) / 2;
	merge_sort(tomb, begin, mid, temp);
	merge_sort(tomb, mid, end, temp);
	merge(tomb, begin, mid, end, temp);
	copy(temp, begin, end, tomb);
}

int main()
{
	const int size = 7;
	int nums[size] = { 5, 2 , 3, 4, 6, 1, 0};
	int out [size];

	merge_sort (nums, 0, 7, out);

	for (auto num : nums)
		std::cout << num << " ";
	std::cout << std::endl;

	for (auto num : out)
		std::cout << num << " ";
	std::cout << std::endl;


    return 0;
}

