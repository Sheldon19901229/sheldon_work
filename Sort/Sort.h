#ifndef SORT_H
#define SORT_H
class Sort {
public:
	// 冒泡排序
	void BubbleSort(int* arr, int len); 
	// 选择排序
	void SelectionSort(int* arr, int len);
	// 插入排序
	void InsertionSort(int* arr, int len);
    // 快速排序
    void QuickSort(int* arr, int left, int right); // right 指数组的有边界+1
private:
    void Swap(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
};

#endif 