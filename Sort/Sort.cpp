#include "Sort.h"
void Sort::BubbleSort(int* arr, int len)
{
    if (arr == nullptr || len == 0) {
        return;
    }

    for (auto i = 0; i < len; ++i) {
        for (auto j = i + 1; j < len; ++j) {
            if (arr[i] < arr[j]) {
                Swap(arr[i], arr[j]);
            }
        }
    }
}

void Sort::SelectionSort(int* arr, int len)
{
    if (arr == nullptr || len == 0) {
        return;
    }

 
    for (auto i = 0; i < len; ++i) {
        int minValIndex = i;
        for (auto j = i + 1; j < len; ++j) {
            if (arr[j] < arr[minValIndex]) {
                minValIndex = j;
            }
        }

        if (minValIndex != i) {
            Swap(arr[i], arr[minValIndex]);
        }
    }
}

void Sort::InsertionSort(int* arr, int len)
{
    if (arr == nullptr || len == 0)
    {
        return;
    }

    for (auto i = 1; i < len; ++i)
    {
        int tmp = arr[i];
        int j = i - 1;
        while (j >= 0 && tmp < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = tmp;
    }
}

void Sort::QuickSort(int* arr, int left, int right)
{
    if (arr == nullptr || left + 1 >=  right) {
        return;
    }

    int first = left;
    int last = right - 1;
    int base = arr[first];
    while (first < last)
    {
        while (first < last && arr[last] > base)
        {
            last--;
        }

        arr[first] = arr[last];

        while (first < last && arr[first] < base)
        {
            first++;
        }

        arr[last] = arr[first];        
    }

    arr[first] = base;
    QuickSort(arr, left, first);
    QuickSort(arr, first + 1, right);
}