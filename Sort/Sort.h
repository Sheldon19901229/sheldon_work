#ifndef SORT_H
#define SORT_H
class Sort {
public:
	Sort() = default;
	~Sort() = default;
	// √∞≈›≈≈–Ú
	void BubbleSort(int* arr, int len); 
	// —°‘Ò≈≈–Ú
	void SelectionSort(int* arr, int len);
	// ≤Â»Î≈≈–Ú
	void InsertionSort(int* arr, int len);
	// øÏÀŸ≈≈–Ú
	void QuickSort(int* arr, int left, int right);
private:
    void Swap(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
};

#endif