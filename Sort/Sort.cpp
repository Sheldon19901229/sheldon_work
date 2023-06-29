#include "Sort.h"
// 冒泡:时间:O(n^2),空间:O(1)
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

// 选择排序:时间:O(n^2),空间:O(1),选取未排序排队中最值放在已排序队列中
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

// 插入排序:时间:O(n^2),空间:O(1),在已排序队列中查找合适为位置并插入当前值
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

// 快速排序:时间:O(nlogn),空间:O(logn),递归思想
void Sort::QuickSort(int* arr, int left, int right)
{
    if (arr == nullptr) {
        return;
    }

    int rtemp = right;
    int ltemp = left;
    int base = arr[(right + left) / 2];
    while (ltemp < rtemp)
    {
        while (arr[ltemp] < base)
        {
            ltemp++;
        }

        while (arr[rtemp] > base)
        {
            rtemp--;
        }
        
        if (ltemp <= rtemp) {
            Swap(arr[rtemp], arr[ltemp]);
            --rtemp;
            ++ltemp;
        }
    }

    if (rtemp == ltemp) {
        ltemp++;
    }

    if (left < rtemp) {
        QuickSort(arr,left, ltemp - 1);
    }

    if (ltemp < right) {
        QuickSort(arr, rtemp + 1, right);
    }
}